# $Header: /usr/cvsroot/gem/host/ei_multiblock_check.tcl,v 1.3 2002/01/19 18:09:24 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: ei_multiblock_check.tcl,v $
# Revision 1.3  2002/01/19 18:09:24  hume
# Changes to support disabling of multiblock inquire/grant using (MULTIBLOCK)
#
# Revision 1.2  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#

#
# if the msg is multiblock, get permission to send it
# using SFR = S2F39R or S6F5R
# returns
#   0=0k send it
#   1=refused
# 
proc ei_multiblock_check {spname msg DATAID SFR} {
    global $spname
    # added configurable bypass of multiblock
    if { [info exists ${spname}(MULTIBLOCK)] && ![set ${spname}(MULTIBLOCK)] } {
        return 0
        }
    set len [llength [TSN_to_secs $msg]]
    if { $len > 244 } {
        #
        set reply [SQL "select value_TSN from ei_variable\
 where spname='$spname' and varID='DATALENGTH'"]
        set value_TSN [lindex [lindex [lindex $reply 6] 0] 0]
        if { $value_TSN == "" } { set value_TSN U4 }
        set reply [secs_xact $spname $SFR \
           "L:2 {$DATAID} {$value_TSN $len}"]
        # expect GRANT
        if { $reply != "B:1 0x00" } {
            return 1
            }
        }
    return 0
    }

