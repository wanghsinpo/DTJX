# $Header: /usr/cvsroot/gem/equip/eq_trace.tcl,v 1.5 2005/04/08 20:55:21 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 2000 Hume Integration Software
# All Rights Reserved
#
# $Log: eq_trace.tcl,v $
# Revision 1.5  2005/04/08 20:55:21  hume
# fixed bug with A:8 DSPER in trace.
#
# Revision 1.4  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.3  2001/11/15 17:03:49  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.2  2000/12/18 23:32:23  hume
# Needed to allow for spooling of S9 messages.
#
# Revision 1.1  2000/12/06 23:34:01  hume
# Renamed trace.tcl to eq_trace.tcl and variables.tcl to eq_variables.tcl
# so you can have custom versions of host and equip files in the same
# directory with the original names without a conflict.
#
# Revision 1.1  2000/12/05 01:21:32  hume
# New Trace Data Collection capability.
#
#
#
# Trace Data Collection Capability - Equipment side
#
# For the results to be changing, the OEM has to install 
#  "varmethod" code in the ei_variable tables that reads the 
#  realtime values.  Either that, or update the table with 
#  data changes.
#
# see GEM doc E30-95 and Appendix A.4
# GEM says you should allow at least 4 traces if implemented
#
#
# Recd S2F23 Trace Initialize Send
#
# L:5 <TRID> <DSPER> <TOTSMP> <REPGSZ> {L:n [<SVID>]+}
#
# TRID  host defined trace_id - we use whatever type code the host wants!
# DSPER {A hhmmss[cc]} sampling period
# TOTSMP   total sample count desired
# REPGSZ   reporting group size   TOTSMP % REPGSZ == 0
#
# reply TIAACK B 0 == ok, 1 == too many SVIDs, 2 == no more traces allowed,
#    3 == invalid period, 4-63 reserved, 
# 
proc eq_trace_init spname {
    global $spname
    set request [set ${spname}(lastrmsg)]
    # trace_id is TSN pair of type and value
    rset $request {L5 trace_id {tDSPER DSPER} {t TOTSMP} {t REPGSZ} SVIDs}
    # any revision cancels and replaces existing trace
    set reply [SQL "select timer_handle from ei_trace_active where\
 spname='$spname' and trace_id='$trace_id'"]
    set handle [lindex [lindex [lindex $reply 6] 0] 0]
    if { $handle != {} } { after cancel $handle }
    SQL "delete from ei_trace_active where\
 spname='$spname' and trace_id='$trace_id'"
    if { $TOTSMP == "0" } {
        # cancellation was the entire intent
        $spname put S2F24 {B 0}
        return
        }
    # so how many active traces are there?
    set reply [SQL "select trace_id from ei_trace_active where\
 spname='$spname'"]
    set ct [lindex $reply 4]
    # TBD parameter for max traces
    if { $ct >= 4 } { 
        $spname put S2F24 {B 2}
        return
       }
    # convert DSPER hhmmss[cc] to milliseconds
    set rc 3
    if { $tDSPER == "A:6" } {
        set cc 0
        set ct [scan $DSPER %02d%02d%02d hh mm ss]
        if { $ct == 3 } { set rc 0 }
        }\
    elseif { $tDSPER == "A:8" } {
        set ct [scan $DSPER %02d%02d%02d%02d hh mm ss cc]
        if { $ct == 4 } { set rc 0 }
        }
    if { $rc == 3 } {
        eq_S9_reply $spname 7 ;# illegal data
        return
        }
    set msecs [expr $hh * 3600000 + $mm * 60000 + $ss * 1000 + $cc * 10]
    # TBD min max parameters
    if { $msecs < 1000 || $msecs > 10000000 } {
        $spname put S2F24 {B 3}
        return
        }
    if { [catch { 
        set TOTSMP [expr int($TOTSMP)]
        set REPGSZ [expr int($REPGSZ)] }] \
 || $TOTSMP <= 0 || $REPGSZ <= 0 || $REPGSZ > $TOTSMP || ([expr $TOTSMP % $REPGSZ] != 0) } {
        eq_S9_reply $spname 7 ;# illegal data
        return
        }
    # validate the SVIDs L:n [{tID ID}]+
    set svids {}
    set SVIDs [lreplace $SVIDs 0 0]
    foreach svid $SVIDs { lappend svids [lindex $svid 1] }
    set reply [SQL "select varID from ei_variable where varID='[join $svids {' or varID='}]'"]
    set ct [lindex $reply 4]
    if { $ct != [llength $svids] || ( $ct == 0 ) } {
        eq_S9_reply $spname 7 ;# illegal data
        return
        }
    set timer_handle [after $msecs [list eq_trace_report_callback $spname $trace_id]]
    set reply [SQL "insert into ei_trace_active (spname,trace_id,period_msecs,sample_n,sample_n_max,\
 report_ct,report_ct_max,timer_handle,SVIDs,data) values ('$spname','$trace_id',$msecs,\
 0,$TOTSMP,0,$REPGSZ,'$timer_handle','$svids','L')"]
    if { [string first {//c 0} $reply] >= 0 } {
       set rc 0
       }\
    else { set rc 65 }
    $spname put S2F24 [list B $rc]
    }

#
# TRACE_REPORT timer callback, observe SVIDs, possibly initiate S6F1 message
#
proc eq_trace_report_callback {spname trace_id} {
   set reply [SQL "select * from ei_trace_active where spname='$spname' and trace_id='$trace_id'"]
   set cols [lindex $reply 2]
   set row [lindex [lindex $reply 6] 0]
   vset $row $cols 
   if { $trace_id == {}} return
   foreach varID $SVIDs {
       lappend data [eq_VV_item $spname $varID]
       }
   incr sample_n
   incr report_ct
   if { $report_ct == $report_ct_max } {
       set CLOCK [secs_CLOCK $spname]
       vset [eq_VV_item $spname TimeFormat varname] "type value"
       if { $value == "1" } { set STIME $CLOCK }\
       else { set STIME [string range $CLOCK 2 13] }
       set msg [list L $trace_id [list U4 $sample_n] "A $STIME" $data]
       # spooling may be active
       eq_checked_put $spname 6 1 0 $msg
       set report_ct 0
       set data L
       }
   if { $sample_n < $sample_n_max } {
       set timer_handle [after $period_msecs [list eq_trace_report_callback $spname $trace_id]]
       set reply [SQL "update ei_trace_active set sample_n=$sample_n, report_ct=$report_ct,\
 data='$data',timer_handle='$timer_handle' where spname='$spname' and trace_id='$trace_id'"]
       }\
    else {
        SQL "delete from ei_trace_active where spname='$spname' and trace_id='$trace_id'"
        }
    }
       

proc eq_trace_startup {spname} {

    # Trace Reports can affect performance so limits may be needed
    # what Hume has implemented is a starting point
    # you may want to parameterize the limits
    # an ECV equipment constant to define the maximum number of permitted simultaneous traces
    # an ECV equipment constant to define the allowed minimum period for trace reporting
    # an ECV equipment constant to define the maximum allowed number of status variables in a trace

    # a table to hold status data for active traces 
    # the Hume host side creates a table, ei_trace_setup
    SQL "create table ei_trace_active (\
 spname varchar(32),\
 trace_id varchar(32),\
 period_msecs int,\
 sample_n int,\
 sample_n_max int,\
 report_ct int,\
 report_ct_max int,\
 timer_handle varchar(12),\
 SVIDs varchar(1000),\
 data varchar(32000),\
 primary key(spname,trace_id))"
    }
 
 
