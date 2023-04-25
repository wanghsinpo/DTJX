# $Header: /usr/cvsroot/gem/equip/eq_clock.tcl,v 1.7 2005/04/12 14:40:29 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: eq_clock.tcl,v $
# Revision 1.7  2005/04/12 14:40:29  hume
# Fixed format errors in comments, code is correct.
#
# Revision 1.6  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.5  2001/11/15 17:03:49  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.4  1999/05/06 19:06:59  hume
# Added TimeFormat variable and logic for A:16 time format.
#
# Revision 1.3  1998/11/17 13:21:19  hume
# Converted while 1 to while {1} for better runtime performance.
#
# Revision 1.2  1998/10/05 12:23:45  hume
# Fix in clock set proc for single digit years after 1999.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#


######################### eq_clock_set ###################
######################### eq_clock_set ###################
######################### eq_clock_set ###################
#
# recd S2F31 to set <TIME>
# need to correct for y2k problem duh!
#
proc eq_clock_set spname {
    global $spname
    $spname whenmsg again
    set request [set ${spname}(lastrmsg)]
    vset $request "type value"
    while {1} {
        if { $type == "A:12" } {
            set ct [scan $value  \
 "%02d%02d%02d%02d%02d%02d" YY MM DD HH mm ss]
           if { $ct != 6 } break
           if { $YY > 96 } { set YYYY [format "19%02d" $YY] }\
           else { set YYYY [format "20%02d" $YY] }
           }\
        elseif { $type == "A:16" } {
            set ct [scan $value  \
 "%04d%02d%02d%02d%02d%02d" YYYY MM DD HH mm ss]
           if { $ct != 6 } break
           }\
        else break

        set my_gmtsecs [localtime 2]
        if [catch {mktime "$YYYY $MM $DD $HH $mm $ss" 2} host_gmt] break
        set diff [expr $host_gmt - $my_gmtsecs]
        set ${spname}(clock_offset) $diff
        set ${spname}(CLOCK) 0	;# clear last value
        set TIACK {B 0}
        $spname put S2F32 $TIACK
        return
        }
    # 2= error not done
    set TIACK {B 2}
    $spname put S2F32 $TIACK
    }


######################## eq_clock_get #####################
######################## eq_clock_get #####################
######################## eq_clock_get #####################
#
# recd S2F17 to request <TIME>
# <TIME> := A:12 yymmddhhmmss
# <TIME> := A:16 yyyymmddhhmmsscc
#
proc eq_clock_get spname {
    set CLOCK [secs_CLOCK $spname]
    vset [eq_VV_item $spname TimeFormat varname] "type value"
    if { $value == "1" } {
        set TIME $CLOCK
        }\
    else {
        set TIME [string range $CLOCK 2 13]
        }
    $spname put S2F18 "A $TIME"
    $spname whenmsg again
    }
