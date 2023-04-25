# $Header: /usr/cvsroot/gem/lib/ei_alarmtab.tcl,v 1.3 2001/11/15 17:03:50 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: ei_alarmtab.tcl,v $
# Revision 1.3  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.2  1997/11/06 14:00:33  hume
# Modified ALID handling to accommodate I8 or U8 type.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#

# table ei_alarm
# a table for alarm management
#   spname
#   ALID (ALARM_ID)    - alarm ID
#   ID_TSN             - the TSN type code of the alarm ID 
#                        (the host discovers what the equipment uses)
#   set_CEID           - set event ID
#   clear_CEID         - clear event ID
#   category (ALARM_CATEGORY)  
#      category == 0 means not used
#      gem does not use category
#   ALTX (ALARM_TEXT) - 40 char max (e5)
#   is_enabled {1|0}   - actual equipment setup state
#   is_set {1|0}       - actual equipment set/clear
# fields used by host:
#   host_managed {1|0} - 1 means setup enable/disable on init
#   host_wants_enabled {1|0} - setup state wanted by host
#
# guidance - number your alarms from 1000-2999 by twos
#            use the ALID for the set_CEID
#            use the ALID+1 for the clear_CEID
# The requirement is that you choose CEID's that do not conflict
# with other events.

##################### ei_alarmtab_create ##########################
##################### ei_alarmtab_create ##########################
##################### ei_alarmtab_create ##########################
proc ei_alarmtab_create spname {
    global $spname
    if { [set ${spname}(EQUIP)] } {
        SQL "create table ei_alarm (spname varchar(32),ALID integer, \
 ID_TSN varchar(8),set_CEID integer, clear_CEID integer, category integer, \
 is_enabled integer, is_set integer, ALTX varchar(40),\
 primary key(spname,ALID))"
        }\
    else {   ;# HOST
        SQL "create table ei_alarm (spname varchar(32),ALID varchar(20), \
 ID_TSN varchar(8), category integer, \
 is_enabled integer, is_set integer, ALTX varchar(40),\
 host_managed integer, host_wants_enabled integer,\
 primary key(spname,ALID))"
        # log table - not used by equipment
        SQL "create table ei_alarm_log (\
 spname varchar(32),\
 clock varchar(16),\
 ALID varchar(20),\
 is_set int,\
 ALTX varchar(40),\
 primary key(spname,clock,ALID))"
        }
    }
