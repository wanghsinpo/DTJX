# $Header: /usr/cvsroot/tcllib84/client.tcl,v 1.4 2002/10/28 22:41:33 hume Exp $
# message hub client
#
# (C) Copyright Hume Integration Software 1994, 1995
# All Rights Reserved
# Licensed Materials - Property of Hume Integration Software
#
# $Log: client.tcl,v $
# Revision 1.4  2002/10/28 22:41:33  hume
# Tweaks for the namespace change.
#
# Revision 1.3  2002/10/28 17:22:05  hume
# Updated to ask for Tcl 8.4
#
# Revision 1.2  2002/10/28 16:12:57  hume
# Support ::dmh::lset for pre-84 DMH client/server interoperability.
#
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.3  2001/11/15 17:14:17  hume
# Updated company name.
#
# Revision 1.2  2000/03/17 19:38:15  hume
# Error returns of mhc_init needed to be single string.
#
# Revision 1.1.1.1  2000/03/01 21:20:55  hume
# pkgindex only change.
#
# Revision 1.3  1999/10/05 17:58:23  hume
# Retry count in mbx init.
#
# Revision 1.2  1999/10/05 17:49:44  hume
# Optional retry count to mbx init - used in EOF.
#
# Revision 1.1.1.1  1999/10/05 00:58:06  hume
# Initial Tcl eight.two version.
#
# Revision 1.2  1999/07/08 19:11:15  hume
# Changed error handling - mbx init returns error condition on failure.
#
# Revision 1.1.1.1  1999/07/02 18:48:36  hume
# Starting point for Tcl 8.1.
#
# Revision 1.5  1998/10/28 20:07:45  hume
# Fix for client-server synchronization bug.
#
# Revision 1.4  1998/08/11 13:02:37  hume
# Added fix for lostserver in situation of more than 1 server connection.
#
# Revision 1.3  1998/07/14 21:33:52  hume
# Fix for problems when client uses IP or alias instead of server hostname.
#
# Revision 1.2  1997/10/14 23:06:39  hume
# Updated error handling.  User is expected to install own bgerror or tkerror
# procedure.
#
# Revision 1.1.1.1  1997/10/03 02:31:41  hume
# From tcllib42 with edits.
#
# Revision 1.5  1997/03/11 18:48:37  hume
# Moved DMH client Tcl logic into C code.
#
# Revision 1.4  1997/03/05 14:58:59  hume
# Changed "mbx count" usage, mbx end for server.
#
# Revision 1.3  1997/03/04 22:01:06  hume
# Has changes for C code queues.
#
# Revision 1.2  1997/03/01 17:47:34  hume
# Fixed bug on cleanup of broken connection when you have multiple connections
# to the same server.  In some circumstances this would affect dmh_gateway.
#
# Revision 1.1.1.1  1997/02/11 14:26:54  hume
# For Tk 4.2
#
#
# Distributed Message Hub Client Logic 
#
package require Tcl 8.4
#
namespace eval ::dmh {

proc mhc_init {{igroup ""} args} {
    global errorInfo
    variable dp_port_debug
    variable mh_alias 
    variable mh_count 
    variable mh_group 
    variable mh_host 
    variable mh_server 
    variable mh_server_count 
    variable mhc_when_msg_again 

    if { $igroup == "" } { set igroup mbx }
    set group $igroup

    # see if the groupname is aliased
    if { [info exists mh_alias($group)] } {
        set group $mh_alias($group) }

    # check for optional host name
    if { [string first : $group] > 0 } {
       vset [split $group :] "host port"
       }\
    else {
       # no, assume this host
       set port $group
       set host [dp_hostname]
       }
    
    # if port is not a number, make it a number
    set portstring $port
    set fullmatch ""
    regexp \[0-9\]+ $port fullmatch
    if { $port == "" || $fullmatch != $port } { 
        set port [mh_name_to_socket $port]
        }

    # strip away optional domain from hostname
    set xmh_group [dp_hostname $host]:$port

    # optional retry count in $args
    if { $args == "" } { set tries 1 }\
    else { set tries [expr $args] }
    for { set i 1} {1} {incr i} {
        set rc [catch {set hserver [dp_MakeRPCClient $host $port]} dp_port_debug]
        lappend dp_port_debug $i
        if { $rc == 0 } break
        if { $i == $tries } break
        if { $i >= 2 } { wait 20000 }\
        else { wait 2000 }
        }
    if { $rc } { 
        # calling bgerror is not catchable - changed with 8.1
        #bgerror "Retried $i times - $errorInfo" 
        return -code error "Could not initialize client DMH connection to $host:$port\n$dp_port_debug"
        }
    # The client has to use the server's name for the group
    # because the client does not resolve IP or alias hostnames 
    # to the server's preferred name, and therefore he could not
    # match received messages against whenmsg codes.
    # This change after seeing problems with client using IP and server
    # using hostname.
    set rc [catch {dp_RPC $hserver set mh_group} svr_group]
    if { $rc == 0 } {
        set mh_server($svr_group) $hserver
        set mhc_when_msg_again($svr_group) 0
        }
    set emsg "Error during client/server setup"
    if { $rc } {
        set info $errorInfo
        catch { mbx end }
        return -code error "$emsg $info"
        }

    if { ![info exists mh_alias()] } {
        # for ambiguous destinations of a client with more than one server
        # the first successful connection is the default server
        set mh_alias() $svr_group
        }
    # The usual case is that aliases are resolved at the server.
    # Alias array is used in the client when you have multiple server connections.
    # Future versions may do more client side use of aliases.
    set anames ""
    set avals ""
    foreach alias [list $igroup $port $xmh_group $host:$portstring] {
        # map any existing user aliases to $svr_group
        # this maps the user's names to socket numbers
        foreach sub [array names mh_alias] {
            if { $sub == "" } continue
            if { $mh_alias($sub) == $alias } {
                set mh_alias($sub) $svr_group
                lappend anames mh_alias($sub)
                lappend avals  $svr_group
                }
            }
        # make sure this alias is installed
        set mh_alias($alias) $svr_group
        lappend anames mh_alias($alias)
        lappend avals  $svr_group
        }
    # The server has to recognize an IP or alias as the
    # server's own group if the client code uses it.  
    # next statement uses lset in 83 server, ::dmh::lset in 84 server
    set rc [catch {dp_RPC $hserver lset $avals $anames}]
    if { $rc } {
        set info $errorInfo
        catch { mbx end }
        return -code error "$emsg $info"
        }

    set mh_server_count [array size mh_server] 
    # new client with new server uses counter for synchronization
    # non-existence means be compatible with 1.0 server
    set rc [catch {dp_RPC $hserver set dmh_version} server_version]
    if {$rc} { set info $errorInfo; catch { mbx end }; return -code error "$emsg $info" }
    if { $server_version > 1.0 } { set mh_count($svr_group) 0 }\
    else { catch {unset mh_count($svr_group)}}
    return [set mh_group $svr_group]
    }

#
# we just lost our DMH server connection
#
proc mh_lostserver { connID } {
    # which hostname:groupname is this?
    foreach v {mh_server_count mh_server mh_alias mh_group mhc_when_msg_again mhc_whenmsg mh_count} {
        variable $v
        }
    if { ![info exists mh_server] } return
    foreach xmh_group [array names mh_server] {
        if { $mh_server($xmh_group) == $connID } break
        }
    if { $mh_server($xmh_group) != $connID } return
    if { [info commands mh_app_lostserver] == "mh_app_lostserver" } {
        # the end user can install logic to inform the user,
        # try to reconnect at timed intervals, exit gracefully, ....
        # Use mbx init to reconnect just like the first time.
        # Do your reconnection in an after command, and subsequently
        # re-establish your whenmsg handlers.
        #
        # When mh_app_lostserver is called,  mh_server()
        # and mh_alias() are still defined and can be referenced
        # Your procedure is also called when you call mbx end.
        #
        # xmh_group is hostname:socket 
        catch { mh_app_lostserver $xmh_group $connID }
        }
    # now we clean up
    if { [info exists mh_server($xmh_group)] } {
        catch { unset mh_server($xmh_group) }
        catch { unset mhc_when_msg_again($xmh_group) }
        catch { unset mh_count($xmh_group)}
        incr mh_server_count -1 
        foreach f [array names mh_alias] {
            if { $mh_alias($f) == $xmh_group } { unset mh_alias($f) }
            }
        set mh_group ""
        }
    if { [info exists mhc_whenmsg] } {
        foreach s [array names mhc_whenmsg] {
            if { [string match *@$xmh_group $s] } {
                unset mhc_whenmsg($s)
                }
            }
        }
    # if we still have a server connection, fix-up global data items to
    # work with one of the remaining connections as the default
    if { $mh_server_count >= 1 } {
        set f [lindex [array names mh_alias] 0]
        set mh_group $mh_alias($f)
        if { ![info exists mh_alias()] } { set mh_alias() $mh_group }
        }
    }

} ;# namespace
