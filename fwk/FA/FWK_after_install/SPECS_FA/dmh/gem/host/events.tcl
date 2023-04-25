# $Header: /usr/cvsroot/gem/host/events.tcl,v 1.24 2004/11/19 20:26:45 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997, 2001 Hume Integration Software
# All Rights Reserved
#
# $Log: events.tcl,v $
# Revision 1.24  2004/11/19 20:26:45  hume
# Updated event discovery to also try EVENTSENABLED variable name.
#
# Revision 1.23  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.22  2002/09/24 18:23:15  hume
# Updated ei_report_define to preserve the caller's variable ordering, and
# to updating the ei_report record if it already exists.
#
# Revision 1.21  2002/09/24 15:56:20  hume
# Updated calls to ei_var_query to explicitly call with a list of names.
# Sets a proper example, and fixes a bug with ei_event_discovery when
# EventsEnabled variable name contains white space.
#
# Revision 1.20  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.19  2001/05/25 21:37:34  hume
# Backup restoration.
#
# Revision 1.19  2001/02/02 19:44:05  hume
# Revised status variable save logic - can save values that are larger than
# the ei_variable table varvalue field size. (Fixes big EventDescriptions).
#
# Revision 1.18  2001/01/26 22:27:23  hume
# If the equipment only had 1 event type, the event_discovery routine had a
# parsing bug which was found when the code was copied as an example.
#
# Revision 1.17  2000/12/12 22:19:49  hume
# Modified last change to work with plural interfaces.
#
# Revision 1.16  2000/12/12 21:38:10  hume
# Changes to keep (control_state) in sync with the equipment. New
# CEID_OFFLINE variable is used to specify the control state offline event.
#
# Revision 1.15  2000/12/03 19:16:08  hume
# Updated event report and trace report handling for vector or list data.
#
# Revision 1.14  2000/12/03 14:28:27  hume
# Fixed parsing bug for data items that are lists or vectors.  Handling of
# EventDescription variable (when defined) works for {L:1 {L:n ...}} format
# or newer format {L:n ...} which is consistent with similar GEM variables.
#
# Revision 1.13  2000/02/16 02:59:02  hume
# Moved variable and event table loading earlier in the initialization.
#
# Revision 1.12  1999/06/11 12:50:10  hume
# Bug fix for non-annotated event reports of more than 1 variable.
#
# Revision 1.11  1999/05/27 18:25:29  hume
# Added braces per procheck scan.
#
# Revision 1.10  1999/04/20 14:48:06  hume
# S2F33 needed to have DATAID based on partners type.
#
# Revision 1.9  1999/04/13 12:15:16  hume
# Needed to call VFEIname for new events to strip whitespace, etc.
#
# Revision 1.8  1999/04/09 20:42:04  hume
# Disabling event reports can now handle non-GEM equipment that rejects
# S2F37.
#
# Revision 1.7  1999/01/22 18:56:33  hume
# Fixed situation where you explicitly disable 1 or more events and they get
# enabled because an empty list is sent to enable.  We still enable all events
# if the user/host has not explicitly enabled or disabled any.
#
# Revision 1.6  1999/01/22 18:23:50  hume
# Added R's to two secs_xact calls even though secs_xact adds it in.
#
# Revision 1.5  1998/11/17 20:27:40  hume
# Fixed mispelling in event description.
#
# Revision 1.4  1998/11/17 13:21:22  hume
# Converted while 1 to while {1} for better runtime performance.
#
# Revision 1.3  1998/11/12 22:22:55  hume
# Added event discovery procedure and UI button.
#
# Revision 1.2  1998/08/06 17:44:05  hume
# Fixed two bugs in the unformatted event report handler.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#

####################### ei_event_init ##############################
####################### ei_event_init ##############################
####################### ei_event_init ##############################
#
# tables to manage events -
# the mapping of VFEInames <-> CEID must be done custom
#
proc ei_event_init spname {
    global $spname
    # loading saved data used to occur in this procedure, but it was
    # moved to ei_defaults to occur earlier, before any event reports 
    # are received.
    # create tables, no harm if they aleady exist
    #ei_eventtab_create $spname
    # if we have saved data from the past, load it in
    # if these rows already exists, they do not overwrite existing rows
    # because of uniqueness constraints
    #SQL "include ei_event.tab"
    #SQL "include ei_event_report.tab"
    #SQL "include ei_report.tab"
    #SQL "include ei_report_cfg.tab"
    #SQL "include ei_event_report_cfg.tab"
    # there is no way to automatically gather event data

    # fix incomplete configurations
    SQL "update ei_event set event_class='EQ' where\
 spname='$spname' and event_class=''"

    # Here are events synthesized by the driver.  If they already
    # exist, fine.
    SQL "insert into ei_event (spname,CEID,ID_TSN,is_reported,description,\
 VFEIname,event_class,host_managed,host_wants_enabled) values (\
 '$spname','COM_ENABLE','A',1, 'Communication has been established', \
 'COM_ENABLE', 'SECS_DRVR',1,1)"
    SQL "insert into ei_event (spname,CEID,ID_TSN,is_reported,description,\
 VFEIname,event_class,host_managed,host_wants_enabled) values (\
 '$spname','COM_DISABLE','A',1, 'Communication has been lost', \
 'COM_DISABLE','SECS_DRVR',1,1)"
    # the AUTO_SECS_INIT event provides a way to report the success or
    # failure of an automatic initialization.
    SQL "insert into ei_event (spname,CEID,ID_TSN,is_reported,description,\
 VFEIname,event_class,host_managed,host_wants_enabled) values (\
 '$spname','AUTO_SECS_INIT','A',1, 'Automatic online initialization', \
 'AUTO_SECS_INIT','SECS_DRVR',1,1)"
    # we handle TRACE_REPORTs as a kind of event and add them to the log
    SQL "insert into ei_event (spname,CEID,ID_TSN,is_reported,description,\
 VFEIname,event_class,host_managed,host_wants_enabled) values (\
 '$spname','TRACE_REPORT','A',1, 'S6F1 Trace Data received', \
 'TRACE_REPORT','SECS_DRVR',1,1)"

    # listen for the event that means the control_state is going OFF-LINE
    # we use the variable value for "CEID_OFFLINE" to specify the CEID
    # You can configure your own CEID_OFFLINE in the ei_variable table 
    # We do not see your configured value until you save table ei_variable and restart
    # lindex is used to separate value from type information for 1st pair in list
    set CEID_OFFLINE [lindex [lindex [ei_var_query $spname [list CEID_OFFLINE] varname 0] 0] 1]
    if { $CEID_OFFLINE == {} } {
        set CEID_OFFLINE 4000 ;# works for Hume gemsim without a save and restart
        }
    set ${spname}(CEID_OFFLINE) $CEID_OFFLINE
    # One sub is used by all host interfaces in this process.
    # It would be slightly more efficient to change the where clause of the subscriptions
    # to only subscribe to the CEIDs that mean offline for the various equipment.
    # The overhead of the subscription procedure is very small so its not so important.
    SQL "open sub ei_event_offline to ei_event_log proc=ei_event_offline insert spname,CEID"
    # the subscription logic updates ${spname}(control_state) 
    }

########################## ei_event_disable ########################
########################## ei_event_disable ########################
########################## ei_event_disable ########################
# 
# disable event reports and if indicated, cascade delete associated
#   reports
# if evlist is empty, disable all
# some are equipment based, some are not
#
# returns 0=ok, 1=denied, other error code, or TIMEOUT
proc ei_event_disable {spname evlist {cascade 0}} {
   global $spname
   set len [llength $evlist]
   if { $len == 0 } {
       # First, turn off all event reports
       set reply [secs_xact $spname S2F37R {L:2 {TF 0} L:0}]
       if { $reply == "B:1 0x00" } {
           SQL "update ei_event set is_reported=0 where spname='$spname'"
           # now discard report definitions
           if {$cascade} {
               set reply [secs_xact $spname S2F33R [list L [ei_dataid $spname] L]]
	       # defined reports may not be supported 
	       if { $reply == "TIMEOUT" } { 
		   set why [secs_xact_failure $spname]
		   if { $why == "REJECTED" } {
		       # if the machine does not do reports 
		       # that is equivalent to them being deleted!
		       set reply "B:1 0x00"
		       }
                   }
               if { $reply == "B:1 0x00" } {
                   SQL "delete from ei_event_report where spname='$spname'"
                   SQL "delete from ei_report where spname='$spname'"
                   }
               }
           }
        if { $reply == "TIMEOUT" } { return $reply }
        return [expr [lindex $reply 1]]
        }
    # disable specified list
    # equipment based
    set where_eq "where spname='$spname' and event_class='EQ' and \
 ((VFEIname='[join $evlist {' or VFEIname='}]') or \
  (CEID='[join $evlist {' or CEID='}]'))"
    # plus others
    set where "where spname='$spname' and \
 ((VFEIname='[join $evlist {' or VFEIname='}]') or \
  (CEID='[join $evlist {' or CEID='}]'))"
    set reply_eq [SQL "select ID_TSN,CEID from ei_event $where_eq"]
    set reply [SQL "select ID_TSN,CEID from ei_event $where"]
    set ct [lindex $reply 4]
    if { $ct < $len } {
        return 1 ;# ERACK denied, at least 1 does not exist
        }
    # first turn off the events
    set CEIDs [lindex $reply_eq 6]
    set reply [secs_xact $spname S2F37R "L:2 {TF 0} {L $CEIDs}"]
    if { $reply == "B:1 0x00" } {
        SQL "update ei_event set is_reported=0 $where"
        if {$cascade} {
            # figure out what RPTIDs are connected to these CEIDs
            # and not connected to other CEIDs
            set CEIDs [lindex [SQL "select CEID from ei_event $where_eq"] 6]
            set where "where spname='$spname' and \
 (CEID='[join $CEIDs {' or CEID='}]')"
            # get associated RPTIDs
            set RPTIDs [lindex [SQL "select RPTID from ei_event_report\
 $where"] 6]
            if { [llength $RPTIDs] == 0 } { return 0 }
            # compute subset that is shared
            set wRPT "RPTID='[join $RPTIDs {' or RPTID='}]'"
            set wCEID "NOT (CEID='[join $CEIDs {' or CEID='}]')"
            set where2 "where spname='$spname' and ($wRPT) and $wCEID"
            set shared [lindex [SQL "select RPTID from ei_event_report\
 $where2"] 6]
            # take original list and removed the ones that are shared
            set deletelist ""
            foreach RPTID $RPTIDs {
                if { [lsearch -exact $shared $RPTID] >= 0 } continue
                lappend deletelist $RPTID
                }
            if { [llength $deletelist] == 0 } { return 0 }
            # delete at equipment
            set msg ""
            foreach RPTID $deletelist {
                lappend msg "L:2 {[ei_RPTID_TSN $spname] $RPTID} L:0"
                }
            set msg "L:2 {[ei_dataid $spname]} {L $msg}"
            set reply [secs_xact $spname S2F33R $msg]
            # expect DRACK 
            if { $reply == "B:1 0x00" } {
                set wRPT "RPTID='[join $deletelist {' or RPTID='}]'"
                set where "where spname='$spname' and $wRPT"
                SQL "delete from ei_report $where"
                SQL "delete from ei_event_report $where"
                return 0
                }
            # the disabling went ok but the cascade delete had problems
            if { $reply != "TIMEOUT" } { set reply [expr [lindex $reply 1]] }
            if { $reply == "2" } {
               error "debug me - invalid format S2F33 $msg"
               }
            }
        return 0
        }
    if { $reply != "TIMEOUT" } { set reply [expr [lindex $reply 1]] }
    return $reply
    }

######################### ei_event_enable #######################
######################### ei_event_enable #######################
######################### ei_event_enable #######################
# enable a set of events
# some are equipment based, some are not
# If there are no equipment based events being enabled, then they
# all get enabled - this one of those goofball special cases in the
# standard.  We do not code around this, because it helps you acquire
# the event data needed to create your own event reports.
# return ERACK value
# 0 = ok, 1 = denied (at least 1 CEID bad)
# TIMEOUT
proc ei_event_enable {spname CEIDs} {
    if { [llength $CEIDs] == 0 } {
        set where "where spname='$spname'"
        set msg "L:2 {TF 1} L"
        }\
    else {
        set where_eq "where spname='$spname' and event_class='EQ' and\
 (CEID='[join $CEIDs {' or CEID='}]')"
        set where "where spname='$spname' and\
 (CEID='[join $CEIDs {' or CEID='}]')"
        set reply [SQL "select ID_TSN,CEID from ei_event $where"]
        if { [lindex $reply 4] < [llength $CEIDs] } { return 1 }
        set reply_eq [SQL "select ID_TSN,CEID from ei_event $where_eq"]
        set CEIDlist [lindex $reply_eq 6] 
        set msg "L:2 {TF 1} {L $CEIDlist}"
        set ct_eq [lindex $reply_eq 4]
        if { $ct_eq == 0 } {
            # the goofball special case...
            # we will enable all events unless one or more events
            # have been explicitly configured off
            set reply_eq0 [SQL "select CEID from ei_event where \
 spname='$spname' and event_class='EQ' and host_managed=1\
 and host_wants_enabled=0"]
            if { [lindex $reply_eq0 4 ] > 0 } { set msg "" }
            }
        }
    if { $msg != "" } {
        set reply [secs_xact $spname S2F37R $msg]
        if { $reply != "TIMEOUT" } {
            set reply [expr [lindex $reply 1]]
            }
        }\
    else {
        set reply 0
        }
    if { $reply == "0" } {
        SQL "update ei_event set is_reported=1 $where"
        }
    return $reply
    }

######################### ei_event_discovery ####################
######################### ei_event_discovery ####################
######################### ei_event_discovery ####################
# enable all events and then
# get the value of the required GEM variable EventsEnabled
# and use the reply to populate the ei_event table
# return value
# positive number == number of new events found
# -1 = no EventsEnabled variable
# -2 could not enable
# -3 data not there
proc ei_event_discovery {spname} {
    # we need to have a variable EventsEnabled
    set reply [SQL "select varname from ei_variable where (varname='EventsEnabled' or\
 VFEIname='EVENTS_ENABLED' or varname='EVENTSENABLED') and spname='$spname'"]
    # the 1st one is ok
    set varname [lindex [lindex [lindex $reply 6] 0] 0]
    if { ![string compare $varname ""] } { return -1 }
    # enable all events
    set reply [ei_event_enable $spname {}]
    if { $reply != "0" } { return -2 }
    # get the value of EventsEnabled
    # take the first reply item for our single variable
    set reply [lindex [ei_var_query $spname [list $varname] varname] 0]
    # reply should be "L {U4:1 1000} {U4:1 1001} ..."
    # but we accommodate extra nesting "L {L {U4:1 1000} {U4:1001} ...}" 
    set value [lreplace $reply 0 0]
    if { ([llength $value] == 1) && ([string index $value 1] == "L") } { ;# remove extra "{L   }"
        set value [lindex $value 0]
        set value [lreplace $value 0 0]
        }
    if { [llength $value] == 0 } { return -3 }
    set ct 0
    foreach pair $value {
        vset $pair "tCEID CEID"
        set CEID_TSN  [lindex [split $tCEID :] 0]
        # make sure CEID is in the table
        set reply [SQL "insert into ei_event (spname, CEID, VFEIname, ID_TSN, is_reported,\
 event_class) values ('$spname', '$CEID', '[VFEIname $CEID]', '$CEID_TSN', 1, 'EQ')"]
        if { [string first {//c 0} $reply] >= 0 } { incr ct }
        }
    return $ct
    }
    

######################### ei_report_define ######################
######################### ei_report_define ######################
######################### ei_report_define ######################
# define a report - a set of variables
# reply DRACK value
# 0=ok, 1=no 2=fmt 3=RPTID is use, 4 bad VID
proc ei_report_define {spname RPTID varIDs} {
    global $spname
    set where "where spname='$spname' and \
 (varID='[join $varIDs {' or varID='}]')"
    set reply [SQL "select ID_TSN,varID from ei_variable $where"]
    if { [lindex $reply 4] < [llength $varIDs] } { return 4 }
    set vplist [lindex $reply 6]
    # re-arrange the variable order to be the caller's order
    set vlist {}
    foreach varID $varIDs { 
        set index 0
        foreach pair $vplist {
            if { $varID == [lindex $pair 1] } { 
                lappend vlist $pair
                set vplist [lreplace $vplist $index $index]
                break
                }
            incr index
            }
        }
    set DATAID [ei_dataid $spname]
    set msg "L:2 {$DATAID} {L:1 {L:2 {[ei_RPTID_TSN $spname] $RPTID}\
 {L $vlist}}}"
    if { [ei_multiblock_check $spname $msg $DATAID S2F39R] } { return 1 }
    set reply [secs_xact $spname S2F33R $msg]
    if { $reply != "TIMEOUT" } {
        set reply [expr [lindex $reply 1]]
        }
    if { $reply == "0" } {
        set ireply [SQL "insert into ei_report (spname,RPTID,VIDs) values\
 ('$spname','$RPTID','$varIDs')"]
        if { [string first {//c 3} $ireply] >= 0 } {  ;# row already exists
            SQL "update ei_report set VIDs='$varIDs' where spname='$spname'\
 and RPTID='$RPTID'"
            }
        }
    return $reply
    }

######################### ei_report_link ########################
######################### ei_report_link ########################
######################### ei_report_link ########################
#
# attach a report to a set of events 
#
# return value of LRACK
# 0=ok 1=no 2=fmt 3=CEID link used, 4=bad CEID, 5=bad RPTID 
#
proc ei_report_link {spname RPTID CEIDs} {
    global $spname
    set where "where spname='$spname' and event_class='EQ' and\
 (CEID='[join $CEIDs {' or CEID='}]')"
    set reply [SQL "select ID_TSN,CEID from ei_event $where"]
    if { [lindex $reply 4] < [llength $CEIDs] } { return 4 }
    set CEIDlist [lindex $reply 6]
    set iRPTID [list [ei_RPTID_TSN $spname] $RPTID]
    set La "L"
    foreach CEID $CEIDlist {
        set L2 [list L:2 $CEID [list L $iRPTID]]
        lappend La $L2
        }
    set DATAID [ei_dataid $spname]
    set msg [list L:2 $DATAID $La]
    if { [ei_multiblock_check $spname $msg $DATAID S2F39R] } { return 1 }
    set reply [secs_xact $spname S2F35R $msg]
    if { $reply != "TIMEOUT" } {
        set reply [expr [lindex $reply 1]]
        }
    if { $reply == "0" } {
        foreach CEID $CEIDs {
            SQL "insert into ei_event_report (spname,CEID,RPTID) values\
 ('$spname', '$CEID', '$RPTID')"
            }
        }
    return $reply
    }

######################### ei_reports_setup #########################
######################### ei_reports_setup #########################
######################### ei_reports_setup #########################
#
# enable the reports that have been configured in the 
# ei_report_cfg and ei_event_report_cfg tables
#
# return value
# 0=ok, 1=no 2=fmt 3=ID in use, 4 bad VID or CEID 5=bad RPTID
#
proc ei_reports_setup {spname {predelete 0}} {
    # optionally, start with a clean slate - no reports, no events
    if { $predelete } { ei_event_disable $spname {} 1 }
    # create,link, and enable the configured reports
    set where "where spname='$spname'"
    set reply [SQL "select RPTID from ei_event_report_cfg $where"]
    set rows [lindex $reply 6]
    set RPTIDs ""
    foreach row $rows {
        set RPTID [lindex $row 0]
        if { [lsearch -exact $RPTIDs $RPTID] < 0 } {
            lappend RPTIDs $RPTID
            }
        }
    foreach RPTID $RPTIDs {
        set reply [SQL "select VIDs from ei_report_cfg where\
 spname='$spname' and RPTID='$RPTID'"]
        set VIDs [lindex [lindex [lindex $reply 6] 0] 0]
        if { [llength $VIDs] == 0 } {
            error "RPTID $RPTID for $spname has no variables in ei_report_cfg"
            }
        set reply [ei_report_define $spname $RPTID $VIDs]
        if { $reply != 0 } { return $reply }
        # link the report to its events
        set reply [SQL "select CEID from ei_event_report_cfg $where and \
 RPTID='$RPTID'"]
        set CEIDs [lindex $reply 6]
        set reply [ei_report_link $spname $RPTID $CEIDs]
        }
    # enable the set of events (report can be linked to N events)
    set reply [SQL "select CEID from ei_event_report_cfg $where"]
    set rows [lindex $reply 6]
    set CEIDs ""
    foreach row $rows {
        set CEID [lindex $row 0]
        if { [lsearch -exact $CEIDs $CEID] < 0 } {
            lappend CEIDs $CEID
            }
        }
    # combine these events with the desired events of ei_event
    set reply [SQL "select CEID from ei_event where spname='$spname'\
 and host_managed=1 and host_wants_enabled=1"]
    set rows [lindex $reply 6]
    foreach row $rows {
        set CEID [lindex $row 0]
        if { [lsearch -exact $CEIDs $CEID] < 0 } {
            lappend CEIDs $CEID
            }
        }
    # enable all these events
    # if there are no events then skip it, because that would turn
    # on all equipment events (no events will not happen with the default
    # configuration because driver level events like COM_ENABLE
    # are reported by default)
    if { [llength $CEIDs] == "0" } { return 0 }
    set reply [ei_event_enable $spname $CEIDs]
    return $reply
    }


######################### ei_event_ann_rpt #########################
######################### ei_event_ann_rpt #########################
######################### ei_event_ann_rpt #########################
#
# received S6F13R annotated event report
# {L:3 <DATAID> <CEID> {L:a {L:2 <RPTID> {L:b {L:2 <VID> <V>} } } } }
#
proc ei_event_ann_rpt spname {
    global $spname
    $spname put S6F14 {B 0}
    rset [set ${spname}(lastrmsg)] "l3 {tDID DATAID} {tCEID CEID} La"
    if { $l3 != "L:3" } return
    # discover/correct/save type codes being used
    #set DATAID_TSN [lindex [split $tDID :] 0]
    set CEID_TSN  [lindex [split $tCEID :] 0]
    # do we know about this event type?
    SQL "insert into ei_event (spname, CEID, VFEIname, ID_TSN, is_reported,\
 event_class) values ('$spname', '$CEID', '[VFEIname $CEID]', '$CEID_TSN', 1, 'EQ')"
    set CLOCK [secs_CLOCK $spname]
    set logdata ""
    while {1} {
        # did we get any reports?
        if { $La == "L:0" } break
        set reports [lreplace $La 0 0]
        foreach report $reports {
            rset $report "L2 {tRPT RPTID} Lb"
            if { $L2 != "L:2" } break
            #set RPTID_TSN [lindex [split $tRPT :] 0]
            #set ${spname}(RPTID_TSN) $RPTID_TSN
            # do know about this report type?
            SQL "insert into ei_event_report (spname,CEID,RPTID) values\
 ('$spname','$CEID','$RPTID')"
            if { $Lb == "L:0" } continue
            set Lb [lreplace $Lb 0 0]
            set VIDs ""
            foreach L2 $Lb {
                rset $L2 "l2 {tVID VID} tVV"
                if { $l2 != "L:2" } break
                set tV [lindex $tVV 0]
                set V [lreplace $tVV 0 0]
                # do we know about this variable?
                set ID_TSN [lindex [split $tVID :] 0]
                set value_TSN [lindex [split $tV :] 0]
                # for gem equipment, we should already know
                SQL "insert into ei_variable (spname,varID,\
 varname, VFEIname, varclass, value_TSN,ID_TSN) values (\
 '$spname','$VID','$VID','[VFEIname $VID]', 'SV','$value_TSN','$ID_TSN')"
                ei_varvalue_save $spname $VID $tVV $CLOCK
                lappend VIDs $VID
                lappend logdata [list $VID $V]
                }
            # do we know about this report?
            SQL "insert into ei_report (spname,RPTID,VIDs) values \
 ('$spname','$RPTID','$VIDs')"
            # we do not try to update/repair a faulty ei_report record
            }
        break
        }
    # at this point the variables table has updated values
    # and these can be combined with driver variables (VFEI)
    # to create and format reports that are sent to higher 
    # level software
    # Just subscribe to ei_event_log to know about event occurrences
    SQL "insert into ei_event_log (spname,clock,CEID,data) values\
 ('$spname','$CLOCK','$CEID','$logdata')"
    }

########################## ei_event_report ########################
########################## ei_event_report ########################
########################## ei_event_report ########################
#
# received S6F11R plain event report
# here we have to trust that our report configuration is accurate 
#
# {L:3 <DATAID> <CEID> {L:a {L:2 <RPTID> {L:b <V> } } } }
proc ei_event_report spname {
    global $spname
    $spname put S6F12 {B 0}
    rset [set ${spname}(lastrmsg)] "l3 {tDID DATAID} {tCEID CEID} La"
    if { $l3 != "L:3" } return
    # discover/correct/save type codes being used
    #set DATAID_TSN [lindex [split $tDID :] 0]
    set CEID_TSN  [lindex [split $tCEID :] 0]
    # do we know about this event type?
    SQL "insert into ei_event (spname, CEID, VFEIname,ID_TSN, is_reported,\
 event_class) values ('$spname', '$CEID', '[VFEIname $CEID]', '$CEID_TSN', 1, 'EQ')"
    set CLOCK [secs_CLOCK $spname]
    set logdata ""
    while {1} {
        # did we get any reports?
        if { $La == "L:0" } break
        set reports [lreplace $La 0 0]
        foreach report $reports {
            rset $report "L2 {tRPT RPTID} Lb"
            if { $L2 != "L:2" } break
            #set RPTID_TSN [lindex [split $tRPT :] 0]
            #set ${spname}(RPTID_TSN) $RPTID_TSN
            if { $Lb == "L:0" } continue
            set Lb [lreplace $Lb 0 0]
            # we should know about this report type
            set reply [SQL "select VIDs from ei_report where spname='$spname'\
 and RPTID='$RPTID'"]
            set VIDs [lindex [lindex [lindex $reply 6] 0] 0]
            if { [llength $VIDs] != [llength $Lb] } continue
            set i 0
            foreach item $Lb {
                #set tV [lindex $item 0]
                set V [lreplace $item 0 0]
                set VID [lindex $VIDs $i] ; incr i
                # we should know about this variable
                ei_varvalue_save $spname $VID $item $CLOCK
                lappend logdata [list $VID $V]
                }
            }
        break
        }
    # at this point the variables table has updated values
    # and these can be combined with driver variables (VFEI)
    # to create and format reports that are sent to higher
    # level software
    # Just subscribe to ei_event_log to know about event occurrences
    SQL "insert into ei_event_log (spname,clock,CEID,data) values\
 ('$spname','$CLOCK','$CEID','$logdata')"
    }


########################## ei_driver_event ######################
########################## ei_driver_event ######################
########################## ei_driver_event ######################
#
# fire an event that is synthesized in the driver
# there are no SECS level reports
# you can create reports with data items using VFEI calls
#
proc ei_driver_event {spname CEID} {
    set reply [SQL "select is_reported from ei_event where \
 spname='$spname' and CEID='$CEID'"]
    set is_reported [lindex [lindex [lindex $reply 6] 0] 0]
    if { $is_reported == "1" } {
        set CLOCK [secs_CLOCK $spname]
        # this does not change the varmethod if you have
        # configured another clock format
        SQL "update ei_variable set varvalue='$CLOCK'\
 where spname='$spname' and VFEIname='CLOCK'"
        SQL "insert into ei_event_log (spname,clock,CEID) values\
 ('$spname', '$CLOCK', '$CEID')"
        }
    }


########################## ei_event_offline #####################
########################## ei_event_offline #####################
########################## ei_event_offline #####################

# called from a subscription of ei_event_log, check for the event that
# means the control state is offline 
#
proc ei_event_offline {notice table cols keys ct err rows} {
    vset [lindex $rows 0] $cols
    # now spname and CEID are known
    global $spname
    # we should be a little careful in case the interface is being shutdown/destroyed
    if { ![info exists ${spname}(CEID_OFFLINE)] } return
    if { $CEID != [set ${spname}(CEID_OFFLINE)] } return
    if { [info exists ${spname}(control_state)] && ([set ${spname}(control_state)] != "OFF-LINE" ) } {
        set ${spname}(control_state) OFF-LINE
        }
    }
