# $Header: /usr/cvsroot/gem/host/ei_DATAID.tcl,v 1.2 2001/11/15 17:03:50 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: ei_DATAID.tcl,v $
# Revision 1.2  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#
#


# generate a new DATAID

proc ei_dataid spname {
   global $spname
   if { ![info exists ${spname}(dataid)] ||
       [set ${spname}(dataid)] >= 255 } {
       set ${spname}(dataid) 0
       }
   incr ${spname}(dataid)
   set reply [SQL "select value_TSN from ei_variable\
 where spname='$spname' and varID='DATAID'"]
   set value_TSN [lindex [lindex [lindex $reply 6] 0] 0]
   if { $value_TSN == "" } { set value_TSN U4 }
   return [list $value_TSN [set ${spname}(dataid)]]
   }
