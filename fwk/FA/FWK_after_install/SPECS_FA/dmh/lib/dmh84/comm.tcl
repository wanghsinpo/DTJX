# $Header: /usr/cvsroot/tcllib84/comm.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
# 
# Licensed and Supported Software
# (C)Copyright 1995, 2001 Hume Integration Software
# All Rights Reserved
#
# $Log: comm.tcl,v $
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.4  2001/11/15 17:14:17  hume
# Updated company name.
#
# Revision 1.3  2001/05/25 22:41:12  hume
# Backup restoration.
#
# Revision 1.3  2001/05/18 18:19:35  hume
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
# Revision 1.1.1.1  1999/07/02 18:48:36  hume
# Starting point for Tcl 8.1.
#
# Revision 1.2  1999/05/06 21:55:22  hume
# Replaced use of menubuttons to have accelerator keys work on NT.
#
# Revision 1.1.1.1  1997/10/03 02:31:41  hume
# From tcllib42 with edits.
#
# Revision 1.2  1997/05/31 14:33:23  hume
# Revised use of tk_dialog - created as child of toplevel parent in case root
# window is iconified, it still shows up.  Deleted obsolete tk_MenuBar calls.
#
# Revision 1.1.1.1  1997/02/11 14:26:54  hume
# For Tk 4.2
#
# Revision 1.1.1.1  1996/07/10 02:01:16  hume
# Reorganized and modified for Tk4.0 dp3.3.
#
# Revision 1.3  1996/02/17  03:22:04  hume
# Had index problem because proc was not left justified.
#
# Revision 1.2  1996/01/31  12:47:49  hume
# Minor polishing.
#
# Revision 1.1  1995/12/28  20:21:50  hume
# Changing and adding HIS content.
#
#
#
namespace eval ::dmh {
proc comm_tracewin {obj} {
    set w .tr_${obj}
    if { [winfo exists $w] } {
        wm deiconify $w
        raise $w
        return $w
        }
    global $obj
    toplevel $w
    wm title $w "$obj Trace"
    menu $w.m -tearoff 0 -relief flat

    set m $w.m.w
    $w.m add cascade -label Window -underline 0 -menu $m
    menu $m -tearoff 0
    $m add command -label "Save" -underline 0\
 -command [list ::dmh::comm_tr_save $obj]
    $m add command -label "appendToSave" -underline 6\
 -command [list ::dmh::comm_tr_save $obj {} a]
    $m add command -label "saveAs..." -underline 4\
 -command [list ::dmh::comm_tr_saveas $obj]
    $m add separator
    $m add command -label "Clear" -underline 0\
 -command "$w.f.lb delete 0 end"
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
 -command "$obj reset"
    $m add separator
    $m add command -label "Close $obj..." -underline 0 \
 -command [list ::dmh::comm_tracewin_close $obj]

    set m $w.m.t
    $w.m add cascade -label Tracing -underline 0 -menu $m
    menu $m -tearoff 0
    $m add command -label "$obj Tracing"
    $m add separator
    set TRACE [set ${obj}(TRACE)]
foreach rec { {cb1 1 "Reads and Writes"}\
 {cb2 2 "Parameter Changes"}\
 {cb200 0x200 "Received Messages"}\
 {cb400 0x400 "Callback Dispatching"}\
 {cb40 0x40 "Receive Replay Tracing"}\
 {cb80 0x80 "Send    Replay Tracing"} } {
        vset $rec [list sub bit txt]
        set ${obj}($sub) [expr $bit & $TRACE ? 1:0]
        $m add check -label $txt -variable ${obj}($sub)\
 -command [list ::dmh::tracebitsync $obj $sub $bit]
        }
    set m $w.m.r
    $w.m add cascade -label Replay -underline 0 -menu $m
    menu $m -tearoff 0
    $m  add command -label "re-Send last send" -underline 3\
 -command [list ::dmh::comm_resend_last $obj]
    $m  add command -label "re-Receive last receive" -underline 3\
 -command [list ::dmh::comm_rerecv_last $obj]
    $m add command -label "Window..." -underline 0\
 -command [list ::dmh::comm_replaywin $obj]


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

proc comm_tracewin_atexit {obj} {
    global $obj
    unset ${obj}(tracewin)
    foreach sub {trace rtrace strace} {
        trace vdelete ${obj}($sub) w ::dmh::comm_tracewin_trace
        }
    }

proc comm_tracewin_trace {obj name2 op} {
    set w .tr_${obj}
    if { ![winfo exists $w] } {
        trace vdelete ${obj}($name2) $op ::dmh::comm_tracewin_trace
        }
    global ${obj}
    set text [set ${obj}($name2)]
    if { $name2 == "rtrace" } { set p "<<<R<<" }\
    elseif { $name2 == "strace" } { set p ">>S>>>" }\
    else { set p "trace:" }
    set otext ""
    foreach line [split $text \n] {
         lappend otext "$p $line"
        }
    comm_tracewin_append $obj [join $otext \n]
    }


#
# add to the listbox keeping the number of lines
# in check and scrolling to show the latest
#
proc comm_tracewin_append {obj txt} {
    set lb ".tr_${obj}.f.lb" 
    foreach line [split $txt \n] {
        $lb insert end $line
        }
    set sz [$lb size]
    if { $sz >= 400 } {
        $lb delete 0 39
        incr sz -40
        }
    incr sz -20
    if { $sz < 0 } { set sz 0 }
    $lb yview $sz
    }

proc comm_tracewin_show obj {
    global $obj
    set txt ""
    foreach sub [lsort [array names $obj]] {
        append txt [list set ${obj}($sub) [set ${obj}($sub)]]\n
        }
    comm_tracewin_append $obj $txt
    }
        

proc comm_tracewin_close {obj} {
    global $obj
    set w .tr_$obj
    set pik [tk_dialog $w.rusure "Close $obj" "Closing\
 $obj will cease communications and eliminate\
 the connection \"$obj\".  Please confirm your action."\
 warning 1 Close Cancel]
    if { $pik == 0 } { $obj close }
    }
 

proc tracebitsync {obj sub bit} {
    global $obj
    if { [set ${obj}($sub)] } { 
       set ${obj}(TRACE) [expr [set ${obj}(TRACE)] | $bit]
       }\
    else {
       set ${obj}(TRACE) [expr [set ${obj}(TRACE)] & ~$bit]
       }
    }


proc comm_tr_save {obj {pathname {}} {mode w}} {
    global $obj
    set element tracesavefile
    set w .tr_${obj}
    if { [llength $pathname] == 0 } {
        if { [info exists ${obj}($element)] } {
            set pathname [set ${obj}($element)]
            } 
        if { [llength $pathname] == 0 } {
            comm_tr_saveas $obj
            return
            }
        }
    set lb ${w}.f.lb
    set text ""
    set ct [$lb size]
    if { [catch { open $pathname $mode } fid] } {
        tk_dialog $w.pop "File Open" \
"File $pathname could not be opened for writing." error 0 Dismiss
        return
        }
    for {set i 0} {$i < $ct} {incr i } {
        append text [$lb get $i]\n
        }
    puts $fid $text
    close $fid
    set ${obj}($element) $pathname
    }

proc comm_tr_saveas obj {
    global $obj
    set ext .txt
    set element tracesavefile
    set w .tr_${obj}
    if {[info exists ${obj}($element)] } {
        set pathname [set ${obj}($element)]
        }\
    else { set pathname {} }
    set types [list [list {SECS Trace Save Files} $ext TEXT] [list {Any filename} *.* TEXT]]
    set pathname [tk_getSaveFile -parent $w -filetypes $types -defaultextension $ext \
 -initialfile $pathname -title "Save $obj Trace Window to File As"]
    if { [llength $pathname] == 0 } return
    # -defaultextension not working
    # if you do not give the file your own
    # ".extension" we give it, except on the mac
    #if { $tcl_platform(platform) != "macintosh" } {
    #    if { [string first . $pathname] < 0 } { append pathname $ext }
    #    }
    comm_tr_save $obj $pathname w
    }
} ;# namespace

