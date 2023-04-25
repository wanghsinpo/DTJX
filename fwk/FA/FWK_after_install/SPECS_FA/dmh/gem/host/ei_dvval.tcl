# $Header: /usr/cvsroot/gem/host/ei_dvval.tcl,v 1.7 2003/06/16 18:19:41 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: ei_dvval.tcl,v $
# Revision 1.7  2003/06/16 18:19:41  hume
# When saving VFEI report configurations for Discrete Variable reports, there
# may be a different VFEIname than the one calculated from the variable ID.
#
# Revision 1.6  2003/06/13 18:55:11  hume
# Made handling of report data items same as user defined event reports to
# fix handling array data, and to accomodate oversize data.
#
# Revision 1.5  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.4  1999/04/13 12:15:16  hume
# Needed to call VFEIname for new events to strip whitespace, etc.
#
# Revision 1.3  1999/04/09 21:00:46  hume
# S6F3 event reports are now automatically configured to be forwarded as
# VFEI reports with the reported data items.
#
# Revision 1.2  1998/11/17 13:21:21  hume
# Converted while 1 to while {1} for better runtime performance.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#


# received S6F3[R] discrete data
#
# this is like a predefined event report
# We will process it like an event report
# and insert the data into ei_event_log
#  we do not update tables ei_report or ei_event_report since
#  this is not an event report that can be configured
#
# the VFEI level can define its own reports on the event, and pull in
# additional variables.
#
proc ei_discrete_data spname {
    global $spname
    # optional reply requested
    if { [string first R [set ${spname}(lastrSFR)]] > 0 } {
        $spname put S6F4 {B 0}
        }
    rset [set ${spname}(lastrmsg)] "l3 {tDID DATAID} {tCEID CEID} La"
    if { $l3 != "L:3" } return
    # record type code being used (can aid configuration)
    set DATAID_TSN [lindex [split $tDID :] 0]
    set ${spname}(DATAID_TSN) $DATAID_TSN
    set CEID_TSN  [lindex [split $tCEID :] 0]
    set ${spname}(CEID_TSN) $CEID_TSN
    # do we know about this event type?
    set VFEIname [VFEIname $CEID]
    SQL "insert into ei_event (spname, CEID, VFEIname, ID_TSN, is_reported,\
 event_class) values ('$spname', '$CEID', '$VFEIname', '$CEID_TSN', 1, 'EQ')"
    set CLOCK [secs_CLOCK $spname]
    set logdata ""
    while {1} {
        # did we get any reports?
        if { $La == "L:0" } break
        set reports [lreplace $La 0 0]
        foreach report $reports {
            rset $report "L2 {tDSID DSID} Lb"
            if { $L2 != "L:2" } break
            #set DSID_TSN [lindex [split $tDSID :] 0]
            #set ${spname}(DSID_TSN) $DSID_TSN
            if { $Lb == "L:0" } continue
            set Lb [lreplace $Lb 0 0]
            set VIDs ""
            foreach L2 $Lb {
                rset $L2 {l2 {tVID VID} tVV}
                if { $l2 != "L:2" } break
                set tV [lindex $tVV 0]
                set V [lreplace $tVV 0 0]
                # do we know about this variable?
                set ID_TSN [lindex [split $tVID :] 0]
                set value_TSN [lindex [split $tV :] 0]
                set VFEIname [VFEIname $VID]
                set reply [SQL "insert into ei_variable (spname,varID,\
 varname, VFEIname, varclass, value_TSN,ID_TSN) values (\
 '$spname','$VID','$VID','$VFEIname', 'DVVAL','$value_TSN','$ID_TSN')"]
                if { [string first {//c 0} $reply] < 0 } {
                    # variable is already known, perhaps with a different VFEIname
                    set VFEIname [lindex [lindex [lindex [SQL \
 "select VFEIname from ei_variable where spname='$spname' and varID='$VID'"] 6] 0] 0]
                    }
                ei_varvalue_save $spname $VID $tVV $CLOCK
                lappend VIDs $VFEIname 
                lappend logdata [list $VID $V]
                }
            }
        break
        }

    # The logic here creates a "vfei_$CEID" record if one does not exist
    # so that this event report automatically creates a VFEI event report
    # with the reported data.
    # Since these reports are not configurable using the UI, 
    # you need custom software to create/change/delete this report 
    # configuration.  
    # -Copy this file and comment out the logic below to
    #   stop these VFEI event reports from being generated.
    # -Have your own insert statement during initialization to modify the
    #   reported VFEI variables.
    if { [info exists VIDs] } {
	# the VIDs are the VFEInames
        SQL "insert into ei_report (spname,RPTID,VIDs) values ('$spname',\
     'vfei_$CEID', '$VIDs')"
	}

    # at this point the variables table has updated values
    # and these can be combined with driver variables (VFEI)
    # to create and format reports that are sent to higher
    # level software
    # Just subscribe to ei_event_log to know about event occurrences
    SQL "insert into ei_event_log (spname,clock,CEID,data) values\
 ('$spname','$CLOCK','$CEID','$logdata')"
    }
