# $Header: /usr/cvsroot/gem/host/supervisor.tcl,v 1.15 2004/09/28 13:39:22 hume Exp $
# Licensed and Supported Software
# (C)Copyright 1998 Hume Integration Software
# All Rights Reserved
#
# Host Interface Supervisor procedures
#
# $Log: supervisor.tcl,v $
# Revision 1.15  2004/09/28 13:39:22  hume
# The recipe upload directory is configurable and defaults to separate sub-
# directories for each connection name.
#
# Revision 1.14  2004/09/24 18:03:20  hume
# Changed default TRACE value to include state & connection attempts.
#
# Revision 1.13  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.12  2002/08/06 21:25:28  hume
# Added checkboxes to disable S1F17 and S2F31 during the initialization flow.
#
# Revision 1.11  2002/07/31 13:12:49  hume
# Changed initialization to have trace window earlier to see 1st messages.
# Proc ei_init has new optional argument, tracewin_TRACE.  Stopped reading
# from <MachineName> DMH mailbox for VFEI commands - only <MachineName>_VFEI.
#
# Revision 1.10  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.9  2000/12/12 04:17:23  hume
# Fixed supervisor stop procedure from initiating comm recovery and leaving
# behind some array elements which affected repeated start/stop.
#
# Revision 1.8  2000/10/10 21:32:43  hume
# updated last edit.
#
# Revision 1.7  2000/10/10 21:00:09  hume
# Added PASSIVE HSMS option for supervisor and gemhost/supervisor command lines.
#
# Revision 1.6  1999/07/24 22:40:05  hume
# Added -notk logic on conditional existence of dmh(notk) (NT, Tcl 8.1)
#
# Revision 1.5  1999/04/13 12:19:51  hume
# Want s5 enabled in default gemhost startup.
#
# Revision 1.4  1999/04/06 18:32:58  hume
# Added startup configuration to disable asking for variable and alarm data
# during initialization to address problem of too much data/too slow a link.
#
# Revision 1.3  1999/01/19 19:49:27  hume
# Handling of empty return of mbx init on reconnect failure was not proper.
#
# Revision 1.2  1998/02/05 22:45:51  hume
# Added automatic reconnection to DMH if the server is stopped and restarted.
# Added listening to SQL mailbox for SQL commands.
#
# Revision 1.1  1998/01/29 16:20:20  hume
# Added supervisor application.
#


# ei_startup table
# spname - interface name, also basis of input mailboxes
# status - used for supervisor window list
# port   - rs232 device name or [hostname:]TCP_port for terminal server or HSMS
# auto_start - 1 if interface should be started when supervisor starts
# DEVID      - equipment SECS-I device ID 
# hsms_PROTOCOL - 0 for non-HSMS, 1995 for standard HSMS, or 1993 
# MULT - set to 1 if equipment can handle more than 1 reply at a time
# BAUD - set to serial port baud rate if applicable
# post_startup_code - Tcl code which is evaluated just after starting an
#      interface.  You can set timeout parameters etc.
#      example: "set ${spname}(T2) 80000"

proc ei_supervisor {} {
    global tk_library 
    # create a table for equipment interface configuration
    SQL "create table ei_startup (\
 spname varchar(32),\
 status varchar(60),\
 port varchar(200),\
 auto_start integer,\
 DEVID integer,\
 hsms_PROTOCOL integer,\
 BAUD integer,\
 MULT integer,\
 use_s1f3 integer,\
 use_s1f11 integer,\
 use_s1f13 integer,\
 use_s1f17 integer,\
 use_s2f13 integer,\
 use_s2f29 integer,\
 use_s2f31 integer,\
 use_s5f5 integer,\
 use_s5f7 integer,\
 hsms_passive integer,\
 recipe_dir varchar(200),\
 post_startup_code varchar(2000),\
 primary key(spname))"
    # load in the table data, if previously saved
    set reply [SQL "include ei_startup.tab"]
    # if we do not have any rows, create a row for the gemhost example
    set ct [lindex [SQL "select spname from ei_startup"] 4]
    if { $ct == 0 } {
        SQL "insert into ei_startup (spname,port,DEVID,hsms_PROTOCOL,BAUD,\
 auto_start,MULT,use_s1f13,use_s1f11,use_s1f3,use_s1f17,use_s2f13,use_s2f29,use_s2f31,\
 use_s5f5,use_s5f7,hsms_passive) values \
 ('gemhost','localhost:5555', 0, 1995, 9600, 0, 1,1,1,1,1,1,1,1,1,1,0)"
        set ct 1
        }\
    else {
        # use_s1f17 and use_s2f31 were added August 2002 for better initialization control.
        # S2F31 to control clock synchronization
        # S1F17 to control requesting the online control state
        # These values become 0 for existing startup tables used by the new software.
        # So here is some migration logic to set these to 1 if the existing .tab
        # file predates this change.
        if { [string first {//c 0 INSERT} $reply] > 0 } {
            # ei_startup.tab file was read and used
            set fid [open ei_startup.tab]
            set tabdata [read $fid]
            close $fid
            if { [string first {use_s2f31} $tabdata] < 0 } { ;# the old schema
                SQL "update ei_startup set use_s1f17=1, use_s2f31=1"
                }
            }
        }

    # if we have only 1 EI
    # apply the parameters called out on the command line to it
    if { $ct == 1 } {
        global PORT HSMS DEVID BAUD PASSIVE 
        if { [info exists PORT] } {
            if { [info exists HSMS] } { set hsms $HSMS }\
            else { set hsms 0 }
            if { $hsms != "0" && $hsms != "1995" && $hsms != "1993" } {
                set hsms 1995 
                }
            SQL "update ei_startup set port='$PORT', hsms_PROTOCOL=$hsms"
            }
        foreach f {DEVID BAUD} {
            if { [info exists $f] } {
                SQL "update ei_startup set $f=[set $f]"
                }
            }
        if { [info exists PASSIVE] } {
            if { $PASSIVE != "0" } { set hsms_passive 1 } \
            else { set hsms_passive 0 }
            SQL "update ei_startup set hsms_passive=$hsms_passive"
            }            
        }

    # start the "auto_start" interfaces 
    ei_super_start "where auto_start<>0"

    # create and refresh the supervisor window 
    if { [info exists tk_library] } {
        set notk_var [dmh_var dmh notk]
        if { [info exists $notk_var] && [set $notk_var] } { } \
        else {
            ei_superwin_create
            ei_superwin_refresh
            # refresh table window after a delay
            after 3000 hub_table_refresh
            }
        }
    }
    
#
# start specified equipment interfaces 
#
proc ei_super_start {{where_clause ""}} {
    set reply [SQL "select * from ei_startup $where_clause"]
    set cols [lindex $reply 2]
    set rows [lindex $reply 6]
    foreach row $rows {
        vset $row $cols
        ei_start_ei $spname $cols $row
        }
    }

# connect or reconnect to DMH message group
# return values
#   -2 - not configured for group
#   -1 - failed to connect
#    0 - already connected
#    1 - restored connection
proc ei_super_dmh_connect {} {
    global MB_GROUP ei_super_status
    if { [info exists MB_GROUP] && [llength $MB_GROUP] } {
        set mh_group_var [dmh_var mh_group]
        if { ![info exists $mh_group_var] || [llength [set $mh_group_var]] == 0 } {
            set ei_super_status "Connecting to DMH Group $MB_GROUP"
            set rc [catch {mbx init $MB_GROUP} text]
            if { $rc } {
                set ei_super_status "DMH server $MB_GROUP not there ($text)."
                return -1
                }\
            else {
                set ei_super_status "Connected to $MB_GROUP"
                return 1
                }
            }\
        else { return 0 }
        }\
    else { return -2 }
    }


# Start an equipment interface.
# We connect to the DMH message system if
# MB_GROUP is defined and we are not already connected.
# Then we connect to the equipment if we are not already started.
proc ei_start_ei {spname cols data} {
    global $spname tk_library ei_super_status
    set dmh_rc [ei_super_dmh_connect]
    # already started check
    if { [info commands $spname] == "$spname" } {
        set ei_super_status "EI $spname already started"
        return
        }\
    else {
        set ei_super_status "EI $spname starting..."
        }
    vset $data $cols
    foreach col {use_s1f13 use_s1f11 use_s1f3 use_s2f13 use_s1f17 use_s2f29 use_s2f31 use_s5f5 use_s5f7 recipe_dir} {
        set ${spname}($col) [set $col]
        }

    # Do we want to show windows for this interface?
    # need Tk, and allow for -notk command line argument
    if { [info exists tk_library] } {
        set notk_var [dmh_var notk]
        if { [info exists $notk_var] && [set $notk_var] } { set tracewin_TRACE 0 }\
        else { set tracewin_TRACE 0x440E }
        }
  
    set rc [catch {
        # do the basic communication initialization
        ei_init $spname $port $hsms_PROTOCOL $DEVID $BAUD $hsms_passive $tracewin_TRACE
        # set the multiple open transactions flag
        set ${spname}(MULT) $MULT
        # respond to a mailbox for SQL commands (hub client)
        if { $dmh_rc >= 0 } {
            mbx whenmsg ${spname}_SQL {mbx whenmsg again; \
 gs_execute $mbxdest $mbxmsg $mbxreply}
            }
        # 
        if { $tracewin_TRACE != 0 } {
            # put up the host UI for status and characterization
            ei_ui $spname
            }
        # eval post_startup_code - can adjust timeouts etc
        eval $post_startup_code
        } text]
    if $rc {
        set ei_super_status "Could not start $spname - $text"
        }\
    else {
        set ei_super_status "$spname started at [localtime 0]"
        }
    }

# terminate an equipment interface
proc ei_super_stop spnames {
    foreach spname $spnames {
        global $spname
        # close control window
        catch { destroy .ei_$spname }
        # end any open transactions or queued sends
        catch { $spname reset } 
        # end trace on state which may try to restore communication
        catch {trace vdelete ${spname}(state) w ei_state_trace}
        # close connection which destroys trace window
        catch { $spname close }  
        # cleanup data
        catch { unset $spname }
        # create a dummy command for a few seconds to catch 
        # "after" scripts
        proc $spname args {}
        after 3000 "rename $spname {}"
        }
    }

# delete an equipment interface
proc ei_super_delete names {
    ei_super_stop $names
    foreach name $names {
        foreach table [hub_tables] {
            if { ![string match ei_* $table] } continue
            SQL "delete from $table where spname='$name'"
            }
         }
    }


########################################################
############ mh_app_lostserver #########################
############ mh_app_lostserver #########################
########################################################

# if we are using the DMH message system, and the server
# is disconnected, try periodically to get reconnected
# When we reconnect, restore listening to the mailboxes 
# and forwarding VFEI output
#
proc mh_app_lostserver {group fileID} {
    global MB_GROUP
    # attempt to rejoin the restarted message system
    # Give it some time between each try.
    after 60000 "ei_try_mbx_init $MB_GROUP"
    }

proc ei_try_mbx_init group {
    if { [catch {mbx init $group} init_reply] || $init_reply == ""} {
        # 300000 milliseconds is 5 minutes
        after 300000 "ei_try_mbx_init $group"
        return
        }
    # we are back online with the message system
    set reply [SQL "select spname from ei_startup"]
    set cols [lindex $reply 2]
    foreach row [lindex $reply 6] {
        vset $row $cols
        global $spname
        if { [info exists ${spname}(state)] } {
            # a running equipment connection
            # listen to a mailbox for remote debugging
            mbx whenmsg ${spname}_RPC mbx_RPC
            # listen to mailboxes for VFEI commands
            foreach MB [list $spname ${spname}_VFEI] {
                mbx whenmsg $MB \
  "mbx whenmsg again; mbx put \$mbxreply \[ei_vfei_cmd $spname \$mbxmsg\]"
                }
            # listen to a mailbox for SQL (hubclient) commands
            mbx whenmsg ${spname}_SQL {mbx whenmsg again; \
 gs_execute $mbxdest $mbxmsg $mbxreply}
            # restore VFEI output 
            catch {ei_vfei_output_init $spname [set ${spname}(VFEI_MID)]}
            }
        }
    }

