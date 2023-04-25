# $Header: /usr/cvsroot/gem/host/vfei.tcl,v 1.20 2002/11/01 15:57:14 hume Exp $
# 
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: vfei.tcl,v $
# Revision 1.20  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.19  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.18  2001/01/25 01:18:37  hume
# Updated 12/3/00 changes of string handling - string values were being
# returned with extra surrounding braces.
#
# Revision 1.17  2000/12/03 19:16:08  hume
# Updated event report and trace report handling for vector or list data.
#
# Revision 1.16  2000/12/03 14:29:50  hume
# Added logic to VFEI STATUS_QUERY to properly handle vector data and to
# handle list data by conversion to vector.
#
# Revision 1.15  1999/07/29 13:48:16  hume
# Fixed S10F1 error when ei_ui is built and dismissed repeatedly.  Non
# VFEI aware term_display code no longer displaces VFEI S10F1 handling.
# EI window is re-created if need be to display equipment operator message.
#
# Revision 1.14  1999/07/28 13:12:14  hume
# Fixed bug where S10F1R got two replies.
#
# Revision 1.13  1999/06/11 16:05:33  hume
# Added VFEI COM_STATE variable, also added braces per procheck warnings.
#
# Revision 1.12  1999/06/11 15:16:16  hume
# Added VFEI Machine Command HELLO.
#
# Revision 1.11  1999/05/27 19:19:54  hume
# Added new logic for VFEI clock synchronization command, and rearranged
# the existing clock setting logic to make it reusable.
#
# Revision 1.10  1998/11/17 20:27:40  hume
# Fixed mispelling in event description.
#
# Revision 1.9  1998/08/25 21:43:10  hume
# Fixed two bugs in TRACE_REPORT code.
#
# Revision 1.8  1998/08/06 22:09:28  hume
# Changed to parameterized queries in the last change so that copying
# records to different machines will work.
#
# Revision 1.7  1998/08/06 18:58:41  hume
# Added VFEI variables VFEI_ALARMS, VFEI_EVENTS, and VFEI_MACH_CMDS which
# can be STATUS_QUERY'd for the known alarms, VFEI events, and Machine
# Commands.  Each variable value is a list of pairs - the pairs are
# the item identifier and a description.
#
# Revision 1.6  1998/01/02 22:37:42  hume
# Bug fix in STATUS_QUERY.
#
# Revision 1.5  1997/12/30 22:55:44  hume
# Fixed bug when cmd_ack was called with TIMEOUT.
#
# Revision 1.4  1997/12/30 22:23:03  hume
# Fixed error - string for data item VARIABLE_ID should be VAR_ID.
#
# Revision 1.3  1997/10/24 19:17:01  hume
# Fixed two typo bugs and added defensive code for existence of VFEI_MID.
#
# Revision 1.2  1997/08/08 21:00:10  hume
# Made mods to promote ease of customization using custom directory.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#

# Take a SEMATECH VFEI command and execute it,
# the return value is the VFEI text of the reply message.
# VFEI is not much more than a formatting layer around
# a dozen or so SECS commands.  
# 
# Our use of VFEI is through a procedure completely decoupled
# from the message system so:
# (1) you can use it with any message system
# (2) you can test it or use it independent of a message system
#
# You do not need to use VFEI to use the gem ei code.
# The VFEI commands are parsed for their semantic content
# and non-vfei action procedures are called.  The usual
# non-vfei replies are then converted to VFEI.
#
# reference: SEMATECH Technology Transfer 95113016A-TR
# Virtual Factory Equipment Interface: Version 2.2
#
# example VFEI commands
# {CMD/A="ABORT" MID/A="TRK1" MTY/A="C" TID/U4=301}
# {CMD/A="INITIALIZE" MID/A="TRK1" MTY/A="C" TID/U4=302}

proc ei_vfei_cmd {spname vfei_cmd} {
   # we assume that the MID called out in the message is 
   # the one we are connected to using $spname
   # parse the VFEI string into a unique global array
   global $spname errorInfo vfei_va
   vfei_2_array $vfei_cmd vfei_va
   # there must always be a CMD, MID,  MTY, and TID
   set bad 0
   foreach item {CMD MID MTY TID} {
       if { ![info exists vfei_va($item)] } {
           set bad 1
           set $item {}
           }\
       else { set $item $vfei_va($item) }
       }
   if {!$bad} {
       # we'll use whatever VFEI MID they want us to
       set ${spname}(VFEI_MID) $MID
       # using $TID, reparse the arguments into a unique global array
       set vname ${spname}_va_${TID}
       global $vname
       vfei_2_array $vfei_cmd $vname
       set rc [catch {ei_vfei_$CMD $spname $vname} reply]
       if {!$rc} { 
           catch { unset $vname }
           return $reply 
           }
       if { [info command ei_vfei_$CMD] == "ei_vfei_$CMD" } {
           # trapped a Tcl error in an implemented proc
           set ETX VFEI_UNKNOWN_ERROR
           }\
       else {
           # improper CMD or not implemented CMD
           set ETX EQUIP_INVALID_COMMAND
           }
       set result [ei_vfei_cmd_ack $vname $ETX]
       catch { unset $vname }
       return $result
       }
    set ECD 40026	
    set ETX COMM_MSG_SYNTAX_ERROR
    if { $TID == "" } { set TID 0 }
    return "CMD/A=\"CMD_ACK\" MID/A=\"$MID\" MTY/A=\"R\"\
 TID/U4=$TID ECD/U4=$ECD ETX/A=\"$ETX\""
    }



#
# format a VFEI command reply
#
# For return codes 0 and TIMEOUT
#  we cheat and call this with the 0 or TIMEOUT value for
#  the ETX argument!
#
proc ei_vfei_cmd_ack {va ETX {ECD lookup}} {
    global $va
    if { $ECD == "lookup" } {
        switch -exact $ETX {
           {}                     { set ECD 0 }
           0                      { set ECD 0 ; set ETX {}}
           TIMEOUT                {
               set spname [substr $va "" _va_[set ${va}(TID)]]
               set reason [secs_xact_failure $spname]
               if { $reason == "BAD_SEND" || $reason == "NO_REPLY" } {
                   set ETX COMM_TIMEOUT
                   set ECD 40028
                   }\
               elseif { $reason == "REJECTED" } { ;# stream 9 reply
                   set ETX EQUIP_INVALID_COMMAND
                   set ECD 50001
                   }\
               elseif { $reason == "ABORTED"} { ;# F0 abort 
                   set ETX EQUIP_CANNOT_DO_NOW
                   set ECD 50002
                   }
               }
           VFEI_UNKNOWN_ERROR     { set ECD 30000}
           VFEI_INVALID_PARAM     { set ECD 30003}
           VFEI_VID_NOT_EXISTS    { set ECD 30009}
           VFEI_EVENT_NOT_EXISTS  { set ECD 30011}
           VFEI_MISSING_PARAM     { set ECD 30014}
           VFEI_CMD_NOT_SUPPORTED { set ECD 30019}
           VFEI_UNEXPECTED_VALUE  { set ECD 30025}
           VFEI_FILE_IO_ERROR     { set ECD 30030}
           VFEI_CANNOT_TIME_SYNCH { set ECD 30050}
           COMM_MSG_SYNTAX_ERROR  { set ECD 40026}
           COMM_TIMEOUT           { set ECD 40028}
           EQUIP_UNKNOWN_ERROR    { set ECD 50000}
           EQUIP_INVALID_COMMAND  { set ECD 50001}
           EQUIP_CANNOT_DO_NOW    { set ECD 50002}
           EQUIP_INVALID_PARAM    { set ECD 50003}
           EQUIP_NOT_ENOUGH_SPACE { set ECD 50006}
           EQUIP_INVALID_FORMAT   { set ECD 50007}
           EQUIP_REPORT_EXISTS    { set ECD 50008}
           EQUIP_VID_NOT_EXISTS   { set ECD 50009}
           EQUIP_LINK_EXISTS      { set ECD 50010}
           EQUIP_EVENT_NOT_EXISTS { set ECD 50011}
           EQUIP_REPORT_NOT_EXISTS {set ECD 50012}
           EQUIP_WILL_NOT_ACCEPT  { set ECD 50016}
           EQUIP_INVALID_TYPE     { set ECD 50017}
           EQUIP_REQUEST_DENIED   { set ECD 50018}
           EQUIP_INCOMPLETE_RESPONSE { set ECD 50020 }
           EQUIP_RESOURCE_NOT_FND { set ECD 50023}
           default { set ECD 30000 ;# VFEI_UNKNOWN_ERROR }
           }
        }
    return "CMD/A=\"CMD_ACK\" MID/A=\"[set ${va}(MID)]\" MTY/A=\"R\"\
 TID/U4=[set ${va}(TID)] ECD/U4=$ECD ETX/A=\"$ETX\""
        }

#
# convert SECS data in TSN format to VFEI name/type=value
# used in STATUS_QUERY and in VFEI event reports
#
proc ei_vfei_from_TSN {name tsn} {
    set text {}
    set type [lindex $tsn 0]
    set type [lindex [split $type :] 0]
    if { $type == "A" } { set value [lindex $tsn 1] }\
    else { set value [lreplace $tsn 0 0] }
    if { $type == "TF" } { set type BL }
    if { $type == "A" } { append text "$name/$type=\"$value\"" } \
    elseif { $type == "VFEI_NTV" } {
        # its already a set of (name/type=value)s
        # this is an escape so that one or more (name/type=value)s
        # can be dynamically computed.
        # use [list VFEI_NTV $ntv_text] or similar to have a proper list for input
        append text $value
        }\
    elseif { $type == "L" } {
        # we do not have element names for a rigorous treatment of lists
        # so we map it to a vector of the first type of item
        # and we do not worry about it because it works well for items like
        # EventsEnabled and will hardly be used otherwise.
        set len [llength $value]
        set subtype [lindex [lindex $value 0] 0]
        set subtype [lindex [split $subtype :] 0]
        if { $subtype == "TF" } { set subtype BL }
        append text "$name/$subtype\[$len\]=\["
        foreach v $value { append text "[lreplace $v 0 0] " }
        append text \]  
        }\
    else {
        set len [llength $value]
        if { $len > 1 } { ;# vector
            append text "$name/$type\[$len\]=\["
            foreach v $value { append text "$v " }
            append text \]
            }\
        else { ;# usual non string scalar 
            append text "$name/$type=$value"
            }
        }
    return $text
    }

proc ei_vfei_ABORT {spname va} {
    global $va
    set cmdargs ""
    # LEVEL is an optional equipment specific parameter
    # "AbortLevel" is mentioned by E5
    # "U2" for level per VFEI
    if { [info exists ${va}(LEVEL)] } {
        set CPNAME "A AbortLevel"
        set CPVAL "U2 [set ${va}(LEVEL)]"
        lappend cmdargs [list $CPNAME $CPVAL]
        }
    return [ei_vfei_rcmd $spname $va ABORT $cmdargs]
    }

proc ei_vfei_PAUSE {spname va} { return [ei_vfei_rcmd $spname $va PAUSE] }
proc ei_vfei_RESUME {spname va} { return [ei_vfei_rcmd $spname $va RESUME] }
proc ei_vfei_START {spname va} { return [ei_vfei_rcmd $spname $va START] }

#
# do a remote command and return a VFEI reply
#
proc ei_vfei_rcmd {spname va verb args} {
    global $va
    set result [ei_rcmd $spname $verb $args]
    # map CMDA result back to VFEI
    if { $result == "0" || $result == "TIMEOUT" } { return [ei_vfei_cmd_ack $va $result] }
    if { $result == "1" } { return [ei_vfei_cmd_ack $va EQUIP_INVALID_COMMAND] }
    if { $result == "2" } { return [ei_vfei_cmd_ack $va EQUIP_CANNOT_DO_NOW] }
    # non-standard return code:
    return [ei_vfei_cmd_ack $va EQUIP_UNKNOWN_ERROR]
    }


# enable or disable specified alarm reports
# ENABLE 1|0
# ALARM_IDs (I4)
proc ei_vfei_ALARM_SETUP {spname va} { 
    global $va
    if { ![info exists ${va}(ENABLE)] } {
        return [ei_vfei_cmd_ack $va VFEI_MISSING_PARAM]
        }
    if { ![info exists ${va}(ALARM_ID)] } {
        set ${va}(ALARM_ID) ""	;# meaning all alarms
        }
    set result [ei_alarm_enable $spname [set ${va}(ENABLE)] [set ${va}(ALARM_ID)]]
    # map S5F4 ACKC5 value
    if { $result == "0" || $result == "TIMEOUT" } { return [ei_vfei_cmd_ack $va $result] }
    return [ei_vfei_cmd_ack $va EQUIP_REQUEST_DENIED]
    }

# return value of VFEI COM_STATE variable
# optionally test communication and return COMMUNICATING or NOT-COMMUNICATING
# configuration varmethod supplies preferred SECS transaction [SnFmR [TSN]]
# for example:
# 'ei_vfei_COM_STATE \$spname S1F1R'
# 'ei_vfei_COM_STATE \$spname S2F25R {B 1}'
proc ei_vfei_COM_STATE {spname args} {
    set len [llength $args]
    if { $len > 2 } { 
        return "CONFIGURATION ERROR"
        }
    if { $len == 0 } {
        # no transaction arguments - base reply on current knowledge without polling
        # comm_state == "ENABLED {NOT-COMMUNICATING}" COMMUNICATING 
        global $spname
        if { [string first NOT [set ${spname}(comm_state)]] > 0 } {
            return NOT-COMMUNICATING
            }
        return COMMUNICATING
        }
    set reply [eval [concat secs_xact $spname $args]]
    if { $reply == "TIMEOUT" } { return NOT-COMMUNICATING }
    return COMMUNICATING
    }

# TERMINAL 
# [MESSAGE]
proc ei_vfei_DISPLAY_MSG {spname va} { 
    global $va
    set msg "" 	;# empty message means clear notice area
    if { [info exists ${va}(MESSAGE)] } { 
        set msg [set ${va}(MESSAGE)]
        }
    set term 0
    if { [info exists ${va}(TERMINAL)] } {
        set term [set ${va}(TERMINAL)]
        }
    set result [ei_terminal_display $spname $msg $term]
    # map the ACKC10 value of S10F4
    if { $result == "0" || $result == "TIMEOUT" } { return [ei_vfei_cmd_ack $va $result] }
    if { $result == "1" } { return [ei_vfei_cmd_ack $va EQUIP_REQUEST_DENIED] }
    return [ei_vfei_cmd_ack $va EQUIP_CANNOT_DO_NOW]
    }

#
# Equipment terminal is sending us a message S10F1[R]
#
proc ei_vfei_display_msg spname {
    global $spname
    # optional reply requested
    if { [string first R [set ${spname}(lastrSFR)]] > 0 } {
        $spname put S10F2 {B 0}
        # prevent 2nd reply from non-VFEI UI code
        set ${spname}(lastrSFR) S10F1
        }
    rset [set ${spname}(lastrmsg)] {L2 {t term} {a text}}
    set term [expr {$term}]
    set MID [set ${spname}(VFEI_MID)]
    set TID 0 
    set msg "CMD/A=\"DISPLAY_MSG\" MID/A=\"$MID\"\
 MTY/A=\"E\" TID/U4=$TID TERMINAL/B=$term MESSAGE/A=\"$text\""
    ei_vfei_output $spname $msg
    # if our UI is up, send it over
    global tk_library
    if { [info exists tk_library] && [winfo exists .ei_${spname}.term.i.h] } {
         ei_term_disp $spname
         }
    }


# EVENT_SETUP
# this guy bypasses the SEMI notion of reports so there
# is more work to implement him
#
# when event reports are created, 
# for every EVENT_ID we create two ei_report records:
#
# spname    RPTID        VIDs
# ------    -----        ----
#          "vfei_$CEID"  <VFEIname>s  ;# virtual VFEI definition
#           $RPTID       <VID>s       ;# actual SECS based definition
#
# And we create a ei_event_report record for the actual SECS based 
# definition:
#
# spname    CEID         RPTID
# ------    ----         -----
#           $CEID        $RPTID
#
# The SECS event report will come up by CEID, we'll parse the
# machine provided data, and then we'll hit table ei_report
# looking for "vfei_$CEID", to see about formatting a VFEI report
# with VFEIname variables.
# We'll get the EVENT_ID from the VFEIname column of ei_event for
# the CEID.
#
proc ei_vfei_EVENT_SETUP {spname va} {
    global $va
    if { ![info exists ${va}(ENABLE)] } {
        return [ei_vfei_cmd_ack $va VFEI_MISSING_PARAM]
        }
    set enable [set ${va}(ENABLE)]
    if { $enable != "0" && $enable != "1" } {
        return [ei_vfei_cmd_ack $va VFEI_UNEXPECTED_VALUE]
        }
    if { ![info exists ${va}(EVENT_ID)] } {
        if {$enable} {
            # enable what?
            return [ei_vfei_cmd_ack $va VFEI_MISSING_PARAM]
            }
        # else
        # disable all event reports
        # And because you are using VFEI, and you will use only
        # this call to manage event reports, we will delete all
        # reports too.
        set reply [ei_event_disable $spname "" 1]
        # "vfei_%" reports were deleted too
        if { $reply == "0" || $reply == "TIMEOUT" } { return [ei_vfei_cmd_ack $va $result] }
        return [ei_vfei_cmd_ack $va EQUIP_REQUEST_DENIED]
        }
    set events [set ${va}(EVENT_ID)]
    if {!$enable} {
        # disable specific event reports
        # And because you are using VFEI, and you will use only
        # this call to manage event reports, we will delete associated
        # reports, too
        set reply [ei_event_disable $spname $events 1]
        if { $reply == "0" } { 
            # now delete associate vfei_* reports for these events
            # first query the CEIDs from the EVENT_IDS
            # then remove the vfei_$CEID reports
            set where "where spname='$spname' and \
 ((VFEIname='[join $events {' or VFEIname='}]') or \
  (CEID='[join $events {' or CEID='}]'))"
            set reply [SQL "select CEID from ei_report $where"]
            set rows [lindex $reply 6]
            foreach row $rows {
                set CEID [lindex $row 0]
                SQL "delete from ei_report where spname='$spname'\
 and RPTID='vfei_$CEID'"
                }
            return [ei_vfei_cmd_ack $va 0] 
            }
        if { $reply == "TIMEOUT" } { return [ei_vfei_cmd_ack $va $reply] }
        return [ei_vfei_cmd_ack $va EQUIP_EVENT_NOT_EXISTS]
        }

    # Else we will enable the event(s)
    # and if need be, define a report
    
    # translate the list of EVENT_IDs to CEIDs
    set where "where spname='$spname' and \
 ((VFEIname='[join $events {' or VFEIname='}]') or \
  (CEID='[join $events {' or CEID='}]'))"
    set reply [SQL "select CEID from ei_event $where"]
    set CEIDs [lindex $reply 6]

    if { [llength $CEIDs] < [llength $events] } {
        return [ei_vfei_cmd_ack $va VFEI_EVENT_NOT_EXISTS]
        }

    # variables are optional, but if they are specifed,
    # they all must exist
    # we expect you to have the VFEIname configured
    # we need to know which are SECS based
    set vidlist ""
    if { [info exists ${va}(VAR_ID)] } {
        set vidlist [set ${va}(VAR_ID)]
        } \
    elseif { [info exists ${va}(VARIABLE_ID)] } {
        set vidlist [set ${va}(VARIABLE_ID)]
        }
    set where "where spname='$spname' and \
 (VFEIname='[join $vidlist {' or VFEIname='}]')"
    set reply [SQL "select varID,varclass from ei_variable $where"]
    set rows [lindex $reply 6]
    set varIDs ""
    set eqVars ""
    foreach row $rows {
        vset $row "varID varclass"
        if { $varclass == "SV" } {
            lappend eqVars $varID
            }
        lappend varIDs $varID
        }
    if { [llength $varIDs] < [llength $vidlist] } {
        return [ei_vfei_cmd_ack $va EQUIP_INVALID_PARAM]
        }

    # destroy any existing report for these events since you are
    # using VFEI and report maintenance is though this proc
    ei_event_disable $spname $events 1
    foreach CEID $CEIDs {
        SQL "delete from ei_report where spname='$spname' and\
 RPTID='vfei_$CEID'"
        }

    # if any variables are equipment based, create a new report
    if { [llength $eqVars] > 0 } {
        # generate an ID for a new report
        set RPTID [ei_RPTID_new $spname $CEIDs]
        set reply [ei_report_define $spname $RPTID $eqVars]
        if { $reply != "0" } { ;# DRACK 1=no, 2=fmt, 3=RPTID in use, 4=bad VID
             switch $reply { 
                 1 { return [ei_vfei_cmd_ack $va EQUIP_NOT_ENOUGH_SPACE] }
                 2 { return [ei_vfei_cmd_ack $va EQUIP_INVALID_FORMAT] }
                 3 { return [ei_vfei_cmd_ack $va EQUIP_REPORT_EXISTS] }
                 4 { return [ei_vfei_cmd_ack $va EQUIP_VID_NOT_EXISTS] }
           default { return [ei_vfei_cmd_ack $va EQUIP_REQUEST_DENIED] }
                 }
             }
        # link the report to the events
        set reply [ei_report_link $spname $RPTID $CEIDs]
        if { $reply != "0" } { 
            # LRACK 1=no 2=fmt 3=CEID linked, 4=bad CEID, 5=bad RPTID
             switch $reply { 
                 1 { return [ei_vfei_cmd_ack $va EQUIP_NOT_ENOUGH_SPACE] }
                 2 { return [ei_vfei_cmd_ack $va EQUIP_INVALID_FORMAT] }
                 3 { return [ei_vfei_cmd_ack $va EQUIP_LINK_EXISTS] }
                 4 { return [ei_vfei_cmd_ack $va EQUIP_VID_NOT_EXISTS] }
                 5 { return [ei_vfei_cmd_ack $va EQUIP_REPORT_NOT_EXISTS] }
           default { return [ei_vfei_cmd_ack $va EQUIP_REQUEST_DENIED] }
                 }
            }
        }
    # store our vfei_ report definitions and VARIABLE_IDs
    foreach CEID $CEIDs {
        SQL "insert into ei_report (spname,RPTID,VIDs) values\
 ('$spname', 'vfei_$CEID', '$vidlist')"
        }
    # turn on event reporting for these events
    set reply [ei_event_enable $spname $CEIDs]
    # ERACK
    if { $reply == "0" } { return  [ei_vfei_cmd_ack $va 0] }
    return [ei_vfei_cmd_ack $va EQUIP_REQUEST_DENIED]
    }
   

proc ei_vfei_INITIALIZE {spname va} {
    global $va $spname

    # turn on alarm and event reporting if not already on
    ei_vfei_output_init $spname $spname

    # make sure that the
    # AUTO_VFEI_INIT event is part of the event configuration table
    # this is an event that is synthesized by the VFEI driver
    SQL "insert into ei_event (spname,CEID,ID_TSN,is_reported,description,\
 VFEIname,event_class,host_managed,host_wants_enabled) values (\
 '$spname','AUTO_VFEI_INIT','A',1, 'VFEI automatic online initialization', \
 'AUTO_VFEI_INIT','VFEI_DRVR',1,1)"

    # set a flag that lets the software know we are using VFEI
    set ${spname}(using_VFEI) 1

    # now do report setups etc
    set reply [ei_initialize $spname]

    # since we are using VFEI, set up a whenmsg to forward 
    # terminal displays that originate at the equipment
    $spname whenever S10F1 "ei_vfei_display_msg $spname"

    # if you configured it, we already did most the logic of 
    # an EVENT_SETUP for real equipment based variables.
    # now we copy configuration records for VFEI event reports
    if { $reply == 0 } {
        set sreply [SQL "select RPTID,VIDs from ei_report_cfg where\
 spname='$spname' and RPTID like 'vfei_%'"]
        set rows [lindex $sreply 6]
        foreach row $rows {
            vset $row "RPTID VIDs"
            SQL "insert into ei_report (spname,RPTID,VIDs) values ('$spname',\
 '$RPTID','$VIDs')"
            }
        }

    #
    # ei_initialize return value
    # 0 = ok
    # 1 = failed comm
    # 2 = failed online
    # 3 = failed clock set
    # 4 = failed setting equipment constants
    # 5 = failed disabling events and reports
    # 6 = failed enabling events and reports
    if { $reply == 0 } { return [ei_vfei_cmd_ack $va 0] }
    #puts $reply
    if { $reply == 1 } { return [ei_vfei_cmd_ack $va COMM_TIMEOUT] }
    if { $reply == 2 } { return [ei_vfei_cmd_ack $va EQUIP_CANNOT_DO_NOW] }
    return [ei_vfei_cmd_ack $va EQUIP_REQUEST_DENIED] 
    }



# if TYPE is MACHINE
#  then each <VFEIname>=<value> is an ECV to set
# if TYPE is VFEI
#    CLOCK=<current_time> [SNTP_SERVER=host_or_ip]
proc ei_vfei_SET_PARAM {spname va} {
    global $va $spname
    if { ![info exists ${va}(TYPE)] } {
        return [ei_vfei_cmd_ack $va VFEI_MISSING_PARAM]
        }
    set list [array names $va]
    foreach name {CMD MID MTY TID TYPE} {
        set i [lsearch -exact $list $name]
        if { $i >= 0 } {
            set list [lreplace $list $i $i]
            }
        }
    if { [llength $list] == 0 } {
        return [ei_vfei_cmd_ack $va VFEI_MISSING_PARAM]
        }
    # 
    if { [set ${va}(TYPE)] == "MACHINE" } {
        set nvlist ""
        foreach name $list {
            lappend nvlist [list $name [set ${va}($name)]]
            }
        set result [ei_eqconst_set $spname $nvlist VFEIname]
        # map <EAC> to VFEI
        # 0=ok, 1=nexist, 2=busy, 3=range err
        if { $result == "0" } { return [ei_vfei_cmd_ack $va 0] }
        if { $result == "1" } { 
            return [ei_vfei_cmd_ack $va EQUIP_INVALID_PARAM] }
        if { $result == "2" } { 
            return [ei_vfei_cmd_ack $va EQUIP_CANNOT_DO_NOW] }
        return [ei_vfei_cmd_ack $va EQUIP_REQUEST_DENIED]
        }\
    elseif { [set ${va}(TYPE)] == "VFEI" } {
        # TYPE="VFEI" CLOCK=<current_time> [SNTP_SERVER=host_or_ip]
        if { [info exists ${va}(CLOCK)] } {
            # time synchronization command - set equipment AND this driver
            set my_gmt [localtime 2]
            # 
            # first, take care of our own clock, and then synch the equipment
            # we can be configured to ignore the request as far as our own clock
            # for example if our system clock is being synched 
            set reply [SQL "select varvalue from ei_variable where\
spname='$spname' and varID='CLOCK_SET_IGNORE'"]
           set ignoreflag [lindex [lindex [lindex $reply 6] 0] 0]
           if { $ignoreflag != "1" } { set ignoreflag 0 }
           #
           set reply_append {}
           if { !$ignoreflag } {
               if { [info exists ${va}(SNTP_SERVER)] } {
                    # they want us to synch with an NTP server
                    # maybe we are already doing that
                    vset [dmh_ntp_status] "s u server"
                    if { [set ${va}(SNTP_SERVER)] != $server } {
                        # we are not currently using this server
                        # set up for daily refresh
                        set rc [catch {dmh_ntp_install [set ${va}(SNTP_SERVER)] 86400}]
                        if { $rc } {
                            # this is a new error return code
                            return [ei_vfei_cmd_ack $va VFEI_CANNOT_TIME_SYNCH]
                            }
                        }
                    # our localtime is correct so erase any offset for secs_CLOCK 
                    catch { unset ${spname}(clock_offset) }
                    set ${spname}(CLOCK) 0 ;# clear last value
                    # the reply will show that we are using NTP
                    set reply_append " SNTP_SERVER/A=\"[set ${va}(SNTP_SERVER)]\""
                    }\
               else {
                    # not using NTP, and clock set is ok
                    # calculate and store offset
                    # expect CLOCK format YYYY-MM-DD hh:mm:ss[.uuuuuu]
                    # but A:16 YYYYMMDDHHMMSScc is also ok
                    if { [string length [set ${va}(CLOCK)]] == 16 } {
                        set ${va}(CLOCK) [ei_clock_reformat [set ${va}(CLOCK)]]
                        }
                    set timevec [lrange [join [split [set ${va}(CLOCK)] "- :."]] 0 5]
                    if { [catch {mktime $timevec 2} host_gmt] } {
                        # this is a new error return code
                        return [ei_vfei_cmd_ack $va VFEI_INVALID_PARAM]
                        }
                    # change offset for secs_CLOCK (code in ../lib)
                    set ${spname}(clock_offset) [expr {$host_gmt - $my_gmt}]
                    set ${spname}(CLOCK) 0 ;# clear last value
                    }
               }
            # our clock is corrected - secs_CLOCK returns corrected strings
            # try to synch equipment
            set ${spname}(clock_was_set) 0
            set reply [ei_clock_set $spname]
            if { $reply == "" } {
                # usual success - 
                set ${spname}(clock_was_set) 1
                return "[ei_vfei_cmd_ack $va 0]$reply_append"
                }
            if { $reply == "BAD_SEND" || $reply == "NO_REPLY" } {
                return "[ei_vfei_cmd_ack $va COMM_TIMEOUT]$reply_append"
                }
            if { $reply == "REFUSED" } {
               # the equipment recognizes S2F31 but refuses the command
               # we will relay that upstairs
               return "[ei_vfei_cmd_ack $va EQUIP_REQUEST_DENIED]$reply_append"
               }
            # REJECTED, ABORTED   
            # clock set is not supported by the equipment, 
            # we need to compensate by supplying our own TIME values
            # we will change the varmethod for variable VFEIname=="CLOCK"
            # so that the usual VFEI event reports will use our clock
            SQL "update ei_variable set varmethod='localtime 9' where\
 spname='$spname' and VFEIname='CLOCK'"
            # custom software can refer to [set ${spname}(clock_was_set)] == 0
            # to know that using our clock is appropriate
            return "[ei_vfei_cmd_ack $va 0]$reply_append"
            }\
        else {
            return [ei_vfei_cmd_ack $va EQUIP_INVALID_PARAM] 
            }
        }
    return [ei_vfei_cmd_ack $va EQUIP_INVALID_TYPE]
    }

#
# read variable values
# reply format is STATUS_LIST
#
proc ei_vfei_STATUS_QUERY {spname va} {
    global $va
    while 1 {
        if { ![info exists ${va}(VAR_ID)] } {
            if { ![info exists ${va}(VARIABLE_ID)] } {
                set result [ei_vfei_cmd_ack $va VFEI_MISSING_PARAM]
                break
                }\
            else {
                set namelist [set ${va}(VARIABLE_ID)]
                }
            }\
        else {
            set namelist [set ${va}(VAR_ID)]
            }
        if { [llength $namelist] < 1 } {
            set result [ei_vfei_cmd_ack $va VFEI_MISSING_PARAM]
            break
            }
        set valuelist [ei_var_query $spname $namelist VFEIname]
        if { $valuelist == "TIMEOUT" } {
            set result [ei_vfei_cmd_ack $va $valuelist]
            break
            }
        set notfound 0
        set max [llength $namelist]
        set text ""
        for {set i 0} {$i < $max} {incr i} {
            set tsn [lindex $valuelist $i]
            if { $tsn == {} } { incr notfound ; continue }
            # a pair is the usual case for {type value}
            set name [lindex $namelist $i]
            append text " [ei_vfei_from_TSN $name $tsn]"
            }
        if { $notfound > 0 } {
            set result [ei_vfei_cmd_ack $va EQUIP_INCOMPLETE_RESPONSE]
            }\
        else { set result [ei_vfei_cmd_ack $va 0] }
        append result $text
        break
        }
    regsub CMD_ACK $result STATUS_LIST result
    return $result
    }


# TRACE_SETUP
#
# VARIABLE_IDs are limited to class SV that are supported
#   by the machine
#
# FREQUENCY is a misnomer.  The value is used as a PERIOD.
#
# DIR is not supported
# Only REPORT_SIZE == 1 is supported.
#
# The standard implies that the parameters are mandatory, even for
# ENABLE=0
proc ei_vfei_TRACE_SETUP {spname va} {
    global $va
    foreach parm {ENABLE TRACE_ID } {
        if { ![info exists ${va}($parm)] } { return [ei_vfei_cmd_ack $va VFEI_MISSING_PARAM] }
        set $parm [set ${va}($parm)]
        }
    if { $ENABLE == "0" } {
        set SAMPLES 0     ;# this is important
        set FREQUENCY 0
        set REPORT_SIZE 1
        set VAR_ID ""
        }\
    else {
        foreach parm {FREQUENCY SAMPLES REPORT_SIZE VAR_ID} {
            if { ![info exists ${va}($parm)] } { return [ei_vfei_cmd_ack $va VFEI_MISSING_PARAM] }
            set $parm [set ${va}($parm)]
            }
        }
    if { [info exists ${va}(DIR)] } {
         return [ei_vfei_cmd_ack $va VFEI_CMD_NOT_SUPPORTED]
         }
    if { $REPORT_SIZE != "1" } {
        return [ei_vfei_cmd_ack $va VFEI_CMD_NOT_SUPPORTED]
        }
    # secs wants <TRID> <DSPER>
    # TRACE_ID = value of TRID
    # FREQUENCY = secs 
    set reply [ei_trace_setup $spname $TRACE_ID $FREQUENCY $SAMPLES\
 $REPORT_SIZE $VAR_ID]
    # map TIAACK value
    if { $reply == "0" } { 
        SQL "open sub vfei_trace_report to ei_event_log\
 proc=ei_vfei_trace_report insert * where CEID='TRACE_REPORT'"
        return [ei_vfei_cmd_ack $va 0] 
        }
    if { $reply == "TIMEOUT" } { return [ei_vfei_cmd_ack $va $reply] }
    if { $reply == "1" ||  $reply == "3" } { return [ei_vfei_cmd_ack $va EQUIP_INVALID_PARAM] }
    return [ei_vfei_cmd_ack $va EQUIP_WILL_NOT_ACCEPT]
    }

#
# received a TRACE_REPORT event from the subscription to ei_event_log
#
proc ei_vfei_trace_report {notice table cols keys ct err rows} {
    vset [lindex $rows 0] $cols
    # we should know spname,clock,CEID,data
    global $spname
    if { ![info exists ${spname}(VFEI_MID)] } { set ${spname}(VFEI_MID) $spname }
    set MID [set ${spname}(VFEI_MID)]
    set msg ""
    set REPORT_SIZE 1
    set TRACE_ID 0
    foreach pair $data {
        vset $pair {name value}
        if { $name == "TRACE_ID" || $name == "REPORT_SIZE"} {
            set $name $value
            continue
            }
        set reply [SQL "select value_TSN from ei_variable where\
 spname='$spname' and (VFEIname='$name' or varID='$name')"]
        set value_TSN [lindex [lindex [lindex $reply 6] 0] 0]
        set tsn $value_TSN
        foreach v $value { lappend tsn $v }
        append msg " [ei_vfei_from_TSN $name $tsn]"
        }
    set msg "CMD/A=\"TRACE_REPORT\" MID/A=\"$MID\" MTY/A=\"E\"\
 ECD/U4=0 ETX/A=\"\" TRACE_ID/U2=$TRACE_ID \
 REPORT_SIZE/U2=$REPORT_SIZE $msg"
    ei_vfei_output $spname $msg $clock
    }
    
    

####################### ei_vfei_cmds #######################
####################### ei_vfei_cmds #######################
####################### ei_vfei_cmds #######################
# return value of required VFEI Driver Variable VFEI_CMDS
proc ei_vfei_cmds {} {
    set list [info commands ei_vfei_\[A-Z\]*]
    regsub -all ei_vfei_ $list {} list
    return $list
    }

######################### ei_vfei_var_init ################
######################### ei_vfei_var_init ################
######################### ei_vfei_var_init ################
#
# add required VFEI Driver Variables to ei_variable table
# ref p16 95113016A-TR
#
proc ei_vfei_var_init spname {
    SQL "insert into ei_variable (spname,varID,varname,varclass,\
 value_TSN,ID_TSN,description,varmethod,varvalue,VFEIname) values ('$spname',\
 'VFEI_CMDS', 'VFEI_CMDS', 'VFEI_DRVR', 'A', 'A', \
 'List of VFEI commands supported', 'ei_vfei_cmds', '', 'VFEI_CMDS')"
    SQL "insert into ei_variable (spname,varID,varname,varclass,\
 value_TSN,ID_TSN,description,varmethod,varvalue,VFEIname) values ('$spname',\
 'VFEI_REL', 'VFEI_REL', 'VFEI_DRVR', 'A', 'A', 'VFEI driver release',\
 'return \$varvalue', '1.0', 'VFEI_REL')"
    SQL "insert into ei_variable (spname,varID,varname,varclass,\
 value_TSN,ID_TSN,description,varmethod,varvalue,VFEIname) values ('$spname',\
 'VFEI_VER', 'VFEI_VER', 'VFEI_DRVR', 'A', 'A', \
 'VFEI specification version', 'return \$varvalue', '2.2', 'VFEI_VER')"

    # 1998-08-06 feature addition
    # here are additional non-standard variables to get
    # lists of alarms and events - (use STATUS_QUERY get STATUS_LIST)
    SQL "insert into ei_variable (spname,varID,varname,varclass,\
 value_TSN,ID_TSN,description,varmethod,varvalue,VFEIname) values ('$spname',\
 'VFEI_ALARMS', 'VFEI_ALARMS', 'VFEI_DRVR', 'A', 'A', \
 'List of alarm ids and descriptions', \
 'return \[lindex \[SQL \"select ALID,ALTX from ei_alarm where spname=''\$spname''\"\] 6\]', \
 '', 'VFEI_ALARMS')"
    # NOTE: the driver developer is expected to update the VFEIname and
    # description fields in the ei_event table to provide meaningful words
    # for the CEID values.
    SQL "insert into ei_variable (spname,varID,varname,varclass,\
 value_TSN,ID_TSN,description,varmethod,varvalue,VFEIname) values ('$spname',\
 'VFEI_EVENTS', 'VFEI_EVENTS', 'VFEI_DRVR', 'A', 'A', \
 'List of VFEI events and descriptions', \
 'return \[lindex \[SQL \"select VFEIname,description from ei_event where spname=''\$spname''\"\] 6\]', \
 '', 'VFEI_EVENTS')"

    # VFEI Machine Commands (MACH_CMDs)
    # the driver developer enters each CMD_TYPE in its own ei_variable record
    # varID - usually the VFEI_MCMD_$CMD_TYPE (can change for uniqueness)
    # varname - usually the VFEI_MCMD_$CMD_TYPE
    # VFEIname - always VFEI_MCMD_$CMD_TYPE
    # varclass - always 'VFEI_MCMD'
    # description - usually provided by driver developer
    # varmethod,varvalue - developer can use to save configuration of  
    #                      expected arguments (custom)
    SQL "insert into ei_variable (spname,varID,varname,varclass,\
 value_TSN,ID_TSN,description,varmethod,varvalue,VFEIname) values ('$spname',\
 'VFEI_MACH_CMDS', 'VFEI_MACH_CMDS', 'VFEI_DRVR', 'A', 'A', \
 'List of VFEI machine commands and descriptions', \
 'ei_vfei_MACH_CMDS \$spname', '', 'VFEI_MACH_CMDS')"

    # the default record for the HELLO MACH_CMD
    SQL "insert into ei_variable (spname,varID,varname,varclass,\
 value_TSN,ID_TSN,description,varmethod,varvalue,VFEIname) values ('$spname',\
 'VFEI_MCMD_HELLO', 'VFEI_MCMD_HELLO', 'VFEI_DRVR', 'A', 'A', \
 'VFEI Machine Command HELLO to Test communication with the equipment', \
 'return \$varvalue', 'S1F1R', 'VFEI_MCMD_HELLO')"

    # here is a configuration for DMH message system output
    # if this is non-blank and you have a message system connection
    # at the time of issuing the INITIALIZE command
    # messages are sent and then deleted locally
    SQL "insert into ei_variable (spname,varID,varname,varclass,\
 value_TSN,ID_TSN,description,varmethod,varvalue,VFEIname) values ('$spname',\
 'VFEI_OUTPUT_MAILBOX', 'VFEI_OUTPUT_MAILBOX', 'VFEI_DRVR', 'A', 'A', \
 'DMH mailbox for VFEI message output',\
 'return \$varvalue', 'equip_box', 'VFEI_OUTPUT_MAILBOX')"

    # VFEI equipment is required to have certain variables
    # that GEM equipment is not required to implement.
    # If these variables are not in the table, create definitions.
    # The definitions we create will return whatever values are in the table.
    # We made up varID numbers, that mesh with our simulator,
    # the values are arbitrary, and hopefully these will work for you.
    foreach rec {\
 {MB_ID 596 "Machine batch ID"}\
 {MBC_ID 597 "Machine batch collection ID"}\
 {MBC_SIZE 598 "Machine batch collection size"}\
 } {
        vset $rec "name varID description"
        set reply [SQL "select varname from ei_variable where\
 spname='$spname' and VFEIname='$name'"]
        set ct [lindex $reply 4]
        if { $ct == 0 } {
            SQL "insert into ei_variable (spname,varID,varname,varclass,\
 value_TSN,ID_TSN,description,varmethod,varvalue,VFEIname) values ('$spname',\
 $varID, '$name', 'VFEI_DRVR', 'A', 'U4', '$description',\
 'return \$varvalue', '', '$name')"
            }
        }

    # VFEI communication state - checks connection and returns
    #    COMMUNICATING or NOT-COMMUNICATING
    SQL "insert into ei_variable (spname,varID,varname,varclass,\
 value_TSN,ID_TSN,description,varmethod,varvalue,VFEIname) values ('$spname',\
 'VFEI_COM_STATE', 'COM_STATE', 'VFEI_DRVR', 'A', 'A', \
 'Test equipment connection and return COMMUNICATING or NOT-COMMUNICATING',\
 'ei_vfei_COM_STATE \$spname S1F1R', '', 'COM_STATE')"
    }
 

#
###################### ei_vfei_event_report ####################
###################### ei_vfei_event_report ####################
###################### ei_vfei_event_report ####################
#
# An event report has been received and the data parsed and saved
# in the variables table.
#
# If we are reporting VFEI event reports, pull together the
# report and send it.
#
proc ei_vfei_event_report {spname CEID {clock ""}} {
    global $spname
    # the VFEI_MID should always exist, but maybe you did something custom...
    if { ![info exists ${spname}(VFEI_MID)] } { set ${spname}(VFEI_MID) $spname }
    # map the CEID to EVENT_ID
    set reply [SQL "select VFEIname from ei_event where \
 spname='$spname' and CEID='$CEID'"]
    set EVENT_ID [lindex [lindex [lindex $reply 6] 0] 0]
    if { $EVENT_ID == "" } return
    set reply [SQL "select * from ei_report where \
 spname='$spname' and RPTID='vfei_$CEID'"]
    set row [lindex [lindex $reply 6] 0]
    if { $row == "" } return
    set cols [lindex $reply 2]
    vset $row $cols
    # the VIDs are VFEInames
    # get the list of current {type value} pairs
    set reply [ei_var_query $spname $VIDs VFEIname 0]
    set msg "CMD/A=\"EVENT_REPORT\" MID/A=\"[set ${spname}(VFEI_MID)]\"\
 MTY/A=\"E\" ECD/U4=0 ETX/A=\"\" EVENT_ID/A=\"$EVENT_ID\""
    set i 0
    foreach name $VIDs {
        set tsn [lindex $reply $i]
        incr i
        if { $tsn == "" } continue
        append msg " [ei_vfei_from_TSN $name $tsn]"
        }
    ei_vfei_output $spname $msg $clock
    }

