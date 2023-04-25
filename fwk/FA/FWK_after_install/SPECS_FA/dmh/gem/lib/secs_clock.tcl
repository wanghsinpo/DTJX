# $Header: /usr/cvsroot/gem/lib/secs_clock.tcl,v 1.7 2005/01/14 20:01:53 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997, 2002 Hume Integration Software
# All Rights Reserved
#
# $Log: secs_clock.tcl,v $
# Revision 1.7  2005/01/14 20:01:53  hume
# Revised variable names to decrease likelihood of conflict with $spname.
#
# Revision 1.6  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.5  2002/05/03 21:07:53  hume
# Added secs_CLOCK_to_ts_utc.
#
# Revision 1.4  2002/05/03 18:50:19  hume
# Added conversion calls for sample time arithmetic.
#
# Revision 1.3  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.2  1999/05/06 19:14:28  hume
# Moved clock query logic into separate host and equipment versions.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#


# format the system clock, optionally with a correction
# return YYYYMMDDHHMMSScc  16 chars
#        
# We guarantee a unique value every time this is
# called for a given spname, except for equipment when the host
# adjusts the clock to an earlier time.  
#
# Alarms and events can be uniquely keyed by the
# CLOCK value of their occurence.
#
proc secs_CLOCK {spname} {
    global $spname
    # not all platforms support localtime 11
    # NT, Linux, Solaris, and AIX do support it
    set rc [catch {vset [localtime 11] [list _secs _usecs]}]
    if { $rc } {
        set _secs [localtime 2]
        set _usecs 0
        }
    # equipment may have a host requested clock adjustment
    if { [info exists ${spname}(clock_offset)] } {
        set _secs [expr $_secs + [set ${spname}(clock_offset)]]
        }
    set _cs [expr int($_usecs/10000)]
    set _csecs [format %02d $_cs]
    set YYYYMMDD [mktime $_secs 5]
    set HHMMSS [mktime $_secs 3]
    set CLOCK ${YYYYMMDD}${HHMMSS}${_csecs}
    while { [string compare $CLOCK [set ${spname}(CLOCK)]] <= 0} {
        incr _cs
        if { $_cs > 99 } { 
            set _cs 0
            incr _secs
            set YYYYMMDD [mktime $_secs 5]
            set HHMMSS [mktime $_secs 3]
            }
        set _csecs [format %02d $_cs]
        set CLOCK ${YYYYMMDD}${HHMMSS}${_csecs}
        }
    return [set ${spname}(CLOCK) $CLOCK]
    }


#
# convert A:16 YYYYMMDDHHMMSScc CLOCK value to 
# seconds for arithmetic (eg trace sample time)
# Has provision for integer or floating pt result
#
proc secs_CLOCK_to_seconds {CLOCK {_int 1}} {
    set _h [set _min [set _s [set _cc 0]]]
    set ct [scan $CLOCK "%4d%02d%02d%02d%02d%02d%02d" _y _m _d _h _min _s _cc]
    if { $ct < 7 } { return {}}
    set _secs [mktime [list $_y $_m $_d $_h $_min $_s] 2]
    if { $_int } {  return $_secs } 
    return [expr {$_secs + double($_cc)/100}]
    }


#
# convert seconds back into a CLOCK value
#
proc secs_CLOCK_from_seconds {_secs} {
    set _cc [format %02d [expr {round(100*($_secs - int($_secs)))}]]
    set _secs [expr {int($_secs)}]
    return [mktime $_secs 5][mktime $_secs 3]${_cc}    
    }

#
# convert A:16 YYYYMMDDHHMMSScc CLOCK value to 
# UTC high-resolution timestamp
#
proc secs_CLOCK_to_ts_utc {CLOCK {is_localtime 1}} {
    if { $is_localtime } {
        set _secs [secs_CLOCK_to_seconds $CLOCK 0]
        set _usecs [expr {int(1000000*($_secs - int($_secs)))}]
        set _secs [expr {int($_secs)}]
        return [mktime [list $_secs $_usecs] 16]
        }
    return "[string range $CLOCK 0 3]-[string range $CLOCK 4 5]-[string range $CLOCK 6 7]\
 [string range $CLOCK 8 9]:[string range $CLOCK 10 11]:[string range $CLOCK 12 13].[string range $CLOCK 14 15]0000"
    }
