# $Header: /usr/cvsroot/gem/equip/eq_events.tcl,v 1.9 2004/11/19 20:17:32 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: eq_events.tcl,v $
# Revision 1.9  2004/11/19 20:17:32  hume
# new events 4035, 4091, 4093 per E30-1103 - 4035 not directly listed but
# implied by requirements.
#
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
# Revision 1.6  2001/02/08 15:41:27  hume
# Fixed reply to S6F17 - was sending S6F16 instead of S6F18.
#
# Revision 1.5  2000/12/03 14:22:03  hume
# Fixed eq_VV_item handling of lists and vectors.  Existing varmethod procs
# that returned lists were fixed to only return the data items, and the
# resulting value is no longer improperly nested as {L:1 {L:n ...}}.
#
# Revision 1.4  2000/01/26 19:44:29  hume
# Updated logic for unknown variables and empty report assoc. per SEMI
# Draft 3088 12/30/99 - even though not yet approved, beneficial changes.
#
# Revision 1.3  1999/01/22 15:51:46  hume
# Added missing GEM events and variable to provide event descriptions.
#
# Revision 1.2  1999/01/12 22:41:32  hume
# Added spooling functionality.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#
#
# Collection Event Reporting
#
#   CEID <<---->> RPTID <<---->> VID
#
# S2F33 - assoc RPTID <<-->> VID, optionally cascade delete RPTID <<-->> CEID
# S2F35 - assoc RPTID <<-->> CEID
# S2F37 - enable/disable CEID
# S2F39 multiblock inq 
#
# Equipment constant AnnotateEventReports Boolean
#   if true send S6F13 else send S6F11
#
# per gem CEID is unsigned numeric -> use U4
# per gem RPTID is unsigned numeric -> use U4
# but we make this schema workable for non-GEM

# S6F5 multiblock inq
# S6F11 event report
# S6F13 annotated event report


########################## eq_eventtab_init ######################
########################## eq_eventtab_init ######################
########################## eq_eventtab_init ######################
# "gem" events that we define have CEID's 4000-4999
# custom events that you define should have CEID's that do not
#   conflict with CEID's needed for alarms.  Suggest you use
#   CEID's of 5000-9999
#
#  Processing Started, Completed, and Stopped are redundant
#    with Process State Change so we default them to off
#
#  Spooling Activated and Spool Transmit Failure cannot be
#   received by the host as they occur so we default them to off.
# 
#  "Process Program Invalid" - recently added as standard way to
#    signal that a downloaded PP in not proper.  Set the PPError
#    DVVAL and signal this event when verification/validation fail.
#    This feature is described and required by GEM but not listed 
#    as a required event.
#
proc eq_eventtab_init {spname} {
    set cols {CEID ID_TSN is_reported description}
    set data [list \
 [list 4000 U4 0 "Control State OFF-LINE"]\
 [list 4001 U4 1 "Control State LOCAL"]\
 [list 4002 U4 1 "Control State REMOTE"]\
 [list 4005 U4 1 "Material Received"]\
 [list 4006 U4 1 "Material Removed"]\
 [list 4015 U4 1 "Operator Command Issued"]\
 [list 4020 U4 1 "Operator Equipment Constant Change"]\
 [list 4030 U4 1 "Process Program Change"]\
 [list 4035 U4 1 "Process Program Invalid"]\
 [list 4040 U4 1 "Process Program Selected"]\
 [list 4047 U4 0 "Processing Started"]\
 [list 4048 U4 0 "Processing Completed"]\
 [list 4049 U4 0 "Processing Stopped"]\
 [list 4050 U4 1 "Process State Update"]\
 [list 4080 U4 0 "Spooling Activated"]\
 [list 4081 U4 1 "Spooling Deactivated"]\
 [list 4083 U4 0 "Spool Transmit Failure"]\
 [list 4091 U4 0 "Stream 15 Execution Recipe - New"]\
 [list 4093 U4 0 "Stream 15 Execution Recipe - Change"]\
 [list 4100 U4 1 "Terminal Services Operator Display Acknowledge"]\
 ]
    foreach item $data {
        vset $item $cols
        SQL "insert into ei_event (spname,[join $cols ,]) values\
 ('$spname', '$CEID', '$ID_TSN', $is_reported, '$description')"
        }
    }


##################### eq_report_enable ##########################
##################### eq_report_enable ##########################
##################### eq_report_enable ##########################
#
# recd S2F37 Enable/Disable Event Report
#
# {L:2 {TF enable} {L:n <CEID>n}}
#
proc eq_report_enable spname {
    global $spname
    set request [set ${spname}(lastrmsg)]
    set enabled [lindex [lindex $request 1] 1]
    set IDs [lindex $request 2]
    if { $IDs == "L:0" } { set where "where spname='$spname'" }\
    else {
        set IDs [lreplace $IDs 0 0]
        set CEIDs ""
        foreach pair $IDs {
            lappend CEIDs [lindex $pair 1]
            }
        set where "where (spname='$spname') and (\
  CEID='[join $CEIDs {' or CEID='}]')"
        # have to make sure each CEID exists
        set reply [SQL "select CEID from ei_event $where"]
        set ct [lindex $reply 4]
        if { $ct < [llength $IDs] } {
            $spname put S2F38 {B 2}
            return
            }
        }
    set reply [SQL "update ei_event set is_reported=$enabled $where"]
    $spname put S2F38 {B 0}
    }

#################### eq_EventsEnabled ###########################
#################### eq_EventsEnabled ###########################
#################### eq_EventsEnabled ###########################
#
# EventsEnabled variable value ref E5-95 p 72
# used to return {L:n <CEID> } of the events enabled for reporting
# revised 12/2/00 to return only the data items of the {L:n [<CEID>]*}
proc eq_EventsEnabled spname {
    set reply [SQL "select CEID,ID_TSN from ei_event where \
 is_reported=1 and spname='$spname'"]
    set result {}
    set rows [lindex $reply 6]
    foreach row $rows {
        vset $row "CEID ID_TSN"
        lappend result [list $ID_TSN $CEID]
        }
    return $result
    }

###################### eq_EventDescriptions #####################
###################### eq_EventDescriptions #####################
###################### eq_EventDescriptions #####################
#
# Not required by GEM or E5 - provide a list of all events and
# their descriptions.  This variable fills a major void in SECS/GEM
# functionality.
# new 1/22/99
# used to return {L:n {L:2 <CEID> {A $description}}
# revised 12/2/00 to return only the data items of the above
proc eq_EventDescriptions spname {
    set reply [SQL "select CEID,ID_TSN, description from ei_event where \
 spname='$spname'"]
    set result {}
    set rows [lindex $reply 6]
    foreach row $rows {
        vset $row "CEID ID_TSN desc"
        lappend result [list L [list $ID_TSN $CEID] [list A $desc]]
        }
    return $result
    }
    
##################### eq_report_define ##########################
##################### eq_report_define ##########################
##################### eq_report_define ##########################
#
# recd S2F33 Define Report
#
# {L:2 <DATAID> {L:a {L:2 <RPTID> {L:b <VID>b}}a }
#      a == 0 means delete report definitions and links to CEIDs
#      b == 0 means delete <RPTID> and associated links to CEIDs 
#
# reply B 0=ok, 2=bad format, 3=RPTID already defined, 4=bad VID
proc eq_report_define {spname} {
    global $spname
    set request [set ${spname}(lastrmsg)]
    set La [lindex $request 2]
    if { $La == "L:0" } {
        SQL "delete from ei_event_report where spname='$spname'"
        SQL "delete from ei_report where spname='$spname'"
        $spname put S2F34 {B 0}
        return
        }
    set stmts ""
    set rc 0
    set La [lreplace $La 0 0]
    foreach L2 $La {
        set RPTID [lindex [lindex $L2 1] 1]
        if { ![is_unsigned $RPTID] } { set rc 2 ; break }
        set Lb [lindex $L2 2]
        if { $Lb == "L:0" } {
            foreach table {ei_event_report ei_report} {
                lappend stmts "delete from $table where\
 spname='$spname' and RPTID='$RPTID'"
                }
            }\
        else {
            # the RPTID should not already be defined
            set ct [lindex [SQL "select RPTID from ei_report where\
 spname='$spname' and RPTID='$RPTID'"] 4]
            if { $ct > 0 } { set rc 3 ; break }
            set Lb [lreplace $Lb 0 0]
            set VIDs ""
            foreach item $Lb { lappend VIDs [lindex $item 1] }
            # all VIDs must exist
            set where "where spname='$spname' and\
 (varID='[join $VIDs {' or varID='}]')"
            set ct [lindex [SQL "select varID from ei_variable $where"] 4]
            if { $ct < [llength $VIDs] } { set rc 4 ; break }
            lappend stmts SQL "insert into ei_report \
 (spname,RPTID, VIDs) values ('$spname', '$RPTID', '$VIDs')"
            }
        }
    if { $rc == 0 } {
        # commit
        foreach stmt $stmts { SQL $stmt }
        }

    $spname put S2F34 "B $rc"
    }


####################### eq_report_assoc ##########################
####################### eq_report_assoc ##########################
####################### eq_report_assoc ##########################
#
# recd S2F35 Link Event Report
# {L:2 <DATAID> {L:a {L:2 <CEID> {L:b <RPTID>b}}a } }
#            
#  reporting for the CEID is to be disabled
#  b == 0 means disassociate links to the CEID
#
# <LRACK> 0=ok, 3=CEID already linked, 4=bad CEID, 5=bad RPTID 
#
proc eq_report_assoc spname {
    global $spname
    set request [set ${spname}(lastrmsg)]
    set rc 0
    set stmts ""
    set La [lindex $request 2]
    if { $La == "L:0" } {
        # SEMI 3088 12/30/99 a==0 deletes all report links for all CEIDs
        # and disables all CEIDs  - being voted on
        # we will do it since doing it is not non-standard no matter what the vote
        # OEM can comment this out 
        # delete linked reports
        lappend stmts "delete from ei_event_report where spname='$spname'"
        # disable all reports
        lappend stmts "update ei_event set is_reported=0 where spname='$spname'"
        }
    set L2s [lreplace $La 0 0]
    foreach L2 $L2s {
        set CEID [lindex [lindex $L2 1] 1]
        set where "where spname='$spname' and CEID='$CEID'"
        set Lb [lindex $L2 2]
        set ct [lindex [SQL "select CEID from ei_event $where"] 4]
        if { $ct != 1 } { set rc 4 ; break }
        # "linked event reports will default to 'disabled' upon linking
        lappend stmts "update ei_event set is_reported=0 $where"
        if { $Lb == "L:0" } {
            lappend stmts "delete from ei_event_report $where"
            continue
            }
        set RPTIDs [lreplace $Lb 0 0]
        foreach item $RPTIDs {
            set RPTID [lindex $item 1]
            if { ![is_unsigned $RPTID] } { set rc 5 ; break }
            set ct [lindex [SQL "select RPTID from ei_report \
 where spname='$spname' and RPTID='$RPTID'"] 4]
            if { $ct != 1 } { set rc 5 ; break }
            lappend stmts "insert into ei_event_report\
 (spname, CEID, RPTID) values ('$spname', '$CEID', '$RPTID')"
            }
        if { $rc != 0 } break
        }
    if { $rc == 0 } {
        foreach stmt $stmts { SQL $stmt }
        }
    $spname put S2F36 "B $rc"
    }


###################### eq_report_data #########################
###################### eq_report_data #########################
###################### eq_report_data #########################
#
# provide the SECS-II message of a plain or annotated report
# per gem we assume that VIDs and RPTIDs are type U4
#
#     plain: {L:n Vn}
# annotated: {L:n {L:2 VID V}n }
#
#
proc eq_report_data {spname RPTID annotate} {
    set reply [SQL "select VIDs from ei_report where\
 spname='$spname' and RPTID='$RPTID'"]
    set result L
    set VIDs [lindex [lindex [lindex $reply 6] 0] 0]
    foreach VID $VIDs {
        set value [eq_VV_item $spname $VID] 
        if $annotate { lappend result [list L:2 "U4 $VID" $value] }\
        else { lappend result $value }
        }
    return $result
    }

##################### eq_report_IRR ###########################
##################### eq_report_IRR ###########################
##################### eq_report_IRR ###########################
#
# on S6F19 <RPTID>
# return plain report data
#
proc eq_report_IRR spname {
    global $spname
    set RPTID [lindex [set ${spname}(lastrmsg)] 1]
    $spname put S6F20 [eq_report_data $spname $RPTID 0]
    }

##################### eq_report_AIRR ###########################
##################### eq_report_AIRR ###########################
##################### eq_report_AIRR ###########################
#
# on S6F21 <RPTID>
# return annotated report data
#
proc eq_report_AIRR spname {
    global $spname
    set RPTID [lindex [set ${spname}(lastrmsg)] 1]
    $spname put S6F22 [eq_report_data $spname $RPTID 1]
    }

##################### eq_report_ERR ###########################
##################### eq_report_ERR ###########################
##################### eq_report_ERR ###########################
#
# on S6F15 <CEID>
# return plain event data
#
proc eq_report_ERR spname {
    global $spname
    set CEID [lindex [set ${spname}(lastrmsg)] 1]
    $spname put S6F16 [eq_event_data $spname $CEID 0]
    }

##################### eq_report_AERR ###########################
##################### eq_report_AERR ###########################
##################### eq_report_AERR ###########################
#
# on S6F17 <CEID>
# return annotated event data
#
proc eq_report_AERR spname {
    global $spname
    set CEID [lindex [set ${spname}(lastrmsg)] 1]
    $spname put S6F18 [eq_event_data $spname $CEID 1]
    }

######################### eq_event_data #######################
######################### eq_event_data #######################
######################### eq_event_data #######################
#
# prepare data of an event
# we set the ID type to U4 per gem
#
proc eq_event_data {spname CEID annotate} {
    set result L:3
    set DATAID [list U4 $CEID]	;# maintain sync with eq_gem_event
    # CEID == DATAID
    lappend result $DATAID $DATAID 
    set reportlist L
    set reply [SQL "select RPTID from ei_event_report where\
 spname='$spname' and CEID='$CEID'"]
    set rows [lindex $reply 6]
    foreach RPTID $rows {
        lappend reportlist [list L:2 [list U4 $RPTID] [eq_report_data $spname $RPTID $annotate]]
        }
    lappend result $reportlist
    return $result
    }
  
######################### eq_gem_event ########################
######################### eq_gem_event ########################
######################### eq_gem_event ########################
######################### eq_gem_event ########################
######################### eq_gem_event ########################
#
# process a collection event by transmitting associated reports
#
# The low level code will get the reply and throw it away.
# Also, if MULT is false, the low level code will enforce
# transaction serialization.
#
proc eq_gem_event {spname CEID} {
    global $spname
    if { ![info exists ${spname}(comm_state)]\
 || [set ${spname}(comm_state)] == "DISABLED" } return

    set reply [SQL "select is_reported from ei_event\
 where spname='$spname' and CEID='$CEID'"]
    vset [lindex [lindex $reply 6] 0] "is_reported"
    if { $is_reported != "1" } return
    # do we AnnotateEventReports ?
    set annotate [lindex [eq_VV_item $spname 220] 1]
    if { $annotate == "" } { set annotate 1 }

    set result [eq_event_data $spname $CEID $annotate]
    set DATAID [list U4 $CEID]	;# maintain sync with eq_event_data

    if {$annotate} {
        eq_checked_put $spname 6 13 1 $result $DATAID
        }\
    else {
        eq_checked_put $spname 6 11 1 $result $DATAID
        }
    }

#
# if we get permission, send a multiblock event report
# provide for spooling if the put fails
#
proc eq_report_mult {spname sfr report} {
    global $spname
    set code [lindex [set ${spname}(lastrmsg)] 1]
    if { $code == "0x00" } {
        $spname put $sfr $report [list eq_checked_put_cb $report]
        }
    }
