# $Header: /usr/cvsroot/tcllib84/hsms.tcl,v 1.16 2005/05/17 19:57:45 hume Exp $
#
# SECS-II over TCP/IP - HSMS "High Speed SECS Message Services"

# Licensed Material, Do not redistribute
# Copyright(C) 1995, 1996, 1997, 2002 Hume Integration Software

namespace eval ::dmh {
#
#  create a listening passive HSMS server
#  called by C code from the hsms command
#  the socket connection name, eg., file5 is returned
#  We keep the server socket listening for any client but we only accept
# the Select of one client.  When he goes away, we will accept another.
proc hsms_passive {sp} {
    global $sp
    set ${sp}(state) OFFLINE
    set _socket [set ${sp}(socket)]
    set _rc [catch {socket -server [list ::dmh::hsms_svr_accept $sp] $_socket} _server]
    if { $_rc } {
        # trace errors like socket already in use
        if { [expr [set ${sp}(TRACE)] & 0x0002] } {
            set ${sp}(trace) "[localtime 9] hsms online error: $_server"
            }
        return -code error -errorinfo $_server
        }
    set ${sp}(listener) $_server
    set ${sp}(filehandle) ""     ;# no selected client
    dp_atclose $_server append [list hsms_passive_atclose $sp $_server]
    return $_server
    }


# shutdown the listening server socket, usually called by atclose
# the filehandler is deleted
# If this gets executed, it is independent of any client 
# communication connection.  If the current
# client goes away, there is no ability for another one to connect.
proc hsms_passive_atclose {sp file} {
    global $sp
    if { [info exists ${sp}(state)] } {
        if { [set ${sp}(state)] == "LISTENING" } {
            set ${sp}(state) "OFFLINE"
            # the c code thinks we are still listening
            }
        }
    }

# a communication connection is being closed
# do related cleanup
# usually called by atclose after there has been a communication error
# or a Separate.req
# Also executed on destruction of hsms
proc hsms_atclose {sp file} {
    global $sp
    fileevent $file readable {}
    # cancel pending T7 timer - no need to close a closed connection
    if { [info exists ${sp}(h_t7)] } {
        set i 0
        foreach record [set ${sp}(h_t7)] {
            vset $record {_uid fid h_t7}
            if { $fid == $file } {
                after cancel $h_t7
                set ${sp}(h_t7) [lreplace [set ${sp}(h_t7)] $i $i]
                if { [info exists ${sp}(TRACE)] && [expr [set ${sp}(TRACE)] & 0x0002] } {
                    set ${sp}(trace) "[localtime 9] Cancelling T7 timer during early close"
                    }
                break
                }
            incr i
            }
        }
    
    if { [info exists ${sp}(TRACE)] && [expr [set ${sp}(TRACE)] & 0x0001] } {
        set ${sp}(trace) "[localtime 9] Communication connection was closed"
        }
    # if the primary HSMS-SS connection closes
    #    a server goes back to LISTENING
    #    a client reverts to OFFLINE
    if { [info exists ${sp}(state)] } { set oldstate [set ${sp}(state)] }\
    else { set oldstate "" }
    if { $oldstate == "ONLINE" } {
        # record the time the connection was lost
        set ${sp}(t_conn_lost) [localtime 2]
        }
    if { [info commands $sp] == $sp } { 
        $sp closed $file 

        # if we are an active client 
        #   if we have been configured to automatically reconnect, 
        #      if we had a connection
        #         schedule an attempt
        # this is the default behavior of an active client
        # prior to 5/10/02 we would not retry if state was NOT SELECTED.  But some
        # equipment will not grant the selection when they first go online.
        if { [set ${sp}(active)] && [info exists ${sp}(active_reconnect)] && \
 [set ${sp}(active_reconnect)] && ($oldstate == "ONLINE" || $oldstate == "NOT SELECTED") } {
             hsms_active_h_reconnect $sp
             }
         }
    }


# the server accepted a connection...
# and calls newclient for the first connection
proc hsms_svr_accept {sp newfile inetAddr port} {
    global $sp
    fconfigure $newfile -blocking 0 -buffersize 32000\
 -translation "binary binary" 
    if { [set ${sp}(state)] == "LISTENING" } {
        # work with the first client (private API)
        $sp newclient $newfile
        }\
    else {
        # with the older standard, the client does not do the Select.req
        # its the servers job to send ConnectionExhaust (stype 2)
        # and close
        if { [set ${sp}(PROTOCOL)] == 1993 } {
            hsms93_conn_rej $sp $newfile
            catch {close $newfile}
            return
            }
        # This could be a reconnection attempt where we do not realize the existing
        # connection is broken.  Using the connection speeds recognition of broken.
        if { [expr [set ${sp}(TRACE)] & 0x0002] } {
            set ${sp}(trace) "[localtime 9] performing linktest because of connection attempt"
            }
        catch {$sp put linktest ::dmh::hsms_linktest_cb}
        }
    # extra clients get the already active response
    # their filehandles are not registered above, and
    # they get closed after T7

    fileevent $newfile readable [list ::dmh::hsms_process_in $sp r $newfile]
    dp_atclose $newfile append [list hsms_atclose $sp $newfile]

    # after T7 we should be in the SELECTED state
    set _uid [localtime 2]
    lappend ${sp}(h_t7) [list $_uid $newfile [after [set ${sp}(T7)] [list ::dmh::hsms_check_selected $sp $newfile $_uid]]]
    }

# linktest callback
# if the connection link test is not working, close the connection
proc hsms_linktest_cb {sp sfr condition desc} {
    global $sp
    if { $condition == "send_failure" || $condition == "receive_failure" } {
        if { [expr [set ${sp}(TRACE)] & 0x0002] } {
            set ${sp}(trace) "[localtime 9] linktest failure, closing connection"
            }
        catch {dp_close [set ${sp}(filehandle)]}
        }
    }


# create a client of a passive server
#  called by C code from the hsms online command
# return the fileID
# updated 9/04 (1) add tracing of error conditions such as unknown host
#              (2) reduce unresponsive period during connection setup
# use unusual variable names in order to not conflict with $sp
proc hsms_active {sp} {
    global $sp tcl_platform
    set ${sp}(state) OFFLINE
    # bad hostname fails immediately
        if {$tcl_platform(os) == "HP-UX"} {
                # if host is not reachable, async results not useable
                # if reachable, see connect refusal quick
                # if not reachable, sync socket connect is 1.5 minutes dead time!
                # ping is 10 seconds of dead time which is lesser of two evils
                set _async 1
                set _bigT5 189876
                set _rc [catch {exec /etc/ping [set ${sp}(hostname)] 64 1} _etxt]
                if { [string first " 0% packet loss" $_etxt] < 0 } {
            if { [expr [set ${sp}(TRACE)] & 0x0002] } {
                set ${sp}(trace) "[localtime 9] hsms online error: host not pingable"
                }
            # these dead intervals play havoc on other connections and UI so change T5
                        # to be much larger - not doing this with other platforms because the 
                        # aync results are useable when the host is not reachable
                        if { [set ${sp}(T5)] < $_bigT5 } { 
                                set ${sp}(oldT5) [set ${sp}(T5)]
                                set ${sp}(T5) $_bigT5  
                if { [expr [set ${sp}(TRACE)] & 0x0002] } {
                    set ${sp}(trace) "[localtime 9] set larger T5 while host is not reachable"
                    }
                                }
                        return -code error -errorinfo "host not reachable"
                        }
        # ok its pingable, if we changed T5 while the host was down, change it back
                if { [set ${sp}(T5)] == $_bigT5 }  { 
                        if { [info exists ${sp}(oldT5)] } { set ${sp}(T5) [set ${sp}(oldT5)] }\
                        else { set ${sp}(T5) 20000 }
                        }
                }\
        elseif {$tcl_platform(os) == "AIX"} {
                set _async 0
                }\
    else {
            set _async 1
                }
    if { $_async } {
        set _rc [catch {socket -async [set ${sp}(hostname)] [set ${sp}(socket)]} _client]
            }\
        else {
            set _rc [catch {socket [set ${sp}(hostname)] [set ${sp}(socket)]} _client]
            }
    if { $_rc } {
        if { [expr [set ${sp}(TRACE)] & 0x0002] } {
            set ${sp}(trace) "[localtime 9] hsms online error: $_client"
            }
        return -code error -errorinfo $_client
        }
    fconfigure $_client -blocking 0 -buffersize 32000\
 -translation "binary binary" 

    set ${sp}(filehandle) $_client

    set _tcum 0
    set _twait 200
    wait 20   ;# success can come < 20 milliseconds, but failure takes a second or so
    set _addrlast {}
    while {$_async} {
        set _src [catch {fconfigure $_client -sockname} _etxt] 
        if { $_src } { set _addr "0.0.0.0" ; set _addrlast {} }\
        else { 
            vset $_etxt {_addr _host _port}
            # a transition from "0.0.0.0" means success irrespective of peername
            if {($_addrlast == "0.0.0.0") && ($_addr != "0.0.0.0")} {
                break
                }
            set _addrlast $_addr
                        if { $_addr != "0.0.0.0" } {
                    if {$tcl_platform(os) == "HP-UX"} break
                # look at peername only if sockname succeeded with a real value
                set _prc [catch {fconfigure $_client -peername} _etxt]
                if { !$_prc } { 
                    # if -peername does not error, thats a success
                    break
                    }
                }
            }
        #
        set _etxt [fconfigure $_client -error]   
        if { $_etxt == {}} {
            if { $_tcum > 3000 } {  ;# some platforms never show an error
                set _etxt "timeout waiting for connection status"
                }
            }
        if { $_etxt != {}} {
            if { [expr [set ${sp}(TRACE)] & 0x0002] } {
                set ${sp}(trace) "[localtime 9] hsms online error: $_etxt"
                }
            close $_client
            return -code error -errorinfo $_etxt
            }
        incr _tcum $_twait
        wait $_twait   ;# this is a responsive wait
        # we could have been deleted
        if { ![info exists ${sp}(state)] || ([info commands $sp] != $sp) } {
            return -code error -errorinfo "hsms instance was deleted"
            }
        if { [info exists ${sp}(comm_state)] && ([set ${sp}(comm_state)] == "DISABLED")} {
           return -code error -errorinfo "online attempt aborted by comm_disable"
           }
        }
    fileevent $_client readable [list ::dmh::hsms_process_in $sp r $_client]
    dp_atclose $_client append [list hsms_atclose $sp $_client]

    # per HSMS-SS, initiate the Select Procedure
    if { [set ${sp}(PROTOCOL)] > 1993 } {
        hsms_select_req $sp
        }

    # we should be in the selected state by T7
    set _uid [localtime 2]
    lappend ${sp}(h_t7) [list $_uid $_client [after [set ${sp}(T7)] [list ::dmh::hsms_check_selected $sp $_client $_uid]]]
    return $_client
    }

# called after T7 delay from connection open
# check that we are in the selected state for the
# indicated connection.  If not, close the connection
proc hsms_check_selected {sp file _uid} {
    global $sp
    # maybe we were deleted
    if { ![info exists ${sp}(state)] || ![info exists ${sp}(h_t7)] } return
    if { [info commands $sp] != $sp } return
    # remove our uid entry for this connection, the same $file can be reused
    set i 0
    set foundit 0
    foreach record [set ${sp}(h_t7)] {
        vset $record {id fid h_t7}
        if { $id == $_uid && $fid == $file} {
            set ${sp}(h_t7) [lreplace [set ${sp}(h_t7)] $i $i]
            set foundit 1
            break
            }
        incr i
        }
    # if we cannot find our uid entry, we must have been closed and re-opened
    # since this T7 timer started, so the earlier client is no longer connected
    if { !$foundit } return
    
    # maybe we were disabled
    if { [info exists ${sp}(comm_state)] && ([set ${sp}(comm_state)] == "DISABLED") } return
    if { [set ${sp}(state)] != "ONLINE" } {
        # suspect both ends are waiting for the Select.req
        # this message goes out and is seen if tracewin is up
        if { ([set ${sp}(active)] && [set ${sp}(PROTOCOL)] == "1993")\
 || (![set ${sp}(active)] && ([set ${sp}(PROTOCOL)] > "1993")) } {
            set ${sp}(trace) "SUSPECT PROTOCOL MISMATCH: (1993 active) <-> (1995 passive)"
            }
        }

    if { $file != [set ${sp}(filehandle)] } {
        # this may be an additional client of a passive server
        # or a protocol mismatch or some other failure
        if { [expr [set ${sp}(TRACE)] & 0x0002] } {
            set ${sp}(trace) "[localtime 9] T7 Timeout: ONLINE connection not found"
            }
        catch { dp_close $file }
        return
        }
    # $file refers to our HSMS-SS connection
    # online state means selected
    if { [set ${sp}(state)] != "ONLINE" } {
        if { [expr [set ${sp}(TRACE)] & 0x0002] } {
            set ${sp}(trace) "[localtime 9] T7 Timeout: Closing Not Selected connection"
            }
        catch { dp_close $file }
        # server now welcomes a new client (LISTENING)
        # client reverts to OFFLINE
        if { [expr [set ${sp}(TRACE)] & 0x0002] } {
            set ${sp}(trace) "[localtime 9] Connection state=[set ${sp}(state)]"
            }
        # 
        return
        }
    # otherwise looks good
    if { [expr [set ${sp}(TRACE)] & 0x0002] } {
        set ${sp}(trace) "[localtime 9] Selected ONLINE state confirmed after T7"
        }
    }
    
#
# initiate a Select.req
# Executed by an active client to setup a SECS HSMS connection
#
# {4 byte len, MSB...LSB} 10 == len header + len data
# {10 byte header }
#
# {header
#    0-1 session ID  0xffff for HSMS-SS
#    4 PType  (0 for SECS-II)
#    5 SType  (see 8.1.4.5) p182 E37-95 1 for Select.req
#    6-9 System
# }
proc hsms_select_req {sp} {
    global $sp
    incr ${sp}(SYSTEM)
    set _s [set ${sp}(SYSTEM)]
    set _msg [concat [list 0 0 0 10 0xff 0xff 0 0 0 1] [hsms_i4list $_s]]
    if { [catch {dp_binsend [set ${sp}(filehandle)] $_msg}] } {
        # the T7 check will close this lost connection
        if { [expr [set ${sp}(TRACE)] & 0x01 ] } {
            set ${sp}(trace) "[localtime 9] Active client cannot send Select.req"
            }
        return
        }
    if { [expr [set ${sp}(TRACE)] & 0x01 ] } {
        set ${sp}(trace) "[localtime 9] Active client sent Select.req"
        }
    # this is a control transaction, T6
    set _h [after [set ${sp}(T6)] [list ::dmh::hsms_select_retry $sp EX_$_s]]
    # expect a reply (handled in C code)
    set ${sp}(EX_$_s) $_h
    }

#
# per 1993 server rejects an additional client 
# with a ConnectionExhaust stype==2
#
proc hsms93_conn_rej {sp newfile} {
    global $sp
    incr ${sp}(SYSTEM)
    set _rbit 0
    if { [set ${sp}(EQUIP)] } { set _rbit 0x80 }
    set _msg [concat [list 0 0 0 10 $_rbit 0 0 0 0 2] [hsms_i4list [set ${sp}(SYSTEM)]]]
    dp_binsend $newfile $_msg
    if { [expr [set ${sp}(TRACE)] & 0x01 ] } {
        set ${sp}(trace) "[localtime 9] Additional client rejected with ConnectionExhaust"
        }
    }

# if we succeeded on the Select.req do nothing
# else try again
proc hsms_select_retry {sp EX} {
    global $sp
    if { ![info exists $sp] } return
    if { [set ${sp}(state)] == "ONLINE" } {
        catch { unset ${sp}($EX) }
        return
        }
    # you may have disabled communication
    if { [info exists ${sp}(comm_state)] && ([set ${sp}(comm_state)] == "DISABLED") } return
    # if we are looping in the active reconnect logic, we do not need to
    # initiate another Select.req - that will happen from the T7 close/ go online again looping
    if { [info exists ${sp}(h_reconnect)] && ([set ${sp}(h_reconnect)] != {}) } { return }
    # if we got a bad reply to our first attempt
    # state goes to OFFLINE and we do not try again
    if { [set ${sp}(state)] == "NOT SELECTED" } {
        hsms_select_req $sp
        }
    }

#
# convert a 4 byte integer to a list of bytes
# MSB..LSB
proc hsms_i4list {i} {
    return [list [expr {($i>>24) & 0xff}] [expr {($i>>16) & 0xff}] [expr {($i>>8) & 0xff}] [expr {$i & 0xff}]]
    }


#
# T6 timeout - a linktest reply did not show up
# exname is like EX_$system
#
proc hsms_T6_timeout {sp exname} {
    global $sp
    set _fullname ${sp}($exname)
    if { ![info exists $_fullname] } {
        # transaction record is gone - can happen on close
        return
        }
    vset [set $_fullname] {_Tid _callback _stype}
    if { $_stype == "5" } { set _desc linktest } else { set _desc S$stype }
    
    if { [expr [set ${sp}(TRACE)] & 0x0001] } {
        set ${sp}(trace) "T6 timeout: Reply to $_desc not received"
        }
    if { $_callback != "" } {
        set _rc [catch {\
   uplevel #0 [concat $_callback $sp $_desc \
   receive_failure {{T6 timeout, no reply}}] } _result]
        if { $_rc != 0 } { bgerror $_result }
        }
    unset $_fullname
    }

#
# dispatch events but
# do not return until a valid selected connection exists
# retry periodically 
# available to be called by user
#
proc hsms_wait_online {sp} {
    global $sp
    while 1 {
        if { ![info exists ${sp}(state)] } {
            error "hsms object $sp no longer exists"
            }
        set _s [set ${sp}(state)]
        if { $_s == "ONLINE" } return
        if { $_s == "OFFLINE" } {
            catch { $sp online }
            set _s [set ${sp}(state)]
            }
        if { $_s == "NOT SELECTED" || $_s == "LISTENING" } {
            vwait ${sp}(state)
            }
        if { $_s == "OFFLINE" } {
            wait [set ${sp}(T5)]
            }
        }
    }

#
# similar to the above, but retries to reconnect are made
# in background - there is no modality,
#
# called in a timed loop when an active client connection is lost
#
proc hsms_active_reconnect {sp} {
    global $sp
    # make sure there is only one reconnect timer loop active at a time
    if { [info exists ${sp}(h_reconnect)] && ([set ${sp}(h_reconnect)] != {})} {
        after cancel [set ${sp}(h_reconnect)]
        # leave the h_reconnect item present as an indicator the loop is active
        set cancelled 1
        }\
    else { set cancelled 0 }
    if { ![info exists ${sp}(state)] || ([info commands $sp] != $sp)}  {
        # the port object was deleted
        return 
        }
    if { ![info exists ${sp}(T5)] || ![info exists ${sp}(active)] || ![set ${sp}(active)]} {
        # you changed the connection type (and you could change it back)
        set ${sp}(h_reconnect) {} 
        return
        }
    if { ![info exists ${sp}(active_reconnect)] || ![set ${sp}(active_reconnect)] } {
        # you no longer want to retry connecting, but you may in the future
        if { $cancelled } { set ${sp}(h_reconnect) {} }
        return
        }
    # you may have disabled communication
    if { [info exists ${sp}(comm_state)] && ([set ${sp}(comm_state)] == "DISABLED") } {
        if { $cancelled } { set ${sp}(h_reconnect) {} }
        return
        }
    set _s [set ${sp}(state)]
    if { $_s == "ONLINE" } {
        set ${sp}(h_reconnect) {}
        return
        }
    if { $_s == "OFFLINE" } {
        catch { $sp online }
        # the world can change inside of online
        if { ![info exists ${sp}(state)] || ([info commands $sp] != $sp)} return
        if { [info exists ${sp}(comm_state)] && ([set ${sp}(comm_state)] == "DISABLED") } {
            if { $cancelled } { set ${sp}(h_reconnect) {} }
            return
            }
        set _s [set ${sp}(state)]
        }
    if { $_s == "NOT SELECTED" || $_s == "LISTENING" } {
        # we have a TCP/IP connection
        # we should transition to ONLINE or OFFLINE within T7
        }
    if { $cancelled } { set ${sp}(h_reconnect) {} }
    hsms_active_h_reconnect $sp
    }

# reschedule an active client reconnection attempt
# store the handle in case cancellation is desired
proc hsms_active_h_reconnect {sp} {
    global $sp
    # make sure there is only one retry timer loop active at a time
    if { [info exists ${sp}(h_reconnect)] && ([set ${sp}(h_reconnect)] != {})}  return 
    if { [expr [set ${sp}(TRACE)] & 0x0001] } {
        if { [set ${sp}(state)] == "OFFLINE" } {
            set ${sp}(trace) "Scheduling reconnect attempt in \
 [expr {[set ${sp}(T5)]/1000}] seconds (T5)"
            set _nowsecs [localtime 2]
            if { [info exists ${sp}(t_conn_lost)] } {
                set _diffsecs [expr {$_nowsecs - [set ${sp}(t_conn_lost)]}]
                set ${sp}(trace) "[localtime 9] Connection has been down\
 [interval_txt $_diffsecs]"
                }
            }
        # else we still check the connection but we do not provide a
        # message because it is confusing in the middle of the getting
        # connected/selected tracing
        }
    set ${sp}(h_reconnect) [after [set ${sp}(T5)] [list ::dmh::hsms_active_reconnect $sp]]
    }


# hsms_reset
# called out of C code when the hsms subcommand reset is issued
# does NOT attempt reconnection
# works with current ONLINE or OFFLINE state
#
#   cancels reconnection attempt timer - you may not want this
#
proc hsms_reset sp {
   global $sp
   # cancel reconnection timer:
   if { [info exist ${sp}(h_reconnect)] } {
       set _h [set ${sp}(h_reconnect)]
       if { [llength $_h] } {
           after cancel $_h
           set ${sp}(h_reconnect) ""
           }
       }
   }

} ;# namespace
