# $Header: /usr/cvsroot/gem/host/host.tcl,v 1.33 2005/06/09 21:49:56 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997, 2004 Hume Integration Software
# All Rights Reserved
#
# $Log: host.tcl,v $
# Revision 1.33  2005/06/09 21:49:56  hume
# Needed special logic in ei_comm_disabled for terminal server connections
# to be initialized with SECS communication disabled.
#
# Revision 1.32  2005/03/25 22:55:46  hume
# Added code for the host to respond to equipment initiated process program
# transfers.  Process program transfer actions create StateChange events when
# used with the .NET SecsHost or similar libraries.
#
# Revision 1.31  2004/10/14 20:11:58  hume
# Made comm_disabled, comm_enabled easier to use by taking care of comm_enable
# array element.
#
# Revision 1.30  2004/10/12 15:11:28  hume
# Updated ei_custom_comm feature to allow for interface specific custom
# procedures (ei_custom_comm_$spname).  (Used by .NET code)
#
# Revision 1.29  2004/09/27 19:22:45  hume
# Changed comm_enabled to call comm_attempt and got rid of redundant online
# call, added callout to ei_custom_comm, changed comm_disabled to be more like
# equipment version, reduced usage of quotes in favor or [list ].
#
# Revision 1.28  2004/09/21 15:45:22  hume
# Use T5 for communication attempt retry cycle, do not call online if HSMS
# reconnect logic is already calling it.
#
# Revision 1.27  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.26  2002/07/31 13:12:49  hume
# Changed initialization to have trace window earlier to see 1st messages.
# Proc ei_init has new optional argument, tracewin_TRACE.  Stopped reading
# from <MachineName> DMH mailbox for VFEI commands - only <MachineName>_VFEI.
#
# Revision 1.25  2002/07/30 15:20:40  hume
# Extended the Device ID fix/verify logic to include S1F13R reception.
#
# Revision 1.24  2002/07/30 14:35:51  hume
# Revised the auto Device ID updating logic for the case when the equipment
# does not send the correct value.
#
# Revision 1.23  2002/07/22 19:22:10  hume
# Added logic to automatically correct the Device ID when S1F13R is used to
# initiate communication.  Fallback use of S1F1 is not changed.
#
# Revision 1.22  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.21  2001/07/12 17:10:21  hume
# Fixed mispelling of terminal.
#
# Revision 1.20  2001/05/25 21:37:34  hume
# Backup restoration.
#
# Revision 1.21  2001/02/08 22:03:17  hume
# Revised comment that implied host side only played passive HSMS role.
#
# Revision 1.20  2001/02/02 19:46:49  hume
# Revised ei_comm_disabled logic based on equipment side improvements.
# This logic is not accessible by the Hume GUI, only by using custom code.
#
# Revision 1.19  2000/12/12 21:38:10  hume
# Changes to keep (control_state) in sync with the equipment. New
# CEID_OFFLINE variable is used to specify the control state offline event.
#
# Revision 1.18  2000/10/12 12:52:11  hume
# If you specify PORT as ":5555" the logic assumes "localhost" is intended.
#
# Revision 1.17  2000/10/10 21:00:09  hume
# Added PASSIVE HSMS option for supervisor and gemhost/supervisor command lines.
#
# Revision 1.16  2000/10/04 00:24:23  hume
# Moved global $spname in case ei_init was called for an existing connection.
#
# Revision 1.15  1999/05/27 18:24:35  hume
# Added braces to expressions per procheck.
#
# Revision 1.14  1999/05/06 19:55:03  hume
# Revised clock handling for possible A:16 format.
#
# Revision 1.13  1999/04/09 02:21:11  hume
# Added statements to guard against re-entering ei_online and secs_xact
# after seeing errors with SECS-I equipment that has long slow transactions.
#
# Also, cycling through the ei_online procedure may be a symptom that the
# equipment cannot handle multiple simultaneous transactions so that S1F1
# winds up timing out, and changes the control state from being online.
# The fix is to set MULT to 0 in the ei_startup record.
#
# Revision 1.12  1999/04/06 18:32:58  hume
# Added startup configuration to disable asking for variable and alarm data
# during initialization to address problem of too much data/too slow a link.
#
# Revision 1.11  1999/03/03 15:28:46  hume
# Fix for faster initialization when equipment does not support S1F13.
#
# Revision 1.10  1998/09/22 12:12:47  hume
# VFEI message system commands are processed using after so the whenmsg
# logic returns and receiving is resumed.
#
# Revision 1.9  1998/09/02 12:46:43  hume
# Correct S1F13 from host to send empty list message, not just header.
#
# Revision 1.8  1998/01/29 13:17:01  hume
# Added BAUD argument to ei_init - has default value for backward compat.
#
# Revision 1.7  1998/01/27 20:57:18  hume
# Broadened use of hsms argument in ei_init to cover 1993 vs 1995 protocols.
#
# Revision 1.6  1997/12/31 03:04:27  hume
# Fixed another place where secs_xact was entered during whenmsg callback.
#
# Revision 1.5  1997/10/24 02:32:31  hume
# Tweaked timing for smoother reconnection and re-initialization of equipment
# when it goes away and comes back.
#
# Revision 1.4  1997/10/23 23:37:58  hume
# Fixed for bug when initial send fails and nothing has been received.
#
# Revision 1.3  1997/09/30 12:58:42  hume
# Added logic to tolerate non-GEM equipment that does not support S1F13.
#
# Revision 1.2  1997/09/08 18:11:45  hume
# Fixed for rs232 by removing use of secs_xact in receive callbacks.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#


# initialize a host interface to a gem or nearly gem equipment
# ei_ == equipment interface
#
# example port arguments:
#     /dev/tty01        system RS-232 port
#     COM2              system RS-232 port
#     xyplex6:2200      SECS-I on TCP/IP terminal server connection
#     somehost:5551 hsms==1  hsms port
#
#  hsms  1 | 0 
#    
#  DEVID == SECS device ID expected by equipment
#
# you can overide default parameters before this procedure is called, eg.,
#  #set ${spname}(T3) 10000
proc ei_init {spname {port ""} {hsms 0} {DEVID 0} {BAUD 9600} {hsms_passive 0} {tracewin_TRACE 0}} {
    global $spname tk_library
    #
    # if we have not created an HSMS or secsport connection, do it now
    #
    if { [info commands $spname] != "$spname" } {
        if { $hsms != "0" } {
            if { [string first : $port] >= 0} { ;# [host:]port
                vset [split $port :] "host port"
                if { $host == "" } { set host localhost }
                }\
            else { set host localhost }
            if { $hsms_passive } {
                set reply [hsms $spname passive $port]
                }\
            else {
                set reply [hsms $spname active $port $host]
                }
            # default hsms PROTOCOL is SEMI standard 1995, you can override...
            if { [string first 93 $hsms] >= 0 } { set ${spname}(PROTOCOL) 1993 }
            set phrase "hsms port $port"
            if { $host != "localhost" && $host != [dp_hostname] } {
                append phrase " on host $host"
                }
            }\
        else {
            if { [llength $port] } {
                if { [string first : $port] >= 0 } {
                    set cmd [list secsport $spname $port]
                    set phrase "terminal server port $port"
                    }\
                else {
                    set cmd [list secsport $spname $port $BAUD]
                    set phrase "serial port $port"
                    }
                set reply [eval $cmd]
                } \
            else {
                set reply [secsport $spname]
                set phrase "default serial port"
                }
            }
        if { $reply != $spname } { error "could not connect to $phrase" }
        # save our invocation in case we go online and then need to
        # go offline - (have to destroy and recreate)
        set ${spname}(init_cmd) [list ei_init $spname $port $hsms $DEVID $BAUD $hsms_passive $tracewin_TRACE]
        # set up a trace on "state" to trap communication failure
        trace variable ${spname}(state) w ei_state_trace
        }

    # equipment expects to see its own device ID
    # we have recently added logic to fix incorrect values
    set ${spname}(DEVID) $DEVID

    # initialize data and variables for items not already set
    ei_defaults $spname

    # you cannot configure "COMMUNICATING"
    if { [set ${spname}(comm_state)] != "DISABLED" } {
        set ${spname}(comm_state) "ENABLED {NOT COMMUNICATING}"
        }

    # DMH message system integration
    # caller -  call "mbx init <groupname>" before this procedure
    set mh_group_var [dmh_var mh_group]
    if { [info exists $mh_group_var] && [llength [set $mh_group_var]] } {

        # If we are using the DMH message system,
        # listen to a mailbox for remote debugging
        mbx whenmsg ${spname}_RPC mbx_RPC

        # listen to a mailbox for VFEI commands, <MachineName>_VFEI
        # evaluate them and send back the VFEI reply
        foreach MB [list ${spname}_VFEI] {
            mbx whenmsg $MB "ei_vfei_msg $spname \$mbxmsg \$mbxreply \$mbxdest"
            }
        }

    # if a trace window is desired, create it now before communicating
    # but verify that window system use is possible and desired
    # (TRACE) should be left at 0 if no one is using the trace data
    if { ($tracewin_TRACE != 0)  && [info exists tk_library] } {
        set notk_var [dmh_var dmh notk]
        if { [info exists $notk_var] && [set $notk_var] } { }\
        else {
            set ${spname}(TRACE) $tracewin_TRACE
            $spname tracewin
            }
        }

    # possibly establish communications
    if { [set ${spname}(comm_state)] == "ENABLED {NOT COMMUNICATING}" } {
        ei_comm_enabled $spname ;# gem level
        }\
    else {
        # "DISABLED"
        ei_comm_disabled $spname ;# gem level
        }
    }

# We process VFEI commands from the background so the normal
# resumption of message receiving occurs at our return.
# We do not refresh receiving on this mailbox until this command is completed.
proc ei_vfei_msg {spname msg reply box} {
    set rearm_cmd "mbx whenmsg $box {ei_vfei_msg $spname \$mbxmsg \$mbxreply \$mbxdest}"
    after 0 "catch {mbx put $reply \[[list ei_vfei_cmd $spname $msg]\]} ; $rearm_cmd "
    }

# This procedure is called whenever  ${spname}(state) is updated
# We look for communication failure and then make sure our comm_state
# is consistent.
# This is better design than coding for every possible bad send or
# non-reply
#
proc ei_state_trace {spname sub op} {
    if { $op != "w" || $sub != "state" } return
    global $spname
    set newstate [set ${spname}(state)]
    if { $newstate != "OFFLINE" &&  $newstate != "LISTENING" } return
    # here on comm problem
    if { [set ${spname}(comm_state)] == "COMMUNICATING" } {
        if { [set ${spname}(comm_enable)] } {
            # looks like a detected problem and not our own disablement
            # we will transition to "ENABLED {NOT COMMUNICATING}"
            after 1 [list ei_comm_enabled $spname]
            # loss of communication is an event reported by the driver
            ei_driver_event $spname COM_DISABLE
            }
        }
    }

#
# disable communications
# It is an unusual to take the host interface offline - why not
# just end the program?
# This procedure shows you how to do it if you want to.
# call ei_comm_enabled to restore.
proc ei_comm_disabled spname {
    global $spname
    catch { unset ${spname}(comm_recovery) }

    # our intention is not to communicate  
    # the comm_enable item needs to be set to 1 by your
    # custom GUI or logic in order to restore communication
    set ${spname}(comm_state) DISABLED
    set ${spname}(comm_enable) 0

    # if not online, return
    if { [set ${spname}(state)] == "OFFLINE" } return
    # SECS-I on TCP/IP can be LISTENING when 1st initialized 
    # this is similar to the never online condition
    if { ![info exists ${spname}(PROTOCOL)] } {
        if { [set ${spname}(state)] == "LISTENING" } return
        # comm disable is imperfect with terminal servers - the usual close and
        # reopen will attempt a socket connection, and the state value will be
        # ONLINE.  The logic is trying to keep the socket connection established,
        # but with SECS communication disabled, we do not actually use it.
        # There can be an infinite loop of ei_init ei_comm_disabled that needs to be
        # broken.  The ONLINE state is not one of the SECS-I states.
        if { [set ${spname}(state)] == "ONLINE" } {
            if { [info level] >= 3 } {
                if { [string first "ei_comm_disabled" [info level -2]] >= 0 } return
                }
            }
        } 

    # abort any open transactions or queued sends
    $spname reset

    # we need to destroy the connection to guarantee there is
    # no SECS-II communication
    # this unsets the array so we need to save and restore the data items
    if { [info exists ${spname}(tracewin)] && [set ${spname}(tracewin)] != "" } {
        set tracewin 1
        catch { 
            set geometry [wm geometry [set ${spname}(tracewin)]] 
            set winstate [wm state [set ${spname}(tracewin)]]
            }
        # close the trace window now to close its variable traces
        catch { destroy [set ${spname}(tracewin)] }
        }\
    else { set tracewin 0 }

    set traces {}
    foreach sub [array names $spname] {
        set info [trace vinfo ${spname}($sub)]
        if { $info != "" } { lappend traces [list $sub $info] }
        } 

    set init_cmd [set ${spname}(init_cmd)]
    set statements [ei_gemdata $spname]
    # shutdown
    $spname close

    # make sure that we are consistent on the comm state
    set ${spname}(comm_state) "DISABLED"
    # re-create connection object without going online
    eval $init_cmd

    # restore data
    foreach statement $statements { eval $statement }

    # restore tracewin state - $init_cmd recreates it
    if { $tracewin && [info exists ${spname}(tracewin)] && [winfo exists [set ${spname}(tracewin)]]} { 
        catch { 
            wm geometry [set ${spname}(tracewin)] $geometry 
            update idletasks
            if { $winstate == "iconic" } { wm iconify [set ${spname}(tracewin)] }\
            elseif { $winstate == "withdrawn" } { wm withdraw [set ${spname}(tracewin)] }\
            else { lower [set ${spname}(tracewin)] }
            }
        }
    # restore traces
    foreach rec $traces {
        vset $rec {sub info}
        if { ![info exists ${spname}($sub)] } { set ${spname}($sub) {} }
        set curinfo [trace vinfo ${spname}($sub)]
        foreach pair $info {
            if { [lsearch -exact $curinfo $pair] >= 0} { continue }
            vset $pair {ops cmd}
            trace variable ${spname}($sub) $ops $cmd
            # do read/write for tracer to see
            # and remove any broken traces (none expected)
            if { [catch { set ${spname}($sub) [set ${spname}($sub)] }] } {
                trace vdelete $spname $ops $cmd
                }
            }
        }
    }


#
# communications are enabled but not established
# called at initialization, or on loss of connection
# This procedure initializes our handling of primaries.
proc ei_comm_enabled spname {
    global $spname errorInfo
    if { ![set ${spname}(comm_enable)] } { set ${spname}(comm_enable) 1 }

    # if we are already trying to establish comm, return
    if { [info exists ${spname}(comm_recovery)] } return
    set ${spname}(comm_recovery) 1

    set ${spname}(comm_state) "ENABLED {NOT COMMUNICATING}"
    # we need to record that the control_state is not ON-LINE
    # GEM equipment tries to pretend that ON-LINE is independent of
    # the communication state.  The host needs to see the change and
    # do (re-)initialization logic.
    set ${spname}(control_state) "OFF-LINE"

    # setup our handling of received messages from the eq
    $spname whenever S1F1  "ei_put_S1F2 $spname"  ;# eq online
    $spname whenever S1F13 "ei_put_S1F14 $spname" ;# lets communicate
    $spname whenever S1F16 "ei_offline_ack $spname"
    $spname whenever S1F18 "ei_online_ack $spname"

    $spname whenever S2F17 "ei_clock_reply $spname" 
    # binary echo
    $spname whenever S2F25 "$spname put S2F26 \$${spname}(lastrmsg)"

    $spname whenever S5F1 "ei_alarm_report $spname"
    $spname whenever S6F1 "ei_trace_data $spname"
    $spname whenever S6F3 "ei_discrete_data $spname"
    # multiblock messages are always ok
    $spname whenever S6F5 "$spname put S6F6 {B 0}" 
    $spname whenever S6F11 "ei_event_report $spname"  ;# plain report
    $spname whenever S6F13 "ei_event_ann_rpt $spname" ;# annotated report

    # allow the equipment to request process program downloads
    # or to initiate process program uploads
    $spname whenever S7F1 [list $spname put S7F2 {B 0}]   ;# PPGNT
    $spname whenever S7F3 [list ei_pp_receive $spname]
    $spname whenever S7F5 [list ei_pp_send $spname]

    # On the host side, you typically code your own ei_custom_init procedure
    # that gets called whenever you get the equipment online.
    # Thats the place to add your own custom message handling code,
    # or replace any of the above callbacks.
    # If you are opting not to use the Hume initialize logic which is
    # enabled by default, and highly configurable, then you may want to
    # customize message handling from this procedure.  So we try to 
    # execute your ei_custom_comm_$spname procedure if you create one.
    # (Create your own proc ei_custom_comm_$spname in your own file, add your file
    # to the custom directory tclIndex by typing "make" or "nmake".  Or, have your own 
    # directory and add it to the auto_path at startup.  Or, create the procedure
    # dynamically in the interpreter.
    if { [catch {ei_custom_comm_$spname $spname} errtext] } {
        if { [info commands ei_custom_comm_$spname] == "ei_custom_comm_$spname" } {
            # the user installed procedure exists and it had an error so inform the user
            set errorInfo "$errorInfo\n    invoked from within\n\"ei_comm_enabled $spname\""
            bgerror "$errtext when calling \"ei_custom_comm_$spname $spname\""
            }
        # else, no procedure, ignore error, 
        # clear error message which may be confusing
        set errorInfo {}
        }
    
    # send abort reply to any other primaries
    # do it in a catch in case no reply was requested
    $spname whenmsg S0F1 "catch {$spname abort \$${spname}(lastrSFR)}"

    # now try to communicate
    # make sure stale HSMS reconnect handle does not prevent us going online
    set ${spname}(h_reconnect) {}
    ei_comm_attempt $spname
    }

proc ei_comm_attempt spname {
    global $spname
    # try to get communication going
    # the world may have changed:
    if { ![info exists $spname] || ([info commands $spname] != $spname)} return
    if { [set ${spname}(comm_state)] != "ENABLED {NOT COMMUNICATING}" } return
    # The HSMS reconnect logic will cycle on T5 trying to restore a lost connection.
    # If the reconnect logic is active, we do not want to have additional failed 
    # online attempts here.  But we do need to try going online if the reconnect
    # logic is not active.  
    # An error is returned if the attempt fails, or we are already online.
    if { ![info exists ${spname}(h_reconnect)] || ([set ${spname}(h_reconnect)] == {})} {
        catch {$spname online}
        }
    # You should use S1F13 almost always - you can configure it disabled for
    # defective equipment.  Proper GEM equipment does not respond to S1F1 until
    # after S1F13.
    if { ![info exists ${spname}(use_s1f13)] || [set ${spname}(use_s1f13)] } {
        # the usual case - use_s1f13 not configured or true
        set ${spname}(lastrSFR) {} ;# preclear for reply diagnostics
        $spname put S1F13R L ei_comm_att_cb -whenreply [list ei_comm_att_rep $spname]
        }\
    else { 
        # use S1F1 instead of S1F13
        $spname put S1F1R {} -whenreply [list ei_comm_att2_rep $spname]
        }
    }

#
# send callback for comm attempt S1F13
# so we can trap failed send or no reply and reschedule
#
proc ei_comm_att_cb {spname sfr reason description} {
    global $spname
    if { $reason == "send_complete" } return
    # here on failed send or receive
    if { $reason == "receive_failure" && ([string first "Stream 9" $description] >= 0) } {
        if { [set ${spname}(lastrSFR)] == "S9F1" } { ;# Device ID mismatch
            # correct and try again
            set rc [ei_comm_fix_DEVID $spname]
            if { $rc == 0 } {
                $spname put S1F13R L ei_comm_att_cb -whenreply [list ei_comm_att_rep $spname]
                }\
            else {
                # user is seeing trace messages to fix the Device ID
                }
            return
            }
        # Stream 9 because S1F13 is not supported 
        # non-GEM equipment may not support S1F13, in this case, use S1F1
        $spname put S1F1R {} -whenreply [list ei_comm_att2_rep $spname]
        return
        }
    # what is our retry delay - use T5 for all connection types, not just HSMS
    if { ![info exists ${spname}(T5)] } { set ${spname}(T5) 15000 }
    after [set ${spname}(T5)] [list ei_comm_attempt $spname]
    }

#
# Device ID verification/correction (aka Session ID for HSMS)
# Called after S9F1 - wrong Device ID error 
#  in this context try to use the value in the equipment's S9F1 message.
# Called with 1st S1F13R to verify/correct
#
proc ei_comm_fix_DEVID {spname} {
    global $spname
    set DEVID [set ${spname}(DEVID)]
    set lastheader [${spname} lastheader]
    set dh [lindex $lastheader 0]
    set dl [lindex $lastheader 1]
    # unsigned 15 bit value
    set newID [expr { ((0x7f & $dh)<<8) + $dl }]
    if { $newID == $DEVID } {
        if { [set ${spname}(lastrSFR)] == "S9F1" } {
            if { [set ${spname}(TRACE)] != 0 } {
                set ${spname}(trace) "Incorrect Device ID $DEVID needs manual correction."
                }
            return 1
            }
        # else if received message was S1F13R we are correct
        if { [set ${spname}(TRACE)] & 1} {
            set ${spname}(trace) "Device ID $DEVID verified correct"
            }
        return 0 
        }
    set ${spname}(DEVID) $newID
    if { [set ${spname}(TRACE)] != 0 } {
        set ${spname}(trace) "Incorrect Device ID $DEVID corrected to $newID"
        }
    # fix supervisor startup table - may not be relevant
    SQL "update ei_startup set DEVID=$newID where spname='$spname'"
    return 0
    }

#
# got a reply to S1F13 that we sent to get communication going...
#
# host expects to receive {L:2 {B b} {L:2 {A:n MDLN} {A:n SOFTREV}}}
#                            b==0 success, b==1 denied
#
proc ei_comm_att_rep spname {
    global $spname
    set reply [set ${spname}(lastrmsg)]
    rset $reply {l2 {B b} {l2 {An MDLN} {Am SOFTREV}}}
    if { $l2 == "L:2" && $b == "0x00" } {
        # lets save the MDLN and SOFTREV, we prepend "_" to avoid name
        # conflicts with the secsport software
        set ${spname}(_MDLN) $MDLN
        set ${spname}(_SOFTREV) $SOFTREV
        # transition to COMMUNICATING
        ei_communicating $spname
        return
        }
    # else treat this like receive failure
    ei_comm_att_cb $spname S1F13 receive_failure {denial in reply message}
    }

#
# got a reply to S1F1 that we sent to get communication going...
# we sent S1F1 in lieu of S1F13 for non-GEM equipment
# we will merge back into the GEM logic where S1F1 will be
# sent again to determine if the equipment is online.
#
# host expects to receive {L:2 {A:n MDLN} {A:n SOFTREV}}
#
proc ei_comm_att2_rep spname {
    global $spname
    set reply [set ${spname}(lastrmsg)]
    rset $reply {l2 {An MDLN} {Am SOFTREV}}
    if { $l2 == "L:2"} {
        # lets save the MDLN and SOFTREV, we prepend "_" to avoid name
        # conflicts with the secsport software
        set ${spname}(_MDLN) $MDLN
        set ${spname}(_SOFTREV) $SOFTREV
        # transition to COMMUNICATING
        ei_communicating $spname
        return
        }
    }


# transition to COMMUNCATING (successful S1F13,F14 H<->E)
# for the host
proc ei_communicating spname {
    global $spname
    set ${spname}(comm_state) "COMMUNICATING"
    # get rid of our internal flag that meant we were trying to get comm going
    catch { unset ${spname}(comm_recovery) }

    # we may be here because the equipment was powered down or reset
    # the equipment may be in offline control
    # lets see if the equipment is online
    # GEM equipment that wants to be online will be sending us a S1F1R
    # right now in the wake of a fresh S1F13.  We need to allow a
    # few seconds for the equipment to send S1F1R and receive S1F2 and be
    # online, and then send our S1F1R.  If we send our S1F1R immediately,
    # proper GEM equipment will reply S1F0 == offline.
    after 5000 \
       "$spname put S1F1R {} -whenreply {ei_online_check $spname}"

    ei_driver_event $spname COM_ENABLE
    }


# recd S1F13 from eq - communications request
# Establish Communications Request Ack
proc ei_put_S1F14 {spname} {
    global $spname
    # this is the first message from proper GEM equipment so verify/fix Device ID
    ei_comm_fix_DEVID $spname
    #"B 0" accept,  "B 1" denied
    $spname put S1F14 "L {B 0} L"
    # transition to COMMUNICATING
    ei_communicating $spname
    }


# recd  S1F1 are you there request
# send reply
proc ei_put_S1F2 {spname} {
    global $spname
    $spname put S1F2 L
    # if we do not know that we are communicating, we know now...
    if { [set ${spname}(comm_state)] != "COMMUNICATING" } {
        ei_communicating $spname
        }
    # this is the gem way for equipment to tell us it is entering
    # an online control state
    if { [set ${spname}(control_state)] != "ON-LINE" } {
        set ${spname}(control_state) "ON-LINE"
        # do not use secs_xact calls in a receive callback 
        # use after to perform after return
        after 1 "ei_online $spname"
        }
    }

# sent S1F1 and got a reply
# if its not an abort, we are online
proc ei_online_check spname {
    global $spname
    if { [set ${spname}(lastrSFR)] == "S1F2" } {
        if { [set ${spname}(control_state)] != "ON-LINE" } {
            # do not use secs_xact calls in a receive callback 
            # use after to perform after return
            set ${spname}(control_state) "ON-LINE"
            after 1 "ei_online $spname"
            }
        return
        }
    # else we got F0 
    if { [set ${spname}(control_state)] != "OFF-LINE" } {
        after 1 "ei_offline $spname"
        }
    }

# fresh transition to online control state
# if we have not characterized alarms, etc, now is the time
# also, do other initializations
proc ei_online spname {
    global $spname
    set ${spname}(control_state) ON-LINE

    # If we are in a modal secs_xact, call this logic later so we do not re-enter secs_xact.
    # A check is needed because we can be in the middle of a modal sequence
    # since we may have been triggered at any time using after.
    if { [info exists ${spname}(result)] && [set ${spname}(result)] == "pending" } {
        after 200 "ei_online $spname"
        return
        }

    # gather/refresh characterization/status data 
    ei_alarms_init $spname
    ei_variables_init $spname

    # optionally do init
    ei_online_auto_init $spname

    # if we are using the hub UI, refresh the table window
    catch { hub_table_refresh }
    }

# new knowledge of offline, or transition to offline
proc ei_offline spname {
    global $spname
    set ${spname}(control_state) OFF-LINE
    # the equipment behavior may be different such as not allowing remote
    # commands, but typically alarms and events are still reported
    #ei_driver_event $spname CONTROL_OFFLINE
    }

#
# recd S1F16 response to offline request
#
proc ei_offline_ack {spname} {
    global $spname
    if { [set ${spname}(lastrmsg)] == "B:1 0x00" } {
        ei_offline $spname
        }\
    elseif { [set ${spname}(lastrSFR)] == "S1F0" } {
       # an abort reply is expected for offline GEM equipment
       # so we have the offline control state result we want
       ei_offline $spname
       }
    }

#
# recd S1F18 response to online request
# even when offline, the equipment should reply properly.
#
proc ei_online_ack spname {
    global $spname
    if { [set ${spname}(lastrmsg)] == "B:1 0x00" || \
         [set ${spname}(lastrmsg)] == "B:1 0x02" } {
       if { [set ${spname}(control_state)] != "ON-LINE" } {
           # do not use secs_xact calls in a receive callback 
           # use after to perform after return
           set ${spname}(control_state) "ON-LINE"
           after 1 "ei_online $spname"
           }
       }\
    else {
       if { [set ${spname}(control_state)] != "OFF-LINE" } {
           set ${spname}(control_state) "OFF-LINE"
           }
       }
    }
    
