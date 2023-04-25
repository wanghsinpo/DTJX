# $Header: /usr/cvsroot/gem/host/initialize.tcl,v 1.14 2004/10/12 15:15:22 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: initialize.tcl,v $
# Revision 1.14  2004/10/12 15:15:22  hume
# Rearranged the variable initialization logic for better external use.
# (Such as new .NET code).  New provision for AUTO_VIRT_INIT - use virtual
# concepts of VFEI without using VFEI commands.  Variable
# table configuration records are put in place earlier.  Separate procedures
# to refresh Status Variable values and EC values.
#
# Revision 1.13  2002/09/24 15:56:20  hume
# Updated calls to ei_var_query to explicitly call with a list of names.
# Sets a proper example, and fixes a bug with ei_event_discovery when
# EventsEnabled variable name contains white space.
#
# Revision 1.12  2002/08/06 21:25:28  hume
# Added checkboxes to disable S1F17 and S2F31 during the initialization flow.
#
# Revision 1.11  2002/07/22 19:22:10  hume
# Added logic to automatically correct the Device ID when S1F13R is used to
# initiate communication.  Fallback use of S1F1 is not changed.
#
# Revision 1.10  2002/07/22 16:54:28  hume
# Added a comment that failure to initialize spooling early in initialization
# can prevent receiving S9 messages if the equipment unexpectedly supports
# spooling but does not support other basic message types.
#
# Revision 1.9  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.8  1999/08/24 14:04:41  hume
# $spname was not substituted in vfei init message (no ill effects).
#
# Revision 1.7  1999/05/27 19:19:53  hume
# Added new logic for VFEI clock synchronization command, and rearranged
# the existing clock setting logic to make it reusable.
#
# Revision 1.6  1999/05/06 19:55:03  hume
# Revised clock handling for possible A:16 format.
#
# Revision 1.5  1999/01/22 18:23:51  hume
# Added R's to two secs_xact calls even though secs_xact adds it in.
#
# Revision 1.4  1999/01/14 16:00:20  hume
# Added support for purging or unloading the spool during initialization.
# Also added callout to customer written ei_custom_init during initialization.
#
# Revision 1.3  1998/09/02 12:46:43  hume
# Correct S1F13 from host to send empty list message, not just header.
#
# Revision 1.2  1997/09/30 12:58:42  hume
# Added logic to tolerate non-GEM equipment that does not support S1F13.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#


# Start with functionality proscribed by VFEI
#
#  - establish communication
#  - request equipment go online
#  +  (and query status of alarms and variables if being online is new)
#  - synch equipment clock
#  - set equipment constants where host_managed=1
#  - disable event reporting and delete reports
#
# And go beyond VFEI if you configured it:
#
#  - setup event reports per tables ei_report_cfg, ei_event_report_cfg 
#    and ei_event.  If you have not configured any equipment based
#    event reports, ALL event reports will be enabled so you can
#    capture the data needed for configuring your own event reports.
#
#  - enable or disable alarms per table ei_alarm
#
#  - unload or purge the spool if SPOOL_INIT variable is "UNLOAD" or "PURGE"
#
#    VFEI compliant drivers will configure ABORT, MB_START, MB_COMPLETE,
#    MBC_COMPLETE, MBC_START, PAUSE, RESUME, MESSAGE_RECEIVE,  and
#    RESOURCE_ACTIVATE events
#
# return value
# 0 = ok
# 1 = failed comm
# 2 = failed online
# 3 = failed clock set
# 4 = failed setting equipment constants
# 5 = failed disabling events and reports
# 6 = failed enabling events and reports
# 7 = failed enabling/disabling alarms
# 8 = spool unload or purge reply was 2 = "Denied, busy try later"

#  *** NOTE ***
#  This initialization logic does NOT get called in the usual startup flow if you
#  configure the the ei_variable values for AUTO_SECS_INIT and AUTO_VFEI_INIT 
#  to be 0.
#
proc ei_initialize {spname} {
    global $spname

    # set an internal flag that means we are doing an init
    set ${spname}(init_active) 1

    # get communications going
    # usually this has already been done when the program starts
    if { [set ${spname}(comm_state)] == "DISABLED" } {
        ei_comm_enabled $spname
        }
    if { [set ${spname}(comm_state)] != "COMMUNICATING" } {
        # this code is similar to our usual startup except its 
        # done with synchronous style calls
        set reply [secs_xact $spname S1F13R L]
        if { ($reply == "TIMEOUT") && ([set ${spname}(lastrSFR)] == "S9F1") } { 
            # Device ID mismatch - correct and try again
            ei_comm_fix_DEVID $spname
            set reply [secs_xact $spname S1F13R L]
            }
        if { $reply == "TIMEOUT" } { 
            set why [secs_xact_failure $spname]
            if { $why == "BAD_SEND" || $why == "NO_REPLY" ||\
                 $why == "ABORTED" } { return 1 }
            # this is non-GEM equipment - "REJECTED" with S9
            # lets try S1F1
            set s1reply [secs_xact $spname S1F1R]
            if { $reply == "TIMEOUT" } { return 1 }
            rset $s1reply {l2 {An MDLN} {Am SOFTREV}}
            set b "0x00" 
            }\
        else {
            # got usual S1F14 reply
            rset $reply {l2 {B b} {l2 {An MDLN} {Am SOFTREV}}}
            }
        if { $l2 == "L:2" && $b == "0x00" } {
            # lets save the MDLN and SOFTREV, we prepend "_" to avoid name
            # conflicts with the secsport software
            set ${spname}(_MDLN) $MDLN
            set ${spname}(_SOFTREV) $SOFTREV
            }
        # transition to COMMUNICATING
        set ${spname}(comm_state) "COMMUNICATING"
        # get rid of our internal flag that meant we were trying to get comm going
        catch { unset ${spname}(comm_recovery) }
        }

    # get the equipment online
    if { ![info exists ${spname}(use_s1f17)] || [set ${spname}(use_s1f17)] } {
        set reply [secs_xact $spname S1F17R]
        }\
    else { ;# if S1F17 is disabled, pretend it succeeded
        set reply {B 2}
        }
    if { $reply == "TIMEOUT" } { ;# abort shows up as TIMEOUT
        set reason [secs_xact_failure $spname]
        if { $reason == "BAD_SEND" || $reason == "NO_REPLY" } { 
            set ${spname}(init_active) 0
            return 1
            }
        if { $reason == "REJECTED" || $reason == "ABORTED" } {
            # its not gem, but lets try to play along
            set reply [secs_xact $spname S1F1R] ;# are you online?
            if { $reply == "TIMEOUT" } { ;# probably ABORTED
                set ${spname}(init_active) 0
                set ${spname}(control_state) "OFF-LINE"
                return 2
                }
            }
        # we are online with non-gem equipment
        }\
    else { ;# look at ONLACK 0=ok,1=refused,2=already
        set reply [expr [lindex $reply 1]]
        if { $reply != "0" && $reply != "2" } {
            set ${spname}(init_active) 0
            set ${spname}(control_state) "OFF-LINE"
            return 2
            }
        }

    # we have achieved online control

    # Theoretically if the equipment supports spooling, you want to take care
    # of it immediately because spooling can interfere with the equipment sending
    # you S9 messages for the transactions that it does not support.  Practically
    # there is more equipment that is messed up by receiving S6F23R than there is
    # equipment that wants to send S9 messages for not supporting basic messages
    # and yet supports spooling.  So spooling initialization is deferred until later.
    #$spname put S6F23R {U1 1} ;# uncomment to purge the spool now

    if { [set ${spname}(control_state)] != "ON-LINE" } {
        # Hey, this is the first time we got em on the wire
        # so lets synch up with alarms and variables
        ei_online $spname
        }
    
    # synch equipment clock
    if { ![info exists ${spname}(use_s2f31)] || [set ${spname}(use_s2f31)] } {
        set reply [ei_clock_set $spname]
        }\
    else {
        # if clock synch is disabled, pretend it happened
        set reply {}
        }
    if { $reply == "REJECTED" || $reply == "ABORTED" } {
        # clock is not supported - non-gem
        # configuration can force ignore
        set reply [SQL "select varvalue from ei_variable where\
 spname='$spname' and varID='CLOCK_FAIL_IS_OK'"]
        set flag [lindex [lindex [lindex $reply 6] 0] 0]
        if { $flag != "1" } {
            set ${spname}(init_active) 0 
            return 3
            }\
        }\
    elseif { $reply != "" } {
        # comm timeout or refusal
        set ${spname}(init_active) 0
        return 3
        }
  
    #  - set equipment constants where host_managed=1
    set reply [ei_eqconst_managed_set $spname]
    if { $reply != 0 } { 
        set ${spname}(init_active) 0
        return 4 
        }

    #  - disable event reporting and delete reports
    set reply [ei_event_disable $spname {} 1]
    if { $reply != 0 } { 
        set ${spname}(init_active) 0
        return 5 
        }
    
    #  - setup configured event reports 
    set reply [ei_reports_setup $spname]
    if { $reply != 0 } { 
        set ${spname}(init_active) 0
        return 6 
        }

    # - enable/disable alarms per configuration data
    set reply [ei_alarm_setup $spname]
    if { $reply != 0 } { 
        set ${spname}(init_active) 0
        return 7 
        }

    # - unload or purge the spool if configured
    set SPOOL_INIT [string toupper [lindex [lindex [\
       ei_var_query $spname [list SPOOL_INIT] varname 0] 0] 1]]
    if { $SPOOL_INIT == "UNLOAD" } { set msg "U1 0" ; set SPOOL_INIT 1 }\
    elseif { $SPOOL_INIT == "PURGE" } { set msg "U1 1" ; set SPOOL_INIT 1 }\
    else { set SPOOL_INIT 0 }
    if { $SPOOL_INIT } {
        set reply [secs_xact $spname S6F23R $msg] ;# expect 0=ok, 2=no data, 1=busy 
        # we ignore replies that imply spooling is not supported (S9 or abort)
        if { $reply == "B:1 0x01" } {
            set ${spname}(init_active) 0
            return 8
            }
        }

    #   You can install a custom procedure to be executed as the last part of
    #   initialization.  For example, you could use S2F43 to make sure
    #   the spooling specification was how you want it.
    #   Your procedure returns 0 for success, or a code for failure
    set rc [catch {ei_custom_init $spname} reply]
    if { $rc == 0 && $reply != 0 } {
        set ${spname}(init_active) 0
        return $reply
        }
    # errorInfo that ei_custom_init not found is normal

    set ${spname}(init_active) 0
    return 0
    }
    

###################### ei_online_auto_init ####################
###################### ei_online_auto_init ####################
###################### ei_online_auto_init ####################
#
# optional automatic initialization the first time we see that
# we are online
#
# 
proc ei_online_auto_init spname {
    global $spname
    # are we in the middle of an init?
    if { [info exists ${spname}(init_active)] &&\
         [set ${spname}(init_active)] } return
    # look at configuration
    foreach parm {AUTO_VFEI_INIT AUTO_VIRT_INIT AUTO_SECS_INIT} {
        set reply [SQL "select varvalue from ei_variable where\
 spname='$spname' and varID='$parm'"]
        set value [lindex [lindex [lindex $reply 6] 0] 0]
        if { $value == "1" } {
            if { [expr [set ${spname}(TRACE)] & 0x0001] } {
                set ${spname}(trace) "Doing $parm online automatic initialize"
                }
            if { $parm == "AUTO_VFEI_INIT" } {
                set reply [ei_vfei_cmd $spname \
 "CMD/A=\"INITIALIZE\" MID/A=\"$spname\" MTY/A=\"C\" TID/U4=0"]
                global vfei_va
                vfei_2_array $reply vfei_va
                set reply [list $vfei_va(ECD) $vfei_va(ETX)]
                }\
            elseif { $parm == "AUTO_VIRT_INIT" } {
                set reply [mh_eval "ei_virt_initialize $spname"]
                }\
            elseif { $parm == "AUTO_SECS_INIT" } {
                set reply [mh_eval "ei_initialize $spname"]
                }
            SQL "update ei_variable set varvalue='$reply',\
 t_latest='[secs_CLOCK $spname]' where\
 spname='$spname' and varID='AUTO_INIT_RESULT'"
            ei_driver_event $spname $parm
            return
            }
        }
    }

###################### ei_virt_initialize #######################
###################### ei_virt_initialize #######################
###################### ei_virt_initialize #######################
#
# using the virtual naming and reporting concepts of VFEI without 
# using VFEI format commands
#
proc ei_virt_initialize {spname} {
    set reply [ei_initialize $spname]
    # ei_initialize did the logic of event report setups for equipment based variables.
    # Now we copy configuration records for Virtual event reports
    # which can combine non-equipment variables.
    if { $reply == 0 } {
        set sreply [SQL "select RPTID,VIDs from ei_report_cfg where\
 spname='$spname' and RPTID like 'vfei_%'"]
        set rows [lindex $sreply 6]
        foreach row $rows {
            vset $row {RPTID VIDs}
            SQL "insert into ei_report (spname,RPTID,VIDs) values ('$spname',\
 '$RPTID','$VIDs')"
            }
        }
    return $reply
    }
