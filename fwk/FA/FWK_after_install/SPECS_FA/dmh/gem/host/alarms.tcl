# $Header: /usr/cvsroot/gem/host/alarms.tcl,v 1.13 2002/11/01 15:57:14 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: alarms.tcl,v $
# Revision 1.13  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.12  2002/07/22 16:56:07  hume
# Rewrote the alarms initialization to try harder and be more forgiving in
# trying to discover the alarm definitions.
#
# Revision 1.11  2002/01/19 14:08:21  hume
# Fixed the second reply check at the end of the ei_alarms_init proc.
#
# Revision 1.10  2002/01/16 21:40:36  hume
# Missing single quotes on alarm text update.
#
# Revision 1.9  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.8  2000/02/16 02:59:02  hume
# Moved variable and event table loading earlier in the initialization.
#
# Revision 1.7  1999/07/01 12:41:18  hume
# Had bug with blank alarm text.
#
# Revision 1.6  1999/05/27 18:23:20  hume
# Added braces on expressions per procheck.
#
# Revision 1.5  1999/04/15 12:36:06  hume
# Added cleansing of alarm text for quotes that interfere with SQL or VFEI.
#
# Revision 1.4  1999/04/06 18:32:58  hume
# Added startup configuration to disable asking for variable and alarm data
# during initialization to address problem of too much data/too slow a link.
#
# Revision 1.3  1997/11/06 14:32:57  hume
# Added redundant alarm initialization before online so alarm text definitions
# from past sessions are used if alarms are reported immediately upon online.
#
# Revision 1.2  1997/11/06 14:00:21  hume
# Modified ALID handling to accommodate I8 or U8 type.  Put close logic on
# ui subscriptions in case gemhost ui was dismissed.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#



# enable or disable specified (or all) alarm messages
# S5F3 {L:2 {B 1|0} <ALID>}
#   <ALID> == {Ux|Ix u|i}
#
# because the underlying S5F3 does not support 
# specifying a set of alarms
# we cannot guarantee complete success or failure
# except for the special cases of all alarms or 1 alarm
# which map to a single physical message
# 
# reply 
#  0 = ok
# non-zero = partial or total failure
#  TIMEOUT = partial or total failure
proc ei_alarm_enable {spname enable ALIDs} {
    set enable [expr {$enable}]
    set ecode $enable
    if { $enable != "0" } { set enable 1 ; set ecode 0x80 }
    set type [lindex [ei_ALID_type $spname] 0]
    set replies ""
    if { [llength $ALIDs] <= 1 } {
        set reply \
          [secs_xact $spname S5F3R "L:2 {B $ecode} {$type $ALIDs}"]
        set b [lindex $reply 1]
        if { $b == "0x00" } {
            set where "where spname='$spname'"
            if { [llength $ALIDs] == 1 } { append where " and ALID='$ALIDs'" }
            SQL "update ei_alarm set is_enabled=$enable $where"
            return 0
            }
        if { $reply == "TIMEOUT" } { return $reply }
        return 1
        }
    set rc 0
    foreach ALID $ALIDs {
        set reply \
            [secs_xact $spname S5F3R "L:2 {B $ecode} {$type $ALID}"]
        if { $reply == "TIMEOUT"} { return $reply }
        # expect ACKC5 {B:1 0x00}
        set b [lindex $reply 1]
        if { $b == "0x00" } {
            SQL "update ei_alarm set is_enabled=$enable \
 where spname='$spname' and ALID='$ALID'"
            }\
         else { incr rc }
         }
    return $rc
    }


#
# we need to know the TSN type of alarm IDs to
# ask about alarms
# this procedure deduces the ALID type
#  SECS ALID is Ux or Ix
#  gem ALID is Ux type
#  VFEI ALID is I4 type
#
proc ei_ALID_type {spname} {
    set possible_types "U4 I4 U2 U1 I2 I1 U8 I8"
    # do we know because its been configured?
    global $spname
    if { [info exists ${spname}(ALID_type)] } {
        return [set ${spname}(ALID_type)] }
    # do we know from prior experience?
    set reply [SQL "select ID_TSN from ei_alarm\
 where spname='$spname'"]
    # look at the first item, first row, of the data rows
    set ID_TSN [lindex [lindex [lindex $reply 6] 0] 0]
    if { $ID_TSN != "" } { 
        return [set ${spname}(ALID_type) $ID_TSN] }
    # unless configured to not use S5F7,
    # lets ask about enabled alarms which we can do
    # without knowing the type
    if { [info exists ${spname}(use_s5f7)] && ([set ${spname}(use_s5f7)] == 0) } {
        return $possible_types
        }
    set reply [secs_xact $spname S5F7R]
    # expect TIMEOUT or {L:m {L:3 <ALCD> <ALID> <ALTX>}*}
    vset [split [lindex $reply 0] :] "L m"
    if { $L == "L" && $m != "" && $m > 0 } {
        set L3 [lindex $reply 1]
        set ALID [lindex $L3 2]   ;# "U4:1 u"
        set ID_TSN [lindex [split $ALID " :"] 0]
        return [set ${spname}(ALID_type) $ID_TSN]
        }
     # well that did not work, so we return all possible types
     # and let the caller try them
     return $possible_types
     }

    
#
# create/refresh our ei_alarm table
# which we use to manage and track the equipment alarms
#
# This is called when the equipment is online
# so we can refresh/create the alarm information
#
proc ei_alarms_init {spname} {
    global $spname
    # Statements in ei_defaults have already created the alarm table
    # and populated it with saved alarm data such as descriptions.
    # These statements used to be executed in this procedure.

    # if we do not have records for alarms, we will try harder to discover them
    set knownct [lindex [SQL "select ALID from ei_alarm where spname='$spname'"] 4]
    # talk to the equipment, and see what alarms are enabled
    # and if any are, this will indicate the type of ALID if we
    # do not know it
    set foundnew 0
    set foundany 0
  if { ![info exists ${spname}(use_s5f7)] || [set ${spname}(use_s5f7)] } {
    set ${spname}(lastrSFR) ""
    set reply [secs_xact $spname S5F7R]
    # expect TIMEOUT or {L:m {L:3 <ALCD> <ALID> <ALTX>}*}
    # the default initialization has S5F7 turned on
    if { $reply == "TIMEOUT" } {
        set why [secs_xact_failure $spname]
        # give up cases - BAD_SEND == no connection
        if { $why == "BAD_SEND" } { return $reply }
        # if we try S5F5R below, there is no point in trying S5F7R to find the type code
        set ${spname}(use_s5f7) 0
        if { $why == "ABORTED" } { 
            # this could be non-standard failure if we do not know the alarms, so try S5F5R next
            if { $knownct > 0 } {return $reply }
            }
        # continue cases
        # NO_REPLY (T3 timeout) 
        if { $why == "NO_REPLY" } {
            if { $knownct > 0 } { return $reply } ;# disconnected SECS-I 
            # could be S9 primary is intended in lieu of a reply, but spooling is active
            # and therefore the primary does not get sent!!!
            # could be non-standard, confused equipment
            if { [set ${spname}(TRACE)] & 0x02 } {
                set ${spname}(trace) "T3 timeout accepted during S5F7R alarm discovery logic"
                }
            }
        # REJECTED - standard equipment that does not support S5F7 uses S9
        if { $why == "REJECTED" } {
            if { [set ${spname}(TRACE)] & 0x02 } {
                set ${spname}(trace) "S9 reply - This equipment does not support S5F7R"
                }
            }
        }\
    else {
        vset [split [lindex $reply 0] :] "L m"
        if { $L == "L" && $m != "" && $m > 0 } {
            set L3s [lreplace $reply 0 0]
            foreach L3 $L3s {
                rset $L3 {l3 {B alcd} {tID alid} {tTX altx}}
                if { $alid == "" } continue
                set ID_TSN [lindex [split $tID :] 0]
                if { $ID_TSN  == "" } continue
                if { $B == "B:0" } { set alcd 0 }\
                elseif { $alcd == "" } continue
                set alcd [expr {$alcd & 0x7f}]
                set foundany 1
                # change quotes that may interfere with VFEI or SQL usage
                regsub -all {[\'\"]} $altx \` altx
                set stmt "insert into ei_alarm (spname,ALID,ID_TSN,category,\
 is_enabled,ALTX) values ('$spname', '$alid', '$ID_TSN', $alcd, 1, '$altx')"
                set reply [SQL $stmt]
                if { [string first "//c 0" $reply] < 0 } {
                    set stmt "update ei_alarm set is_enabled=1 where\
 spname='$spname' and ALID='$alid'"
                    set reply [SQL $stmt]
                    if { [string first "//c 0" $reply] < 0 } {
                        error "cannot save enabled alarm data"
                        }
                    }\
                else { set foundnew 1 }
                }
            }
        }
    } ;# S5F7 
    if { (!$foundany || $foundnew) && \
 (![info exists ${spname}(use_s5f5)] || [set ${spname}(use_s5f5)]) } { 
        # we did not find any enabled alarms or
        # at least one of the enabled alarms was a new alarm
        # so we better try to find out about the alarms in general
        # because we do not seem to know about them already
        set ID_TSNs [ei_ALID_type $spname]
        # we may not even know the data type of ALIDs so we try them all
        set trymax [llength $ID_TSNs]
        set tryct 0
        foreach ID_TSN $ID_TSNs {
            incr tryct
            set ${spname}(lastrSFR) ""
            set reply [secs_xact $spname S5F5R $ID_TSN]
            if { $reply == "TIMEOUT" } {
                if { $tryct >= $trymax } { return $reply ;# failure }
                set why [secs_xact_failure $spname]
                # give up cases
                if { $why == "BAD_SEND" } { return $reply }
                if { $why == "ABORTED" } { return $reply }
                if { $why == "NO_REPLY" } {
                    if { [set ${spname}(TRACE)] & 0x02 } {
                        set ${spname}(trace) "T3 timeout during S5F5R alarm discovery logic"
                        }
                    if { $knownct == 0 } { 
                        # could have S9 primary being spooled and not sent as a reply
                        # could have non-standard confused equipment
                        if { [set ${spname}(TRACE)] & 0x02 } {
                            set ${spname}(trace) "accepting T3 and retrying S5F5R alarm discovery"
                            }
                        continue
                        }\
                    else { return $reply }
                    }
                # unknown Stream or Function - give up
                if { [set ${spname}(lastrSFR)] == "S9F5" || [set ${spname}(lastrSFR)] == "S9F3" } { 
                    return $reply
                    }
                # REJECTED for data, S9F7 is ok
                continue   ;# try another type code
                }\
            else {
                # got a data response
                # but keep trying if there is no data in the data response
                if { $tryct < $trymax } {
                    # we have seen non-standard equipment with a blank reply
                    # L:0 is a possible reply for the wrong alarm type code
                    if { [llength $reply] <= 1 } {
                        if { [set ${spname}(TRACE)] & 0x02 } {
                            set ${spname}(trace) "S5F5R alarm discovery retrying after empty reply"
                            }
                        continue
                        }
                    }
                }
            break   ;# got a data response
            }
        # if we got a valid data reply, populate/update the table
        vset [split [lindex $reply 0] :] "L m"
        if { $L == "L" && $m != "" && $m > 0 } {
            set L3s [lreplace $reply 0 0]
            foreach L3 $L3s {
                rset $L3 {l3 {B alcd} {tID alid} {tTX altx}}
                if { $alid == "" } continue
                set ID_TSN [lindex [split $tID :] 0]
                if { $ID_TSN  == "" } continue
                if { $B == "B:0" } { set alcd 0 ; set is_set 0}\
                elseif { $alcd == "" } continue \
                else {
                     if { [expr {$alcd & 0x80}] } { set is_set 1 }\
                     else { set is_set 0 }
                     set alcd [expr {$alcd & 0x7f}]
                     }
                # change quotes that may interfere with VFEI or SQL usage
                regsub -all {[\'\"]} $altx \` altx 
                # if the insert works, the alarm must not be enabled
                set stmt "insert into ei_alarm (spname,ALID,ID_TSN,\
 category, is_set,is_enabled,ALTX) values ('$spname', '$alid', '$ID_TSN',\
 $alcd, $is_set, 0, '$altx')"
                set reply [SQL $stmt]
                if { [string first "//c 0" $reply] < 0 } {
                    # the insert did not work, we do not touch is_enabled
                    set stmt "update ei_alarm set is_set=$is_set,\
 ALTX='$altx' where spname='$spname' and ALID='$alid'"
                    set reply [SQL $stmt]
                    if { [string first "//c 0" $reply] < 0 } {
                        error "cannot save alarm list data"
                        }
                    }
                }
            # save the newly discovered data for next time
            #SQL "write over ei_alarm"
            }
        }
    }

#################### ei_alarm_setup #########################
#################### ei_alarm_setup #########################
#################### ei_alarm_setup #########################
#
# take the configuration data in ei_alarms and enable/disable
# the reporting of alarms accordingly.
#
# returns 0=ok 1=failure
proc ei_alarm_setup spname {
    global $spname
    foreach way {1 0} {
        set reply [SQL "select ALID from ei_alarm where\
 spname='$spname' and host_managed=1 and host_wants_enabled=$way"]
        set ALIDs [lindex $reply 6]
        if { [llength $ALIDs] } {
            set reply [ei_alarm_enable $spname $way $ALIDs]
            if { $reply != 0 } { return 1 }
            }
        }
    return 0
    }
    
    
#################### ei_alarm_report ########################
#################### ei_alarm_report ########################
#################### ei_alarm_report ########################
# equipment is reporting a S5F1
proc ei_alarm_report spname {
    global $spname
    # optional reply requested
    if { [string first R [set ${spname}(lastrSFR)]] > 0 } {
        $spname put S5F2 {B 0}
        }
    # expect {L:3 <ALCD> <ALID> ALTX>}
    rset [set ${spname}(lastrmsg)] {l3 {B alcd} {tID alid} {tTX altx}}
    if { $l3 != "L:3" } return
    if { [expr {$alcd & 0x80}] } { set is_set 1 }\
    else { set is_set 0 }
    # we should already have this alarm in our table
    # we will use configured text if the altx comes up blank
    if { $altx == "" } {
        # altx is blank - see if we have configured text for the alarm_log
        set altx [lindex [lindex [lindex [SQL "select ALTX from ei_alarm where\
 spname='$spname' and ALID='$alid'"] 6] 0] 0]
        }
    if { $altx != "" } {
        # change quotes that may interfere with VFEI or SQL usage
        regsub -all {[\'\"]} $altx \` altx
        set phrase ", ALTX='$altx'" 
        } \
    else { set phrase "" }
    set stmt "update ei_alarm set is_set=$is_set,is_enabled=1 $phrase\
  where spname='$spname' and ALID='$alid'"
    set reply [SQL $stmt]
    if { [string first "//c 0" $reply] < 0 } {
        # update did not work, so do insert
        set ID_TSN [lindex [split $tID :] 0]
        set alcd [expr {$alcd & 0x7f}]
        set stmt "insert into ei_alarm (spname,ALID,ID_TSN,\
 category, is_set,is_enabled,ALTX) values ('$spname', '$alid', '$ID_TSN',\
 $alcd, $is_set, 1, '$altx')"
        SQL $stmt
        }
    SQL "insert into ei_alarm_log (spname, clock, ALID, is_set,ALTX)\
 values ('$spname', '[secs_CLOCK $spname]', '$alid', $is_set, '$altx')"

    # VFEI event reports and the like are created by subscriptions 
    } 
