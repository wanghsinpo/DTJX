# $Header: /usr/cvsroot/gem/lib/dmh_var.tcl,v 1.1 2002/11/04 20:25:33 hume Exp $
# 
# Licensed and Supported Software
# (C)Copyright 2002 Hume Integration Software
# All Rights Reserved
#
# $Log: dmh_var.tcl,v $
# Revision 1.1  2002/11/04 20:25:33  hume
# Added to gem/lib so updated gem files can be used with older DMH83 files.
#
#
# dmh_var:
# A procedure to resolve dmh package variables
# either as globals or in the dmh namespace
#
# This procedure lets you create scripts that can be used without
# change in different versions of Tcl.
#
# Return the qualified name of a Hume dmh package variable
# so that it is accessible to the caller 
# without a global or namespace variable declaration.
#
proc dmh_var {name1 {name2 {}}} {
    if { [namespace children :: dmh] != "::dmh" } {
        # dmh package used globals with Tcl 8.3 and earlier
        if { [string compare $name2 {}] } { 
            return ::${name1}($name2)
            }
        return ::$name1
        }
    if { $name1 == "dmh" } {
        return ::dmh::$name2
        }
    if { [string compare $name2 {}] } { 
        return ::dmh::${name1}($name2)
        }
    return ::dmh::$name1
    }

# eg usage:
# set varname [dmh_var SQL GROUP]
# set value [set $varname]
# info exists $varname
#
# set group [set [dmh_var SQL GROUP]]
# 
# set groupvar [dmh_var mh_group]
# info exists $groupvar
#

# versus:
# if { [info exists ::dmh::SQL(GROUP)] } {
#    set value $::dmh::SQL(GROUP)
#    } else { set value $::SQL(GROUP) }
#
