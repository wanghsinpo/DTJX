# $Header: /usr/cvsroot/gem/equip/eq_alarms.tcl,v 1.8 2002/11/01 15:57:14 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: eq_alarms.tcl,v $
# Revision 1.8  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.7  2001/11/15 17:03:49  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.6  2001/05/25 21:37:34  hume
# Backup restoration.
#
# Revision 1.6  2001/02/08 16:22:09  hume
# Fixed minor bugs when host uses unknown ALID.
#
# Revision 1.5  2000/12/03 14:22:03  hume
# Fixed eq_VV_item handling of lists and vectors.  Existing varmethod procs
# that returned lists were fixed to only return the data items, and the
# resulting value is no longer improperly nested as {L:1 {L:n ...}}.
#
# Revision 1.4  1999/01/13 15:46:01  hume
# New alarm types are enabled when added.
#
# Revision 1.3  1999/01/12 22:41:32  hume
# Added spooling functionality.
#
# Revision 1.2  1998/11/17 13:21:19  hume
# Converted while 1 to while {1} for better runtime performance.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#

#
# guidance - number your alarms from 1000-2999 by twos
#            use the ALID for the set_CEID
#            use the ALID+1 for the clear_CEID
#
# The requirement is that you choose CEID's that do not conflict
# with other events.

###################### eq_alarm_add ###############################
###################### eq_alarm_add ###############################
###################### eq_alarm_add ###############################
# convenience function to add an alarm definition and its related 
# collection event definitions
proc eq_alarm_add {spname ALID ALTX} {
    set set_CEID $ALID
    set clear_CEID [expr $ALID+1]
    SQL "insert into ei_alarm (spname,ALID,ID_TSN,set_CEID,clear_CEID,ALTX,is_enabled)\
 values ('$spname', $ALID, 'U4',$set_CEID, $clear_CEID, '$ALTX',1)"
    SQL "insert into ei_event (spname, CEID, ID_TSN, is_reported,\
 description) values ('$spname', '$set_CEID', 'U4', 1, 'Alarm Set: $ALTX')"
    SQL "insert into ei_event (spname, CEID, ID_TSN, is_reported,\
 description) values ('$spname', '$clear_CEID', 'U4', 1, \
 'Alarm Clr: $ALTX')"
    }
###################### eq_alarmtab_init ###########################
###################### eq_alarmtab_init ###########################
###################### eq_alarmtab_init ###########################
#
#  This procedure is called to activate the usual processing and
#   and reporting of alarms.  The latter is triggered by updates
#   to the is_set field in the ei_alarm table.  In other words, the
#   equipment "reports" or "clears" an alarm by updating the is_set
#   field to 1 or 0, and the gem logic is activated by subscription
#
proc eq_alarmtab_init {spname} {
    # you always get keys without asking for them
    SQL "open sub eq_gem_alarmsub to ei_alarm proc=eq_gem_alarmsub\
 update is_set where spname='$spname'"
    }

###################### eq_gem_alarmsub ############################
###################### eq_gem_alarmsub ############################
###################### eq_gem_alarmsub ############################
#
# called by subscription because the state of an alarm changed
#
proc eq_gem_alarmsub {notice table cols keys ct err data} {
    # we get called with just 1 row of data
    foreach row $data {
        vset $row $cols
        # now know ALID, spname, and is_set
        global $spname
        if { ![info exists ${spname}(comm_state)]\
 || [set ${spname}(comm_state)] == "DISABLED" } return
        # but need to know other fields
        set reply [SQL "select * from ei_alarm where spname='$spname' and ALID=$ALID"]
        set rcols [lindex $reply 2]
        set rrow [lindex [lindex $reply 6] 0]
        vset $rrow $rcols
        # per gem update AlarmID DVVAL
        SQL "update ei_variable set varvalue='$ALID' where varname='AlarmID'\
 and spname='$spname'"
        if { $is_enabled } {
            set ALCD [expr $category & 0x7f]
            if { $is_set } { set ALCD [expr $ALCD | 0x80] }
            # comm may be down and/or spooling
            eq_checked_put $spname 5 1 0 "L {B $ALCD} {U4 $ALID} {A {$ALTX}}"
            }
        # per GEM, alarm set and alarm clear are separate collection events
        # and an integer ID is used
        if { $is_set } { set CEID $set_CEID }\
        else { set CEID $clear_CEID }
        # fire event and format reports while current values are current
        eq_gem_event $spname $CEID
        }
    }


#
# process and reply to S5F3R Enable/Disable Alarm Send
#
proc eq_alarm_enable {spname} {
    global $spname
    $spname whenmsg again
    set request [set ${spname}(lastrmsg)]
    set R [expr [string first R [set ${spname}(lastrSFR)]] > 0]
    # {L:2 {B:1 ALED} {x ALID}}
    rset $request {l {b ALED} {x ALID}}
    while {1} {
        if { $l != "L:2" || $b != "B:1" } { return [eq_S9_reply $spname 7] }
        if { [expr $ALED & 0x80] } { set is_enabled 1 }\
        else { set is_enabled 0 }
        set reply [SQL "update ei_alarm set is_enabled=$is_enabled\
 where spname='$spname' and ALID=$ALID"]
        if { [string first "//c 0" $reply] < 0 } break
        set ACKC5 {B 0}
        if $R { $spname put S5F4 $ACKC5 }
        return
        }
    set ACKC5 {B 64}
    if $R { $spname put S5F4 $ACKC5 }
    }


# process and reply to S5F5 List Alarms Request
# or S5F7 List Enabled Alarms Request
#
proc eq_alarm_list {spname} {
    global $spname
    $spname whenmsg again
    set request [set ${spname}(lastrmsg)]
    set where "where spname='$spname'"
    set use_list 0
    if { [string first 7 [set ${spname}(lastrSFR)]] > 0 } {
        set isS5F7 1
        append where " and is_enabled=1"
        } \
    else { set isS5F7 0 }
    if {!$isS5F7} {
        if { [string match "*:0" $request] } { }\
        else {
            # shift away type token
            set list [lreplace $request 0 0]
            # where ALID=x1 or ALID=x2 ...
            append where " and ( ALID=[join $list { or ALID=}] )"
            set use_list 1
            }
        }
    set cols "ALID category is_set ALTX"
    set data [SQL "select [join $cols ,] from ei_alarm $where"]
    set rows [lindex $data 6]
    set reply L
    foreach row $rows {
        vset $row $cols
        set ALCD [expr $category & 0x7f]
        if { $is_set } { set ALCD [expr $ALCD | 0x80] }
        set item "L {B $ALCD} {U4 $ALID} {A {$ALTX}}"
        if { $use_list } {
            set alm($ALID) $item
            }\
        else { lappend reply "L {B $ALCD} {U4 $ALID} {A {$ALTX}}" }
        }
    if { $use_list } {
        foreach ALID $list {
            if { [info exists alm($ALID)] } { lappend reply $alm($ALID) }\
            else { lappend reply "L {B} {U4 $ALID} {A}" } ;# does not exist
            }
        }
    if $isS5F7 { $spname put S5F8 $reply }\
    else { $spname put S5F6 $reply }
    }

####################### eq_AlarmsEnabled ######################
####################### eq_AlarmsEnabled ######################
####################### eq_AlarmsEnabled ######################
#    
# return the variable value of AlarmsEnabled 
#
proc eq_AlarmsEnabled {spname} {
    return [eq_AlarmsSelect "where spname='$spname' and is_enabled=1"]
    }
 
####################### eq_AlarmsSet ##########################
####################### eq_AlarmsSet ##########################
####################### eq_AlarmsSet ##########################
#    
# return the variable value of AlarmsSet
#
proc eq_AlarmsSet {spname} {
    return [eq_AlarmsSelect "where spname='$spname' and is_set=1"]
    }
    
####################### eq_AlarmsSelect #######################
####################### eq_AlarmsSelect #######################
####################### eq_AlarmsSelect #######################

# used to return {L ALID1..N} meeting criteria
# revised 12/2/00 to return only the data items of the above
proc eq_AlarmsSelect {where} {
    set reply [SQL "select ALID from ei_alarm $where"]
    set rows [lindex $reply 6]
    set reply {}
    foreach ALID $rows { lappend reply [list U4 $ALID] }
    return $reply
    }
    
    

