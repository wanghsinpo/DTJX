# $Header: /usr/cvsroot/tcllib84/dmh_import.tcl,v 1.3 2005/04/05 12:29:37 hume Exp $
# 
# Licensed and Supported Software
# (C)Copyright 2002 Hume Integration Software
# All Rights Reserved
#
# $Log: dmh_import.tcl,v $
# Revision 1.3  2005/04/05 12:29:37  hume
# Workaround namespace import unexpectedly auto_loading all of ::dmh::*
#
# Revision 1.2  2002/10/30 14:35:38  hume
# Added namespace qualifiers to the lset renaming to make it unambiguous
# which commands were affected.
#
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.1  2002/10/01 13:15:10  hume
# New commands to support Tcl 8.4+ application compatibility.
#
#
# dmh_import:
# If needed, import dmh package commands into the global namespace
# so that applications work with the new or the older
# Tcl versions.
#
# The latest Tcl versions, 8.4+, have the command "lset" as part of
# the core.  The name conflict with the dmh package is the motivation
# to cleanup the dmh package by moving commands and variables into the
# namespace "dmh".  New applications can choose which package commands
# to import into the global namespace, so future conflicts are 
# avoidable.  
# 
# As detailed below, most existing applications will run without
# change after calling dmh_import.  It is proper to call dmh_import
# when using Tcl 8.3, and this is the supported and proper way to
# code applications that run unchanged with Tcl 8.3 and 8.4+.
#
# To run Tcl 8.3 dmh package applications with Tcl 8.4+, you need to:
#
#   (1) Call dmh_import and optionally restore the old lset.
#
#       If you restore the old lset you will not be able to use the
#       new core lset command, but you may skip step (2).
#
#       The Hume GEM applications have been revised to call 
#       dmh_import without restoring the old lset.  If you have
#       custom code that uses lset, in order to run with Tcl
#       8.4+, you need to either revise the lset usages to vset, 
#       or customize your application startup.  You do not need
#       to change your custom code to continue running on Tcl
#       8.3 with or without the latest dmh package or GEM application
#       changes.
#
#   (2) If you did not restore the old lset, replace usage of lset
#       with vset, and have vset.tcl as part of your auto_load
#       library.  vset.tcl is part of the latest Tcl 8.3.3 dmh
#       package library, and is part of the latest GEM 
#       application library. The logic in vset.tcl lets you use
#       the vset command with Tcl 8.3 and earlier.  This is the
#       proper and supported way to have an application that can
#       run with the older and newer Tcl versions, and can use 
#       the new core lset command when running in Tcl 8.4+.
#
#   (3) Replace any access to dmh package global variables
#       such as "mh_group", "SQL()", or "dmh()"
#       with access using the dmh_var procedure.  See the GEM
#       application code for examples.  Dmh_var.tcl has been
#       made part of the latest Tcl 8.3.3 dmh package library,
#       and the latest GEM application library so that you can
#       revise applications to be runnable with Tcl 8.3 and 
#       8.4+.
#

proc dmh_import {{want_old_lset 0}} {
    # make sure the dmh package is loaded and the auto_path is set
    # it does not hurt if the package has already been loaded
    package require dmh
    # if dmh namespace is in use, import the commands
    if { [namespace children :: dmh] == "::dmh" } {
        # force is needed if done more than once, or in case of new name conflicts.
        # namespace import -force dmh::* ;# unexpectedly this autoloads all of ::dmh::*!
        # As a workaround we explicitly import only the exported commands which is the 
        # documented behavior of namespace import.  There is still an undocumented side effect
        # of auto_loading all of the exported procedures.
        foreach cmd [::namespace eval ::dmh ::namespace export] {
            ::namespace import -force ::dmh::$cmd 
            }
        # Tcl 8.4 has a core lset command
        # We can rename it and make lset work the way it used to.
        # new code should call vset (dmh::vset).
        if { $want_old_lset } {
            # rename the core lset command
            if { [info commands ::lset] == "::lset" && [info commands ::lupdate] != "::lupdate" } {
                rename ::lset ::lupdate
                }
            # point lset to the imported dmh::vset command
            interp alias {} ::lset {} ::dmh::vset
            }
        }
    # else - Tcl 8.3 already has dmh package commands in 
    # the global namespace
    # and the lset command is the dmh package version.
    }
