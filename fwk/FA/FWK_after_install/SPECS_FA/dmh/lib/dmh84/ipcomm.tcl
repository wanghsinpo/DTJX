# $Header: /usr/cvsroot/tcllib84/ipcomm.tcl,v 1.2 2004/09/22 12:29:23 hume Exp $
#
# Licensed and Supported Material
# (C)Copyright 1995, 1996 Hume Integration Software
# All Rights Reserved
#
# $Log: ipcomm.tcl,v $
# Revision 1.2  2004/09/22 12:29:23  hume
# Moved h_reconnect clear so non-blank value implies reconnect in progress.
#
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.3  2002/07/22 14:28:31  hume
# h_reconnect could have been set after the connection was deleted.
#
# Revision 1.2  2001/11/15 17:14:17  hume
# Updated company name.
#
# Revision 1.1.1.1  2000/03/01 21:20:55  hume
# pkgindex only change.
#
# Revision 1.1.1.1  1999/10/05 00:58:06  hume
# Initial Tcl eight.two version.
#
# Revision 1.1.1.1  1999/07/02 18:48:37  hume
# Starting point for Tcl 8.1.
#
# Revision 1.1.1.1  1997/10/03 02:31:41  hume
# From tcllib42 with edits.
#
# Revision 1.2  1997/05/29 13:13:53  hume
# Changed variable names to reduce name collisions with user secsport names.
#
# Revision 1.1.1.1  1997/02/11 14:26:54  hume
# For Tk 4.2
#
# Revision 1.1.1.1  1996/07/10 02:01:16  hume
# Reorganized and modified for Tk4.0 dp3.3.
#
# Revision 1.2  1996/01/11  14:07:55  hume
# Server socket does not need dp_shutdown call.
#
# Revision 1.1  1995/12/28  20:21:50  hume
# Changing and adding HIS content.
#
namespace eval ::dmh {
#
# called by C-code when you create an ipcomm
#
proc ipcomm_online cp {
    global $cp
    set _socket [set ${cp}(socket)]
    if { [set ${cp}(active)] } {
        set _host [set ${cp}(hostname)]
        set _client [socket $_host $_socket]
        fconfigure $_client -blocking 0 -buffering none -buffersize 16000\
 -translation "binary binary"
        fileevent $_client readable [list ::dmh::ipcomm_process_in $cp r $_client]
        dp_atclose $_client appendUnique [list ipcomm_atclose $cp $_client]
        set ${cp}(state) ONLINE
        return $_client
        }\
    else {
        set _server [socket -server [list ::dmh::ipcomm_svr_accept $cp] $_socket ]
        dp_atclose $_server append [list ipcomm_svr_atclose $cp $_server]
        set ${cp}(state) LISTENING
        return $_server
        }
    }


# a communication connection is being closed
# do related cleanup
# usually called by atclose after there has been a communication error
# Also executed on destruction of ipcomm
proc ipcomm_atclose {sp file} {
    global $sp
    fileevent $file readable {}
    if { [info exists ${sp}(TRACE)] && [expr [set ${sp}(TRACE)] & 0x0001] } {
        set ${sp}(trace) "[localtime 0] Communication connection was closed"
        }
    # if the primary connection closes
    #    a server goes back to LISTENING
    #    a client reverts to OFFLINE
    if { [info exists ${sp}(state)] } { 
        set oldstate [set ${sp}(state)] 
        if { [set ${sp}(active)] } {
            set ${sp}(state) OFFLINE
            }\
        else {
            set ${sp}(state) LISTENING
            }
        }\
    else { set oldstate "" }
    if { $oldstate == "ONLINE" } {
        # record the time the connection was lost
        set ${sp}(t_conn_lost) [localtime 2]
        }
    if { [info commands $sp] == $sp } {
        $sp closed $file

        # if we are an active client
        #   if we have been configured to automatically reconnect,
        #      if we had a valid connection
        #         schedule an attempt
        # this is the default behavior of an active client
        if { [info exists ${sp}(active_reconnect)] && \
 [set ${sp}(active_reconnect)] && $oldstate == "ONLINE" } {
             ipcomm_active_h_reconnect $sp
             }
         }
    }



# shutdown the listening server socket, usually called by atclose
# the filehandler is deleted
# If this gets executed, it is independent of any client
# communication connection.  If the current
# client goes away, there is no ability for another one to connect.
proc ipcomm_svr_atclose {sp file} {
    global $sp
    if { [info exists ${sp}(state)] } {
        if { [set ${sp}(state)] == "LISTENING" } {
            set ${sp}(state) "OFFLINE"
            }
        }
    }

# the server accepted a connection...
# and calls newclient for the first connection
proc ipcomm_svr_accept {sp newfile inetAddr _port} {
    global $sp
    if { [set ${sp}(state)] == "LISTENING" } {
        # work with only the first client (private API)
        $sp newclient $newfile
        set ${sp}(state) "ONLINE"
        }\
    else {
        # close extra clients
        catch {close $newfile}
        return
        }

    fconfigure $newfile -blocking 0 -buffering none -buffersize 16000\
 -translation "binary binary"
    fileevent $newfile readable [list ::dmh::ipcomm_process_in $sp r $newfile]
    dp_atclose $newfile append [list ipcomm_atclose $sp $newfile]
    }

#
# called when an active client connection is lost
#
proc ipcomm_active_reconnect {sp} {
    global $sp
    if { ![info exists ${sp}(state)] }  {
        # the port object was deleted
        return
        }
    set _s [set ${sp}(state)]
    if { $_s == "ONLINE" } {
        set ${sp}(h_reconnect) ""
        return
        }
    if { $_s == "OFFLINE" } {
        catch { $sp newclient [ipcomm_online $sp]  }
        }
    ipcomm_active_h_reconnect $sp
    }


# reschedule an active client reconnection attempt
# store the handle in case cancellation is desired
proc ipcomm_active_h_reconnect {sp} {
    global $sp
    if { [expr [set ${sp}(TRACE)] & 0x0001] } {
        if { [set ${sp}(state)] == "OFFLINE" } {
            set ${sp}(trace) "Scheduling reconnect attempt in \
 [expr {[set ${sp}(T5)]/1000}] seconds (T5)"
            set _nowsecs [localtime 2]
            if { [info exists ${sp}(t_conn_lost)] } {
                set _diffsecs [expr {$_nowsecs - [set ${sp}(t_conn_lost)]}]
                set ${sp}(trace) "[localtime 9]: Connection has been down\
 [interval_txt $_diffsecs]"
                }
            }
        # else we still check the connection but we do not provide a
        # message because it is confusing in the middle of the getting
        # connected/selected tracing
        }
    set ${sp}(h_reconnect) [after [set ${sp}(T5)] [list ::dmh::ipcomm_active_reconnect $sp]]
   }

} ;# namespace
