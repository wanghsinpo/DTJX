# $Header: /usr/cvsroot/gem/host/ei_clock.tcl,v 1.4 2002/09/24 15:56:20 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1999 Hume Integration Software
# All Rights Reserved
#
# $Log: ei_clock.tcl,v $
# Revision 1.4  2002/09/24 15:56:20  hume
# Updated calls to ei_var_query to explicitly call with a list of names.
# Sets a proper example, and fixes a bug with ei_event_discovery when
# EventsEnabled variable name contains white space.
#
# Revision 1.3  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.2  1999/05/27 19:19:53  hume
# Added new logic for VFEI clock synchronization command, and rearranged
# the existing clock setting logic to make it reusable.
#
# Revision 1.1  1999/05/06 19:55:03  hume
# Revised clock handling for possible A:16 format.
#
#
#
#
# Return host TIME in the format preferred by the equipment
# <TIME> := A:12 yymmddhhmmss   ;# older
# <TIME> := A:16 yyyymmddhhmmsscc ;# newer
#
proc ei_clock_get spname {
    set CLOCK [secs_CLOCK $spname]
    # look for a variable, VFEIname==TIME_FORMAT to see if
    # this equipment wants A:16 clock values
    # If the equipment names the variable something other than TimeFormat
    # its your job to update the VFEIname to TIME_FORMAT
    rset [ei_var_query $spname [list TIME_FORMAT] VFEIname 0] {{t value}}
    if { $value == "1" } {
        # newer format if variable exists and value == 1
        set TIME $CLOCK
        }\
    else {
        # older format is used if variable not found
        set TIME [string range $CLOCK 2 13]
        }
    return [list A $TIME]
    }

# recd S2F17 to request <TIME>
proc ei_clock_reply spname {
    $spname put S2F18 [ei_clock_get $spname]
    }


#
# set the equipment time to our time
# our time is possibly corrected to the factory time
# possibly retry with alternate TIME format
#
# returns
#  {}            (empty result means success)
#  REJECTED
#  ABORTED
#  BAD_SEND
#  NO_REPLY
#  REFUSED  (TIACK != 0)
proc ei_clock_set spname {
    global $spname
    set TIME [ei_clock_get $spname]
    set reply [secs_xact $spname S2F31R $TIME]
    if { $reply == "TIMEOUT" } {
        # we will try again if we got S9F7 == illegal data
        if { [string first S9F7 [set ${spname}(lastrSFR)]] != 0 } {
            return [secs_xact_failure $spname]
            }
        }
    # the command is supported, check the reply
    if { $reply != "B:1 0x00" } {
        # since the command is supported
        # maybe he wants the newer format but we do not know the TimeFormat
        # variable or it is named differently (configuration error)
        set reply [secs_xact $spname S2F31R [list A [secs_CLOCK $spname]]]
        if { $reply == "B:1 0x00" } {
            # ok he likes the new format
            set ${spname}(strace) \
"Equipment wants A:16 clock format - missing or improper TimeFormat variable configuration"
            }\
        else {
            # failed
            return REFUSED
            }
        }
    return {}
    }
    

# convert from A:16 SECS CLOCK variable format YYYYMMDDhhmmsscc
# to localtime style YYYY-MM-DD hh:mm:ss.cc
#
proc ei_clock_reformat a16 {
   set result [string range $a16 0 3]-[string range $a16 4 5]-[string range $a16 6 7]
   append result { } [string range $a16 8 9]:[string range $a16 10 11]:[string range $a16 12 13]
   append result . [string range $a16 14 15]
   return $result
   }
