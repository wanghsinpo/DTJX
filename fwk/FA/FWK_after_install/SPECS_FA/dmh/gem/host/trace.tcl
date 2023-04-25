# $Header: /usr/cvsroot/gem/host/trace.tcl,v 1.7 2002/11/01 15:57:14 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: trace.tcl,v $
# Revision 1.7  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.6  2002/05/03 18:48:50  hume
# Updated trace handling for more than one sample in a message.
#
# Revision 1.5  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.4  2000/12/03 19:16:08  hume
# Updated event report and trace report handling for vector or list data.
#
# Revision 1.3  1999/05/26 20:30:59  hume
# Allow for 16 or 12 character STIME in trace report.
#
# Revision 1.2  1998/08/25 21:43:09  hume
# Fixed two bugs in TRACE_REPORT code.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#

########################## ei_trace_data #######################
########################## ei_trace_data #######################
########################## ei_trace_data #######################
#
# received S6F1[R] trace data
# 
# we update ei_variable table with these values 
# we add it to the event_log table as CEID=TRACE_REPORT
# you could base a VFEI report on the event TRACE_REPORT
#
# {L:4 <TRID> <SMPLN> <STIME> {L:n <SV>s}
#                     yymmddhhmmss
#
proc ei_trace_data spname {
    global $spname
    # optional reply requested
    if { [string first R [set ${spname}(lastrSFR)]] > 0 } {
        $spname put S6F2 {B 0}
        }
    rset [set ${spname}(lastrmsg)] \
        {L4 {ttid trace_id} {tsm smpln} {tt stime} Ln}
    set reply [SQL "select period_secs, SVIDs from ei_trace_setup where\
 spname='$spname' and trace_id='$trace_id'"]
    vset [lindex [lindex $reply 6] 0] {period_secs SVIDs}
    if { $SVIDs == "" } return
    if { [llength $Ln] <= 1 } return
    set Ln [lreplace $Ln 0 0]
    if { ([llength $Ln] % [llength $SVIDs]) != 0 } return
    if { $tt == "A:16" } { ;# YYYYMMDDhhmmsscc
        set CLOCK ${stime}
        }\
    else { ;# YYMMDDhhmmss
        set YY [string range [localtime 9] 0 1]
        set CLOCK ${YY}${stime}00
        }

    # in the case of more than one report per message, the sample time, STIME
    # is for the last sample, and the time has to be computed for the earlier
    # samples, based on the period.
    set n_samples [expr {[llength $Ln]/[llength $SVIDs]}]
    if { $n_samples > 1 } { 
        set stime_last [secs_CLOCK_to_seconds $CLOCK 0]
        set CLOCK {}
        for {set n 1} {$n <= $n_samples} {incr n} {
            set stime [expr {$stime_last - $period_secs*($n_samples-$n)}]
            lappend CLOCK [secs_CLOCK_from_seconds $stime]
            }
        }
    set i 0
    for {set n 0} {$n < $n_samples} {incr n} {
        set logdata {}
        lappend logdata [list TRACE_ID $trace_id]
        set Clock [lindex $CLOCK $n]
        foreach SVID $SVIDs {
            set SV [lindex $Ln $i]
            # remove value type code
            set value [lreplace $SV 0 0]
            incr i
            SQL "update ei_variable set varvalue='$value', t_latest='$Clock'\
 where spname='$spname' and varclass='SV' and \
 (varID='$SVID' or VFEIname='$SVID')"
            lappend logdata [list $SVID $value]
            }
        set reply [SQL "insert into ei_event_log (spname,clock,CEID,data) values\
 ('$spname','$Clock','TRACE_REPORT','$logdata')"]
        }
    }


######################### ei_trace_setup ########################
######################### ei_trace_setup ########################
######################### ei_trace_setup ########################
#
# see GEM Appendix A.4 for trace details
#
# TOTSMP == 0 means disable
#
# return value (TIAACK)
# 0 = ok
# TIMEOUT
# 1 = too many SVIDS
# 2 = no more traces allowed
# 3 = invalid period
proc ei_trace_setup {spname TRID period_secs TOTSMP REPGSZ SVIDs} {
    global $spname
    # convert period seconds to <DSPER> {A:6 hhmmss} 
    # some equipment can also use A:8 hhmmsscc - Hume handles both
    set secs [set period_secs [expr {int($period_secs)}]]
    set hours [expr {int( $secs / 3600)}]
    if { $hours > 99 } { return 3 } ;# invalid period
    set secs [expr {int( $secs % 3600)}]
    set mins [expr {int( $secs / 60)}]
    set secs [expr {int( $secs % 60)}]
    set DSPER [format "A %02d%02d%02d" $hours $mins $secs]
    # look up the variables, they must be SVs
    if { [llength $SVIDs] > 0 } {
        set where "where spname='$spname' and varclass='SV' and\
 ((VFEIname='[join $SVIDs {' or VFEIname='}]') or \
  (varID='[join $SVIDs {' or varID='}]'))"
        set reply [SQL "select ID_TSN, varID from ei_variable $where"]
        if { [lindex $reply 4] != [llength $SVIDs] } {
            return 1 
            }
        set SVIDtvs [lindex $reply 6]
        }\
    else { set SVIDtvs ""}

    # get the SECS TSN types we need from the ei_variable table
    # these are configuration items that have defaults
    # TRID A,Ix,Ux ; TOTSMP A,Ix,Ux ; REPGSZ A,Ix,Ux
    foreach parm {TRID TOTSMP REPGSZ} {
        set reply [SQL "select value_TSN from ei_variable\
 where spname='$spname' and varID='$parm'"]
        set TSN [lindex [lindex [lindex $reply 6] 0] 0]
        if { $TSN == "" } {
            error "${parm} value_TSN has not been configured"
            }
        # revalue as type value pairs
        set ${parm}tv [list $TSN [set $parm]]
        }
    set msg [list L:5 $TRIDtv $DSPER $TOTSMPtv $REPGSZtv "L $SVIDtvs"]
    set reply [secs_xact $spname S2F23R $msg]
    if { $reply != "TIMEOUT" } { set reply [expr [lindex $reply 1]] }
    if { $reply == "0" } {
        # we have to remember the variables and period
        SQL "create table ei_trace_setup (spname varchar(32),\
 trace_id varchar(32), period_secs float, SVIDs varchar(1000),primary key(spname,trace_id))"
        SQL "delete from ei_trace_setup where spname='$spname' and\
 trace_id='$TRID'"
        if { $TOTSMP > 0 } {
            SQL "insert into ei_trace_setup (spname,trace_id,period_secs,SVIDs) values (\
 '$spname','$TRID',$period_secs,'$SVIDs')"
            }
        }
    return $reply
    }
    
