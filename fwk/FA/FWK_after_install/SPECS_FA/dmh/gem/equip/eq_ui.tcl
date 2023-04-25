# $Header: /usr/cvsroot/gem/equip/eq_ui.tcl,v 1.17 2004/09/05 15:13:21 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997, 2000 Hume Integration Software
# All Rights Reserved
#
# $Log: eq_ui.tcl,v $
# Revision 1.17  2004/09/05 15:13:21  hume
# Made recipe directory configurable, recipe events can be seen by tracing
# recipe_delete, recipe_download and recipe_upload.
#
# Revision 1.16  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.15  2001/11/15 17:03:49  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.14  2000/12/16 16:08:12  hume
# Added new streams to spooling, decided to send offline event after S1F16
#
# Revision 1.13  2000/12/16 01:23:19  hume
# Repeated pressing of Comm enabled/disabled or local/remote buttons ignored.
#
# Revision 1.12  2000/12/15 03:53:46  hume
# If the control_state starts as "OFF-LINE SeekOnline" the online and offline
# buttons need to be disabled until the control_state reaches a stable
# state. Used a variable trace to do it and modified the control_intent proc
# to use the variable trace and not vwait.
#
# Revision 1.11  2000/12/12 19:54:56  hume
# In GEM 3.3 when offline only S1F13, S1F1, and S9Fx should be sent.
#
# Revision 1.10  2000/12/12 05:12:01  hume
# Disallow On-line control state requests from "OFF-LINE Host" control state.
# On-line/Off-line radio buttons stay consistent with operator's intent.
#
# Revision 1.9  2000/12/12 03:07:47  hume
# Small fix to allow for control_state "OFF-LINE Host" to "OFF-LINE Equipment
# transistion.
#
# Revision 1.8  2000/09/19 01:37:42  hume
# Made window argument optional so logic can be used remotely.
#
# Revision 1.7  1999/01/22 16:39:42  hume
# Tweaked last edit.
#
# Revision 1.6  1999/01/22 15:51:47  hume
# Added missing GEM events and variable to provide event descriptions.
#
# Revision 1.5  1999/01/13 16:54:40  hume
# Added horizontal scrollbar to alarm list.
#
# Revision 1.4  1999/01/13 15:38:44  hume
# Added UI for Spooling.
#
# Revision 1.3  1998/01/12 01:10:20  hume
# Tweaked last change.
#
# Revision 1.2  1998/01/09 22:24:47  hume
# Avoid error if gemsim UI is dismissed and alarms change.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#

#
# create a user interface for gem equipment 
#
proc eq_ui spname {
    global $spname

    # make sure the data items we use exist 
    eq_defaults $spname

    set w .eq_$spname
    if { [winfo exists $w] } {
        wm deiconify $w
        raise $w
        return $w
        }

    toplevel $w
    wm title $w "Gem Equipment User Interface -\"$spname\""
 
    # we will build a bunch of grouped widgets and arrange them in
    # this grid.  The grid is created first to get the stacking
    # order correct.
    frame $w.grid
    pack $w.grid -side top -expand 1 -fill both 

    # Communications
    frame $w.comm -borderwidth 2 -relief raised
    label $w.comm.l -text "Communications"
    pack $w.comm.l -side top -fill x
    frame $w.comm.s 
    pack $w.comm.s -side top -fill x  -padx 2m -pady 2m
    label $w.comm.s.l -text State: -anchor e -width 8
    label $w.comm.s.t -textvariable ${spname}(comm_state) -relief sunken\
       -width 30 -anchor w
    pack $w.comm.s.l $w.comm.s.t  -side left 
    radiobutton $w.comm.be -text "enabled" -anchor w\
 -variable ${spname}(comm_enable) -value 1 \
 -command "eq_ui_comm_enable $spname"
    radiobutton $w.comm.bd -text "disabled" -anchor w\
 -variable ${spname}(comm_enable) -value 0 \
 -command "eq_ui_comm_enable $spname"
    pack $w.comm.be $w.comm.bd -side top -fill x -padx 16m 

    # Control Online/Offline/Local/Remote
    frame $w.cntrl -borderwidth 2 -relief raised
    label $w.cntrl.l -text Control
    pack $w.cntrl.l -side top -fill x
    frame $w.cntrl.s 
    pack $w.cntrl.s -side top -fill x -padx 2m -pady 2m
    label $w.cntrl.s.l -text State: -anchor e -width 8
    label $w.cntrl.s.t -textvariable ${spname}(control_state) \
 -relief sunken -width 30 -anchor w
    pack $w.cntrl.s.l $w.cntrl.s.t  -side left 

    frame $w.cntrl.b1
    frame $w.cntrl.b2
    radiobutton $w.cntrl.e  -text "local" -anchor w \
 -variable ${spname}(control_mode) -value LOCAL -width 12\
 -command "eq_ui_control_mode $spname"
    radiobutton $w.cntrl.h -text "remote" -anchor w \
 -variable ${spname}(control_mode) -value REMOTE -width 12\
 -command "eq_ui_control_mode $spname"
    
    radiobutton $w.cntrl.on  -text "On-line" -anchor w \
 -variable ${spname}(control_intent) -value ON-LINE -width 12\
 -command "eq_ui_control_intent $spname $w.cntrl"
    radiobutton $w.cntrl.off -text "Off-line" -anchor w \
 -variable ${spname}(control_intent) -value OFF-LINE -width 12\
 -command "eq_ui_control_intent $spname $w.cntrl"
    pack $w.cntrl.b1 $w.cntrl.b2 -side top -fill x -padx 8m

    pack $w.cntrl.e $w.cntrl.on -side left -in $w.cntrl.b1
    pack $w.cntrl.h $w.cntrl.off -side left -in $w.cntrl.b2

    # the GUI has to be consistent with possible startup control states
    if { [set ${spname}(control_state)] == "OFF-LINE SeekOnline" } {
        # control intent must be OFF-LINE - verified in eq_defaults.tcl
        $w.cntrl.on configure -state disabled
        $w.cntrl.off configure -state disabled
        }
    # we enable the buttons once we get out of the SeekOnline substate
    # we create a variable trace to do this
    trace variable ${spname}(control_state) w eq_ui_control_state_trace
    bind $w.cntrl.on <Destroy> "+ trace vdelete ${spname}(control_state) w eq_ui_control_state_trace"

    # Alarms
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
  -font fixed -height 3 -xscroll "$w.alrm.f.sx set"
    pack $w.alrm.f.sy -side right -fill y
    pack $w.alrm.f.sx -side bottom -fill x
    pack $w.alrm.f.lb -side left -expand 1 -fill both
    pack $w.alrm.f -side top -expand 1 -fill both -padx 2m -pady 1m
    frame $w.alrm.fb
    pack $w.alrm.fb -side top -fill x
    foreach pair {{e Enable} {d Disable} {s Set} {c Clear} {a Add...}} {
        vset $pair "tok label"
        button $w.alrm.fb.$tok -text $label \
 -command "eq_ui_alarm_action $spname $tok $w.alrm.f.lb"
        pack $w.alrm.fb.$tok -side left
        }
    after 1 "eq_ui_alarm_refresh $spname $w.alrm.f.lb"

    # Processing
    frame $w.proc -borderwidth 2 -relief raised
    label $w.proc.l -text Processing
    pack $w.proc.l -side top -fill x
    frame $w.proc.s 
    pack $w.proc.s -side top -fill x -padx 2m -pady 2m
    label $w.proc.s.l -text State: -anchor e -width 12
    label $w.proc.s.t -textvariable ${spname}(process_state) \
 -relief sunken -width 26 -anchor w
    pack $w.proc.s.l $w.proc.s.t  -side left 
    frame $w.proc.r 
    pack $w.proc.r -side top -fill x -padx 2m -pady 2m
    label $w.proc.r.l -text PPExecName: -anchor e -width 12
    label $w.proc.r.t -textvariable ${spname}(PPExecName) \
 -relief sunken -width 26 -anchor w
    pack $w.proc.r.l $w.proc.r.t  -side left 

    frame $w.proc.fa
    pack $w.proc.fa -side top -fill x -padx 4m
    foreach record {{c Select...} {g Start} {p Pause}} {
        vset $record "tok label"
        button $w.proc.fa.$tok -text $label -width 10\
 -command "eq_ui_proc_action $spname [string tolower $label]"
        pack $w.proc.fa.$tok -side left
        }
    frame $w.proc.fb
    pack $w.proc.fb -side top -fill x -padx 4m 
    foreach record {{r Resume} {s Stop} {a Abort}} {
        vset $record "tok label"
        button $w.proc.fb.$tok -text $label -width 10\
 -command "eq_ui_proc_action $spname [string tolower $label]"
        pack $w.proc.fb.$tok -side left
        }
    

    # Terminal Services
    frame $w.term -borderwidth 2 -relief raised
    label $w.term.l -text "Terminal Services"
    pack $w.term.l -side top -fill x
    frame $w.term.o
    frame $w.term.i
    pack $w.term.o $w.term.i -side top -fill x -padx 4m
    label $w.term.o.l -text "From Host:" -anchor e -width 12
    text $w.term.o.h -width 60 -height 3 -state disabled
    button $w.term.o.b -text Acknowledge -state disabled\
 -command "eq_term_ack $spname $w.term.o.b"
    pack $w.term.o.l $w.term.o.h $w.term.o.b -side left 

    label $w.term.i.l -text "Input:" -anchor e -width 12
    text $w.term.i.h -width 60 -height 3
    button $w.term.i.b -text Send \
 -command "eq_term_req $spname $w.term.i.h $w.term.i.b"
    pack $w.term.i.l $w.term.i.h $w.term.i.b -side left 
   
    # Spooling 
    frame $w.sp -borderwidth 2 -relief raised
    label $w.sp.l -text "Spooling of Messages for Host"
    pack $w.sp.l -side top -fill x

    frame $w.sp.f1
    pack $w.sp.f1 -side top -fill x  -padx 2m -pady 2m
    label $w.sp.f1.l1 -text State: -anchor e -width 8
    label $w.sp.f1.t1 -textvariable ${spname}(spooling_state) -relief sunken\
      -width 10 -anchor w
    label $w.sp.f1.l2 -text "Spooled Msg Types:" -anchor e -width 22
    label $w.sp.f1.t2 -textvariable ${spname}(SpoolStreamFns)  -relief sunken\
      -width 48 -anchor w
    pack $w.sp.f1.l1 $w.sp.f1.t1 $w.sp.f1.l2 $w.sp.f1.t2 -side left

    frame $w.sp.f2
    pack $w.sp.f2 -side top -fill x  -padx 2m -pady 2m
    label $w.sp.f2.l1 -text "Counts -    In Spool:" -anchor e -width 24
    label $w.sp.f2.t1 -textvariable ${spname}(SpoolCountActual) -relief sunken\
      -width 10 -anchor w
    label $w.sp.f2.l2 -text "Max In Spool:"  -anchor e -width 16
    label $w.sp.f2.t2 -textvariable ${spname}(SpoolMax)  -relief sunken\
      -width 10 -anchor w
    label $w.sp.f2.l3 -text "Input Total:" -anchor e -width 16
    label $w.sp.f2.t3 -textvariable ${spname}(SpoolCountTotal) -relief sunken\
      -width 10 -anchor w
    pack $w.sp.f2.l1 $w.sp.f2.t1 $w.sp.f2.l2 $w.sp.f2.t2  $w.sp.f2.l3 $w.sp.f2.t3 -side left

    frame $w.sp.f3
    pack $w.sp.f3 -side top -fill x  -padx 2m -pady 2m
    button $w.sp.f3.b1 -text "Purge Spool" -command "eq_spool_purge $spname 0"
    button $w.sp.f3.b2  -text "Stop Spooling" \
      -command "SQL {update ei_variable set varvalue='' where varname='SpoolStreamFns'\
 and spname='$spname'}"
    button $w.sp.f3.b3 -text "Configure..." -command [list eq_ui_spool_cfg $spname $w]
    pack $w.sp.f3.b1 $w.sp.f3.b2 $w.sp.f3.b3  -side left -padx 10m -ipadx 1m


    grid $w.comm -in $w.grid -row 0 -column 0 -sticky nesw -padx 1 -pady 1
    grid $w.cntrl -in $w.grid -row 0 -column 1 -sticky nesw -padx 1 -pady 1

    grid $w.alrm -in $w.grid -row 1 -column 0 -sticky nesw -padx 1 -pady 1
    grid $w.proc -in $w.grid -row 1 -column 1 -sticky nesw -padx 1 -pady 1

    grid $w.term -in $w.grid -row 2 -column 0 -columnspan 2 -sticky nesw -padx 1 -pady 1

    grid $w.sp -in $w.grid -row 3 -column 0 -columnspan 2 -sticky nesw -padx 1 -pady 1

    }

####################### COMMUNICATIONS #########################
####################### COMMUNICATIONS #########################
    
# 
# operator has toggled comm_enable
#
proc eq_ui_comm_enable spname {
    global $spname
    set enabled [set ${spname}(comm_enable)]
    if { !$enabled } {
        if { [set ${spname}(comm_state)] == "DISABLED" } return
        eq_comm_disabled $spname
        }\
    else {
        if { [set ${spname}(comm_state)] != "DISABLED" } return
        eq_comm_enabled $spname
        }
    }
    
##################### CONTROL STATE ###########################
##################### CONTROL STATE ###########################


# operator has toggled LOCAL/REMOTE
proc eq_ui_control_mode spname {
    global $spname
    set state [set ${spname}(control_state)]
    # if we are offline, we do not care
    if { [string first OFF-LINE $state] >= 0 } return
    set mode [set ${spname}(control_mode)]
    set newmode "ON-LINE $mode"
    if { $newmode == [set ${spname}(control_state)] } return
    set ${spname}(control_state) $newmode
    # report event
    if { $mode == "LOCAL" } { eq_gem_event $spname 4001}\
    else { eq_gem_event $spname 4002 }
    }

# operator has toggled ONLINE/OFFLINE control intent
proc eq_ui_control_intent {spname {w {}}} {
    global $spname
    set state [set ${spname}(control_state)]
    set intent [set ${spname}(control_intent)]
    if { [string first OFF-LINE $state] >= 0 } {
        if { $intent == "OFF-LINE" } {
            # allow for "OFF-LINE Host" to "OFF-LINE Equipment" transition
            if { $state != "OFF-LINE Equipment" } {
                set ${spname}(control_state) "OFF-LINE Equipment"
                # handlers etc are already set for OFF-LINE
                # table 3.3 says there is an event for this substate transition
                # paragraph 3.3 says event reports are not sent when OFF-LINE!
                eq_gem_event $spname 4000
                }
            return
            }
        # else intent is ON-LINE
        # A strict interpretation of GEM says that the equipment does not request
        # online from the "OFF-LINE Host" state.
        if { $state == "OFF-LINE Host" } return
        #
        # attempt transition from "OFF-LINE Equipment"
        set offline_substate SeekOnline
        }\
    else {
        if { $intent == "ON-LINE" } return
        # switch from ONLINE
        set offline_substate Equipment
        }
    # no matter what, we are now in an OFFLINE state!
    eq_offline_start $spname $offline_substate
    # gem says
    # freeze the control_intent buttons, while we are in SeekOnline
    # per gem you do not iterate SeekOnline, so this happens before T3
    # the revised GUI uses a variable trace and does not vwait
    if { [set ${spname}(control_state)] == "OFF-LINE SeekOnline" } {
        if { $w != {}} {
            $w.on configure -state disabled
            $w.off configure -state disabled
            # the buttons are enabled from eq_control_state_trace
            }
        }
    # if the intent was online and we did not achieve it,
    # Leave the button in On-line since that is our control intent.
    # We complied with the momentary switch by the disable/enable logic.
    # Per GEM there is no equipment initiated transition from
    # OFF-LINE Host.  
    # the operator can initiate a request to the host by pressing Off-line resulting in 
    # "OFF-LINE Equipment" and then pressing On-line.
    }
  
# we start or enter the "OFF-LINE SeekOnline" control state with
# disabled buttons, so when this is called, see if we can turn the
# buttons back on
proc eq_ui_control_state_trace {spname sub op} {
    if { $op != "w" || $sub != "control_state" } return
    global $spname
    set newstate [set ${spname}(control_state)]
    if { $newstate != "OFF-LINE SeekOnline" } {
        set w .eq_$spname
        catch {
            $w.cntrl.on configure -state normal
            $w.cntrl.off configure -state normal
            }
        }
    }

##################### TERMINAL SERVICES ###########################
##################### TERMINAL SERVICES ###########################

#
# send operators input
#
proc eq_term_req {spname text button} {
    $button configure -state disabled
    set TID "B 0"
    set TEXT [list A [$text get 0.0 end]]
    set TEXT [string trimright $TEXT \n]
    $spname put S10F1 [list L $TID $TEXT] eq_term_req_cb
    $button configure -state normal
    }

proc eq_term_req_cb {spname sfr reason desc} {
    set w .eq_$spname
    if { $reason == "send_failure" } {
        tk_dialog $w.pop "Terminal Services - \"$spname\""\
 "Your message was NOT received by the host." error 0 Dismiss
        }\
    elseif { $reason == "send_complete" } {
        tk_dialog $w.pop "Terminal Services - \"$spname\""\
 "Your message was received by the host." info 0 Dismiss
        }
    }
    

#
# operator acknowledges host message
#
proc eq_term_ack {spname b} {
    eq_gem_event $spname 4100
    $b configure -state disabled
    }

#
# host asks to display message
# S10F3[R] {L:2 {B TID} <TEXT>
# S10F5[R] {L:2 {B TID} {L:N <TEXT>...}}
proc eq_term_disp spname {
    global $spname
    $spname whenmsg again
    set request [set ${spname}(lastrmsg)]
    set R [expr [string first R [set ${spname}(lastrSFR)]] > 0]
    set F3 [expr [string first 3 [set ${spname}(lastrSFR)]] > 0]
    
    if $F3 {
        rset $request {L2 {tTID TID} {tTEXT TEXT}}
        }\
    else {
        set LN [lindex $request 2]
        set TEXT ""
        if { [llength $LN] > 1 } { 
            set TEXTs [lreplace $LN 0 0] 
            foreach line $TEXTs { append TEXT $line\n }
            set TEXT [string trimright $TEXT \n]
            }
        }
    
    set w .eq_${spname}.term.o.h
    set b .eq_${spname}.term.o.b
    $w configure -state normal
    $w delete 0.0 end
    if { ![string match $TEXT ""] } {
        $w insert 0.0 $TEXT
        $b configure -state normal
        catch {
            wm deiconify .eq_${spname}
            raise .eq_${spname}
            }
        }
    if $R {
        if $F3 { $spname put S10F4 "B 0" }\
        else { $spname put S10F6 "B 0" }
        }
    $w configure -state disabled
    }
    
  
############################## Alarms #############################
############################## Alarms #############################
############################## Alarms #############################
proc eq_ui_alarm_refresh {spname lb} {
    # this is a way to get an extra argument passed to a 
    # subscription procedure - define a custom procedure
    proc eq_ui_alarm_$spname {args} "eval \[concat eq_ui_alarm\
 $spname $lb \$args \]"
    # clear and refresh the alarm listbox
    $lb delete 0 end
    SQL "close sub $spname to ei_alarm"
    SQL "open sub $spname to ei_alarm proc=eq_ui_alarm_$spname \
 sync spname,ALID,is_enabled,is_set,ALTX where spname='$spname'"
    }

#
# subscription notice - update view of alarm table
#
proc eq_ui_alarm {spname lb notice table cols keys ct err data} {
    set row [lindex $data 0]
    vset $row $cols
    if { ![winfo exists $lb] } { ;# window must have been closed
        # finish this subscription notice, and then close the sub.
        after 1 "SQL {close sub $spname to ei_alarm}"
        return
        }
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
#  {{e Enable} {d Disable} {s Set} {c Clear} {a Add...}} 
proc eq_ui_alarm_action {spname token lb} {
    if { $token == "a" } { ;# add
        # whats the current max ALID
        set max 1000
        set reply [SQL "select ALID from ei_alarm where spname='$spname'"]
        set rows [lindex $reply 6]
        foreach ALID $rows {
            if { $ALID > $max } { set max $ALID }
            }
        incr max 2
        if { [expr $max & 1] } { incr max }
        set ALID $max
        set ALTX [dmh_gets "Add New Alarm" \
 "What should the descriptive text be (40 chars max) ?"\
 "Alarm $ALID" .* .eq_$spname.pop]
        if { $ALTX == "" } return
        # add as alarm and as set/clear events
        eq_alarm_add $spname $ALID $ALTX
        return
        }
    set selection [$lb curselection]
    if { $selection == "" } {
        set w .eq_$spname
        tk_dialog $w.pop "Alarm Action Usage"\
          "Select an alarm from the list before indicating this action."\
          error 0 Dismiss
        return
        }

    set ALIDs ""
    foreach index $selection {
        set record [$lb get $index]
        lappend ALIDs [lindex $record 0]
        }
    set where "where spname='$spname' and (ALID=[join $ALIDs { or ALID=}])"
    switch -exact $token {
          e { SQL "update ei_alarm set is_enabled=1 $where" }
          d { SQL "update ei_alarm set is_enabled=0 $where" }
          s { SQL "update ei_alarm set is_set=1 $where" }
          c { SQL "update ei_alarm set is_set=0 $where" }
        }
    # view is updated by subscription
    }
    
    
####################### PROCESS #############################
####################### PROCESS #############################
####################### PROCESS #############################
proc eq_ui_proc_action {spname cmd} {
    global $spname
    if { $cmd == "select..." } {
        fileselect [set ${spname}(recipe_dir)] * {PPExecName Select} [list eq_ui_PPselected $spname]
        return
        }
    set rc [eq_process_state_set $spname $cmd]
    if { $rc != 0 } {
        set w .eq_$spname
        tk_dialog $w.pop "Process Action"\
          "The $cmd action cannot be done in the current state."\
          error 0 Dismiss
        }\
    else {
        eq_ui_operator_cmd_event $spname $cmd
        }
    }

# per GEM send event if operator issues a command in the REMOTE 
# control mode
proc eq_ui_operator_cmd_event {spname cmd} {
    global $spname
    if { [set ${spname}(control_mode)] == "REMOTE" } {
        # update last command issued as 'OperatorCommand' 
        # host can attach to event report
        SQL "update ei_variable set varvalue='$cmd' where \
 spname='$spname' and varID='650'"
        # Operator Command Issued event
        eq_gem_event $spname 4015
        }
    }

#
# the user chose a PPExecName (recipe)
#
proc eq_ui_PPselected {spname pathname} {
    set recipe [file tail $pathname]
    set rc [eq_process_state_set $spname select $recipe]
    if { $rc != 0 } {
        set w .eq_$spname
        tk_dialog $w.pop "PPExecName Selection"\
          "You have to be in the IDLE or SELECT state to assign a recipe."\
          error 0 Dismiss
        }\
    else {
        # possible operator command event
        eq_ui_operator_cmd_event $spname select
        }
    }
   

########################### SPOOLING CONFIG #######################
########################### SPOOLING CONFIG #######################
########################### SPOOLING CONFIG #######################
# 
# provide for Stream definition
#   an OEM may want to provide for setting SpoolMax, OverWriteSpool
proc eq_ui_spool_cfg {spname w} {
    global $spname
    set w $w.spool_cfg
    catch {destroy $w}
    toplevel $w
    wm title $w "Spooling Configuration - \"$spname\""
    message $w.m -aspect 600 -text "Choose the SECS Message Stream\
 types that should be spooled when the host is down (Only S5 and S6 are recommended):"
    pack $w.m -side top -padx 2m
    foreach rec {
      {2 {Equipment Control}} {3 {Material Status}} {4 {Material Control}}\
      {5 Alarms} {6 {Data Collection}} {7 {Process Programs}} {9 {SECS Errors}}\
      {10 {Terminal Services}} {12 {Wafer Mapping}} {13 {Data Set Transfers}}\
      {14 {Object Services}} {15 {Recipe Management}} {16 {Processing Management}}\
 {17 {Control and Diagnostics}} } {
       vset $rec "s txt"
       checkbutton $w.cb$s -text "S$s - $txt" -variable ${spname}(spool_cb$s)
       pack $w.cb$s -side top -anchor w -padx 2m
       }

    frame $w.bot
    pack $w.bot -side top -pady 2m
    button $w.bot.ok -text "Ok" -command [list eq_ui_spool_cfg_ok $spname $w]
    button $w.bot.can -text "Cancel" -command "destroy $w"
    pack $w.bot.ok $w.bot.can -side left -padx 6m -ipadx 2m
    }

# Ok pressed on Spooling Configuration dialog
proc eq_ui_spool_cfg_ok {spname w} {
    global $spname
    set slist [set result ""]
    foreach subscript [array names $spname spool_cb*] {
        set stream [substr $subscript spool_cb {}]
        set value [set ${spname}($subscript)]
        if { $value } { lappend slist $stream }
        }
    set slist [lsort -integer $slist]
    foreach s $slist {lappend result S$s}
    SQL "update ei_variable set varvalue='$result' where\
 varname='SpoolStreamFns' and spname='$spname'"
    destroy $w
    }
        
