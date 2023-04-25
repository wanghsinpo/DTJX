# $Header: /usr/cvsroot/gem/equip/eq_defaults.tcl,v 1.7 2005/03/20 15:37:37 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997, 2005 Hume Integration Software
# All Rights Reserved
#
# $Log: eq_defaults.tcl,v $
# Revision 1.7  2005/03/20 15:37:37  hume
# Added features to make persistent saving of dynamic reports configurable.
#
# Revision 1.6  2004/09/05 15:13:21  hume
# Made recipe directory configurable, recipe events can be seen by tracing
# recipe_delete, recipe_download and recipe_upload.
#
# Revision 1.5  2002/01/19 18:15:59  hume
# Added ECV varID 920, varname UseMultiBlockInquire, to configure use of
# multiblock inquire/grant.  For HSMS it defaults to off so multiblock event
# reports are as fast as single block ones.  The array element (MULTIBLOCK)
# is updated if the UseMultiBlockInquire variable is set by the host.
#
# Revision 1.4  2001/11/15 17:03:49  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.3  2000/12/19 14:55:36  hume
# Improved ease of customization by call to eq_custom_online from
# eq_when_online, and saving of custom array data during communication
# disablement (eq_gemdata revised).
#
# Revision 1.2  2000/10/06 17:12:55  hume
# Had incorrect call but it was never executed by gemsim.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#


#
# initialize gem status and "control panel" data
# for items that are not already defined and set by custom code
#
proc eq_defaults spname {
    global $spname

    # initialize gem equipment comm model
    # "DISABLED"
    # "ENABLED {NOT COMMUNICATING}" 
    # "COMMUNICATING" 
    if { ![info exists ${spname}(comm_state)] } {
        set ${spname}(comm_state) "ENABLED {NOT COMMUNICATING}"
        #set ${spname}(comm_state) "DISABLED"
        }

    # Our desired communications as set by user interface
    if { ![info exists ${spname}(comm_enable)] } {
        if { [set ${spname}(comm_state)] == "DISABLED" } {
            set ${spname}(comm_enable) 0 }\
        else { set ${spname}(comm_enable) 1 }
        }

    # Our desired Online/Offline control aspect
    if { ![info exists ${spname}(control_intent)] } {
        set ${spname}(control_intent) ON-LINE  
        #set ${spname}(control_intent) OFF-LINE  
        }

    # Our desired LOCAL/REMOTE control aspect
    if { ![info exists ${spname}(control_mode)] } { 
        set ${spname}(control_mode) REMOTE  
        #set ${spname}(control_mode) LOCAL
        }
    # Our actual control state
    # "ON-LINE REMOTE" "ON-LINE LOCAL" 
    # "OFF-LINE Equipment" "OFF-LINE Host" "OFF-LINE SeekOnline"
    if { ![info exists ${spname}(control_state)] } {
        if { [set ${spname}(control_intent)] == "OFF-LINE" } {
            set ${spname}(control_state) "OFF-LINE Equipment"
            }\
        else {
            set ${spname}(control_state) "OFF-LINE SeekOnline"
            }
        }

    if { ![info exists ${spname}(process_state)] } {
        set ${spname}(process_state) IDLE
        }

    if { ![info exists ${spname}(spooling_state)]} {
        set ${spname}(spooling_state) INACTIVE
        }

    # initialize Clock
    # Clock adjustment requested by host
    if { ![info exists ${spname}(clock_offset)] } {
        set ${spname}(clock_offset) 0
        }
    # we guarantee unique CLOCK readings by checking last values
    if { ![info exists ${spname}(CLOCK)] } {
        set ${spname}(CLOCK) 0 
        }

    # create a table of variables, unless the caller has
    # already created/loaded/restored his custom data
    set reply [SQL "select spname from ei_variable\
 where spname='$spname'"]
    set ct [lindex $reply 4]
    if { $ct == "0" } { ei_var_create $spname}
   
    # the desired use of MultiBlock inquire/grant (a legacy from the past)
    if { ![info exists ${spname}(MULTIBLOCK)] } {
        if { [info exists ${spname}(T6)] } { ;# hsms
            set ECDEF 0 ;# disable it for best performance
            }\
        else { ;# SECS-I
            set ECDEF 1 ;# its still part of the standard
            }
        set ${spname}(MULTIBLOCK) $ECDEF
        # since it has not already been set, we'll define the default now
        SQL "update ei_variable set ECDEF='$ECDEF' where spname='$spname' and varID='920'"
        }

    # the default recipe directory
    if { ![info exists ${spname}(recipe_dir)] } { 
        set ${spname}(recipe_dir) [file join [pwd] recipes]
        }
    # the default recipe upload/download type, (B) Binary or (A) ASCII, configured as 1 | 0
    if { ![info exists ${spname}(binary_recipes)] } {
        set ${spname}(binary_recipes) 1
        }
    # array items that can be subscribed to for recipe events
    set ${spname}(recipe_delete) {}    ;# you see this for download too (recipe replacement)
    set ${spname}(recipe_download) {}  ;# received by us
    set ${spname}(recipe_upload) {}    ;# sent to host

    # GEM E37 says the state of dynamic event reports is persistent.  
    # This can conflict with the equipment wanting to provide built-in predefined reports.
    # So report persistence is controllable with the ReportsAreSaved element
    # (see the comments and logic in the eq_reports.tcl file)
    if { ![info exists ${spname}(ReportsAreSaved)] } {
        set ${spname}(ReportsAreSaved) 1
        }
    }


# We may need to close and reopen the connection in order to
# disable communication. This procedure creates Tcl statements representing the 
# data that is in the spname array that must be saved and restored.
# Revised 12/19/00 to save everything except low-level connection data,
# and SnFm callback data.  With this change new data items added to the
# array are saved by default.  Also, items like DEVID, T3 and RTY which may be
# at non-default values are saved and restored.
proc eq_gemdata spname {
    global $spname
    set statements {}
    foreach sub [array names $spname] {
        if { $sub == "comm_enable" || $sub == "comm_recovery" || $sub == "comm_state" } continue
        if { $sub == "filehandle" || $sub == "hostname" } continue
        if { $sub == "listener" || $sub == "state" } continue
        if { $sub == "tracewin" } continue
        if { [string match {S[0-9]*} $sub] } continue
        lappend statements\
  [list set ${spname}($sub) [set ${spname}($sub)]]
      }
    return $statements
    }



