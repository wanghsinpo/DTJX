# $Header: /usr/cvsroot/gem/host/ei_RPTID.tcl,v 1.2 2001/11/15 17:03:50 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: ei_RPTID.tcl,v $
# Revision 1.2  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#



# The VFEI EVENT_SETUP command requires creating a report without
# the caller being aware of the report, or providing a name
# for it.  
# This procedure provides a name for a new report for a set of
# CEIDs.  We put this in a separate file to ease replacement,
# if it not suitable for your application.
#
# Our design is to return first CEID value in the list.  If you are
# using VFEI, you will have 0 or 1 reports per CEID, and there
# will not be a conflict if you issue a revised EVENT_SETUP for
# a particular CEID, because you will delete the existing report.
# We do not even look at the existing reports and see if this
# name is in use.
#
proc ei_RPTID_new {spname CEIDs} {
    return [lindex $CEIDs 0]
    }

#
# return the type of a RPTID
# 
proc ei_RPTID_TSN spname {
    set reply [SQL "select value_TSN from ei_variable where\
 spname='$spname' and varID='RPTID'"]
    set type [lindex [lindex [lindex $reply 6] 0] 0]
    if { $type == "" } { set type U4 }
    return $type
    }
