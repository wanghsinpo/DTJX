# $Header: /usr/cvsroot/tcllib84/interval.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
# Licensed and Supported Software
# (C)Copyright 1996 Hume Integration Software
# All Rights Reserved
# $Log: interval.tcl,v $
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.2  2001/11/15 17:14:17  hume
# Updated company name.
#
# Revision 1.1.1.1  2000/03/01 21:20:55  hume
# pkgindex only change.
#
# Revision 1.1.1.1  1999/10/05 00:58:06  hume
# Initial Tcl eight.two version.
#
# Revision 1.1.1.1  1999/07/02 18:48:37  hume
# Starting point for Tcl 8.1.
#
# Revision 1.1.1.1  1997/10/03 02:31:41  hume
# From tcllib42 with edits.
#
# Revision 1.1.1.1  1997/02/11 14:26:54  hume
# For Tk 4.2
#
# Revision 1.1.1.1  1996/07/10 02:01:16  hume
# Reorganized and modified for Tk4.0 dp3.3.
#
# Revision 1.1  1995/12/28  20:22:16  hume
# Split out of hsms.tcl
#
namespace eval ::dmh {

# provide a description of an interval
proc interval_txt secs {
    if { $secs < 0 } { set secs [expr 0 - $secs] }
    set days 0
    set days [expr {int( $secs / 86400)}]
    set secs [expr {int( $secs % 86400)}]
    set hours [expr {int( $secs / 3600)}]
    set secs [expr {int( $secs % 3600)}]
    set mins [expr {int( $secs / 60)}]
    set secs [expr {int( $secs % 60)}]
    set tenths [expr {int( ($secs + 3)/ 6)}]
    if { $tenths == 10 } { incr mins ; set tenths 0 }
    if { $days > 0 } {
        set result "$days days, "
        }\
    else { set result "" }
    if { $hours > 0 } { append result "$hours hours, "}
    append result "${mins}.${tenths} minutes"
    return $result
    }

} ;# namespace
