# $Header: /usr/cvsroot/tcllib84/info_data.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
#
# (C) Copyright Hume Integration Software 2000
# All Rights Reserved
# Licensed Materials - Property of Hume Integration Software
#
# $Log: info_data.tcl,v $
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.3  2001/11/15 17:14:17  hume
# Updated company name.
#
# Revision 1.2  2000/04/06 13:59:28  hume
# Sort array names.
#
# Revision 1.1  2000/03/22 02:59:06  hume
# New display/save/recall data functions info_data, info_var.
#
#
namespace eval ::dmh {
# info_data
# return information on variable(s) matching a pattern
# information is formatted as Tcl statements for display
# or for execution in another context (for example, send
# in a DMH message to a remote Tcl shell, and feed to eval)
# superior and more versatile than parray
#
# variable pattern matching defaults to global scope, 
#   but level==1 specifies callers scope
#
proc info_data {namepattern {level #0} {separator " \n"}} {
    set result {}
    set names [lsort [uplevel $level info vars $namepattern]]
    if { [string first # $level] < 0 } {
       incr level	;# correct for descending into info_var 
       }
    foreach name $names {
        set reply [info_var $name $level $separator]
        if { $result != "" } {
            append result $separator
            }
        append result $reply
        }
    return $result
    }

# info_var
# return information on a variable as Tcl statements
# that are displayable as a set of text lines or 
# can be eval'd to recreate the variable
# we use the scope (local or global) that the variable
# has in the caller - specify #0 to get global
#
#
proc info_var {varname {level 1} {separator " \n"} {newname {}}} {
    set result {}
    if { ![string compare $newname {}] } { set newname $varname }
    if { [uplevel $level array exists $varname] } {
        set names [uplevel $level array names $varname]
        if { [llength $names] == 0 } {
            # the oddball case, an empty array 
            lappend result [list set ${newname}(x) {an empty array}]
            lappend result [list unset ${newname}(x)]
            }\
        else {
            foreach name [lsort $names] {
                lappend result [list set ${newname}($name) [uplevel $level set ${varname}($name)]]
                }
            }
        }\
    elseif { [uplevel $level info vars $varname] == "$varname" } {
        lappend result [list set $newname [uplevel $level set $varname]]
        }

    return [join $result $separator]
    }
    
} ;# namespace    
