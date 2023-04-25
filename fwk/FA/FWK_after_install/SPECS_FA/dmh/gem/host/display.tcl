# $Header: /usr/cvsroot/gem/host/display.tcl,v 1.2 2001/11/15 17:03:50 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: display.tcl,v $
# Revision 1.2  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#

#
# synchronous call to display a message and return
# with the ACKC10 value or TIMEOUT
#
# An empty message usually results in clearing the display.
#
# Return values
# 0 = ok
# 1 = no 
# 2 = not available
# TIMEOUT - timeout or abort
proc ei_terminal_display {spname msg {term 0}} {
    set reply [secs_xact $spname S10F3R "L:2 {B $term} {A {$msg}}"]
    # expect ACKC10 {B:1 0x0n}
    if { $reply != "TIMEOUT"} {
        set reply [expr [lindex $reply 1]]
        }
    return $reply
    }


