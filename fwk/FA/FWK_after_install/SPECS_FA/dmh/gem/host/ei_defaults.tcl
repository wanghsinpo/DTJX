# $Header: /usr/cvsroot/gem/host/ei_defaults.tcl,v 1.9 2004/10/12 15:15:22 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 2004 Hume Integration Software
# All Rights Reserved
#
# $Log: ei_defaults.tcl,v $
# Revision 1.9  2004/10/12 15:15:22  hume
# Rearranged the variable initialization logic for better external use.
# (Such as new .NET code).  New provision for AUTO_VIRT_INIT - use virtual
# concepts of VFEI without using VFEI commands.  Variable
# table configuration records are put in place earlier.  Separate procedures
# to refresh Status Variable values and EC values.
#
# Revision 1.8  2004/09/28 13:39:22  hume
# The recipe upload directory is configurable and defaults to separate sub-
# directories for each connection name.
#
# Revision 1.7  2004/09/27 19:22:45  hume
# Changed comm_enabled to call comm_attempt and got rid of redundant online
# call, added callout to ei_custom_comm, changed comm_disabled to be more like
# equipment version, reduced usage of quotes in favor or [list ].
#
# Revision 1.6  2002/01/19 18:09:24  hume
# Changes to support disabling of multiblock inquire/grant using (MULTIBLOCK)
#
# Revision 1.5  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.4  2001/05/25 21:37:34  hume
# Backup restoration.
#
# Revision 1.4  2001/02/02 19:46:49  hume
# Revised ei_comm_disabled logic based on equipment side improvements.
# This logic is not accessible by the Hume GUI, only by using custom code.
#
# Revision 1.3  2000/02/16 02:59:02  hume
# Moved variable and event table loading earlier in the initialization.
#
# Revision 1.2  1997/11/06 14:32:57  hume
# Added redundant alarm initialization before online so alarm text definitions
# from past sessions are used if alarms are reported immediately upon online.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#


#
# initialize gem status 
# for items that are not already defined and set by custom code
#
proc ei_defaults spname {
    global $spname

    # initialize gem communication model
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

    set ${spname}(CLOCK) 0
    set ${spname}(EQUIP) 0

    # we have a simple control_state model of the equipment-
    # "ON-LINE" "OFF-LINE"
    if { ![info exists ${spname}(control_state)] } {
        set ${spname}(control_state) "OFF-LINE"
        }

    # create a table of variables, unless the caller has
    # already created/loaded/restored his custom data
    set reply [SQL "select spname from ei_variable\
 where spname='$spname'"]
    set ct [lindex $reply 4]
    if { $ct == "0" } { 
        ei_var_create $spname
        SQL "include ei_variable.tab"
        ei_variables_default $spname
        }
    # We cache the size of the varvalue field and work-around this limit if necessary.
    set reply [hub_fieldtype varvalue [hub_table_schema_list ei_variable]]
    set ${spname}(maxlen_varvalue) [substr $reply {(} {)}]
    
    # we will fully initialize alarms and variables after we get online
    # and we can do some queries.  

    # These lines insure that early alarms
    # are handled properly if we have already defined alarm text etc
    ei_alarmtab_create $spname
    SQL "include ei_alarm.tab"

    # and similarly we need to make sure early event reports have our
    # persistent knowledge of variable and event names etc
    ei_eventtab_create $spname
    SQL "include ei_event.tab"
    SQL "include ei_event_report.tab"
    SQL "include ei_report.tab"
    SQL "include ei_report_cfg.tab"
    SQL "include ei_event_report_cfg.tab"

    # setup tables to manage event reports
    # there are no online discovery mechanisms
    ei_event_init $spname

    # the desired use of MultiBlock inquire/grant (a legacy from the past)
    # The host uses it for S2F33, S2F35, S2F45.  These are infrequent setup
    # messages, and also they are rarely long enough to be multiblock.
    # Use 1 to be standard, and know that it doesn't matter.
    if { ![info exists ${spname}(MULTIBLOCK)] } {
        set ${spname}(MULTIBLOCK) 1  
        }

    # new feature - per connection recipe directory - lets go with safer default
    # of keeping separate directories, but let gemhost use "recipes" to be compatible with
    # earlier versions
    if { ![info exists ${spname}(recipe_dir)] || ([set ${spname}(recipe_dir)] == "")} {
        if { $spname == "gemhost" } { set subdir recipes }\
        else {
            set subdir ${spname}_recipes
            }
        set ${spname}(recipe_dir) [file join [pwd] $subdir]
        }
    }


# We may need to close and reopen the connection in order to
# disable communication. This procedure creates Tcl statements representing the gem level
# data that is in the spname array that must be saved and restored.
# Revised 2/2/01 to save everything except low-level connection data,
# and SnFm callback data.  With this change new data items added to the
# array are saved by default.  Also, items like DEVID, T3 and RTY which may be
# at non-default values are saved and restored.
# 
proc ei_gemdata spname {
    global $spname
    set statements {}
    foreach sub [array names $spname] {
        if { $sub == "comm_enable" || $sub == "comm_recovery" || $sub == "comm_state" } continue
        if { $sub == "filehandle" || $sub == "hostname" } continue
        if { $sub == "listener" || $sub == "state" } continue
        if { $sub == "tracewin" } continue
        if { $sub == "trace" || $sub == "rtrace" || $sub == "strace"} continue
        if { [string match {S[0-9]*} $sub] } continue
        lappend statements\
  [list set ${spname}($sub) [set ${spname}($sub)]]
      }
    return $statements
    }



