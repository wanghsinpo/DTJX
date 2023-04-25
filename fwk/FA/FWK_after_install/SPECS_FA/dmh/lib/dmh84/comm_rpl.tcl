# $Header: /usr/cvsroot/tcllib84/comm_rpl.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
#
# $Log: comm_rpl.tcl,v $
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.1  2000/03/09 15:27:54  hume
# Comm replay tracing.
#
#
#
namespace eval ::dmh {
proc comm_resend_last obj {
    global $obj
    set txt [set ${obj}(last_send)]
    if { [llength $txt] == 0 } {
        if { [expr [set ${obj}(TRACE)] & 0x80] } { set txt "" }\
        else { set txt "You need to have Replay Tracing on to use this feature." }
        tk_dialog .tr_$obj.pop "Resend Last Message"\
 "There is no previous message to resend. $txt" error 0 Dismiss
        return
        }
    comm_resend $obj $txt
    }

proc comm_rerecv_last obj {
    global $obj
    set txt [set ${obj}(last_recv)]
    if { [llength $txt] == 0 } {
        if { [expr [set ${obj}(TRACE)] & 0x40] } { set txt "" }\
        else { set txt "You need to have Replay Tracing on to use this feature." }
        tk_dialog .tr_$obj.pop "Re-Receive Last Message"\
 "There is no previously received message to simulate receiving. $txt" error 0 Dismiss
        return
        }
    comm_rereceive $obj $txt
    }

proc comm_replaywin obj {
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
    wm title $w "Hume Integration's Comm Replay Workbench - $obj"
    wm iconname $w "$obj COMM\nReplay"
    wm minsize $w 6 6
    menu $w.m -tearoff 0 -relief flat
    set m $w.m.f
    $w.m add cascade -label File -underline 0 -menu $m
    menu $m -tearoff 0
    $m add command -label "New" -underline 0 \
 -command [list ::dmh::comm_rw_new $obj]
    $m add command -label "Open..." -underline 0 \
 -command [list ::dmh::comm_rw_open $obj]
    $m add command -label "Save" -underline 0 \
 -command [list ::dmh::comm_rw_save $obj]
    $m add command -label "saveAs..." -underline 5\
 -command [list ::dmh::comm_rw_saveas $obj]
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
 -command [list ::dmh::comm_replaywin_send $obj $w.f.l.lb]
    button $w.f.r.br -text "Receive" -width 10\
 -command [list ::dmh::comm_replaywin_recv $obj $w.f.l.lb]
    pack $w.f.r.bs $w.f.r.br -padx 2m -pady 5m -side top
    $w.f.l.lb configure -width 80 -height 24 
    
    foreach sub {last_send last_recv} {
        trace variable ${obj}($sub) w ::dmh::comm_replaywin_trace
        }
    bind  $w.f.l.lb <Destroy> "+ ::dmh::comm_replaywin_atexit $obj"
    return $w
    }

proc comm_rw_new obj {
    global $obj
    set lb .sr_${obj}.f.l.lb
    $lb delete 0 end
    set ${obj}(replay_file) ""
    }

proc comm_rw_open {obj {pathname ""}} {
    global $obj
    set w .sr_${obj}
    if { $pathname == "" } {
        set types {{"Comm Replay Files" {.crp} TEXT}}
        set pathname [tk_getOpenFile -parent $w -filetypes $types\
  -title "Open Comm Replay File"]
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
    
proc comm_rw_save {obj {pathname ""}} {
    global $obj
    set w .sr_${obj}
    if { [llength $pathname] == 0 } {
        set pathname [set ${obj}(replay_file)]
        if { [llength $pathname] == 0 } {
            comm_rw_saveas $obj
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

proc comm_rw_saveas obj {
    global tcl_platform
    set w .sr_${obj}
    set types {{"Comm Replay Files" {.crp} TEXT}}
    set pathname [tk_getSaveFile -parent $w -filetypes $types\
 -defaultextension .crp -title "Save Replay File As"]
    if { [llength $pathname] == 0 } return
    # -defaultextension .srp not working
    # if you do not give the file your own
    # ".extension" we give it .crp, except on the mac
    if { $tcl_platform(platform) != "macintosh" } {
        if { [string first . $pathname] < 0 } { append pathname .crp }
        }
    comm_rw_save $obj $pathname
    }

proc comm_replaywin_send {obj lb} {
    set w .sr_${obj}
    set i [lindex [$lb curselection] 0]
    if { $i == "" } { 
        tk_dialog $w.pop "Comm Replay Send" \
 "Select a message to send in the list before indicating the send action."\
 warning 0 Dismiss 
        return
        }
    set txt [$lb get $i]
    # needs to start with put[l] to be sendable
    #{yyyy-mm-dd hh:mm:ss} put
    #01234567890123456789012
    if { [string first put $txt] != 22} {
        tk_dialog $w.pop "Comm Replay Send" \
 "Select an list in the list that is sendable using the put or putl commands."\
 warning 0 Dismiss 
        return
        }
 
    comm_resend $obj $txt
    }

# send the indicated message out the port    
proc comm_resend {obj txt} {
    vset $txt "ts verb data"
    $obj $verb $data
    }
    
# simulate receiving the indicated message
# we dont fuss about the quality of the data since the
# interpreter traps errors
proc comm_replaywin_recv {obj lb} {
    global $obj
    set w .sr_${obj}
    set i [lindex [$lb curselection] 0]
    if { $i == "" } { 
        tk_dialog $w.pop "Comm Replay Receive" \
 "Select a message to receive in the list before indicating the receive action."\
 warning 0 Dismiss 
        return
        }
    set txt [$lb get $i]
    if { [string first reception $txt] != 22 } {
        tk_dialog $w.pop "Comm Replay Receive"\
 "Select an list in the list that represents a reception."\
 warning 0 Dismiss 
        return
        }
    comm_rereceive $obj $txt
    }

proc comm_rereceive {obj txt} {
    global $obj
    vset $txt [list ts rec callback]
    eval $callback
    }

proc comm_replaywin_trace {obj name2 op} {
    set w .sr_${obj}
    if { ![winfo exists $w] } {
        trace vdelete ${obj}($name2) $op ::dmh::comm_replywin_trace
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

proc comm_replaywin_atexit {obj} {
    global $obj
    unset ${obj}(replaywin)
    foreach sub {last_send last_recv} {
        trace vdelete ${obj}($sub) w ::dmh::comm_replaywin_trace
        }
    }

} ;# namespace
