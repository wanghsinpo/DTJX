# $Header: /usr/cvsroot/gem/equip/eq_variables.tcl,v 1.13 2005/04/12 14:40:30 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997, 2004 Hume Integration Software
# All Rights Reserved
#
# $Log: eq_variables.tcl,v $
# Revision 1.13  2005/04/12 14:40:30  hume
# Fixed format errors in comments, code is correct.
#
# Revision 1.12  2004/11/19 20:21:30  hume
# New DvvalList variable to support DVVAL discovery.  New variables PPError,
# PPFormat, RcpChangeName, RcpChangeStatus per GEM E30-1103.
#
# Revision 1.11  2004/09/24 16:58:31  hume
# ControlMode variable value was not being maintained - added varmethod to
# read array element (control_mode)
#
# Revision 1.10  2003/02/27 13:46:28  hume
# Subscription ECV_monitor needed to be $spname specific for host and
# equipment to share the same ei_variable table.
#
# Revision 1.9  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.8  2002/05/28 20:53:14  hume
# Revised handling of Equipment constants, ECV values, so that range checking
# can accomodate vectors.  ECMIN, ECMAX, and ECDEF are always scalar values and
# are applied to each element of a vector.  Think most host software will expect
# ECV's to be scalar data, so the recommendation is to just use scalars.
# Validation logic makes sure host sends compatible
# size of data.  Have special logic for U4, U8, and I8 values since their
# range is outside of the usual Tcl integer range.  Users should use a
# value method like 'return $varvalue' and not 'expr $varvalue' when using
# U4 data and allowing values > 2^31.  Have rejection of List type since it
# is not standard for ECV data.  ASCII or Variant String comparison with
# ECMIN, ECMAX is skipped if ECMIN and ECMAX are empty values.
#
# Revision 1.6  2002/05/15 12:31:05  hume
# Added some status variables with interesting values for demos and testing.
#
# Revision 1.5  2002/03/07 22:49:39  hume
# When S2F15 is used to set the value of ECV character data parameters, the
# ECMIN, ECMAX comparison should use string compare to avoid expr errors when
# the character data can be interpreted as numeric.
#
# Revision 1.4  2002/01/19 18:15:59  hume
# Added ECV varID 920, varname UseMultiBlockInquire, to configure use of
# multiblock inquire/grant.  For HSMS it defaults to off so multiblock event
# reports are as fast as single block ones.  The array element (MULTIBLOCK)
# is updated if the UseMultiBlockInquire variable is set by the host.
#
# Revision 1.3  2001/11/15 17:03:49  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.2  2001/01/24 23:42:32  hume
# Updated the 12/3/00 change of eq_VV_item to be foregiving of the format of
# string values by using them directly, as was done before 12/3/00, but the
# change breaks string values that were reformatted to be single lists.
#
# Revision 1.1  2000/12/06 23:34:01  hume
# Renamed trace.tcl to eq_trace.tcl and variables.tcl to eq_variables.tcl
# so you can have custom versions of host and equip files in the same
# directory with the original names without a conflict.
#
# Revision 1.8  2000/12/03 14:22:03  hume
# Fixed eq_VV_item handling of lists and vectors.  Existing varmethod procs
# that returned lists were fixed to only return the data items, and the
# resulting value is no longer improperly nested as {L:1 {L:n ...}}.
#
# Revision 1.7  2000/01/26 19:44:29  hume
# Updated logic for unknown variables and empty report assoc. per SEMI
# Draft 3088 12/30/99 - even though not yet approved, beneficial changes.
#
# Revision 1.6  1999/05/06 19:06:59  hume
# Added TimeFormat variable and logic for A:16 time format.
#
# Revision 1.5  1999/01/22 15:51:48  hume
# Added missing GEM events and variable to provide event descriptions.
#
# Revision 1.4  1999/01/12 22:41:35  hume
# Added spooling functionality.
#
# Revision 1.3  1998/11/17 13:21:20  hume
# Converted while 1 to while {1} for better runtime performance.
#
# Revision 1.2  1997/09/08 17:39:27  hume
# Changed default EstablishCommunications retry time to 30 sec.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#
#
#

# table ei_variable
# Configuration and value table for equipment interface "variables"
#
# Your additions to this table will sort nicely in table displays
# if you number your varIDs to be: 
#       1000-1999    - listed first
#    or 9000-9999    - listed last
#
# This table schema is used by equipment and host interfaces.
# Host queries/sets ECV's via S2F13,F15
#   ECs have ECNAME, min,max,default,units (S2F30)
# Host queries SV's via S1F3, or in event reports S2F33 S6F11,F15,F17,F19,F21
#   SVs have SVID, SVNAME, UNITS (S1F12)
#   SVs may have n LIMITIDs - UPPERDB,LOWERDB (S2F45) 
#     use another table to allow for n per SV
# Host queries DVVAL's S6F7 sees them in S6F3 and event reports
# 
# Guidance:
# Gem says to use Un for your SVID's (class SV)  -> use U4
# Gem says to use Un for your ECID's (class ECV) -> use U4
#
# 

proc eq_var_init {spname} {
    global $spname
    # SVs and DVVALS
    # add the gem variable items (E-30-95 p 61) (E5-95 pp 71-75)
    set ID_TSN U4
    set cols \
 "varID varname description varclass value_TSN varmethod varvalue"
    set data [list \
      [list 200 AlarmsEnabled \
 "the list of alarms ALIDs enabled for reporting via S5" \
 SV L "eq_AlarmsEnabled $spname" {}]\
      [list 201 AlarmID "the current alarm identifier\
 ALID at the setting or clearing of an alarm irrespective of reporting"\
 DVVAL U4 {return $varvalue} {}] \
      [list 202 AlarmsSet \
 "the list of alarms ALIDs in the set state, irrespective of reporting" \
 SV L "eq_AlarmsSet $spname" {}]\
      [list 250 Clock "the value of the equipment''s clock"\
  SV A:16 "secs_CLOCK $spname" {}]\
      [list 300 ControlMode \
 "0=Local, 1=Remote (aka E5-95 ControlState 2nd definition)"\
 SV U1 "if {\$${spname}(control_mode) == \"LOCAL\" } {return 0} else {return 1}"]\
      [list 301 ControlState  \
 "1=off-line/eq off-line 2=off/seek on 3=off/host off 4=on/local 5=on/remote"\
 SV B "eq_ControlState $spname" {}]\
      [list 310 DemoAngularMinutes \
 "AngularMinutes - A changing status variable value for testing & demonstration" \
 SV F4 {expr {sin(.1047*[lindex [localtime] 4])}} {}] \
      [list 312 DemoAngularSeconds \
 "AngularSeconds - A changing status variable value for testing & demonstration" \
 SV F4 {expr {sin(.1047*[lindex [localtime] 5])}} {}] \
      [list 314 DemoDiceRoll \
 "DemoDiceRoll - A changing status variable value for testing & demonstration" \
 SV U1 {expr {int(1+6*rand())+int(1+6*rand())}} {}] \
      [list 316 DemoLottoTX \
 "Random 1..54 - A changing status variable value for testing & demonstration" \
 SV U1 {expr {int(1 + 54*rand())}} {}] \
      [list 318 DemoLUFactor \
 "LUFactor - A changing status variable value for testing & demonstration" \
 SV F4 {expr {.5*rand()+.25*(1 - cos(.2618*[lindex [localtime] 3]))}} {}] \
      [list 320 DemoNotchAngle \
 "NotchAngle - A changing status variable value for testing & demonstration" \
 SV F4 {expr {int(rand()*3600)/10.0}} {}] \
      [list 322 DemoRand \
 "Rand - A changing status variable value for testing & demonstration" \
 SV F4 {expr {rand()}} {}] \
      [list 324 DemoRandNormal \
 "RandNormal - A changing status variable value for testing & demonstration" \
 SV F4 {randnormal} {}] \
      [list 330 DvvalList \
 "A list of all DVVAL variables, their IDs and names (L \[L:2 <VID> <DVNAME>]+)" \
 SV L [list eq_DVVALlist $spname] {}] \
      [list 350 ECIDChangeName \
 "The equipment constant, ECID, last updated independent of the host" \
 DVVAL U4 {return $varvalue} {}] \
      [list 400 EventsEnabled \
 "the list of events CEIDs enabled for reporting via S6" \
 SV L "eq_EventsEnabled $spname" {}]\
      [list 410 EventDescriptions \
 "A list of all event CEIDs and their descriptions" \
 SV L "eq_EventDescriptions $spname" {}]\
      [list 500 LimitVariable \
 "contains the VID for the variable whose value changed monitoring zones"\
 DVVAL U4 {return $varvalue} {}]\
      [list 501 EventLimit \
 "contains LIMITID(s) of the limit reached by LimitVariable(s)" \
 DVVAL L {return $varvalue} {}]\
      [list 502 TransitionType \
 "the direction of limits zone transition 0=low2hi, 1=hi2low" \
 DVVAL B {expr $varvalue} 0] \
      [list 600 MDLN "Equipment Model Type"\
 SV A:6 "return \$${spname}(_MDLN)" ""] \
      [list 650 OperatorCommand \
 "The last operator command issued during control_mode of REMOTE" \
 DVVAL A {return $varvalue} {}] \
      [list 700 PPChangeName \
 "The Process Program ID, PPID, affected by the creation, edit,\
 or delete local to the equipment" \
 DVVAL A {return $varvalue} {}] \
      [list 710 PPChangeStatus \
 "The action taken on PPChangeName, 1=create, 2=edit, 3=deleted"\
 DVVAL U1 {return $varvalue} 2]\
      [list 715 PPError \
 "Contains information about a failure to verify a process program" \
 DVVAL A {return $varvalue} {}] \
      [list 720 PPExecName \
 "the PPID(s) of the selected Process Program(s)"\
 SV A "return \$${spname}(PPExecName)" {}]\
      [list 725 PPFormat \
 "Indicates the type or types of process programs and recipes supported, 1==unformatted PPs" \
 SV U1 {return $varvalue} 1] \
      [list 800 PreviousProcessState \
 "the previous processing state"\
 SV U1 "eq_ProcessState $spname \$varvalue" INIT]\
      [list 810 ProcessState \
 "the current processing state"\
 SV U1 "eq_ProcessState $spname \$varvalue" IDLE]\
      [list 820 RcpChangeName \
 "the identifier of the Stream 15 recipe affected by creation, editing, or deletion"\
 DVVAL A {return $varvalue} {}] \
      [list 825 RcpChangeStatus \
 "the type of change for RcpChangeName, 1=created, 2=updated, 3=stored new, 4=overwritten, 5=deleted, 6=copied, 7=renamed"\
 DVVAL U1 {return $varvalue} 0]\
      [list 830 RcpExecName \
 "the identifier of the currently selected Stream 15 recipe"\
 SV A {return $varvalue} {}]\
      [list 850 SOFTREV "Equipment Software Revision ID"\
 SV A:6 "return \$${spname}(_SOFTREV)" ""]\
      ]
  
    foreach record $data {
        vset $record $cols
        set reply [SQL "insert into ei_variable (spname,[join $cols ,],ID_TSN)\
 values ('$spname', '$varID', '$varname', '$description', \
 '$varclass', '$value_TSN', '$varmethod', '$varvalue', '$ID_TSN')"]
        }

    #
    # now ECVs
    #
    set cols "varID varname description varclass value_TSN\
 varmethod varvalue ECMIN ECMAX ECDEF units"
    set data [list \
      [list 220 AnnotateEventReports \
"send annotated event reports as S6F13 instead of S6F11"\
 ECV TF {expr $varvalue} 1 0 1 1 {}]\
      [list 375 EstablishCommunicationsTimeout \
"the length of time in seconds between S1F13 attempts when\
 initializing communications"\
 ECV U2 {expr $varvalue} 30 10 65535 10 s]\
      [list 900 TimeFormat \
"0==YYMMDDHHMMSS 1==YYYYMMDDHHMMSScc in S2F18, S2F31, S6F1, 1 is the default" \
 ECV U4 {expr $varvalue} 1 0 1 1 {}]\
      ]
    foreach record $data {
        vset $record $cols
        set reply [SQL "insert into ei_variable (spname,[join $cols ,],ID_TSN)\
 values ('$spname', '$varID','$varname', '$description',\
 '$varclass', '$value_TSN', '$varmethod', '$varvalue', '$ECMIN', '$ECMAX',\
 '$ECDEF', '$units', '$ID_TSN')"]
        }
    # Our default for UseMultiBlockInquire depends on HSMS or SECS-I.
    # We make the behavior controllable with an ECV setting
    # if you have already set it, we use your value as default
    # this code is called very early so the ${spname}( ) data is not there yet
    if { [info exists ${spname}(MULTIBLOCK)] } { 
        set ECDEF [set ${spname}(MULTIBLOCK)] 
        }\
    else {
        # with SECS-I its standard to have it on 
        set ECDEF 1 
        # we will wait until we know whether HSMS is in use before
        # setting the array MULTIBLOCK value, and possibly changing ECDEF
        #set ${spname}(MULTIBLOCK) $ECDEF
        }
    SQL "insert into ei_variable (spname,[join $cols ,],ID_TSN)\
 values ('$spname', '920','UseMultiBlockInquire', \
 'If true, S6F5 is used before sending multiblock event reports',\
 'ECV', 'TF', 'return \$${spname}(MULTIBLOCK)', '', '0', '1',\
 '$ECDEF', '', '$ID_TSN')"
    }
 
#
# monitor ECV's for change 
# Save the last changed ECID in ECIDChangeName
# Send the "Operator Equipment Constant Change"
# event to the host, if the host did not initate the change
#
proc eq_var_ECVsub_init spname {
    # subscription is connection specific so host and equipment 
    # can share the same table
    SQL "open sub ECV_monitor_${spname} to ei_variable proc=eq_var_ECV_update\
 update varvalue where varclass='ECV' and spname='$spname'"
    }

proc eq_var_ECV_update {notice table cols keys ct etxt rows} {
    vset [lindex $rows 0] $cols
    # now have spname and varID  
    global $spname
    # synch UseMultiBlockInquire 
    if { $varID == "920" && [info exists varvalue] } {
        set ${spname}(MULTIBLOCK) $varvalue
        }
    if { [info exists ${spname}(ECVHostChange)] && \
            [set ${spname}(ECVHostChange)] == 1 } return
    # set 'ECIDChangeName' - faster to use keys
    SQL "update ei_variable set varvalue='$varID' where\
 spname='$spname' and varID='350'"
    eq_gem_event $spname 4020
    }


#
# given a variable ID, return valid TSN for the secs item value
#    usually {type value} but possibly {type val1 val2 ... valN} or {type}
#   eg SV or ECV
# can also be used to look up value by name:
#   eq_VV_item $sp 900
#   eq_VV_item $sp TimeFormat varname
#   
proc eq_VV_item {spname SVID {fieldname varID}} {
    global $spname
    set cols "value_TSN varmethod varvalue"
    set reply [SQL "select [join $cols ,] from ei_variable\
 where spname='$spname' and $fieldname='$SVID'"]
    set row [lindex [lindex $reply 6] 0]
    set value "configuration"
    while {1} {
        if { $row == "" } break
        vset $row $cols
        if { $value_TSN == "" } break
        # return code 2 is ok
        if { [catch $varmethod value]  == 1 } {
            return [list A "value method error: $value"]
            }
        # The value may be a list of values, possibly empty for most data types.
        # The parsing of string data types is different - only a single argument,
        # possibly empty is expected.  We special case the handling to make the
        # logic forgiving of string values.
        if { [string match A* $value_TSN] } { ;# A or A:<n> are possible
            return [list $value_TSN $value]
            } 
        set result $value_TSN
        foreach item $value { lappend result $item }
        return $result
        }
    # configuration error
    # SEMI Draft 3088 12/30/99 says return zero-length list for S1F4, S2F14 for unknown
    return L
    }


# answer S1F3
# Selected Equipment Status Data
# reply  L [$SV]*
proc eq_put_S1F4 {spname} {
    global $spname
    $spname whenmsg again
    set request [set ${spname}(lastrmsg)]
    if { $request == "L:0" } {
       # 0 length list means report everything
       # but the receiver does not know what he is getting! duh!
       # unwritten rule -> the order here should match S1F11, S1F12
       set select [SQL "select varID from ei_variable where \
spname='$spname' and varclass='SV'"]
       set SVIDs [lindex $select 6]
       }\
    else {
       # answer specific request
       # old format <SVID,...>
       # new format {L [<SVID>]+}
       set type [lindex $request 0]
       if { [string index $type 0] == "L" } {
           set SVIDlist [lreplace $request 0 0]
           set SVIDs ""
           foreach item $SVIDlist {
               # ignore item type
               lappend SVIDs [lindex $item 1]
               }
           }\
       else {
           # old format - array of numbers
           set SVIDs [lreplace $request 0 0]
           }
       }

    set reply L
    foreach SVID $SVIDs {
       lappend reply [eq_VV_item $spname $SVID]
       }

    $spname put S1F4 $reply
    }


#
# answer S1F11 Status Variable Namelist Request
#
# L [<SVID>]*
#
# reply
#  S1F12 {L [{L:3 <SVID> <SVNAME> <UNITS>}]+}
proc eq_put_S1F12 {spname} {
    global $spname
    $spname whenmsg again
    set request [set ${spname}(lastrmsg)]
    # request format {L [<SVID>]*}
    set SVIDlist [lreplace $request 0 0]
    set SVIDs ""
    foreach item $SVIDlist {
        # ignore SVID type in {type value}
        lappend SVIDs [lindex $item 1]
        }
    if { [llength $SVIDs] == 0 } {
        # 0 length list means report everything
        # unwritten rule -> the order here should match S1F4
        set select [SQL "select varID from ei_variable where \
 spname='$spname' and varclass='SV'"]
        set SVIDs [lindex $select 6]
        }

    set reply L
    foreach varID $SVIDs {
        set cols "ID_TSN varname units"
        set select [SQL "select [join $cols ,] from ei_variable\
 where spname='$spname' and varID='$varID'"]
        set row [lindex [lindex $select 6] 0]
        if { $row == "" } {
             # bad SVID in input
             # SEMI draft 3088 12/30/99 says return A:0s
             # U4 may not be the caller's ID TSN but the real problem is the bad SVID
             lappend reply [list L [list U4 $varID] A:0 A:0]
             }\
        else {
            vset $row $cols
            # <SVID> <SVNAME> <UNITS>
            lappend reply \
 [list L [list $ID_TSN $varID] [list A $varname] [list A $units]]
            }
        }
    $spname put S1F12 $reply
    }

#
# answer S2F13 Equipment Constant Request
#
proc eq_put_S2F14 spname {
    global $spname
    $spname whenmsg again
    set request [set ${spname}(lastrmsg)]
    if { $request == "L:0" } {
       # 0 length list means report everything
       # but the receiver does not know what he is getting! duh!
       # unwritten rule -> the order here should match S2F30
       set select [SQL "select varID from ei_variable where\
 spname='$spname' and varclass='ECV'"]
       set IDs [lindex $select 6]
       }\
    else {
       # answer specific request
       # old format <ECID,...>
       # new format {L [<ECID>]+}
       set type [lindex $request 0]
       if { [string index $type 0] == "L" } {
           set IDlist [lreplace $request 0 0]
           set IDs ""
           foreach item $IDlist {
               # ignore item type
               lappend IDs [lindex $item 1]
               }
           }\
       else {
           # old format - array of numbers
           set IDs [lreplace $request 0 0]
           }
       }

    set reply L
    foreach ID $IDs {
       lappend reply [eq_VV_item $spname $ID]
       }

    $spname put S2F14 $reply
    }

#
# respond to S2F15 New Equipment Constant Send 
#
# L:n [{L:2 <ECID> <ECV>}]n
#
# two passes: - make sure all changes are ok and
#               then commit
#
# The standard does not directly address the use of vector data for 
# Equipment Constant values, (ECV's).
# We think the common thinking is that an equipment constant is a single
# value (scalar) and not a vector.  For example, there is no discussion of
# ECMIN, ECMAX as vectors, or as being applicable to each value is a vector.
# We will assume that ECMIN, ECMAX, and ECDEF are always scalar values.
# Further, there is no standard concept for ECMIN, ECMAX, or ECDEF to be 
# non-applicable or not defined.  You can always specify the lowest possible
# value supported by the data type for ECMIN and similarly the max for ECMAX,
# so this is probably a better thing to do than pass an empty array for not 
# applicable.  For string data, a minimum value of an empty string, and a 
# maximum value of 'zzzzzz' or '~~~~~~~' will serve for ECMIN, ECMAX if you
# want to have a comparison.  We will ignore checks if both ECMIN and ECMAX 
# are empty strings.
#
proc eq_put_S2F16 spname {
    global $spname
    $spname whenmsg again
    set request [set ${spname}(lastrmsg)]
    set items [lreplace $request 0 0]
    set ok 1
    set EAC "B 0" 
    set nvlist ""
    foreach item $items {
        rset $item {l2 {t1 ID} ECV}
        if { $l2 != "L:2" || ![llength $ID] } { 
            set ok 0 ; set EAC "B 1" ; break }
        set reply [SQL "select ECMIN, ECMAX, value_TSN from ei_variable\
 where spname='$spname' and varID='$ID' and varclass='ECV'"]
        set row [lindex [lindex $reply 6] 0]
        if { $row == "" } { set ok 0 ; set EAC "B 1" ; break }
        vset $row {ECMIN ECMAX value_TSN}
        set size 1  ;# default expectation is 1 value
        if { [string first : $value_TSN] > 0 } { ;# "A:16", "U4:1" or some such thing
            vset [split $value_TSN :] {value_TSN size}
            }
        set t2 [lindex $ECV 0]
        set VALUES [lrange $ECV 1 end]
        vset [split $t2 :] {recd_TSN recd_size}
        # lists are not supposed to be used for ECVs
        if { $recd_TSN == "L" } {
            set ok 0 ; set EAC "B 3" ; break 
            }
        set ch [string toupper [string index $value_TSN 0]]
        # for character data, size is a max, for other data, want size to match
        if { $ch == "A" || $ch == "V" } { ;# Ascii or Variant character data
            if { $recd_size > $size } {
                set ok 0 ; set EAC "B 3" ; break 
                }
            }\
        else { ;# numeric data
            if { $recd_size != $size } {
                set ok 0 ; set EAC "B 3" ; break 
                }
            }
        # so now we know the sizes are compatible
        # the value ECMIN, ECMAX checks lets to host substitute equivalent types
        # if character data, use string compare with min and max
        #   {} is less than any string, {zzzzzz} is greater than most application data
        if { $ch == "A" || $ch == "V" } {
            set VAL $VALUES
            # skip validation if both min and max are blank
            if { [string compare $ECMIN {}] == 0 && [string compare $ECMAX {}]==0 } {
                # NOP
                }\
            elseif { [string compare $VAL $ECMIN] < 0 || [string compare $VAL $ECMAX] > 0} {
                set ok 0 ; set EAC "B 3" ; break 
                }
            }\
        else {  ;# numeric type
            # it is possible to pass vectors-
            # so we will loop like there could be more than 1 value
            foreach VAL $VALUES {
                if { $value_TSN == "U4" } {
                    # values > 2^31 but < 2^32 are too big for Tcl's default handling as signed integers
                    # they become negative integers.
                    # so we need to parse the string representation as floating point
                    set dval [expr ${VAL}.0]
                    set dmin [expr ${ECMIN}.0]
                    set dmax [expr ${ECMAX}.0]
                    if { $dval < $dmin || $dval > $dmax } { set ok 0 ; set EAC "B 3" ; break }
                    }\
                elseif { $value_TSN == "U8" } {
                    # 8 byte unsigned integers - if the values are represented as hex strings with
                    # consistent use of alphabetic case string comparison will work
                    # since a>9, b>a, etc.
                    # must be same data type
                    if { $recd_TSN != $value_TSN } { set ok 0 ; set EAC "B 3" ; break }
                    # skip validation if either min and max are blank
                    if { [string compare $ECMIN {}] == 0 || [string compare $ECMAX {}]==0 } {
                        # NOP
                        }\
                    else {
                        # expect error here if user has not configured 0xnnnn style values
                        # roundtrip conversion to put into standard format
                        set hmin [secs_to_TSN [TSN_to_secs [list $value_TSN $ECMIN]]]
                        set hmax [secs_to_TSN [TSN_to_secs [list $value_TSN $ECMAX]]]
                        set hval [secs_to_TSN [TSN_to_secs [list $value_TSN $VAL]]]
                        if { [string compare $hval $hmin] < 0 || [string compare $hval $hmax] > 0} {
                            set ok 0 ; set EAC "B 3" ; break 
                            }
                        }
                    }\
                elseif { $value_TSN == "I8" } {
                    # 8 byte signed integers - Here the highest bit is a sign bit so when
                    # it is set it is awkward to compare values
                    # must be same data type
                    if { $recd_TSN != $value_TSN } { set ok 0 ; set EAC "B 3" ; break }
                    # skip validation if either min and max are blank
                    if { [string compare $ECMIN {}] == 0 || [string compare $ECMAX {}]==0 } {
                        # NOP
                        }\
                    else {
                        # expect error here if user has not configured 0xnnnn style values
                        set hmin [secs_to_TSN [TSN_to_secs [list $value_TSN $ECMIN]]]
                        set hmax [secs_to_TSN [TSN_to_secs [list $value_TSN $ECMAX]]]
                        set hval [secs_to_TSN [TSN_to_secs [list $value_TSN $VAL]]]
                        set hneg [secs_to_TSN [TSN_to_secs {I8:1 0x8000000000000000}]]
                        if { [string compare $hmin $hneg] < 0 } {  ;# min is 0 or positive
                            # reject negative or positive < $hmin
                            if { ([string compare $hval $hneg] > 0) || ([string compare $hval $hmin] < 0)} {
                                set ok 0; set EAC "B 3" ; break
                                }
                            }\
                        else { ;# min is negative
                            if { [string compare $hval $hmin] > 0 } { ;# its more negative
                                set ok 0; set EAC "B 3" ; break
                                }
                            }
                        if { [string compare $hmax $hneg] < 0 } {  ;# max is 0 or positive
                            # reject positive values > $hmax
                            if { ([string compare $hval $hneg] < 0) && ([string compare $hval $hmax] > 0)} {
                                set ok 0; set EAC "B 3" ; break
                                }
                            }\
                        else { ;# max is negative
                            # reject positive value or a smaller negative than $hmax
                            if {([string compare $hval $hneg] < 0) || ([string compare $hval $hmax] < 0)} { 
                                set ok 0; set EAC "B 3" ; break
                                }
                            }            
                        }
                    }\
                elseif { $VAL < $ECMIN || $VAL > $ECMAX } { set ok 0 ; set EAC "B 3" ; break }
                } ;# foreach VAL
            if { !$ok } break
            } ;# numeric
        lappend nvlist [list $ID $VALUES]
        }  ;# each item
    if {!$ok} {set nvlist {}}
    set ${spname}(ECVHostChange) 1
    foreach item $nvlist {
        vset $item "ID VALUES"
        SQL "update ei_variable set varvalue='$VALUES' where spname='$spname'\
 and varID='$ID'"
        }
    set ${spname}(ECVHostChange) 0
    $spname put S2F16 $EAC
    }
 
 
#
# answer S2F29 Eq Constant Namelist Request
#
proc eq_ECNAMELIST {spname} {
    global $spname
    $spname whenmsg again
    set request [set ${spname}(lastrmsg)]
    # request format {L [<ID>]*}
    set IDlist [lreplace $request 0 0]
    set IDs ""
    foreach item $IDlist {
        # ignore ID type in {type value}
        lappend IDs [lindex $item 1]
        }
    if { [llength $IDs] == 0 } {
        # 0 length list means report everything
        set select [SQL "select varID from ei_variable where \
 spname='$spname' and varclass='ECV'"]
        set IDs [lindex $select 6]
        }

    set reply L
    foreach varID $IDs {
        set cols "varname value_TSN ID_TSN ECMIN ECMAX ECDEF units"
        set select [SQL "select [join $cols ,] from ei_variable\
 where spname='$spname' and varID='$varID'"]
        set row [lindex [lindex $select 6] 0]
        if { $row == "" } {
            # bad ID in input
            # SEMI 3088 12/30/99 says return A:0's
            lappend reply \
 [list L:6 [list U4 $varID] A:0 A:0 A:0 A:0 A:0]
            }\
        else {
            vset $row $cols
            # there could be a size specification on $value_TSN which we 
            # will not apply to ECMIN, ECMAX, and ECDEF
            if { [string first : $value_TSN] > 0 } { set value_TSN [substr $value_TSN {} :] }
            # <ID> <ECNAME> <ECMIN> <ECMAX> <ECDEF> <UNITS>
            lappend reply \
 [list L:6 [list $ID_TSN $varID] [list A $varname] \
 [list $value_TSN $ECMIN] [list $value_TSN $ECMAX] [list $value_TSN $ECDEF] \
 [list A $units]]
            }
        }
    $spname put S2F30 $reply
    }


###################### eq_DVVALlist #############################
###################### eq_DVVALlist #############################
###################### eq_DVVALlist #############################
#
# Not required by GEM or E5 - provide a list of all DVVAL variables.
# This variable fills a major void in SECS/GEM functionality.
# new 11/2004
# returns list of L:2 <VID> <DVNAME>
proc eq_DVVALlist spname {
    set reply [SQL "select ID_TSN, varID, varname from ei_variable where spname='$spname'\
 and varclass='DVVAL'"]
    set result {}
    set rows [lindex $reply 6]
    foreach row $rows {
        vset $row {ID_TSN VID DVNAME}
        lappend result [list L [list $ID_TSN $VID] [list A $DVNAME]]
        }
    return $result
    }
