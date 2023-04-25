# $Header: /usr/cvsroot/tcllib84/secs_trc.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
# 
# Licensed and Supported Software
# (C)Copyright 1995, 2001 Hume Integration Software
# All Rights Reserved
#
# $Log: secs_trc.tcl,v $
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.4  2001/11/15 17:14:17  hume
# Updated company name.
#
# Revision 1.3  2001/05/25 22:41:12  hume
# Backup restoration.
#
# Revision 1.3  2001/05/18 18:19:36  hume
# Added trace window save actions as suggested by Pierre Gauthier of Agilent.
#
# Revision 1.2  2000/03/09 03:49:51  hume
# Basic comm Replay is working.
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
# Revision 1.4  1999/05/06 21:55:22  hume
# Replaced use of menubuttons to have accelerator keys work on NT.
#
# Revision 1.3  1997/10/24 22:53:03  hume
# Tweaked trace menu item text.
#
# Revision 1.1.1.1  1997/10/03 02:31:41  hume
# From tcllib42 with edits.
#
# Revision 1.2  1997/05/31 14:33:25  hume
# Revised use of tk_dialog - created as child of toplevel parent in case root
# window is iconified, it still shows up.  Deleted obsolete tk_MenuBar calls.
#
# Revision 1.1.1.1  1997/02/11 14:26:54  hume
# For Tk 4.2
#
# Revision 1.1.1.1  1996/07/10 02:01:16  hume
# Reorganized and modified for Tk4.0 dp3.3.
#
# Revision 1.1  1996/01/31  12:48:54  hume
# Rewrote tracewin code.  Added replay window.
#
namespace eval ::dmh {
#
# the default traces window for a secsport
# this window and the comm_tracewin share some common code
#
proc secsport_tracewin obj {
    global $obj
    set w .tr_${obj}
    if { [winfo exists $w] } {
        wm deiconify $w
        raise $w
        return $w
        }
    global $obj
    set ${obj}(tracewin) $w
    toplevel $w
    wm title $w "$obj Trace"
    menu $w.m -tearoff 0 -relief flat

    set m $w.m.w
    $w.m add cascade -label Window -underline 0 -menu $w.m.w
    menu $m -tearoff 0
    $m add command -label "Save" -underline 0\
 -command [list ::dmh::comm_tr_save $obj]
    $m add command -label "appendToSave" -underline 6\
 -command [list ::dmh::comm_tr_save $obj {} a]
    $m add command -label "saveAs..." -underline 4\
 -command [list ::dmh::comm_tr_saveas $obj]
    $m add separator
    $m add command -label "Clear" -underline 0\
 -command [list $w.f.lb delete 0 end]
    $m add separator
    $m add command -label "Dismiss" -underline 0\
 -command "destroy $w"
    $m add separator
    $m add command -label "Exit..." -underline 0\
 -command "if {\[tk_dialog $w.popup {Exit Program} {Please confirm\
 the shutdown of this program.} questhead 0 Cancel Ok\] == 1 } exit"

    set m $w.m.o
    $w.m add cascade -label Object -underline 0 -menu $m
    menu $m -tearoff 0
    $m add command -label "Show $obj" -underline 0 \
 -command [list ::dmh::comm_tracewin_show $obj]
    $m add separator
    $m add command -label "Reset $obj" -underline 0 \
 -command [list $obj reset]
    $m add separator
    $m add command -label "Close $obj..." -underline 0 \
 -command [list ::dmh::comm_tracewin_close $obj]
    
    set m $w.m.t
    $w.m add cascade -label Tracing -underline 0 -menu $m
    menu $m
    $m add command -label "$obj Tracing"
    $m add separator
    set TRACE [set ${obj}(TRACE)]
foreach rec { 
 {cb1 1 "Reads and Writes"}
 {cb2 2 "State Changes"}
 {"" "" "Receive Tracing"}
 {cb100 0x100 "Header Hex Dump"}
 {cb200 0x200 "Header Interpretation"}
 {cb400 0x400 "Stream/Func Description"}
 {cb800 0x800 "Data Hex Dump"}
 {cb4 4 "SECS-II Messages"}
 {cb40 0x40 "Replay Tracing"}
 {"" "" "Send Tracing"}
 {cb1000 0x1000 "Header Hex Dump"}
 {cb2000 0x2000 "Header Interpretation"}
 {cb4000 0x4000 "Stream/Func Description"}
 {cb8000 0x8000 "Data Hex Dump"}
 {cb8 8 "SECS-II Messages"}
 {cb80 0x80 "Replay Tracing"}
 } {
        vset $rec "sub bit txt"
        if { $sub == "" } {
            $m add separator
            $m add separator
            $m add command -label $txt
            $m add separator
            }\
        else {
            set ${obj}($sub) [expr $bit & $TRACE ? 1:0]
            $m add check -label $txt -variable ${obj}($sub)\
 -command [list ::dmh::tracebitsync $obj $sub $bit]
            }
        }
    set m $w.m.s
    $w.m add cascade -label Send -underline 0 -menu $m
    menu $m
    $m add command -label "S1F1R" -command [list $obj put S1F1R]
    # this message has ^C, ^X, the telnet escape sequence,  ^S, ^Z, and ^D
    $m add command -label "Binary echo - S2F25R"\
 -command "$obj put S2F25R\
 {B 0 1 3 3 0x0a 0x0d 0x1B 0x5d 0x18 0x18 0x18 0x1a 0x04 0x13 127 128 254 255}"

    set m $w.m.r
    $w.m add cascade -label Replay -underline 0 -menu $m
    menu $m -tearoff 0
    $m  add command -label "re-Send last send" -underline 3\
 -command [list ::dmh::secs_resend_last $obj]
    $m  add command -label "re-Receive last receive" -underline 3\
 -command [list ::dmh::secs_rerecv_last $obj]
    $m add command -label "Window..." -underline 0\
 -command [list ::dmh::secs_replaywin $obj]

    $w configure -menu $w.m

    frame $w.f
    pack $w.f -side top -expand yes -fill both
    scrollbar $w.f.v -relief sunken -command "$w.f.lb yview"
    scrollbar $w.f.h -relief sunken -command "$w.f.lb xview" -orient horizontal
    pack $w.f.v -side right -fill y
    pack $w.f.h -side bottom -fill x
    listbox $w.f.lb -font fixed -setgrid 1 -relief sunken\
 -xscroll "$w.f.h set" -yscroll "$w.f.v set"
    pack $w.f.lb -side left -expand yes -fill both
    $w.f.lb configure -height 24 -width 80
    foreach sub {trace rtrace strace} {
        trace variable ${obj}($sub) w ::dmh::comm_tracewin_trace
        }
    bind  $w.f.lb <Destroy> "+ ::dmh::comm_tracewin_atexit $obj"
    return $w
    }

} ;# namespace
