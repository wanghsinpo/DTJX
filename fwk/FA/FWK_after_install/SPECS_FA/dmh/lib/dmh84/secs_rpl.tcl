# $Header: /usr/cvsroot/tcllib84/secs_rpl.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1996, 2001 Hume Integration Software
# All Rights Reserved
#
# $Log: secs_rpl.tcl,v $
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.3  2001/11/15 17:14:17  hume
# Updated company name.
#
# Revision 1.2  2001/05/25 22:41:12  hume
# Backup restoration.
#
# Revision 1.2  2001/05/18 18:19:36  hume
# Added trace window save actions as suggested by Pierre Gauthier of Agilent.
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
# Revision 1.2  1999/05/06 21:55:22  hume
# Replaced use of menubuttons to have accelerator keys work on NT.
#
# Revision 1.1.1.1  1997/10/03 02:31:41  hume
# From tcllib42 with edits.
#
# Revision 1.2  1997/05/31 14:33:24  hume
# Revised use of tk_dialog - created as child of toplevel parent in case root
# window is iconified, it still shows up.  Deleted obsolete tk_MenuBar calls.
#
# Revision 1.1.1.1  1997/02/11 14:26:54  hume
# For Tk 4.2
#
# Revision 1.1.1.1  1996/07/10 02:01:16  hume
# Reorganized and modified for Tk4.0 dp3.3.
#
# Revision 1.4  1996/02/14  02:34:21  hume
# More logic in C code.
#
# Revision 1.3  1996/02/08  13:24:30  hume
# Resend last and receive last will tell you you need Replay Tracing.
#
# Revision 1.2  1996/02/08  13:11:39  hume
# Has dialogs for replay actions when nothing is selected.
#
# Revision 1.1  1996/01/31  12:48:53  hume
# Rewrote tracewin code.  Added replay window.
#
namespace eval ::dmh {

proc secs_resend_last obj {
    global $obj
    set txt [set ${obj}(last_send)]
    if { [llength $txt] == 0 } {
        if { [expr [set ${obj}(TRACE)] & 0x80] } { set txt "" }\
        else { set txt "You need to have Replay Tracing on to use this feature." }
        tk_dialog .tr_$obj.pop "Resend Last Message"\
 "There is no previous message to resend. $txt" error 0 Dismiss
        return
        }
    secs_resend $obj $txt
    }

proc secs_rerecv_last obj {
    global $obj
    set txt [set ${obj}(last_recv)]
    if { [llength $txt] == 0 } {
        if { [expr [set ${obj}(TRACE)] & 0x40] } { set txt "" }\
        else { set txt "You need to have Replay Tracing on to use this feature." }
        tk_dialog .tr_$obj.pop "Re-Receive Last Message"\
 "There is no previously received message to simulate receiving. $txt" error 0 Dismiss
        return
        }
    secs_rereceive $obj $txt
    }

proc secs_replaywin obj {
    global $obj
    set w .sr_${obj}
    if { [winfo exists $w] } {
        wm deiconify $w
        raise $w
        return $w
        }

    set ${obj}(replay_file) ""
    set ${obj}(replaywin) $w
    # turn on tracing for replay
    set ${obj}(cb40) 1
    set ${obj}(cb80) 1
    tracebitsync $obj cb40 0x40
    tracebitsync $obj cb80 0x80
    toplevel $w
    wm title $w "Hume Integration's SECS Replay Workbench - $obj"
    wm iconname $w "$obj SECS\nReplay"
    wm minsize $w 6 6
    menu $w.m -tearoff 0 -relief flat
    set m $w.m.f
    $w.m add cascade -label File -underline 0 -menu $m
    menu $m -tearoff 0
    $m add command -label "New" -underline 0 \
 -command [list ::dmh::secs_rw_new $obj]
    $m add command -label "Open..." -underline 0 \
 -command [list ::dmh::secs_rw_open $obj]
    $m add command -label "Save" -underline 0 \
 -command [list ::dmh::secs_rw_save $obj]
    $m add command -label "saveAs..." -underline 4\
 -command [list ::dmh::secs_rw_saveas $obj]
    $m add separator
    $m add command -label "Dismiss" -underline 0 \
 -command "destroy $w"
    $m add separator
    $m add command -label "Exit..." -underline 0 \
 -command "if {\[tk_dialog .sr_$obj.pop {Exit Program} {Please confirm\
 the shutdown of this program.} questhead 0 Cancel Ok\] == 1 } { exit }"

    $w configure -menu $w.m

    frame $w.f
    pack $w.f -side top -expand yes -fill both
    frame $w.f.l
    pack $w.f.l -side left -expand yes -fill both
    frame $w.f.r
    pack $w.f.r -side right -fill y
    scrollbar $w.f.l.v -relief sunken -command "$w.f.l.lb yview"
    scrollbar $w.f.l.h -relief sunken -command "$w.f.l.lb xview" -orient horizontal
    pack $w.f.l.v -side right -fill y
    pack $w.f.l.h -side bottom -fill x
    listbox $w.f.l.lb -font fixed -setgrid 1 -relief sunken\
 -xscroll "$w.f.l.h set" -yscroll "$w.f.l.v set"
    pack $w.f.l.lb -side left -expand yes -fill both
   
    button $w.f.r.bs -text "Send" -width 10\
 -command [list ::dmh::secs_replaywin_send $obj $w.f.l.lb]
    button $w.f.r.br -text "Receive" -width 10\
 -command [list ::dmh::secs_replaywin_recv $obj $w.f.l.lb]
    pack $w.f.r.bs $w.f.r.br -padx 2m -pady 5m -side top
    $w.f.l.lb configure -width 80 -height 24 
    
    foreach sub {last_send last_recv} {
        trace variable ${obj}($sub) w ::dmh::secs_replaywin_trace
        }
    bind  $w.f.l.lb <Destroy> "+ ::dmh::secs_replaywin_atexit $obj"
    return $w
    }

proc secs_rw_new obj {
    global $obj
    set lb .sr_${obj}.f.l.lb
    $lb delete 0 end
    set ${obj}(replay_file) ""
    }

proc secs_rw_open {obj {pathname ""}} {
    global $obj
    set w .sr_${obj}
    if { $pathname == "" } {
        #set action "secs_rw_open $obj"
        #fileselect "" *.srp "Open SECS Replay File" $action
        #return
        set types {{"SECS Replay Files" {.srp} TEXT}}
        set pathname [tk_getOpenFile -parent $w -filetypes $types\
  -title "Open SECS Replay File"]
        if { [llength $pathname] == 0 } return
        }
    if { [catch {open $pathname r} fid] } {
        tk_dialog $w.pop "File Open" \
"File $pathname could not be opened for reading." error 0 Dismiss
        return
        }
    set text [read $fid]
    close $fid
    set lb .sr_${obj}.f.l.lb
    $lb delete 0 end
    foreach line $text {
        if { $line != "" } {
            $lb insert end $line
            }
        }
    set ${obj}(replay_file) $pathname
    }
    
proc secs_rw_save {obj {pathname ""}} {
    global $obj
    set w .sr_${obj}
    if { [llength $pathname] == 0 } {
        set pathname [set ${obj}(replay_file)]
        if { [llength $pathname] == 0 } {
            secs_rw_saveas $obj
            return
            }
        }
    set lb .sr_${obj}.f.l.lb
    set text ""
    set ct [$lb size]
    if { [catch { open $pathname w } fid] } {
        tk_dialog $w.pop "File Open" \
"File $pathname could not be opened for writing." error 0 Dismiss
        return
        }
    for {set i 0} {$i < $ct} {incr i } {
        append text "{[$lb get $i]}\n"
        }
    puts $fid $text
    close $fid
    set ${obj}(replay_file) $pathname
    }

proc secs_rw_saveas obj {
    global tcl_platform
    #fileselect "" *.srp "Save Replay File As" "secs_rw_save $obj"
    set w .sr_${obj}
    set types {{"SECS Replay Files" {.srp} TEXT}}
    set pathname [tk_getSaveFile -parent $w -filetypes $types\
 -defaultextension .srp -title "Save Replay File As"]
    if { [llength $pathname] == 0 } return
    # -defaultextension .srp not working
    # if you do not give the file your own
    # ".extension" we give it .srp, except on the mac
    if { $tcl_platform(platform) != "macintosh" } {
        if { [string first . $pathname] < 0 } { append pathname .srp }
        }
    secs_rw_save $obj $pathname
    }

proc secs_replaywin_send {obj lb} {
    set w .sr_${obj}
    set i [lindex [$lb curselection] 0]
    if { $i == "" } { 
        tk_dialog $w.pop "SECS Replay Send" \
 "Select a message to send in the list before indicating the send action."\
 warning 0 Dismiss 
        return
        }
    set txt [$lb get $i]
    secs_resend $obj $txt
    }

# send the indicated message out the port    
proc secs_resend {obj txt} {
    vset $txt "ts sfr tsn"
    $obj put $sfr $tsn
    }
    
# simulate receiving the indicated message
# we dont fuss about the quality of the data since the
# interpreter traps errors
proc secs_replaywin_recv {obj lb} {
    global $obj
    set w .sr_${obj}
    set i [lindex [$lb curselection] 0]
    if { $i == "" } { 
        tk_dialog $w.pop "SECS Replay Receive" \
 "Select a message to receive in the list before indicating the receive action."\
 warning 0 Dismiss 
        return
        }
    set txt [$lb get $i]
    secs_rereceive $obj $txt
    }

proc secs_rereceive {obj txt} {
    global $obj
    vset $txt "ts sfr tsn system ex callback"
    # we can re-expect a reply if the expectation data is there
    if { [llength $system] && [llength $ex] } {
        set sub EX_$system
        set ${obj}($sub) $ex
        }\
    else {
       # We really ought to have system bytes for a receive, so
       # we will assign a unique one just like we do
       # when we send a primary
       if { ![llength $system] } {
           incr ${obj}(SYSTEM)
           set system [set ${obj}(SYSTEM)]
           }
       }
    set SFR [string toupper $sfr]
    vset [split $SFR "SFR"] "x stream func"
    if { [string first R $SFR ] > 0 } { set reply 1 } else { set reply 0 }
    secs_msg_in $obj $stream $func $reply $system $tsn
    }

proc secs_replaywin_trace {obj name2 op} {
    set w .sr_${obj}
    if { ![winfo exists $w] } {
        trace vdelete ${obj}($name2) $op ::dmh::secs_replywin_trace
        }
    global ${obj}
    set text [set ${obj}($name2)]
    set lb ".sr_${obj}.f.l.lb"
    $lb insert end $text
    set sz [$lb size]
    if { $sz >= 400 } {
        $lb delete 0 39
        incr sz -40
        }
    incr sz -20
    if { $sz < 0 } { set sz 0 }
    $lb yview $sz
    }

proc secs_replaywin_atexit {obj} {
    global $obj
    unset ${obj}(replaywin)
    foreach sub {last_send last_recv} {
        trace vdelete ${obj}($sub) w ::dmh::secs_replaywin_trace
        }
    }

} ;# namespace
