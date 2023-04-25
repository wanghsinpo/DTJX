# $Header: /usr/cvsroot/tcllib84/dp.tcl,v 1.2 2002/10/28 22:41:33 hume Exp $
#
# Tcl-dp emulation
#
# $Log: dp.tcl,v $
# Revision 1.2  2002/10/28 22:41:33  hume
# Tweaks for the namespace change.
#
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.1.1.1  2000/03/01 21:20:55  hume
# pkgindex only change.
#
# Revision 1.1.1.1  1999/10/05 00:58:06  hume
# Initial Tcl eight.two version.
#
# Revision 1.2  1999/07/08 13:14:53  hume
# Server side DMH can specify which network interface.
#
# Revision 1.1.1.1  1999/07/02 18:48:37  hume
# Starting point for Tcl 8.1.
#
# Revision 1.1.1.1  1997/10/03 02:31:41  hume
# From tcllib42 with edits.
#
# Revision 1.2  1997/04/17 00:28:17  hume
# Experimenting with connection configuration.
#
# Revision 1.1.1.1  1997/02/11 14:26:54  hume
# For Tk 4.2
#
#
namespace eval ::dmh {

proc dp_MakeRPCClient {host port} {
    set conn [socket $host $port]
    set return [gets $conn]
    fconfigure $conn -buffersize 32000 -translation "binary binary"
    if {[lindex $return 1] == "refused:"} {
        close $conn
        error $return;
    }
    if {$return == "Server not responding"} {
        close $conn
        error $return;
    }
    fileevent $conn readable [list ::dmh::dp_ProcessRPCCommand $conn]
    dp_CleanupRPC $conn
    dp_atclose $conn appendUnique [list dp_ShutdownRPC $conn]
    dp_atclose $conn appendUnique [list mh_lostserver $conn]
    return $conn
    }

# server
proc dp_MakeRPCServer {port {hostname_or_ip ""}} {
   if { [string compare $hostname_or_ip ""] } {
       set server [socket -server ::dmh::dp_AcceptedClient -myaddr $hostname_or_ip $port]
       }\
   else {
       set server [socket -server ::dmh::dp_AcceptedClient $port]
       }
   return $server
   }


# executes in the server
proc dp_AcceptedClient {conn hostaddr port} {
    # could check if hostaddr approved, 
    # if not approved
    #    puts $conn "Connection refused: $msg"
    #    close $conn
    fconfigure $conn -buffersize 32000 -translation {binary binary}
    if { [catch {puts $conn "Connection accepted";flush $conn}] } return
    dp_CleanupRPC $conn
    fileevent $conn readable [list ::dmh::dp_ProcessRPCCommand $conn]
    dp_atclose $conn appendUnique [list dp_ShutdownRPC $conn]
    dp_atclose $conn appendUnique [list mh_lostclient $conn]
    }

# for new connections
#   reset any incomplete RDO/RPC transactions from prior use of $conn
#   insure that close action exists
#
# also called on error/close of existing connections
# 
proc dp_CleanupRPC conn {
    foreach v {dp_rpc dp_rpc_tid dp_rpc_inc dp_rpc_buff} { variable $v }
    # a variable for RPC transactions
    # "PENDING" "TIMEOUT" "[list $rc $result]"
    if { [info exists dp_rpc_tid($conn)] } {
        after cancel $dp_rpc_tid($conn)
        unset dp_rpc_tid($conn)
        # timer was going
        if { [info exists dp_rpc($conn)] && $dp_rpc($conn) == "PENDING" } {
            # client is waiting for reply - he sees error
            set dp_rpc($conn) [list 1 "RPC Cancelled on $conn"]
            # dispatch events so he sees it
            after 2000 [list set ::dmh::dp_rpc($conn) TIMEOUT]
            vwait ::dmh::dp_rpc($conn)
            }
        }
    catch { unset dp_rpc($conn) }
    catch { unset dp_rpc_inc($conn) }
    catch { unset dp_rpc_buff($conn) }
    }

# initiated locally during close, tell the other side
proc dp_ShutdownRPC conn {
    fileevent $conn readable ""
    dp_RDO $conn dp_CloseRPCFile
    dp_CleanupRPC $conn
    }

# initiated remotely, the connection is closing
proc dp_CloseRPCFile {} {
    variable dp_rpcFile
    set conn $dp_rpcFile
    dp_atclose $conn delete [list dp_ShutdownRPC $dp_rpcFile]
    fileevent $conn readable ""
    dp_CleanupRPC $conn
    dp_close $conn
    }


proc dp_atclose {fileId {option list} args} {
  # The option may be appendUnique, append, prepend, insert, delete,
  # clear, set, or list.
  # The args depends on the option specified.
  #
  # The dp_atclose_callbacks array holds the installed dp_atclose callbacks,
  # indexed by fileId.
  #
  variable dp_atclose_callbacks
  if {[catch {set dp_atclose_callbacks($fileId)}]} {
    set dp_atclose_callbacks($fileId) {}
  }

  case $option in {
    set {
      #
      # set callbacks list.
      #
      set dp_atclose_callbacks($fileId) $args
    }
    appendUnique {
      #
      # append callback to end of the callbacks list.
      #
      if {[llength $args] != 1} {
	error {wrong # args: try "dp_atclose fileId appendUnique callback"}
      }
      set callback [lindex $args 0]
      if {[lsearch $dp_atclose_callbacks($fileId) $callback] == -1} {
	  lappend dp_atclose_callbacks($fileId) $callback
      }
    }
    append {
      #
      # append callback to end of the callbacks list.
      #
      if {[llength $args] != 1} {
	error {wrong # args: try "dp_atclose fileId append callback"}
      }
      set callback [lindex $args 0]
      lappend dp_atclose_callbacks($fileId) $callback
    }
    prepend {
      #
      # prepend callback to front of the callbacks list.
      #
      if {[llength $args] != 1} {
	error {wrong # args: try "dp_atclose fileId prepend callback"}
      }
      set callback [lindex $args 0]
      set dp_atclose_callbacks($fileId)  "\{$callback\} $dp_atclose_callbacks($fileId)"
    }
    insert {
      #
      # insert callback before the "before" callback in the callbacks list.
      #
      if {[llength $args] != 2} {
	error {wrong # args: try "dp_atclose fileId insert before callback"}
      }
      set before   [lindex $args 0]
      set callback [lindex $args 1]
      set l {}
      foreach c $dp_atclose_callbacks($fileId) {
	if {[string compare $before $c] == 0} {
	  lappend l $callback
	}
	lappend l $c
      }
      set dp_atclose_callbacks($fileId) $l
    }
    delete {
      #
      # delete callback from the callbacks list.
      #
      if {[llength $args] != 1} {
	error {wrong # args : should be "dp_atclose fileId delete callback"}
      }
      set callback [lindex $args 0]
      set l {}
      foreach c $dp_atclose_callbacks($fileId) {
	if {[string compare $callback $c] != 0} {
	  lappend l $c
	}
      }
      set dp_atclose_callbacks($fileId) $l
    }
    clear {
      #
      # clear callbacks list.
      #
      if {[llength $args] != 0} {
	error {wrong # args : should be "dp_atclose fileId clear"}
      }
      set dp_atclose_callbacks($fileId) {}
    }
    list {
      #
      # list currently installed callbacks.
      #
    }
    default {
      error {options: appendUnique, append, prepend, insert, delete, clear, set, or list}
    }
  }
  return $dp_atclose_callbacks($fileId)
}


# augment Tcl close with atclose actions
proc dp_close fileId {
  variable dp_atclose_callbacks 
  while {1} {
    # Every iteration, we rescan dp_atclose_callbacks, in case
    # some callback modifies it.
    #
    if {[catch {set dp_atclose_callbacks($fileId)} callbacks]} break
    if {[llength $callbacks] <= 0} break
    set callback [lindex $callbacks 0]
    set dp_atclose_callbacks($fileId) [lrange $callbacks 1 end]
    catch {uplevel #0 [list namespace eval ::dmh $callback]}
    }
  catch {unset dp_atclose_callbacks($fileId)}
  return [close $fileId]
  }

    
proc dp_whenidle {args} {
    return [after idle [list namespace eval ::dmh $args]]
    }
} ;# namespace
