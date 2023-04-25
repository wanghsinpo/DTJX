# $Header: /usr/cvsroot/gem/equip/equip.tcl,v 1.31 2005/03/20 15:37:37 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997, 2005 Hume Integration Software
# All Rights Reserved
#
# $Log: equip.tcl,v $
# Revision 1.31  2005/03/20 15:37:37  hume
# Added features to make persistent saving of dynamic reports configurable.
#
# Revision 1.30  2004/10/14 20:12:47  hume
# Made comm_disable, comm_enable easier to use by taking care of comm_enable
# array element.
#
# Revision 1.29  2004/10/12 15:19:03  hume
# Updated eq_custom_online logic to first try interface specific
# eq_custom_online_$spname.  So .NET or other applications can deploy
# multiple equipment interfaces without needing a shared eq_custom_online
# procedure.
#
# Revision 1.28  2004/09/27 16:09:22  hume
# Avoid duplicating variable traces in comm_disabled logic.
#
# Revision 1.27  2004/09/24 19:56:40  hume
# end redundant online attempt from comm_enable, fix comm_disable for active
# HSMS which has not connected.
#
# Revision 1.26  2004/09/21 18:13:56  hume
# Added check for HSMS reconnect to prevent redundant online attempts.
# Updated known stream and function values.  other tweaks.
#
# Revision 1.25  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.24  2002/10/04 20:30:17  hume
# Needed to send data with S1F13R.
#
# Revision 1.23  2002/01/19 18:15:59  hume
# Added ECV varID 920, varname UseMultiBlockInquire, to configure use of
# multiblock inquire/grant.  For HSMS it defaults to off so multiblock event
# reports are as fast as single block ones.  The array element (MULTIBLOCK)
# is updated if the UseMultiBlockInquire variable is set by the host.
#
# Revision 1.22  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.21  2001/05/25 21:37:34  hume
# Backup restoration.
#
# Revision 1.21  2001/02/08 22:08:12  hume
# Added $spname online call to eq_comm_attempt which is needed for an active
# HSMS equipment who has never connected to the passive host.
#
# Revision 1.20  2000/12/19 14:55:36  hume
# Improved ease of customization by call to eq_custom_online from
# eq_when_online, and saving of custom array data during communication
# disablement (eq_gemdata revised).
#
# Revision 1.19  2000/12/16 16:08:12  hume
# Added new streams to spooling, decided to send offline event after S1F16
#
# Revision 1.18  2000/12/15 03:53:46  hume
# If the control_state starts as "OFF-LINE SeekOnline" the online and offline
# buttons need to be disabled until the control_state reaches a stable
# state. Used a variable trace to do it and modified the control_intent proc
# to use the variable trace and not vwait.
#
# Revision 1.17  2000/12/13 19:24:02  hume
# Updated eq_reject for E5-0699 and sending aborts versus S9 when offline.
# Added comments in the code for S2F25 and S1F18 where useful or rational
# behavior technically violates GEM.
#
# Revision 1.16  2000/12/12 20:03:13  hume
# When offline we are not supposed to reply to S1F15 with S1F16!
#
# Revision 1.15  2000/12/12 19:54:56  hume
# In GEM 3.3 when offline only S1F13, S1F1, and S9Fx should be sent.
#
# Revision 1.14  2000/12/11 14:54:51  hume
# Fix for display of control state "OFF-LINE Host" when Host S1F15R request.
#
# Revision 1.13  2000/12/05 22:27:25  hume
# Fixed typo mispelling in comment.
#
# Revision 1.12  2000/12/05 01:21:32  hume
# New Trace Data Collection capability.
#
# Revision 1.11  2000/10/12 19:12:12  hume
# Added DEVID commandline option to startup.
#
# Revision 1.10  2000/10/10 20:56:41  hume
# Added provision for HSMS active role startup - usual mode is passive.
#
# Revision 1.9  2000/10/10 17:40:10  hume
# Spooling changes broke S9 send - fixed.
#
# Revision 1.8  2000/09/21 16:05:27  hume
# On X-Windows needed to allow for idletasks before manipulating tracewin.
#
# Revision 1.7  2000/09/21 15:48:09  hume
# Communication disable preserves tracewin.
#
# Revision 1.6  2000/09/19 01:36:53  hume
# Added logic to save and restore variable traces when the array is
# unset in order to cease communication.
#
# Revision 1.5  1999/05/06 19:06:59  hume
# Added TimeFormat variable and logic for A:16 time format.
#
# Revision 1.4  1999/04/08 14:30:48  hume
# Bug fix needed S6F5R for multiblock send.
#
# Revision 1.3  1999/01/12 22:41:33  hume
# Added spooling functionality.
#
# Revision 1.2  1998/01/27 17:44:09  hume
# Fixed problem with disable/enable communications on SECS-I TCP/IP connection.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#




# initialize a gem equipment
# connect to a secs port
# install gem equipment logic
# setup response logic
proc eq_init {spname {port ""} {MDLN gemsim} {SOFTREV 1.0} {hsms_passive 1} {host {}} {devid 0}} {
    #
    # if we have not created an HSMS or secsport connection, do it now
    if { [info commands $spname] != "$spname" } {
        # if the "port" argument is an integer, assume hsms,
        # else assume RS-232 or terminal server
        set ct [scan $port "%d" num]
        if { $ct == 1 && $port == $num } { set hsms 1 }\
        else {set hsms 0}
        if { $hsms } {
            if { $hsms_passive } {
                set reply [hsms $spname passive $port]
                }\
            else {
                # hsms active role (usually host is the active one)
                if { $host != "" } {
                    set reply [hsms $spname active $port $host]
                    }\
                else {
                    # the default host is our own system's default network interface
                    set reply [hsms $spname active $port]
                    }
                }
            set phrase "hsms port $port"
            } \
        else { 
            if { [llength $port] } {
                set cmd [list secsport $spname $port]
                set phrase "serial port $port"
                } \
            else {
                set cmd [list secsport $spname]
                set phrase "default serial port"
                }
            set reply [eval $cmd]
            }
        if { $reply != $spname } { error "could not connect to $phrase" }
        # save our invocation in case we go online and then need to
        # go offline - (have to destroy and recreate)
        global $spname
        set ${spname}(init_cmd) [list eq_init $spname $port $MDLN $SOFTREV $hsms_passive $host $devid]
        # set up a trace on "state" to monitor the communications
        trace variable ${spname}(state) w eq_state_trace
        }
    global $spname 
    # save our MDLN and SOFTREV 
    set ${spname}(_MDLN) $MDLN
    set ${spname}(_SOFTREV) $SOFTREV
    # our device ID
    set ${spname}(DEVID) $devid

    # you can overide some default parameters before or after this procedure is called
    #set ${spname}(T2) 8000
    set ${spname}(EQUIP) 1
    
    # initialize data and variables for items not already set
    eq_defaults $spname

    # you cannot configure "COMMUNICATING"
    if { [set ${spname}(comm_state)] != "DISABLED" } {
        set ${spname}(comm_state) "ENABLED {NOT COMMUNICATING}"
        }

    # possibly establish communications
    if { [set ${spname}(comm_state)] == "ENABLED {NOT COMMUNICATING}" } {
        eq_comm_enabled $spname ;# gem level
        }\
    else {
        # "DISABLED"
        eq_comm_disabled $spname ;# gem level
        }
    }



# This procedure is called whenever  ${spname}(state) is updated
# We look for communication failure and then make sure our comm_state
# is consistent.  
# This is better design than coding for every possible bad send or
# non-reply
#
proc eq_state_trace {spname sub op} {
    if { $op != "w" || $sub != "state" } return
    global $spname
    set newstate [set ${spname}(state)]
    if { $newstate != "OFFLINE" &&  $newstate != "LISTENING" } return
    # here on comm problem
    if { [set ${spname}(comm_state)] == "COMMUNICATING" } {
        if { [set ${spname}(comm_enable)] } {
            # looks like a detected problem and not our own disablement
            # we will transition to "ENABLED {NOT COMMUNICATING}"
            after 1 "eq_comm_enabled $spname"
            # we will also activate spooling 
            after 1 "eq_spool_activate $spname"
            }
        }
    }


#
# disable communications 
# "no messages are generated until comm is subsequently enabled"
# thus, nothing is spooled
proc eq_comm_disabled spname {
    global $spname
    catch { unset ${spname}(comm_recovery) }
    # setting comm_state to DISABLED will abort an HSMS active online attempt
    # any pending eq_comm_attempt afters will see the new comm_state and quit
    set ${spname}(comm_state) "DISABLED"
    if {[set ${spname}(comm_enable)] != 0} {set ${spname}(comm_enable) 0}

    # if not online, return
    if { [set ${spname}(state)] == "OFFLINE" } return
    # SECS-I on TCP/IP is LISTENING when 1st initialized 
    # this is similar to the never online condition
    if { [set ${spname}(state)] == "LISTENING" && \
         ![info exists ${spname}(PROTOCOL)] } return

    # abort any open transactions or queued sends or h_reconnect looping
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
    set statements [eq_gemdata $spname]

    # shutdown
    $spname close

    # disable the comm state
    set ${spname}(comm_state) "DISABLED"

    # re-create connection object without going online
    eval $init_cmd

    # restore data including items like SYSTEM, TRACE, *Spool*, T*, control_state
    # but not includng comm_state
    foreach statement $statements { eval $statement }

    # restore tracewin
    if { $tracewin } { 
        $spname tracewin 
        update idletasks
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
# possibly called at initialization
# possibly called from UI action disabled->enabled
#
proc eq_comm_enabled spname {
    global $spname
    if {[set ${spname}(comm_enable)] != 1} {set ${spname}(comm_enable) 1}
    # block re-entrancy into retry logic
    if { [info exists ${spname}(comm_recovery)] } return
    # The 1st time called, initialize persistence for report definitions.
    # We needed to wait until variables and events have been defined
    # so waiting until communication is enabled is appropriate.
    if { ![info exists ${spname}(_ReportsInitialized)] } {
        if { [info exists ${spname}(ReportsAreSaved)] && [set ${spname}(ReportsAreSaved)] } {
            eq_reports_restore $spname
            }
        }
    set ${spname}(comm_recovery) 1
    set ${spname}(comm_state) "ENABLED {NOT COMMUNICATING}"
    # remove existing handlers
    foreach sf [array names $spname S\[0-9\]*F*] {
        $spname whenmsg $sf 
        }
    # turn on:
    $spname whenever S1F13 "eq_put_S1F14 $spname" ;# lets communicate
    # discard any other primaries
    $spname whenmsg S0F1 ""
    # there should not be a reconnect timer handle, but just make sure
    set ${spname}(h_reconnect) {}
    # eq_comm_attempt will call online 
    eq_comm_attempt $spname
    }

proc eq_comm_attempt spname {
    global $spname
    # the world may have changed:
    if { ![info exists $spname] } return
    if { [set ${spname}(comm_state)] != "ENABLED {NOT COMMUNICATING}" } return
    # The HSMS reconnect logic will cycle on T5 trying to restore a lost connection.
    # If the reconnect logic is active, we do not want to have additional failed 
    # online attempts here.  But we do need to try going online if the reconnect
    # logic is not active.  
    # An error is returned if the attempt fails, or we are already online.
    if { ![info exists ${spname}(h_reconnect)] || ([set ${spname}(h_reconnect)] == {})} {
        catch {$spname online}
        }
    $spname whenmsg S1F14 "eq_comm_att_rep $spname"
    set MDLN [set ${spname}(_MDLN)]
    set SOFTREV [set ${spname}(_SOFTREV)]
    # there may be spaces in $MDLN and $SOFTREV 
    $spname put S1F13R [list L:2 [list A $MDLN] [list A $SOFTREV]] eq_comm_att_cb
    }

#
# send callback for eq_comm_attempt S1F13
# so we can trap failed send or no reply and reschedule
proc eq_comm_att_cb {spname sfr reason description} {
    global $spname
    if { $reason == "send_complete" } return
    # failed send or receive
    # what is our retry delay
    set reply [SQL "select varvalue from ei_variable where\
 spname='$spname' and varname='EstablishCommunicationsTimeout'"]
    set value [lindex [lindex [lindex $reply 6] 0] 0]
    if { $value == "" } { 
        set ${spname}(strace) "EstablishCommunicationsTimeout was not configured"
        set value 60 
        }
    after [expr 1000*$value] "eq_comm_attempt $spname"
    }

#
# got a reply to S1F13 that we sent to get communication going...
#
# eq expects to receive {L:2 {B b} L:0}
#                            b==0 success, b==1 denied
#
proc eq_comm_att_rep spname {
    global $spname
    $spname whenmsg again
    set reply [set ${spname}(lastrmsg)]
    rset $reply {l2 {B b} l0}
    if { $l2 == "L:2" && $b == "0x00" } {
        # transition to COMMUNICATING
        eq_communicating $spname
        return
        }
    # else treat this like receive failure
    eq_comm_att_cb $spname S1F13 receive_failure {denial in reply message}
    }

# 
# transition to COMMUNICATING (successful S1F13,F14 H<->E)
# update status data
# install handlers 
#
proc eq_communicating spname {
    global $spname
    set ${spname}(comm_state) "COMMUNICATING"
    catch { unset ${spname}(comm_recovery) }
 
    # Now that we are communicating, we officially enter the
    # Control state model.  We could be in any of the states.
    # "ON-LINE REMOTE" "ON-LINE LOCAL" 
    # "OFF-LINE Equipment" "OFF-LINE Host" "OFF-LINE SeekOnline"
    vset [set ${spname}(control_state)] "cs substate"
    if { [string first ON-LINE $cs] >= 0 } {
         eq_online_start $spname
         }\
    else { 
        eq_offline_start $spname $substate
        }
    
    }

#
# translate our internal control_state representation into the gem variable value
# 1=off-line/eq off-line 2=off/att on 3=off/host off 4=on/local 5=on/remote 
#
proc eq_ControlState spname {
    global $spname
    if { [set ${spname}(control_state)] == "ON-LINE REMOTE" } { return 5 }
    if { [set ${spname}(control_state)] == "ON-LINE LOCAL" } { return 4 }
    if { [set ${spname}(control_state)] == "OFF-LINE Equipment" } { return 1 }
    if { [set ${spname}(control_state)] == "OFF-LINE Host" } { return 3 }
    if { [set ${spname}(control_state)] == "OFF-LINE SeekOnline" } { return 2 }
    return 0  ;# internal error
    }


#
# whenmsg behavior for OFF-LINE control state
#
# per gem:
#   respond to S1F13 S1F17
#   do not allow initiation of messages other than S1F13 and S1F1
#   since messages are not initiated, no spooling is occuring
#   reply SxF0 to any other primary
#
proc eq_when_offline {spname} {
    global $spname 
    # turn off receiving
    foreach sf [array names $spname S\[0-9\]*F*] {
        $spname whenmsg $sf 
        }
    # turn on selected messages
    # per the standard, we do not respond to S1F1!
    $spname whenever S1F2  "eq_recv_S1F2 $spname" ;# got ON-LINE reply
    $spname whenever S1F13 "eq_put_S1F14 $spname" ;# lets communicate
    $spname whenever S1F17 "eq_put_S1F18 $spname" ;# request online
    # responding to S2F25 is non-standard when offline but it is a useful communication check
    # comment out the next line for strict compliance
    $spname whenever S2F25 "$spname put S2F26 \$${spname}(lastrmsg)"

    # reject anything else 
    $spname whenmsg S0F1 "eq_reject $spname"
    }


#
# whenmsg behavior for ON-LINE control state
#
#   LOCAL control per gem E30-95 p 14
#   do not allow remote commands that cause physical movement or that initiate processing
#   host is prohibited from modifying ECV's that affect processing during processing
#   host can select recipes for exec as long as this does not affect current processing
#   host can do any other capabilities not prohibited in the above such as
#      upload/download recipes 
#      configure alarms, event reporting, traces, 
#      receive alarms, event reports, trace data
#      host can query SV's, ECVs, event reports, PP directories, and alarms
#      host can perform Terminal services
#
#  REMOTE control - all communication interface functionality is available
#   operator can switch to LOCAL online control
#   operator can switch to equipment off-line control
#   operator can disable communication 
#   there may be configurable operator restrictions, such as:
#       can change process related ECV's?
#       can select PP?
#       can pause/resume PP?
#       can initiate material movement?
#   
proc eq_when_online {spname} {
    global $spname errorInfo
    # setup callbacks for inbound messages
    # modulate LOCAL vs REMOTE inside of your procedures
    # by looking at [set ${spname}(control_mode)]
    $spname whenever S1F1  "eq_put_S1F2 $spname"
    $spname whenever S1F2  "eq_recv_S1F2 $spname" ;# got ON-LINE reply
    $spname whenmsg S1F3  "eq_put_S1F4 $spname"
    $spname whenmsg S1F11 "eq_put_S1F12 $spname"
    $spname whenever S1F13 "eq_put_S1F14 $spname" ;# lets communicate
    $spname whenmsg S1F15 "eq_put_S1F16 $spname" ;# request offline
    $spname whenever S1F17 "eq_put_S1F18 $spname" ;# request online
    $spname whenmsg S2F13 "eq_put_S2F14 $spname"
    $spname whenmsg S2F15 "eq_put_S2F16 $spname"
    $spname whenmsg S2F17 "eq_clock_get $spname"
    $spname whenever S2F21 "eq_S2F21_RCMD $spname"
    # allow Trace Reports only if eq_trace_startup was called
    if { [hub_table_exists ei_trace_active] } {
        $spname whenever S2F23 "eq_trace_init $spname"
        }
    $spname whenever S2F25 "$spname put S2F26 \$${spname}(lastrmsg)"
    $spname whenmsg S2F29 "eq_ECNAMELIST $spname"
    $spname whenmsg S2F31 "eq_clock_set $spname"
    $spname whenever S2F33 "eq_report_define $spname"
    $spname whenever S2F35 "eq_report_assoc $spname"
    $spname whenever S2F37 "eq_report_enable $spname"
    $spname whenever S2F39 "$spname put S2F40 {B 0}" ;# grant multiblock
    $spname whenever S2F41 "eq_S2F41_RCMD $spname"
    $spname whenever S2F43 "eq_spool_control $spname"
    $spname whenmsg S5F3 "eq_alarm_enable $spname"
    $spname whenmsg S5F5 "eq_alarm_list $spname"
    $spname whenmsg S5F7 "eq_alarm_list $spname"
    $spname whenever S6F15 "eq_report_ERR $spname"
    $spname whenever S6F17 "eq_report_AERR $spname"
    $spname whenever S6F19 "eq_report_IRR $spname"
    $spname whenever S6F21 "eq_report_AIRR $spname"
    $spname whenever S6F23 "eq_spool_request $spname"
    $spname whenever S7F1 "$spname put S7F2 {B 0}" ;# download ok
    $spname whenever S7F3 "eq_recipe_download $spname"
    $spname whenever S7F5 "eq_recipe_upload $spname"
    $spname whenever S7F17 "eq_recipe_del $spname"
    $spname whenever S7F19 "eq_recipe_dir $spname"
    $spname whenmsg S10F3 "eq_term_disp $spname"
    $spname whenmsg S10F5 "eq_term_disp $spname"

    # Add additional callbacks that the user has coded in his own procedure.
    # Your code can also deactivate any of the above handlers.
    # We try to execute (1) eq_custom_online_$spname and if it does not exist,
    # we try to execute (2) eq_custom_online.  So you can write a custom procedure
    # that is specific to an interface or shared among interfaces.
    # (Create your own proc eq_custom_online in your own file, add your file
    #  to the tclIndex by typing "make" or "nmake".  Or, have your own 
    #  directory and add it to the auto_path at startup.  Or, create your procedure
    #  dynamically in the interpreter.)
    if { [catch {eq_custom_online_$spname $spname} errtext] } {
        if { [info commands eq_custom_online_$spname] == "eq_custom_online_$spname" } {
            # the user installed procedure exists and it had an error so inform the user
            set errorInfo "$errorInfo\n    invoked from within\n\"eq_when_online $spname\""
            bgerror "$errtext when calling \"eq_custom_online_$spname $spname\""
            }\
        else {  ;# specific $spname procedure did not exist, try generic
            if { [catch {eq_custom_online $spname} errtext] } {
                if { [info commands eq_custom_online] == "eq_custom_online" } {
                    # the user installed procedure exists and it had an error so inform the user
                    set errorInfo "$errorInfo\n    invoked from within\n\"eq_when_online $spname\""
                    bgerror "$errtext when calling \"eq_custom_online $spname\""
                    }
                }
            }
        # else, no procedure, ignore error, 
        # clear error message which may be confusing
        set errorInfo {}
        }

    # reject anything else 
    $spname whenmsg S0F1 "eq_reject $spname"
    }



#
# the equipment is initiating a message such as an alarm or event
# this code sees if we are communicating or spooling etc and handles
# the message accordingly.
#
# this procedure is only called for primary messages that may
# be subject to spooling
#
# According to the GEM standard, ALL primary messages except for 
# stream 1 may be spooled so even stream 9 and realtime transaction
# messages such as for material movement should be routed through
# this proc.
#
proc eq_checked_put {spname s f reply data {DATAID {}}} {
    global $spname
    # if communication is disabled, per gem, no messages are to
    # be created, and thus no spooling etc
    if { [set ${spname}(comm_state)] == "DISABLED" } return

    # paragraph 3.3 says that if the state is OFF-LINE only S1F13, S1F1, and S9Fx
    # are initiated, and these are not routed through this proc
    # the event to notify the host of going offline is sent while still online
    if { [string first OFF-LINE [set ${spname}(control_state)]] >= 0 } return

    set sfr S${s}F${f}
    if { $reply } { append sfr R }

    if { [set ${spname}(spooling_state)] == "INACTIVE" } {
        # the usual condition
        # send (or try to send) the message
        set sent 0
        # added configurable bypass of multiblock enquire/grant (1/19/02)
        if { ![info exists ${spname}(MULTIBLOCK)] || [set ${spname}(MULTIBLOCK)] } {
            # special case messages that need multiblock enquire/grant
            # S6F3,9,11,13
            if { $s == 6 && ($f == 11 || $f == 13 || $f == 3 || $f == 9) } {
                set len [llength [TSN_to_secs $data]]
                if { $len > 244 } {
                    $spname put S6F5R [list L:2 $DATAID "U4 $len"] \
 [list eq_checked_put_mbcb $sfr $data]\
  -whenreply [list eq_report_mult $spname $sfr $data]
                    set sent 1
                    }
                }
            }
        if { !$sent } {
            $spname put $sfr $data [list eq_checked_put_cb $data]
            }
        return
        }
    # spooling is active
    eq_spool_add $spname $sfr $data
    }

# A callback to see if the message was sent ok, and if not
# possibly add it to the spool
proc eq_checked_put_cb {data spname sfr reason desc} {
    if { $reason == "send_failure" } {
        eq_spool_add $spname $sfr $data
        }
    }
    
# if the multiblock permission message is not sent ok,
# possibly spool the multiblock message and not the permission message
proc eq_checked_put_mbcb {SFR data spname sfr reason desc} {
    if { $reason == "send_failure" } {
        eq_spool_add $spname $SFR $data
        }
    }

# even S9 may be spooled so we route it through checked_put
proc eq_S9_reply {spname fn} {
    #$sp put S9F$fn "B [$spname lastheader]"
    eq_checked_put $spname 9 $fn 0 "B [$spname lastheader]"
    }

    
# Are you there reply
proc eq_put_S1F2 {spname} {
    global $spname
    $spname put S1F2 \
 [list L \
    [list A [set ${spname}(_MDLN)]]  \
    [list A [set ${spname}(_SOFTREV)]] ]
    }

#
# got a reply to S1F1
#
proc eq_recv_S1F2 spname {
   global $spname
   # if we are seeking to go online, we succeeded
   if { [set ${spname}(control_state)] == "OFF-LINE SeekOnline" } { 
       eq_online_start $spname
       }
   }

#
# send callback on S1F1 when used to initiate online control
# so we can trap failed send or no reply 
proc eq_online_att_cb {spname sfr reason description} {
    global $spname
    if { $reason == "send_complete" } return
    # failed send or receive
    set ${spname}(control_state) "OFF-LINE Host"
    }

#
# enter online control state
#
proc eq_online_start spname {
    global $spname
    # enter ON-LINE {LOCAL|REMOTE} control
    set mode [set ${spname}(control_mode)]
    set ${spname}(control_state) "ON-LINE $mode"
    # set up handlers
    eq_when_online $spname
    # report event
    if { $mode == "LOCAL" } { eq_gem_event $spname 4001}\
    else { eq_gem_event $spname 4002 }
    }
    
#
# enter offline control state
# called on transition or entry into control model
#
proc eq_offline_start {spname {substate Equipment}} {
    global $spname
    # if we in an online state, change and report transition event
    if { [string first ON-LINE [set ${spname}(control_state)]] >= 0 } {
        eq_gem_event $spname 4000
        }
    # set the [new] state
    set ${spname}(control_state) "OFF-LINE $substate"
    # set up handlers
    eq_when_offline $spname
    # try to get ON-LINE if appropriate
    if { [set ${spname}(control_state)] == "OFF-LINE SeekOnline" } {
        $spname put S1F1R {} eq_online_att_cb
        }
    }

# Establish Communications Request Ack
proc eq_put_S1F14 {spname} {
    global $spname
    set COMMACK "B 0"	;# accept,  "B 1" denied
    set MDLN [set ${spname}(_MDLN)]
    set SOFTREV [set ${spname}(_SOFTREV)]
    # there may be spaces in $MDLN and $SOFTREV so we use [list ]
    $spname put S1F14 [list L $COMMACK [list L [list A $MDLN] [list A $SOFTREV]]]
    # transition to COMMUNICATING
    eq_communicating $spname
    }


# Request OFF-LINE control state Ack  
proc eq_put_S1F16 {spname} {
    global $spname
    $spname put S1F16 "B 0"
    # notes
    # (1) whether the reply message is sent successfully or not we go offline
    # (2) we do not write to ${spname}(control_state) unless we change it
    #     out of consideration for possible variable traces
    # (3) we do not re-arm for another S1F15 since we are going offline
    if { [set ${spname}(control_state)] != "OFF-LINE Host" } {
        # Uncomment the next line to suppress the event report that we are going offline.
        #set ${spname}(control_state) "OFF-LINE Host"
        eq_offline_start $spname Host
        }
    }


# Request ON-LINE control state Ack  
proc eq_put_S1F18 {spname} {
    global $spname
    if { [set ${spname}(control_intent)] == "OFF-LINE" } {
        set ${spname}(control_state) [set ${spname}(control_intent)]
        set ONLACK "B 1"
        $spname put S1F18 $ONLACK 
        }\
    elseif { [string first ON-LINE [set ${spname}(control_state)]] >= 0 } {
        set ONLACK "B 2"	;# already ON-LINE
        $spname put S1F18 $ONLACK 
        }\
    else { 
        # the GEM standard does not show a transition from the "OFF-LINE SeekOnline" based on
        # S1F17R from the host.   We believe this is an oversight, since we are trying to be online.
        # However, the window of time is so small it is of little consequence.
        # Comment out the next line to accept the host's request.
        if { [set ${spname}(control_state)] == "OFF-LINE SeekOnline" } {  $spname put S1F18 {B 1} ; return }
        set ONLACK "B 0" 
        $spname put S1F18 $ONLACK eq_S1F18_sent_callback
        }
    }


# transition to ON-LINE control_state
proc eq_S1F18_sent_callback {spname sfr reason description} {
    global $spname
    if { $reason == "send_complete" } {
        eq_online_start $spname
        }
    }


######################### eq_reject ##############################
######################### eq_reject ##############################
######################### eq_reject ##############################

# reject the message because we do not recognize it or
# we are offline and not responding to it
#
# supply a suitable response such as
#   S9F3 - bad stream
#   S9F5 - bad fn
#   SxF0 - abort
#
proc eq_reject spname {
    global $spname
    #
    set ct [scan [set ${spname}(lastrSFR)] "S%dF%d" stream func]
    if { $ct != 2 } return ;# Huh?
    if { $stream == 9 } return 
    set R [expr [string first R [set ${spname}(lastrSFR)]] > 0]
    # when control state is OFF-LINE, GEM paragraph 3.3 says reply with F0 abort
    # and the abort reply does not get spooled
    if { [string first OFF-LINE [set ${spname}(control_state)]] >= 0 } {
        # if they want a reply, send abort
        if { $R } { $spname abort [set ${spname}(lastrSFR)] }
        # nothing happens for an ignored non-reply primary message.
        return
        }
    # else we are in the online control state
    # I would just send SxF0 but the standard says you need to use S9.
    # The detailed use of S9 is a maintenance nightmare.
    # just reject the streams that E5 does not know about
    if { $stream <= 0 || $stream == 11 || $stream > 18 } {
        eq_S9_reply $spname 3 
        return
        }
    # check the functions - just non E5-0304
    # here is the max fn in each stream
    foreach pair {{1 20} {2 50} {3 36} {4 41} {5 18} {6 30}\
 {7 44} {8 4} {9 13} {10 10} {12 19} {13 16} {14 28} {15 54} {16 30} {17 14} {18 16}} {
        vset $pair "s max"
        set fmax($s) $max
        }
    if { $func == 0 } return
    if { $func > $fmax($stream) } {
        eq_S9_reply $spname 5 
        return
        }
    # ok its a reasonable SxFy but we are not handling it
    # so just send abort reply
    if { $R } { 
        # if reply is wanted, send abort reply
        $spname abort [set ${spname}(lastrSFR)]
        return
        }
    # used to ignore no reply primary
    # think its probably best to flag it as an unknown function error
    eq_S9_reply $spname 5
    }
