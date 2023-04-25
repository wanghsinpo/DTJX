# $Header: /usr/cvsroot/gem/equip/eq_reports.tcl,v 1.2 2005/03/21 17:01:03 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 2005 Hume Integration Software
# All Rights Reserved
#
# $Log: eq_reports.tcl,v $
# Revision 1.2  2005/03/21 17:01:03  hume
# Added helper routines for the .NET and similar libraries.
#
# Revision 1.1  2005/03/20 15:37:37  hume
# Added features to make persistent saving of dynamic reports configurable.
#
#

# Logic for saving and restoring the state of dynamic event reports
# also some helper procedures for the .NET and similar libraries
# The logic for SECS message handling is in file eq_events.tcl.

# GEM (E37) says dynamic event reporting setup by the host is persistent.
# This has not been an important requirement because most hosts are programmed
# to setup their desired event reporting each time the equipment comes
# online.
#
# If you want your equipment to feature some predefined event reports, you have
# a tricky situation since the saved and restored reports can delete your predefined ones.
# Our recommendation is not to feature built-in, predefined reports.  If you choose
# to offer predefined reports, we recommend you add a persistent equipment parameter 
# and make the user choose between having your predefined reports at startup, or having the reports
# from last session be saved and restored.  To have your predefined reports available,
# do one of the following:
#  (1) Set the property ReportsAreSaved to 0 to prevent your predefined reports
#     from being replaced by the restore logic. 
#     (make this a user choice - predefined built-in reports, or persistent
#     host defined reports) 
#  (2) Call ReportsRestore explicitly after events and variables are defined, and then
#     add your prefined reports after the restore logic has run.

###################################### eq_reports_restore #######################################
###################################### eq_reports_restore #######################################
###################################### eq_reports_restore #######################################
# Public API call
# eq_reports_restore is called from eq_comm_enabled the first time eq_comm_enabled is called if array 
# element ReportsAreSaved is defined and true.  This is the usual case for
# the .NET SecsPort and similar libraries.
#  -restore report definitions and enablement from last session if they exist
#  -setup saving for this time
#  set array element _ReportsInitialized so we are not called again
proc eq_reports_restore spname {
    global $spname
    if { ![info exists ${spname}(_ReportsFile)] } { eq_reports_savefile $spname }
    set pathname [set ${spname}(_ReportsFile)]
    if { [file exists $pathname] } {
        # delete existing reports
        foreach table {ei_report ei_event_report} { 
            SQL "delete from $table where spname='$spname'"
            }
        # and restore the ones saved from last session
        set reply [SQL [list include $pathname]]
        #dmh_show_text $reply "Report Restore Replies"
        }
    eq_report_saving_init $spname
    set ${spname}(_ReportsInitialized) 1
    }

# return the pathname for the reports save file
# save report information in the spool file directory
proc eq_reports_savefile {spname} {
    global $spname
    set dir [file dirname [eq_spoolfile $spname]]
    set file [file join $dir reportdata_${spname}.sql]
    set ${spname}(_ReportsFile) $file
    }

#################################### eq_reports_clear ##################################
#################################### eq_reports_clear ##################################
#################################### eq_reports_clear ##################################
# public API call
# delete existing reports and also the saved report configuration 
# also disables event reporting for events that were linked to reports
proc eq_reports_clear {spname} {
    global $spname
    # delete the save file if it exists
    if { ![info exists ${spname}(_ReportsFile)] } { eq_reports_savefile $spname }
    # there is no error if the save file does not exist
    file delete [set ${spname}(_ReportsFile)]
    # disable events linked to reports
    set reply [SQL "select CEID from ei_event_report where spname='$spname'"]
    foreach row [lindex $reply 6] {
        SQL "update ei_event set is_reported=0 where CEID=[lindex $row 0] and spname='$spname'"
        }
    # delete the reports and the links
    SQL "delete from ei_report where spname='$spname'"
    SQL "delete from ei_event_report where spname='$spname'"
    }

# internal call
proc eq_report_saving_init {spname} {
    global $spname
    # if we have a normal shutdown, we write a save file
    dp_atexit appendUnique [list eq_reports_save $spname]
    # and while we run, we could save incremental changes, but it does not seem to be that important
    # clear out the save data from last time
    file delete [set ${spname}(_ReportsFile)]
    }

# Called at exit to save reporting state.
# If you call it earlier, the save information gets overwritten at exit time.
# You can use this call to delete the save file by setting ReportsAreSaved to 0.
proc eq_reports_save {spname} {
    global $spname
    if { ![info exists ${spname}(ReportsAreSaved)] } return 
    if { ![info exists ${spname}(_ReportsFile)] } { eq_reports_savefile $spname }
    set pathname [set ${spname}(_ReportsFile)]
    if { ![set ${spname}(ReportsAreSaved)] } {
        # make sure the save file is deleted since no saving is wanted
        file delete $pathname
        return
        }
    if {[catch {open $pathname w} fid]} return
    # the open file descriptor is passed as a default procedure argument
    proc eq_report_save_stmt [list stmt [list fid $fid]] { puts $fid $stmt }
    set subname report_save_${spname}
    # a SYNC subscription is a quick way to create insert statements for saving
    SQL "open sub $subname to ei_report sqlproc=eq_report_save_stmt insert sync * where spname='$spname'"
    SQL "close sub $subname to ei_report"
    SQL "open sub $subname to ei_event_report sqlproc=eq_report_save_stmt insert sync * where spname='$spname'"
    SQL "close sub $subname to ei_event_report"
    # now write the state of event report enablement
    set reply [SQL "select CEID, is_reported from ei_event where spname='$spname'"]
    foreach row [lindex $reply 6] {
        vset $row {CEID is_reported}
        catch {
            puts $fid "update ei_event set is_reported=$is_reported where spname='$spname' and CEID=$CEID"
            }
        }
    catch {close $fid}
    }


################################# eq_ReportDefine ##################################
################################# eq_ReportDefine ##################################
################################# eq_ReportDefine ##################################
# helper routine to 
# manage report definitions
# return code 
#    0 - new report created
#    1 - existing definition replaced
#    2 - (empty varIDs) - definition deleted (even if it did not exist)
#   -2 - one or more variables does not exist
proc eq_ReportDefine {spname RPTID varIDs} {
    foreach v $varIDs {
        # each varID must exist
        set reply [SQL "select varID from ei_variable where spname='$spname' and varID='$v'"]
        if { [lindex $reply 4] != 1 } { return -2; }
        }
    set reply [SQL "delete from ei_report where RPTID='$RPTID' and spname='$spname'"]
    # its an update if the reply starts with //c 0
    if { [string first {//c 0} $reply] >= 0 } { set rc 1 }\
	else { set rc 0 }
    if { [llength $varIDs] == 0 } { ;# deletion intended
        return 2 
        }
        
    set reply [SQL "insert into ei_report (spname, RPTID, VIDs) values ('$spname', '$RPTID', \
 '$varIDs')"]
    if { [string first {//c 0} $reply] < 0 } { return -1 ;# error }
    return $rc
    }
################################# eq_ReportLink ####################################
################################# eq_ReportLink ####################################
################################# eq_ReportLink ####################################
# helper routine to 
# create an event report association
# its not an error if the link already exists
# return code 
#    0 - link created
#   -2 - invalid RPTID
#   -3 - invalid CEID
#   -1 - unexpected error 
proc eq_ReportLink {spname RPTID CEID} {
    # each ID must exist
    set reply [SQL "select RPTID from ei_report where spname='$spname' and RPTID='$RPTID'"]
    if { [lindex $reply 4] != 1 } { return -2; }
    set reply [SQL "select CEID from ei_event where spname='$spname' and CEID='$CEID'"]
    if { [lindex $reply 4] != 1 } { return -3; }
   
    set reply [SQL "insert into ei_event_report (spname, CEID, RPTID) values ('$spname', '$CEID', '$RPTID')"]
    if { [string first {//c 0} $reply] >= 0 } { set rc 0 }\
	elseif { [string first {//c 3} $reply] >= 0 } { set rc 0 }\
    else { set rc -1 } 
    return $rc
    }
