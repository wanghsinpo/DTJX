# $Header: /usr/cvsroot/gem/lib/ei_events.tcl,v 1.3 2001/11/15 17:03:50 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: ei_events.tcl,v $
# Revision 1.3  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.2  2001/05/25 21:37:34  hume
# Backup restoration.
#
# Revision 1.2  2001/02/02 19:38:32  hume
# Changed event log data field size to 20000 from 2000.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#
#
# Collection Event Reporting
#
#   CEID <<---->> RPTID <<---->> VID
#
# "host_managed" == 1 - configuration records of what the host 
#                       wants 
#                   0 - actual records 

########################## ei_eventtab_create ####################
########################## ei_eventtab_create ####################
########################## ei_eventtab_create ####################
proc ei_eventtab_create {spname} {
    global $spname

    # common tables
    SQL "create table ei_event_report (spname varchar(32),CEID varchar(32),\
 RPTID varchar(32),  primary key(spname,CEID,RPTID))"
    SQL "create table ei_report (spname varchar(32), RPTID varchar(32),\
 VIDs varchar(1000), primary key(spname,RPTID))"
    if { [set ${spname}(EQUIP)] } {

        SQL "create table ei_event (spname varchar(32),CEID varchar(32),\
 ID_TSN varchar(4), is_reported integer, description varchar(120),\
 primary key(spname, CEID))"

        } else {   ;# HOST

        # host has VFEIname, event_class
        SQL "create table ei_event (spname varchar(32),CEID varchar(32),\
 VFEIname varchar(32), host_managed int, host_wants_enabled int,\
 event_class varchar(10), ID_TSN varchar(4), is_reported integer,\
 description varchar(120), primary key(spname, CEID))"

        SQL "create table ei_event_report_cfg (spname varchar(32),\
 CEID varchar(32), RPTID varchar(32), primary key(spname,CEID,RPTID))"
        SQL "create table ei_report_cfg (spname varchar(32), \
 RPTID varchar(32), VIDs varchar(1000), primary key(spname,RPTID))"
        SQL "create table ei_event_log (\
 spname varchar(32),\
 clock varchar(16),\
 CEID varchar(32),\
 data varchar(20000),\
 primary key(spname,clock,CEID))"
        }
    }

