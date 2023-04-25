# $Header: /usr/cvsroot/tcllib84/dmhc_sta.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
#
# Licensed and Supported Material
# (C)Copyright 1995, 1999 Hume Integration Software
# All Rights Reserved
#
# $Log: dmhc_sta.tcl,v $
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.2  2001/11/15 17:14:17  hume
# Updated company name.
#
# Revision 1.1.1.1  2000/03/01 21:20:55  hume
# pkgindex only change.
#
# Revision 1.1.1.1  1999/10/05 00:58:06  hume
# Initial Tcl eight.two version.
#
# Revision 1.1.1.1  1999/07/02 18:48:37  hume
# Starting point for Tcl 8.1.
#
# Revision 1.4  1999/01/19 19:47:58  hume
# Added Header and Log cvs tags.
#
namespace eval ::dmh {
#
# DMH client code to display a status window depicting the state of the server
#
# This code only runs in clients, not the server.
#

#
# get the servers status data
# we interoperate with older servers and older applications
#
# if you want the newer version you have to ask
# version 7.6: <box> <ctIn> <ctOut> <count> <client>
# version 7.4: <box> <count> <client>
proc mh_server_status {{version 7.4}} {
    global tcl_version
    foreach v {mh_msgs_in mh_msgs_out mh_group mh_server} { variable $v }
    if { ![info exists mh_server($mh_group)] } { 
        if { ![info exists mh_msgs_in] } {
            set mh_msgs_in [set mh_msgs_out 0]
            }
        return "" 
        }
    set cmd "dp_RPC $mh_server($mh_group)\
 if { \$tcl_version < 7.6 }\
 mh_server_status else {mh_server_status $version}"
    set rc [catch $cmd data]
    if { $rc } {
        set mh_msgs_in [set mh_msgs_out 0]
        return
        }
    set firstrow [lindex $data 0]
    vset $firstrow "x mh_msgs_in mh_msgs_out"
    return $data
    }


proc mh_sw_box_view_data box {
    variable mh_group 
    variable mh_server
    set rc [catch { dp_RPC $mh_server($mh_group) mh_sw_box_view_data $box} data]
    if { $rc } { return "COMMUNICATION ERROR - NO DATA AVAILABLE" }
    return $data
    }

proc mh_ping_client {connID} {
    variable mh_group 
    variable mh_server
    set rc [catch { dp_RPC $mh_server($mh_group) mh_ping_client $connID } data]
    if { $rc } {return "COMMUNICATION ERROR - NO DATA AVAILABLE" }
    return $data
    }

# request and display client identity 
# this is a bad example because it asks the server to do something
# synchronous with another client.  The other client may be busy, and
# the server will be unresponsive.
proc mh_sw_cli_id lb {
    variable mh_group 
    variable mh_server
    variable mh_statwin_stat
    set client [mh_sw_get_client $lb]
    if { $client != "" } {
        set rc [catch { dp_RPC $mh_server($mh_group) mh_client_id $client } data]
        if { $rc } {
            set mh_statwin_stat "COMMUNICATION ERROR - NO DATA AVAILABLE"
            return
            }
        set mh_statwin_stat $data
        }
    }

# close a client connection
proc mh_sw_cli_close lb { 
    variable mh_group 
    variable mh_server
    variable mh_statwin_stat
    set client [mh_sw_get_client $lb]
    if { $client != "" && $client != "__me__" } {
        # you may be disconnecting yourself - we do not know it
        # because the file numbers are the servers, not ours
        set rc [catch { dp_RPC $mh_server($mh_group) close $client } data]
        if { $rc } { 
            set mh_statwin_stat "COMMUNICATION ERROR - NO DATA AVAILABLE" 
            return
            }
        set mh_statwin_stat $data
        after 100 ::dmh::mh_statuswin
        }
    }


proc mh_sw_cli_kill lb {
    variable mh_group 
    variable mh_server
    variable mh_statwin_stat
    set client [mh_sw_get_client $lb]
    if { $client != "" && $client != "__me__" } {
        # this could be suicide
        set rc [catch { dp_RPC $mh_server($mh_group) mh_client_kill $client } data]
        if { $rc } {
            set mh_statwin_stat "COMMUNICATION ERROR - NO DATA AVAILABLE"
            return
            }
        set mh_statwin_stat $data
        after 100 ::dmh::mh_statuswin
        }
    }
} ;# namespace
