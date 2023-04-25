# $Header: /usr/cvsroot/gem/lib/is_unsigned.tcl,v 1.2 2001/11/15 17:03:50 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: is_unsigned.tcl,v $
# Revision 1.2  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#
#

#
# return True if the argument is an unsigned integer
#
proc is_unsigned num {
    set match ""
    regexp \[0-9\]+ $num match
    if { [string compare $num ""] && $num == $match } { return 1}
    return 0
    }
