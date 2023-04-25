# $Header: /usr/cvsroot/gem/equip/process.tcl,v 1.10 2004/09/05 15:13:21 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: process.tcl,v $
# Revision 1.10  2004/09/05 15:13:21  hume
# Made recipe directory configurable, recipe events can be seen by tracing
# recipe_delete, recipe_download and recipe_upload.
#
# Revision 1.9  2002/07/23 13:42:00  hume
# Updated recipe name validation to look for file existence.  So now you can
# have recipe names with imbedded whitespace if they exist as files.
#
# Revision 1.8  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.7  2000/10/10 18:57:02  hume
# fixed last change of RCMD processing - needed to send reply SECS message.
#
# Revision 1.6  2000/09/29 21:48:49  hume
# Rearranged control_mode test for RCMDs for GUI and remote controller use.
#
# Revision 1.5  2000/09/29 20:33:14  hume
# Need to reject RCMDs that affect processing in LOCAL control mode.
#
# Revision 1.4  2000/08/18 14:36:20  hume
# Fixed mispelling in comment text.
#
# Revision 1.3  1999/01/22 15:51:47  hume
# Added missing GEM events and variable to provide event descriptions.
#
# Revision 1.2  1999/01/12 22:41:34  hume
# Added spooling functionality.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#
#

#  ${spname}(process_state)
#      INIT - power up
#      IDLE
#      SETUP - like idle but have a current recipe
#      EXECUTING
#      PAUSED
#
#  need to maintain ei_variables
#   800, PreviousProcessState
#   810, ProcessState 
#
###################### eq_ProcessState #######################
###################### eq_ProcessState #######################
###################### eq_ProcessState #######################
#
# translate our internal process state into the U1 value
# required by SEMI E-5, 0-63 are reserved
#
proc eq_ProcessState {spname statename} {
    switch -exact $statename {
      INIT { return 64 }
      IDLE { return 65 }
      SETUP {return 66 }
      EXECUTING {return 67}
      PAUSED {return 68}
      default {}
      }
    return 255
    }

######################## eq_S2F21_RCMD ########################
######################## eq_S2F21_RCMD ########################
######################## eq_S2F21_RCMD ########################

# recd 
# S2F21 <RCMD>
# remote command <RCMD> is {A {start|stop|resume|pause|abort}}
# send back <CMDA> {U1 $rc}
# S2F22 U1 {0 - ok, 1 bad command, 2=not now}
#
proc eq_S2F21_RCMD spname {
    global $spname
    set RCMD [set ${spname}(lastrmsg)]
    set Cmd [lindex $RCMD 1]
    # per GEM - reject any commands that affect processing when in LOCAL control mode
    if { [set ${spname}(control_mode)] == "LOCAL" } {
        # all of our RCMDs affect processing
        set rc 2
        }\
    else {
        set rc [eq_process_state_set $spname $Cmd]
        }
    # send reply if requested
    if { [string first R [set ${spname}(lastrSFR)]] > 0 } {
        $spname put S2F22 "U1 $rc"
        }
    }

# process S2F41 RCMD
# the only command with a parameter we handle is 
# "select <PPExecName>" (or pp-select)
#
# S2F41 {L:2 <RCMD> {L:n {L:2 <CPNAME> <CPVAL>} }
# reply
# S2F42 {L:2 <HCACK> {L:n {L:2 <CPNAME> <CPVAL>} }
#     <HCACK> {B 0 - ok, 1 bad command, 2 not now, 3 bad parameter, 4 ok-later}
#     L:n is to indicate bad parameters
# 
proc eq_S2F41_RCMD spname {
    global $spname
    set request [set ${spname}(lastrmsg)]
    if { [lindex $request 0] != "L:2" } {
        eq_S9_reply $spname 7 ;# bad data
        return
        }
    set RCMD [lindex $request 1]
    set Cmd [lindex $RCMD 1]
    set parmlist [lindex $request 2]
    set Ln [lindex $parmlist 0]
    set parmlist [lreplace $parmlist 0 0]
    #set argc [llength $parmlist]
    # check the parameters
    set badlist L
    foreach item $parmlist {
        # {L:2 <CPNAME> <CPVAL>} == {L:2 {A:n NAME} {A:n VALUE}}
        rset $item "l2 {nt Name} {vt value}"
        if { $l2 != "L:2" } {
            eq_S9_reply $spname 7 ;# bad data
            return
            }
        set name [string tolower $Name]
        if { [string index $nt 0] != "A" } {
            lappend badlist [list L:2 [list $nt $Name] {B 1}]  ;# bad name
            continue
            }
        # verify names and values
        if { $name == "ppexecname" } {
            # a good name, so look at the value
            # we expect Ascii, blank is ok - means deselect recipe
            if { [string index $nt 0] != "A" } {
                lappend badlist [list L:2 [list $nt $Name] {B 3}]  ;# bad format
                continue
                }
            # trim blanks from beginning and end
            set value [string trim $value]
            # see if the recipe exists as a file 
            set pathname [file join [set ${spname}(recipe_dir)] $value]
            if { ![file exists $pathname] } {
                lappend badlist [list L:2 [list $nt $Name] {B 2}]  ;# bad value
                continue
                }
            set PPExecName $value
            continue
            }
        # verify other possible parameters...
        }
    if { [llength $badlist] > 1 } {
        set HCACK "B 3"   ;# bad parameter
        $spname put S2F42 [list L:2 $HCACK $badlist]
        return
        }
    set cmd [string tolower $Cmd]
    if { $cmd == "pp-select" } { 
        set cmd select
        set Cmd [string range $Cmd 3 end]
        }
    # per GEM - reject any commands that affect processing when in LOCAL control mode
    if { [set ${spname}(control_mode)] == "LOCAL" } {
        # all of our RCMDs affect processing
        set rc 2
        }\
    else {
        if { [info exists PPExecName] && $cmd == "select" } {
            set rc [eq_process_state_set $spname $Cmd $PPExecName]
            }\
        else {
            set rc [eq_process_state_set $spname $Cmd]
            }
        }
    set HCACK "B $rc"
    # send reply if requested (standard says they should ask for reply)
    if { [string first R [set ${spname}(lastrSFR)]] > 0 } {
        $spname put S2F42 [list L:2 $HCACK L]
        }
    }



#
# internal equipment call to perform a command and
# set a new process state and save the previous state and signal events
#
# Used by the GUI logic, internal process logic, and to process RCMDs.
# When called for RCMDs,  it is already known that the request is ok 
# for our control mode.
#
# cmd - select/start/stop/resume/pause/abort/completed
# newstate - ""/IDLE/SETUP/EXECUTING/PAUSED
# args - optional new recipe
#
# returns 0 for ok
# returns 1 for bad command
#         2 for not now
#
proc eq_process_state_set {spname Cmd args} {
    global $spname
    set prevstate [set ${spname}(process_state)]
    # validate Cmd
    set cmd [string tolower $Cmd]
    if { $cmd != "select" && $cmd != "start" && $cmd != "stop" && $cmd != "resume"\
 && "$cmd" != "pause" && $cmd != "abort" && $cmd != "completed" } { return 1 }
    # validate that the cmd is appropriate in the current state
    if { $prevstate == "IDLE" } {
        if { $cmd != "select" } { return 2 }
        }
    if { $prevstate == "SETUP" } {
        if { $cmd != "select" && $cmd != "start" } { return 2 }
        }
    if { $prevstate == "EXECUTING" } {
        if { $cmd != "stop" && $cmd != "pause" && $cmd != "abort" && $cmd != "completed"} { return 2 }
        }
    if { $prevstate == "PAUSED" } {
        if { $cmd != "stop" && $cmd != "resume" && $cmd != "abort" } { return 2 }
        }

    # compute the next state
    if { $cmd == "select" } { 
        # recipe select/deselect
        if { [llength $args] > 0 } {
            set newstate SETUP
            }\
        else { set newstate IDLE }
        }\
    elseif { $cmd == "start" || $cmd == "resume" } { set newstate EXECUTING }\
    elseif { $cmd == "stop" } { set newstate SETUP }\
    elseif { $cmd == "completed" } { set newstate SETUP }\
    elseif { $cmd == "abort" } { set newstate SETUP }\
    elseif { $cmd == "pause" } { set newstate PAUSED }

    # we can have newstate == oldstate if the guy changed recipes or reselected the
    # same recipe

    # initiate the new action
    # real equipment actions ....
    if { $cmd == "select" } { ;# SET RECIPE ACTION
        set ${spname}(PPExecName) [lindex $args 0]
        }

    # update our process state variables
    SQL "update ei_variable set varvalue='$prevstate' where \
 spname='$spname' and varname='PreviousProcessState'"
        set ${spname}(process_state) $newstate
    SQL "update ei_variable set varvalue='$newstate' where \
 spname='$spname' and varname='ProcessState'"

    # send event reports using current updated variables
    if { $cmd == "start" } { eq_gem_event $spname 4047 }
    if { $cmd == "completed" } { eq_gem_event $spname 4048 }
    if { $cmd == "stop" } { eq_gem_event $spname 4049 }
    # Process Program Selected event - report can attach PPExecName
    if { $cmd == "select" } { eq_gem_event $spname 4040 }
    eq_gem_event $spname 4050 ;# Process State Update

    return 0
    }

    
