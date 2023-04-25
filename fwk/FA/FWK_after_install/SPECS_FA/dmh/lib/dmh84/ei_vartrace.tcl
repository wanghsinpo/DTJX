# $Header: /usr/cvsroot/tcllib84/ei_vartrace.tcl,v 1.2 2002/11/01 21:06:54 hume Exp $
#
# $Log: ei_vartrace.tcl,v $
# Revision 1.2  2002/11/01 21:06:54  hume
# Namespace change tweaks.
#
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
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
# Revision 1.1.1.1  1997/10/03 02:31:41  hume
# From tcllib42 with edits.
#
# Revision 1.1  1997/07/24 15:59:05  hume
# Support for remote equipment interfaces.
#

# Logic to distribute equipment interface data
# to DMH message system clients
#
# This makes possible viewing and controlling an equipment
# interface from any seat on the network.

namespace eval ::dmh {

# return a list of {name class} of equipment interfaces
#
# class is {secsport | hsms | comm}
#
proc ei_vartrace_selection {} {
   set result ""
   foreach name [info globals] {
       global $name
       if { ![info exists ${name}(TRACE)] } continue
       if { [info commands $name] != $name } continue
       if { [info exists ${name}(DEVID)] } {
           if { [info exists ${name}(T6)] && [info exists ${name}(socket)] } {
               lappend result [list $name hsms]
               continue 
               }
           if { [info exists ${name}(state)] } {
               lappend result [list $name secsport]
               continue 
               }
           }\
       else {
           if { [info exists ${name}(BAUD)] && [info exists ${name}(DATABITS)] } {
               lappend result [list $name comm]
               continue 
               }
           if { [info exists ${name}(T5)] && [info exists ${name}(socket)] } {
               # comm with TCP/IP connection
               lappend result [list $name comm]
               continue 
               }
           }
       }
    return $result
    }
      

# Trace a global array variable, and send Tcl statements
# that represent its current value and changes to that value
# to a DMH mailbox
# This is done via an SQL table so that only actual
# changes to the data are seen by the client, and the
# hubclient UI can be used to manage the subscription.
#
# primary==1 means that the variable lives in this
# process, and that the current value should be sent
# when the trace is opened.  primary==0 means that a
# copy of the variable lives in this process, and that
# only updates should be forwarded to be applied to the
# primary instance.
#
# We assume only 1 subscriber per variable, because:
#   - the overhead of multiple subscribers is undesirable
#     since the subscriber is notified on every data change
#   - the trickiness of suppressing change notifications
#     back to the originating source is simplified
#   - the closing logic is simplified
#   - the monitoring logic is simplified
#
proc ei_vartrace {varname boxname open primary} {
    global $varname 
    variable ei_vartrace_timer 
    variable ei_vartrace_ignore
    if { ![info exists ei_vartrace_ignore] } {
        set ei_vartrace_ignore 0
        }
    if $open {
        # if the table exists, a harmless error
        SQL "create table ei_vartrace (name1 varchar(80),name2 varchar(80),\
 value varchar(32000),primary key(name1,name2))"
        set names [array names $varname]
        foreach name $names {
            regsub -all ' [set ${varname}($name)] '' value
            set reply [SQL "insert into ei_vartrace (name1,name2,value) values (\
 '$varname','$name','$value')"]
            if { [string first "//c 0" $reply ] < 0 } {
                # it may be in the table already from prior cloning
                SQL "update ei_vartrace set value='$value' where name1='$varname'\
 and name2='$name'"
                }
            }
        # define a procedure to forward changes to the remote process
        proc ::dmh::ei_client_$boxname "notice tab cols keys ct err data"\
 "variable ei_vartrace_ignore ; if  \$ei_vartrace_ignore return ;\
 set value {} ; vset \[lindex \$data 0\] \$cols ; \
 mbx put $boxname \[list ::dmh::ei_vartrace_msg \$notice \$name1 \$name2 \$value\]"

        if $primary {
            # open a sync subscription so the current value is sent
            set SYNC "sync"
            # close any instance from a prior life to insure a new open
            SQL "close sub ei_${boxname}_${varname} to ei_vartrace"
            }\
        else {
            # do not send current value
            set SYNC ""
            }

        SQL "open sub ei_${boxname}_${varname} to ei_vartrace \
 proc=::dmh::ei_client_$boxname $SYNC insert update delete * where name1='$varname'"
        trace variable $varname wu ::dmh::ei_vartrace_handler

        # we just set up a busy feed of messages
        # we want to periodically check and see if there is a
        # reader for the messages, and if not, shutdown the flow
        # With no reader, the unchecked memory growth of
        # the server would eventually crash it.
        if { ![info exists ei_vartrace_timer] } {
            # 600,000 millisecs == 10 minutes
            set ei_vartrace_timer [after 600000 ::dmh::ei_vartrace_monitor]
            }
        }\
    else {	;# close
       # we assume only this client, so we end the trace
       trace vdelete $varname wu ::dmh::ei_vartrace_handler 
       # close the specific subscription
       SQL "close sub ei_${boxname}_${varname} to ei_vartrace"
       }
    }


# called on write access to a traced global variable
# update the SQL table data
#
proc ei_vartrace_handler {name1 name2 op} {
    global $name1
    if { $op == "w" } {
        regsub -all ' [set ${name1}($name2)] '' value
        set reply [SQL "update ei_vartrace set value='$value'\
 where name1='$name1' and name2='$name2'"]
        if { [string first "//c 0" $reply] < 0 } {
            SQL "insert into ei_vartrace (name1,name2,value) values (\
 '$name1','$name2','$value')"
            }
        return
        }
    if { $op == "u" } {
        SQL "delete from ei_vartrace where name1='$name1' and name2='$name2'"
        }
    }


#
# called periodically by timer
# to monitor and possibly shutdown a subscription feed
#
proc ei_vartrace_monitor {} {
    variable ei_vartrace_timer
    variable mh_group
    catch {unset ei_vartrace_timer}
    set sublist [hub_table_sub_list ei_vartrace]
    set good 0
    foreach sub $sublist {
        vset $sub "tab subname open_stmt"
        if { ![string match ei_* $subname] } continue
        set boxname [substr $open_stmt "ei_client_" " "]
        if { $boxname == "" } continue
        set close 0
        if { $mh_group == "" } { ;# message system was disconnected
            set close 1
            }\
        else {
            vset [mbx count $boxname] "in out unread"
            if { $unread > 10 } { set close 1 }\
            else { incr good }
            }
        if $close {
            SQL "close sub $subname to $tab" 
            set varname [substr ${subname}| ei_${boxname}_ |]
            global $varname
            trace vdelete $varname wu ::dmh::ei_vartrace_handler 
            # the mbx calls are in a catch in case the message system
            # was disconnected
            catch {
                mbx flush $boxname
                mbx close $boxname
                }
            }
        }
        
    # reschedule monitoring check if any good subs are left
    if { $good > 0 } {
        set ei_vartrace_timer [after 600000 ::dmh::ei_vartrace_monitor]
        }
    }
    
# This procedure is called by receiving a message from a remote source.
# There has been a change to a remote data item.  Update our copy.
# Since the remote side already knows about it, we use a 
# flag to suppress copying the change back.
proc ei_vartrace_msg {notice name1 name2 value} {
    global $name1
    variable ei_vartrace_ignore 
    set ei_vartrace_ignore 1
    if { $notice == "delete" } { catch { unset ${name1}($name2) }}\
    else {
        set ${name1}($name2) $value
        }
    set ei_vartrace_ignore 0
    }

} ;# namespace
