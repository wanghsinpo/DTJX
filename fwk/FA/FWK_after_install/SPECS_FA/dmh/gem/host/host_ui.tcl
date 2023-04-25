# $Header: /usr/cvsroot/gem/host/host_ui.tcl,v 1.24 2005/02/24 15:31:36 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 2004, Hume Integration Software
# All Rights Reserved
#
# $Log: host_ui.tcl,v $
# Revision 1.24  2005/02/24 15:31:36  hume
# Changed exec mkdir to file mkdir for recipe directory create.
#
# Revision 1.23  2004/10/12 15:06:05  hume
# Fixed inconsistency of using vfei_$EVENT_ID instead of vfei_$CEID for report
# configuration delete.
#
# Revision 1.22  2004/09/28 13:39:22  hume
# The recipe upload directory is configurable and defaults to separate sub-
# directories for each connection name.
#
# Revision 1.21  2004/09/04 23:24:47  hume
# write recipe data as binary in case of binary data passed as ASCII strings
#
# Revision 1.20  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.19  2002/09/24 15:56:20  hume
# Updated calls to ei_var_query to explicitly call with a list of names.
# Sets a proper example, and fixes a bug with ei_event_discovery when
# EventsEnabled variable name contains white space.
#
# Revision 1.18  2002/07/23 14:08:07  hume
# Made small changes to accomodate recipe names with embedded spaces.
#
# Revision 1.17  2002/05/10 15:46:38  hume
# Needed a tweak so that DVVAL items tied to event reports are included with
# SV items in the report definition at the equipment.
#
# Revision 1.16  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.15  2001/06/21 01:22:51  hume
# Host UI failed to enable events that had empty reports.
#
# Revision 1.14  2000/12/12 21:38:10  hume
# Changes to keep (control_state) in sync with the equipment. New
# CEID_OFFLINE variable is used to specify the control state offline event.
#
# Revision 1.13  1999/07/29 13:48:16  hume
# Fixed S10F1 error when ei_ui is built and dismissed repeatedly.  Non
# VFEI aware term_display code no longer displaces VFEI S10F1 handling.
# EI window is re-created if need be to display equipment operator message.
#
# Revision 1.12  1999/05/27 18:24:35  hume
# Added braces to expressions per procheck.
#
# Revision 1.11  1999/04/09 21:49:47  hume
# Recipe names (PPIDs) may not be valid filenames.  Added ei_ui_ppid_filename
# to map to a filename, and changed the file format to store the original
# PPID name that came from the tool.
#
# Revision 1.10  1999/04/09 21:11:09  hume
# Updated to handle CEIDs that have white space in or around their names.
#
# Revision 1.9  1999/01/20 17:51:34  hume
# Custom varmethod can be used with ANY varclass - changed ProcessState
# text mapping customization to keep ProcessState as variable SV.
#
# Revision 1.8  1999/01/19 20:04:40  hume
# Text for process states on UI, tweaked C & C label widths.
#
# Revision 1.7  1998/11/17 20:28:33  hume
# Event descriptions are visible, alarm list has horizontal scroll.
#
# Revision 1.6  1998/11/12 22:22:56  hume
# Added event discovery procedure and UI button.
#
# Revision 1.5  1998/11/03 20:50:04  hume
# UI Process State or recipe would not update for multiple ui's.
#
# Revision 1.4  1998/03/19 14:19:37  hume
# Tweak needed so DVVAL variables could be tied to event reports.
#
# Revision 1.3  1998/01/29 13:14:32  hume
# Window will be raised instead of re-created if reinvoked.
#
# Revision 1.2  1997/11/06 14:00:22  hume
# Modified ALID handling to accommodate I8 or U8 type.  Put close logic on
# ui subscriptions in case gemhost ui was dismissed.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#

#
# A user interface for the Host Interface to SECS equipment
# 
proc ei_ui spname {
    global $spname

    set w .ei_$spname
    if { [winfo exists $w] } {
        wm deiconify $w
        raise $w
        return $w
        }

    toplevel $w
    wm title $w "Host Equipment Interface -\"$spname\""

    # we will build a bunch of grouped widgets and arrange them in
    # this grid.  The grid is created first to get the stacking
    # order correct.
    frame $w.grid
    pack $w.grid -side top -expand 1 -fill both

    # Communications and Control
    frame $w.comm -borderwidth 2 -relief raised
    label $w.comm.l -text "Communications & Control"
    pack $w.comm.l -side top -fill x
    frame $w.comm.s
    pack $w.comm.s -side top -fill x  -padx 2m -pady 2m
    label $w.comm.s.l -text "Comm State:" -anchor e -width 16
    label $w.comm.s.t -textvariable ${spname}(comm_state) -relief sunken\
       -width 30 -anchor w
    pack $w.comm.s.l $w.comm.s.t  -side left
    frame $w.comm.c
    pack $w.comm.c -side top -fill x  -padx 2m -pady 2m
    label $w.comm.c.l -text "Control State:" -anchor e -width 16
    label $w.comm.c.t -textvariable ${spname}(control_state) -relief sunken\
       -width 30 -anchor w
    pack $w.comm.c.l $w.comm.c.t  -side left

    frame $w.comm.fb
    pack $w.comm.fb -side top -fill x
    # use -whenreply so that reply and possible S1F0 are handled in same proc
    button $w.comm.fb.n -text {Request Online}  \
 -command "$spname put S1F17R -whenreply {ei_online_ack $spname}"
    pack $w.comm.fb.n -side left -padx 5m
    button $w.comm.fb.f -text {Request Offline}  \
 -command "$spname put S1F15R -whenreply {ei_offline_ack $spname}"
    pack $w.comm.fb.f -side left -padx 5m

    # VFEI Reports
    frame $w.vfei -borderwidth 2 -relief raised
    label $w.vfei.l -text "VFEI Reports"
    pack $w.vfei.l -side top -fill x
    frame $w.vfei.f
    label $w.vfei.f.l -text "Event           Description         Variables" -anchor w
    pack $w.vfei.f.l -side top -fill x
    scrollbar $w.vfei.f.sy -relief sunken -command "$w.vfei.f.lb yview"
    scrollbar $w.vfei.f.sx -relief sunken -command "$w.vfei.f.lb xview"\
 -orient horizontal
    listbox $w.vfei.f.lb -yscroll "$w.vfei.f.sy set" -relief sunken \
  -font fixed -height 3 -selectmode browse -xscroll "$w.vfei.f.sx set"
    pack $w.vfei.f.sy -side right -fill y
    pack $w.vfei.f.sx -side bottom -fill x
    pack $w.vfei.f.lb -side left -expand 1 -fill both
    pack $w.vfei.f -side top -expand 1 -fill both -padx 2m -pady 1m
    frame $w.vfei.fb
    pack $w.vfei.fb -side top -fill x
    foreach pair {{c Create} {e Edit} {d Delete} {p Save}} {
        vset $pair "tok label"
        button $w.vfei.fb.$tok -text $label \
 -command "ei_ui_vfei_action $spname $tok $w.vfei.f.lb" -width 8
        pack $w.vfei.fb.$tok -side left 
        }
    label $w.vfei.ll -text "/\\ Offline Configuration /\\         \\/ Online Actions \\/"
    pack  $w.vfei.ll -side top -fill x
   # other commands
    frame $w.vfei.fbb
    pack $w.vfei.fbb -side top -fill x
    foreach pair {{i "Initialize" } {n "Enable Events" }\
 {v "Data Refresh"} {q "Event Discovery"}} {
        vset $pair "tok label"
        button $w.vfei.fbb.$tok -text $label \
 -command "ei_ui_vfei_action $spname $tok $w.vfei.f.lb"
        pack $w.vfei.fbb.$tok -side left 
        }
    after 1 "ei_ui_report_refresh $spname $w.vfei.f.lb"

    # Processing & Recipes
    frame $w.proc -borderwidth 2 -relief raised
    label $w.proc.l -text "Processing & Process Programs"
    pack $w.proc.l -side top -fill x
    frame $w.proc.s
    pack $w.proc.s -side top -fill x  -padx 2m -pady 2m
    label $w.proc.s.l -text "Process State:" -anchor e -width 14
    label $w.proc.s.t -textvariable ${spname}(proc_state) -relief sunken\
       -width 30 -anchor w
    pack $w.proc.s.l $w.proc.s.t  -side left
    frame $w.proc.c
    pack $w.proc.c -side top -fill x  -padx 2m -pady 2m
    label $w.proc.c.l -text "PPExecName:" -anchor e -width 14
    label $w.proc.c.t -textvariable ${spname}(PPExecName) -relief sunken\
       -width 30 -anchor w
    pack $w.proc.c.l $w.proc.c.t  -side left
    frame $w.proc.f
    label $w.proc.f.l -text "Equipment Resident Process Programs" -anchor w
    pack $w.proc.f.l -side top -fill x

    scrollbar $w.proc.f.sy -relief sunken -command "$w.proc.f.lb yview"
    listbox $w.proc.f.lb -yscroll "$w.proc.f.sy set" -relief sunken \
  -font fixed -height 3 -selectmode extended
    pack $w.proc.f.sy -side right -fill y
    pack $w.proc.f.lb -side left -expand 1 -fill both
    pack $w.proc.f -side top -expand 1 -fill both -padx 2m -pady 1m
    frame $w.proc.fb
    pack $w.proc.fb -side top -fill x
    foreach pair {{r Refresh} {s Select} {u Upload} {d Download}} {
        vset $pair "tok label"
        button $w.proc.fb.$tok -text $label \
 -command "ei_ui_proc_action $spname $tok $w.proc.f.lb" 
        pack $w.proc.fb.$tok -side left
        }
    frame $w.proc.fbb
    pack $w.proc.fbb -side top -fill x
    foreach pair {{s Start} {p Pause} {r Resume} {t Stop} {a Abort}} {
        vset $pair "tok label cmd"
        button $w.proc.fbb.$tok -text $label \
 -command "ei_ui_proc_cmd $spname $tok $w"
        pack $w.proc.fbb.$tok -side left 
        }
    # subscribe to latest values for realtime update
    SQL "open sub ${spname}_ui to ei_variable proc=ei_ui_proc\
 insert update varvalue where spname='$spname' and (VFEIname='PP_EXEC_NAME'\
 or VFEIname='PROCESS_STATE')"

    # Alarm Status
    frame $w.alrm -borderwidth 2 -relief raised
    label $w.alrm.l -text Alarms
    pack $w.alrm.l -side top -fill x
    frame $w.alrm.f
    label $w.alrm.f.l -text "ALID Enabled Set Description (ALTX)" -anchor w
    pack $w.alrm.f.l -side top -fill x

    scrollbar $w.alrm.f.sy -relief sunken -command "$w.alrm.f.lb yview"
    scrollbar $w.alrm.f.sx -relief sunken -command "$w.alrm.f.lb xview"\
 -orient horizontal
    listbox $w.alrm.f.lb -yscroll "$w.alrm.f.sy set" -relief sunken \
  -font fixed -height 3 -selectmode extended
    pack $w.alrm.f.sy -side right -fill y
    pack $w.alrm.f.sx -side bottom -fill x
    pack $w.alrm.f.lb -side left -expand 1 -fill both
    pack $w.alrm.f -side top -expand 1 -fill both -padx 2m -pady 1m
    frame $w.alrm.fb
    pack $w.alrm.fb -side top -fill x
    foreach pair {{e Enable} {d Disable} {s {Select All}} {p Save}} {
        vset $pair "tok label"
        button $w.alrm.fb.$tok -text $label \
 -command "ei_ui_alarm_action $spname $tok $w.alrm.f.lb" -width 8
        pack $w.alrm.fb.$tok -side left
        }
    after 1 "ei_ui_alarm_refresh $spname $w.alrm.f.lb"

    # Terminal Services
    frame $w.term -borderwidth 2 -relief raised
    label $w.term.l -text "Terminal Services"
    pack $w.term.l -side top -fill x
    frame $w.term.o
    frame $w.term.i
    pack $w.term.o $w.term.i -side top -fill x -padx 4m
    label $w.term.o.l -text "From Host:" -anchor e -width 12
    text $w.term.o.h -width 60 -height 3 
    button $w.term.o.b -text Send \
 -command "ei_term_req $spname $w.term.o.h $w.term.o.b"
    pack $w.term.o.l $w.term.o.h $w.term.o.b -side left

    label $w.term.i.l -text "From Equip:" -anchor e -width 12
    text $w.term.i.h -width 60 -height 3 -state disabled
    pack $w.term.i.l $w.term.i.h -side left

    # if we are not already listening to S10F1 for VFEI,....
    if { ![info exists ${spname}(using_VFEI)] || ![set ${spname}(using_VFEI)] } {
        $spname whenever S10F1 "ei_term_disp $spname"
        }

    # arrangement
    grid $w.comm -in $w.grid -row 0 -column 0 -sticky nesw -padx 1 -pady 1
    grid $w.alrm -in $w.grid -row 0 -column 1 -sticky nesw -padx 1 -pady 1
    grid $w.vfei -in $w.grid -row 1 -column 0 -sticky nesw -padx 1 -pady 1
    grid $w.proc -in $w.grid -row 1 -column 1 -sticky nesw -padx 1 -pady 1
    grid $w.term -in $w.grid -row 2 -column 0 -columnspan 2 -sticky nesw -padx 1 -pady 1

    }



##################### TERMINAL SERVICES ###########################
##################### TERMINAL SERVICES ###########################
##################### TERMINAL SERVICES ###########################

#
# send terminal message
#
proc ei_term_req {spname text button} {
    $button configure -state disabled
    set TID "B 0"
    set TEXT [list A [$text get 0.0 end]]
    set TEXT [string trimright $TEXT \n]
    if { [ catch {$spname put S10F3 [list L $TID $TEXT] ei_term_req_cb}] } {
        tk_dialog $w.pop "Terminal Services - \"$spname\""\
 "Your message was NOT received by the equipment." error 0 Dismiss
        }
    $button configure -state normal
    }

proc ei_term_req_cb {spname sfr reason desc} {
    set w .ei_$spname
    if { $reason == "send_failure" } {
        tk_dialog $w.pop "Terminal Services - \"$spname\""\
 "Your message was NOT received by the equipment." error 0 Dismiss
        }\
    elseif { $reason == "send_complete" } {
        tk_dialog $w.pop "Terminal Services - \"$spname\""\
 "Your message was received by the equipment." info 0 Dismiss
        }
    }


#
# recd S10F1 from equipment - terminal message from operator
#
# for this code to be called, the ui existed at an earlier time
# thus we are not running as a background process
# we try to recreate the window to display the message
proc ei_term_disp spname {
    global $spname 
    $spname whenmsg again
    set request [set ${spname}(lastrmsg)]
    set R [expr [string first R [set ${spname}(lastrSFR)]] > 0]
    set w .ei_${spname}.term.i.h
    if { ![winfo exists $w] } {
        set rc [catch {ei_ui $spname}]
        if { $rc } { set w_exists 0 }\
        else { set w_exists 1 }
        }\
    else { set w_exists 1 }
    if {$R} { 
        if { $w_exists} { $spname put S10F2 "B 0" } \
        else { $spname put S10F2 "B 1" } ;# msg not displayed
        }

    if { !$w_exists } return
    rset $request {L2 {tTID TID} {tTEXT TEXT}}
   
    $w configure -state normal
    $w delete 0.0 end
    if { ![string match $TEXT ""] } {
        $w insert 0.0 $TEXT
        catch {
            wm deiconify .ei_${spname}
            raise .ei_${spname}
            }
        }
    $w configure -state disabled
    }


############################# VFEI Reports ########################
############################# VFEI Reports ########################
############################# VFEI Reports ########################
#
proc ei_ui_report_refresh {spname lb} {
    # this is a way to get an extra argument passed to a
    # subscription procedure - define a custom procedure
    proc ei_ui_report_$spname {args} "eval \[concat ei_ui_report\
 $spname $lb \$args \]"
    # clear and refresh the listbox
    $lb delete 0 end
    SQL "close sub $spname to ei_report_cfg"
    SQL "open sub $spname to ei_report_cfg proc=ei_ui_report_$spname \
 sync RPTID,VIDs where spname='$spname' and RPTID like 'vfei_%'"
    }

#
# subscription notice - update view of report_cfg table
#    report_cfg has vfei_<CEID> entries
#
proc ei_ui_report {spname lb notice table cols keys ct err data} {
    if { ![winfo exists $lb] } {
        SQL "close sub $spname to ei_report_cfg"
        return
        }
    set row [lindex $data 0]
    vset $row $cols
    set CEID [substr $RPTID vfei_ {}]
    set reply [SQL "select VFEIname,description from ei_event where spname='$spname' \
 and CEID='$CEID'"]
    vset [lindex [lindex $reply 6] 0] "EVENT_ID description"
    if { $EVENT_ID == "" } return
    set format "%-16s %s %s"
    if { $notice == "update" || $notice == "delete" } {
        set max [$lb size]
        for {set i 0} {$i < $max} {incr i} {
            set text [$lb get $i]
            vset $text "oevent odesc oVIDs"
            if { $oevent == $EVENT_ID } {
                $lb delete $i
                if { $notice  == "delete" } return
                $lb insert $i [format $format [list $EVENT_ID] [list $description] [list $VIDs]]
                return
                }
            }
        return
        }
    if { $notice == "insert" } {
        $lb insert end [format $format [list $EVENT_ID] [list $description] [list $VIDs]]
        return
        }
    }

#
# action button
proc ei_ui_vfei_action {spname tok lb} {
    global $spname
    if { $tok == "p" } { ;# save
        hub_save {ei_event ei_report_cfg ei_event_report_cfg ei_variable}
        return
        }
    if { $tok == "i" } {
        set cmd "CMD/A=\"INITIALIZE\" MID/A=\"$spname\" MTY/A=\"C\" TID/U4=0"
        set cmd [list ei_vfei_cmd $spname $cmd]
        set ${spname}(iresult) ""
        after 1 "set ${spname}(iresult) \[$cmd\]"
        tk_dialog $lb.pop "Initialize" "VFEI Initialize proceeding..."\
 info 0 Dismiss
        if { [set ${spname}(iresult)] == ""  } {
            vwait ${spname}(iresult)
            }
        set reply [set ${spname}(iresult)]
        set ECD [substr $reply "ECD/U4=" { }] 
        set ETX [substr $reply "ETX/A=\"" \"]
        if { $ECD != "0" } {
            tk_dialog $lb.pop "Initialize Result" "The initialization failed.\
 $reply ECD=$ECD, ETX=\"$ETX\"" error 0 Dismiss
            }\
        else {
            tk_dialog $lb.pop "Initialize Result" "The initialization\
 succeeded." info 0 Dismiss
            }
        return
        }
    if { $tok == "n" } { ;# enable events
        set reply [ei_event_enable $spname ""]
        if { $reply == "0" } {
            tk_dialog $lb.pop "Event Enable" "All equipment events should\
 be reported from now on." info 0 Dismiss
            }\
        else {
            tk_dialog $lb.pop "Event Enable" "Enabling the reporting of\
 all equipment events failed ($reply)." error 0 Dismiss
            }
        return
        }
    if { $tok == "q" } { ;# event discovery
        set reply [ei_event_discovery $spname]
        if { $reply == "-1" } {
            tk_dialog $lb.pop "Event Discovery" "A variable\
 with the name EventsEnabled or VFEI name EVENTS_ENABLED was\
 not found, so this action cannot be performed." error 0 Dismiss
           }\
       elseif { $reply == "-2" } {
            tk_dialog $lb.pop "Event Discovery" "Enabling the reporting of\
 all equipment events failed." error 0 Dismiss
            }\
        elseif { $reply == "-3" } {
            tk_dialog $lb.pop "Event Discovery" "EventsEnabled data\
 was not properly formatted." error 0 Dismiss
            }\
        elseif { $reply == "0" } {
            tk_dialog $lb.pop "Event Discovery" "No new events were\
 found." info 0 Dismiss
            }\
        elseif { $reply > 0 } {
            tk_dialog $lb.pop "Event Discovery" "$reply new events were\
 found." info 0 Dismiss
            }
        return
        }
    if { $tok == "v" } { ;# variables
        after 1 "ei_variables_init $spname"
        tk_dialog $lb.pop "Variable Refresh" "Messages to refresh the\
 knowledge of equipment data items have been initiated." info 0 Dismiss
        return
        }
    if { $tok == "c" } { ;# create
        set max [$lb size]
        # build list of inuse VFEIname event IDs
        set defined_events ""
        for {set i 0} {$i < $max} {incr i} {
            lappend defined_events [lindex [$lb get $i] 0]
            }
        # get other possibles
        set where "where spname='$spname' and\
 VFEIname<>'[join $defined_events {' and VFEIname<>'}]'"
        set reply [SQL "select VFEIname,description from ei_event $where"]
        set picks [lindex $reply 6]
        if { [llength $picks] == 0 } {
            tk_dialog $lb.pop "Report Create" "All of the events\
 already have report definitions." error 0 Dismiss
            return
            }
        dmh_listpick $picks "Choose an EVENT_ID for the new report:"\
 "ei_ui_vfei_repnew $spname"
        return
        }
    if { $tok == "d" || $tok == "e" } {
        set index [$lb curselection]
        if { $index == "" } {
            tk_dialog $lb.popup "VFEI Report" \
 "Select a report before indicating this action." error 0 Dismiss
            return
            }
        vset [$lb get $index] "EVENT_ID description VIDs"
        set reply [SQL "select CEID from ei_event where spname='$spname' \
 and VFEIname='$EVENT_ID'"]
        set CEID [lindex [lindex [lindex $reply 6] 0] 0]
        if { $tok == "d" } {
            SQL "delete from ei_report_cfg where \
 spname='$spname' and RPTID='vfei_$CEID'"
            # This assumes our RPTID == CEID map for vfei event reports
            SQL "delete from ei_report_cfg where \
 spname='$spname' and RPTID='$CEID'"
            SQL "delete from ei_event_report_cfg where \
 spname='$spname' and CEID='$CEID' and RPTID='$CEID'"
            # and we assume that the reporting of this event should not
            # be configured to be enabled 
            SQL "update ei_event set host_managed=0, host_wants_enabled=0\
 where spname='$spname' and CEID='$CEID'"
            return
            }
        if { $tok == "e" } {
            # edit the VIDs
            if { [string compare $description ""] } { set phrase " ($description)" }\
            else { set phrase "" }
            set reply [SQL "select VFEIname from ei_variable where\
 spname='$spname' and (varclass='SV' or varclass='SECS_DRVR' or \
 varclass='VFEI_DRVR' or varclass='DVVAL') and VFEIname<>''"]
            set all_list [lsort [lindex $reply 6]]
            dmh_sublist "Select the variables that you want for\
 the event report of ${EVENT_ID}${phrase}" $all_list $VIDs \
 [list ei_ui_vfei_repvids $spname $CEID]\
 Variables "VFEI Event Report Edit"
            }
        }
    }

#
# user has selected updated list of VIDs for VFEI report
# this code assumes CEID == event report RPTID
#
proc ei_ui_vfei_repvids {spname CEID VIDs} {
    set RPTID vfei_$CEID
    set msg "update ei_report_cfg set VIDs='$VIDs' where\
 spname='$spname' and RPTID='$RPTID'"
    SQL $msg
    # for an equipment based event
    # figure out which VIDs are equipment based, 
    # and update the SECS report configuration
    set reply [SQL "select CEID from ei_event where \
 spname='$spname' and CEID='$CEID' and event_class='EQ'"]
    if { [lindex $reply 4] != "1" } {
        # its not an equipment based event, so SECS reports NA
        # next line should not find anything but user maybe changing class
        SQL "delete from ei_event_report_cfg where
 spname='$spname' and CEID='$CEID' and RPTID='$CEID'"
        # ditto this line - we are leaving RPTID==vfei_$CEID
        SQL "delete from ei_report_cfg where\
 spname='$spname' and RPTID='$CEID'"
        return
        }
    set reply [SQL "select varID from ei_variable where\
 spname='$spname' and (varclass='SV' or varclass='DVVAL') and \
 (VFEIname='[join $VIDs {' or VFEIname='}]')"]
    set VarIDs ""
    foreach row [lindex $reply 6] { 
        lappend VarIDs [lindex $row 0] }
    SQL "delete from ei_report_cfg where spname='$spname' and RPTID='$CEID'"
    if { [llength $VarIDs] > 0 } {
        # the SECS level is in terms of varIDs not VFEInames
        SQL "insert into ei_report_cfg (spname, RPTID, VIDs) values\
 ('$spname','$CEID', '$VarIDs')"
        # SECS RPTID == CEID
        SQL "insert into ei_event_report_cfg (spname, CEID, RPTID) values\
 ('$spname','$CEID', '$CEID')"
        }
    }

#
# new event report create
#
proc ei_ui_vfei_repnew {spname text} {
    global $spname
    set VFEIname [lindex $text 0]
    set reply [SQL "select CEID from ei_event where spname='$spname'\
 and VFEIname='$VFEIname'"]
    if { [lindex $reply 4] != "1" } {
       tk_dialog .popup "Report Create" "The VFEI event $VFEIname\
 cannot be mapped to a single CEID using the current ei_event data."\
 error 0 Dismiss
       return
       }
    set CEID [lindex [lindex [lindex $reply 6] 0] 0]
    SQL "insert into ei_report_cfg (spname,RPTID) values\
 ('$spname','vfei_${CEID}')"
    # also, make sure that the reporting of this event is configured
    # to be enabled
    SQL "update ei_event set host_managed=1, host_wants_enabled=1\
 where spname='$spname' and CEID='$CEID'"
    }
 
############################## Alarms #############################
############################## Alarms #############################
############################## Alarms #############################
proc ei_ui_alarm_refresh {spname lb} {
    # this is a way to get an extra argument passed to a
    # subscription procedure - define a custom procedure
    proc ei_ui_alarm_$spname {args} "eval \[concat ei_ui_alarm\
 $spname $lb \$args \]"
    # clear and refresh the alarm listbox
    $lb delete 0 end
    SQL "close sub $spname to ei_alarm"
    SQL "open sub $spname to ei_alarm proc=ei_ui_alarm_$spname \
 sync spname,ALID,is_enabled,is_set,ALTX where spname='$spname'"
    }

#
# subscription notice - update view of alarm table
#
proc ei_ui_alarm {spname lb notice table cols keys ct err data} {
    if { ![winfo exists $lb] } {
        SQL "close sub $spname to ei_alarm"
        return
        }
    set row [lindex $data 0]
    vset $row $cols
    set format "%-10s  %d       %d   {%s}"
    if { $notice == "update" || $notice == "delete" } {
        set max [$lb size]
        for {set i 0} {$i < $max} {incr i} {
            set text [$lb get $i]
            vset $text "oALID was_enabled was_set oALTX"
            if { $oALID == $ALID } {
                $lb delete $i
                if { $notice  == "delete" } return
                if { ![info exists is_enabled] } { set is_enabled $was_enabled }
                if { ![info exists is_set] } { set is_set $was_set }
                if { ![info exists ALTX] } { set ALTX $oALTX }
                $lb insert $i [format $format $ALID $is_enabled $is_set $ALTX]
                return
                }
            }
        return
        }
    if { $notice == "insert" } {
        $lb insert end [format $format $ALID $is_enabled $is_set $ALTX]
        return
        }
    }


# implement UI action on alarm(s)
#  {{e Enable} {d Disable} {s select} {p save}}
proc ei_ui_alarm_action {spname token lb} {
    if { $token == "s" } {
        $lb selection set 0 end
        return
        }
    if { $token == "p" } {
        hub_save ei_alarm
        return
        }
    set selection [$lb curselection]
    if { $selection == "" } {
        set w .ei_$spname
        tk_dialog $w.pop "Alarm Action Usage"\
          "Select one or more alarms from the list before indicating this action."\
          error 0 Dismiss
        return
        }

    set ALIDs ""
    foreach index $selection {
        set record [$lb get $index]
        lappend ALIDs [lindex $record 0]
        }
    set where "where spname='$spname' and (ALID='[join $ALIDs {' or ALID='}]')"
    switch -exact $token {
      e { 
         SQL "update ei_alarm set host_managed=1,host_wants_enabled=1 $where" 
         ei_alarm_enable $spname 1 $ALIDs
        }
      d { 
         SQL "update ei_alarm set host_managed=1,host_wants_enabled=0 $where" 
         ei_alarm_enable $spname 0 $ALIDs
        }
      }
    # view is updated by subscription
    }


################### Process & Recipes ###########################
################### Process & Recipes ###########################
################### Process & Recipes ###########################
#
# {r Refresh} {s Select} {u Upload} {d Download}
#
proc ei_ui_proc_action {spname token lb} {
    global $spname
    if { $token == "r" } {
        # refresh PPExecName, ProcessState 
        set reply [ei_var_query $spname [list PP_EXEC_NAME PROCESS_STATE]\
 VFEIname]
        if { $reply == "TIMEOUT" } {
            set reason [secs_xact_failure $spname]
            tk_dialog $lb.popup "Process Status Refresh" \
 "Fresh status information is not available. ($reason)" error 0 Dismiss
            }
        # refresh recipe dir
        set dirlist [ei_recipe_dir $spname]
        if { $dirlist == "TIMEOUT" } {
            set reason [secs_xact_failure $spname]
            tk_dialog $lb.popup "PP Directory Refresh" \
 "A current Process Program Directory is not available. ($reason)" error 0 Dismiss
            }\
        else {
            $lb delete 0 end
            eval [concat $lb insert end $dirlist]
            }
        return
        }
    if { $token == "d" } { ;# download
        if { ![file isdirectory [set ${spname}(recipe_dir)]] } {
            tk_dialog $lb.popup "Download Process Program"\
 "The recipes directory, \"[set ${spname}(recipe_dir)]\" is not found.  Maybe you have not\
 uploaded any process programs." error 0 Dismiss
            return
            }
        set filename [fileselect [set ${spname}(recipe_dir)] * "Download Recipe"\
 "ei_ui_proc_dnld $spname $lb"]
        return
        }

    set pik [$lb curselection]
    if { $pik == "" } {
        tk_dialog $lb.pop "Process Program Usage"\
          "Select a Process Program from the list before\
 indicating this action ." error 0 Dismiss
        return
        }
    set recipe [$lb get $pik]
    if { $token == "s" } { ;# select
        # each additional arg to ei_rcmd is a name value pair 
        set recspec [list {A PPExecName} [list A $recipe]]
        set reply [ei_rcmd $spname PP-SELECT $recspec]
        if { $reply != "0" } {
            if { $reply == "TIMEOUT" } {
                set reason [secs_xact_failure $spname] }\
            else { set reason "RCMD result $reply" }
            tk_dialog $lb.popup "Process Program Select" \
 "The process program could not be selected at the equipment. ($reason)" error 0 Dismiss
            }\
        else {
            set ${spname}(PPExecName) $recipe
            tk_dialog $lb.popup "Process Program Select" \
 "The Process Program was selected at the equipment." info 0 Dismiss
            }
        return
        }
    if { $token == "u" } { ;# upload
        set reply [ei_recipe_get $spname $recipe]
        # expect "L:2 <ppid> <PPBODY>"
        if { $reply == "" } {
            set reason [secs_xact_failure $spname]
            tk_dialog $lb.popup "Process Program Upload" \
 "The Process Program could not be Uploaded. ($reason)" error 0 Dismiss
            }\
        else {
            set recipe_dir [set ${spname}(recipe_dir)]
            if { ![file isdirectory $recipe_dir] } {
                file mkdir $recipe_dir
                }
            set fname [file join $recipe_dir [ei_ui_ppid_filename $recipe]]
            set fid [open $fname w]
            fconfigure $fid -translation binary 
            puts -nonewline $fid $reply
            close $fid
            tk_dialog $lb.popup "Process Program Upload" \
 "The Process Program was saved in file $fname." info 0 Dismiss
            }
        return
        }
    }

proc ei_ui_ppid_filename {recipe} {
    # "sanitize" a ppid to be a valid filename
    # by substituting _ for questionable characters
    regsub -all {[^-A-Z_a-z0-9]} $recipe _ recipe
    return $recipe
    }
   
    
# a recipe file was selected for downloading
#
proc  ei_ui_proc_dnld {spname lb pathname} {
    global $spname
    set fid [open $pathname r]
    # there can be troublesome data inside of string values
    fconfigure $fid -translation binary 
    set reply [read $fid]
    close $fid
    rset $reply {l2 {t recipe} PPBODY}
    if { ![string compare $recipe ""] || ![string compare $PPBODY ""] } {
        tk_dialog $lb.popup "Process Program Download" \
"The Process Program file $pathname does not have valid data." error 0 Dismiss
        return
        }
    set reply [ei_recipe_put $spname $recipe $PPBODY]
    if { $reply != "0" } {
        if { $reply == "TIMEOUT" } { set reason [secs_xact_failure $spname] }\
        else { set reason "S7F3 rc=$reply" }
        tk_dialog $lb.popup "Process Program Download" \
 "The Process Program could not be Downloaded. ($reason)" error 0 Dismiss
        }\
    else {
        tk_dialog $lb.popup "Process Program Download" \
 "The Process Program was Downloaded successfully." info 0 Dismiss
        }
    }

#
# recipe or process state has been updated (event report or query)
#
proc ei_ui_proc {notice table cols keys ct err rows} {
    set row [lindex $rows 0]
    vset [lindex $rows 0] $cols
    # must now have spname and varID because they are keys
    global $spname
    # map $varID to VFEIname of PP_EXEC_NAME or PROCESS_STATE
    set VFEIname [lindex [lindex [lindex [SQL "select VFEIname\
 from ei_variable where spname='$spname' and varID='$varID'"] 6] 0] 0]
    if { $VFEIname == "PP_EXEC_NAME" } {
        set ${spname}(PPExecName) $varvalue
        }\
    elseif { $VFEIname == "PROCESS_STATE" } {
        # we install a custom varmethod to map the state number to text
        # so we use the normal ei_var_query to get the value
        rset [ei_var_query $spname [list PROCESS_STATE] VFEIname 0] {{t value}}
        set ${spname}(proc_state) $value
        }
    }
 
    

######################## Processing Command #####################
######################## Processing Command #####################
######################## Processing Command #####################
#
# {s Start} {p Pause} {r Resume} {t Stop} {a Abort}
#
proc ei_ui_proc_cmd {spname token w} {
    foreach pair {{s START} {p PAUSE} {r RESUME} {t STOP} {a ABORT}} {
        vset $pair "tok cmd"
        if { $tok == $token } {
            set reply [ei_rcmd $spname $cmd]
            if { $reply != "0" } {
                if { $reply == "TIMEOUT" } { 
                    set reason [secs_xact_failure $spname] }\
                else { set reason "rc=$reply" }
                tk_dialog $w.popup "Process Command" \
 "The Process Command was NOT executed. ($reason)" error 0 Dismiss
                }\
            else {
                ei_var_query $spname [list PROCESS_STATE] VFEIname
                tk_dialog $w.popup "Process Command" \
 "The Process Command was executed successfully." info 0 Dismiss
                }
            return
            }
        }
    }
