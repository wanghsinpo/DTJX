# $Header: /usr/cvsroot/gem/host/vfei_output.tcl,v 1.5 2002/11/01 15:57:14 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: vfei_output.tcl,v $
# Revision 1.5  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.4  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.3  2001/05/25 21:37:34  hume
# Backup restoration.
#
# Revision 1.3  2001/02/02 19:39:35  hume
# Changed vfei_msg field size to 20000 from 2000.
#
# Revision 1.2  1997/10/24 19:17:02  hume
# Fixed two typo bugs and added defensive code for existence of VFEI_MID.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#


proc ei_vfei_output_init {spname MID} {
    global $spname
    set ${spname}(VFEI_MID) $MID
    # no harm if the table exists:
    SQL "create table ei_vfei_output (spname varchar(32),\
 clock varchar(16), vfei_msg varchar(20000), \
 primary key(spname,clock))"
    # events - keys are good enough
    SQL "open sub vfei_output to ei_event_log proc=ei_vfei_outsub\
 insert spname,clock,CEID"
    # alarms - want all data
    SQL "open sub vfei_output to ei_alarm_log proc=ei_vfei_outsub\
 insert *"

    # if you have configured it, and you have a DMH message
    # system connection, we will send your vfei output message
    # to your destination, and then delete them
    # the SYNC flag causes send and deletion of existing messages
    SQL "close sub ei_vfei_send to ei_vfei_output"
    set reply [SQL "select varvalue from ei_variable\
 where spname='$spname' and varID='VFEI_OUTPUT_MAILBOX'"]
    set box [lindex [lindex [lindex $reply 6] 0] 0]
    if { $box != "" } {
        set ${spname}(VFEI_OUTPUT_MAILBOX) $box
        set mh_group_var [dmh_var mh_group]
        if { [info exists $mh_group_var] && [llength [set $mh_group_var]] } {
            SQL "open sub ei_vfei_send to ei_vfei_output proc=ei_vfei_send insert SYNC *"
            }
        }
    }


#################### ei_vfei_outsub ########################
#################### ei_vfei_outsub ########################
#################### ei_vfei_outsub ########################
#
# called by subscription notification
#
# table is assumed to have "spname" and "clock" as keys
#
proc ei_vfei_outsub {notice table cols keys ct err rows} {
    vset [lindex $rows 0] $cols
    global $spname
    # VFEI_MID should exist, but maybe you did something custom...
    if { ![info exists ${spname}(VFEI_MID)] } { set ${spname}(VFEI_MID) $spname }
    set MID [set ${spname}(VFEI_MID)]
    if { $table == "ei_alarm_log" } {
        set msg "CMD/A=\"ALARM_REPORT\" MID/A=\"$MID\"\
 MTY/A=\"E\" ECD/U4=0 ETX/A=\"\" ALARM_ID/I4=$ALID\
 ALARM_STATE/U1=$is_set ALARM_TEXT/A=\"$ALTX\""
        ei_vfei_output $spname $msg $clock
        return
        }
    if { $table == "ei_event_log" } {
        ei_vfei_event_report $spname $CEID $clock
        return
        }
    }

 

#################### ei_vfei_output #########################
#################### ei_vfei_output #########################
#################### ei_vfei_output #########################
#
# here we have an asynchronous vfei message such as an
# event or alarm report
#
# In this model application, we will put these messages in
# a table.  You can subscribe to this table, and delete
# the messages after they have been successfully transferred
# or processed.  
#
proc ei_vfei_output {spname msg {clock ""}} {
    if { ![string compare $clock ""] } { set clock [secs_CLOCK $spname] }
    SQL "insert into ei_vfei_output (spname,clock,vfei_msg)\
 values ('$spname', '$clock', '$msg')"
    }

#################### ei_vfei_send #########################
#################### ei_vfei_send #########################
#################### ei_vfei_send #########################
#
# here we have a subscription routine that sends vfei output
# to a mailbox and deletes it after it is sent successfully
#
# This logic also prunes the ei_alarm_log and ei_event_log tables
# that feed the ei_vfei_output table
#
proc ei_vfei_send {notice table cols keys ct err rows} {
   vset [lindex $rows 0] $cols
   global $spname
   set rc [catch {
       mbx put [set ${spname}(VFEI_OUTPUT_MAILBOX)] $vfei_msg
       } ]
   if !$rc {
       # delete follows successful put
       set cleanup "foreach table {ei_alarm_log ei_event_log\
 ei_vfei_output} { SQL \"delete from \$table where spname='$spname'\
 and clock='$clock'\"}"
       # do the cleanup after all the insert subscriptions are processed
       after idle $cleanup
       }\
   else {
       #
       # the factory system is offline
       # when they get back online, they can tell us to 
       # INITIALIZE which will cause the send and delete to be
       # resumed
       # or they can tell us to flush the tables and start fresh
       # or we could use mbx init to connect to a different system.
       #
       # we will continue to prune the secs log tables
       # but we will preserve the vfei_output for the reconnection
       set cleanup "foreach table {ei_alarm_log ei_event_log} {\
 SQL \"delete from \$table where spname='$spname'\
 and clock='$clock'\"}"
       # do the cleanup after all the insert subscriptions are processed
       after idle $cleanup
       }
   } 

