# $Header: /usr/cvsroot/gem/equip/eq_server.tcl,v 1.8 2002/11/01 15:57:14 hume Exp $
#
# $Log: eq_server.tcl,v $
# Revision 1.8  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.7  2002/07/23 13:42:00  hume
# Updated recipe name validation to look for file existence.  So now you can
# have recipe names with imbedded whitespace if they exist as files.
#
# Revision 1.6  2000/09/29 20:33:14  hume
# Need to reject RCMDs that affect processing in LOCAL control mode.
#
# Revision 1.5  2000/09/20 13:55:28  hume
# Added table window display.
#
# Revision 1.4  2000/09/19 19:44:56  hume
# Tweaking new logic.
#
# Revision 1.3  2000/09/19 01:39:02  hume
# Added more logic for support of external process user.
#
# Revision 1.2  2000/08/24 13:29:30  hume
# testing and polishing.
#
# Revision 1.1  2000/08/24 12:30:02  hume
# Example use of separate background process for equipment SECS interface.
#

# Example logic to help the GEM EQUIPMENT code work as a background process
# integrated with a separate GUI and Equipment using DMH messaging.

###################### eq_server_init ######################################
###################### eq_server_init ######################################
###################### eq_server_init ######################################

proc eq_server_init {spname {groupname EQUIP}} {
    global $spname
    # called at startup, but after the gemsim script is sourced

    # don't initialize DMH twice 
    set mh_group_var [dmh_var mh_group]
    if { ![info exists $mh_group_var] || [set $mh_group_var] == "" } {

        # be a server for the DMH message system (mh_group gets defined)
        mbx server $groupname

        # replace the GEMSIM handling of Remote Command (RCMD) messages 
        # first pull in the usual version using auto_path lookup instead
        # of coding a directory path
        # original versions in process.tcl
        if { [info procs eq_server_RCMD] == "eq_server_RCMD" } {
            catch { eq_S2F21_RCMD }
            # now replace the procs
            rename eq_S2F21_RCMD {}
            rename eq_S2F41_RCMD {}
            rename eq_server_S2F21_RCMD eq_S2F21_RCMD
            rename eq_server_S2F41_RCMD eq_S2F41_RCMD
            }

        # replace handling of operator alerts
        if { [info procs eq_server_operator_alert] == "eq_server_operator_alert" } {
            catch { eq_operator_alert }
            rename eq_operator_alert {}
            rename eq_server_operator_alert eq_operator_alert
            }
        # replace handling of S10 terminal displays
        if { [info procs eq_server_term_disp] == "eq_server_term_disp" } {
            catch { eq_term_disp }
            rename eq_term_disp {}
            rename eq_server_term_disp eq_term_disp
            }

        # send Tcl background errors 
        proc bgerror {msg} { mbx put TCL_ERROR $msg }
        }

    # it is harmless to initialize for this equipment twice
    #if { [info exists ${spname}(replybox)] } return

    # listen for SQL commands (see Datahub docs)
    mbx whenmsg ${spname}_SQL {mbx whenmsg again ; gs_execute $mbxdest $mbxmsg $mbxreply}

    # listen for Tcl commands
    mbx whenmsg ${spname}_RPC mbx_RPC

    # open a subscription to advise of host inititated parameter changes
    SQL "open sub eq_server_${spname} to ei_variable proc=eq_server_ECV_update\
 update varvalue where varclass='ECV' and spname='$spname'"

    # we use a dedicated reply mailbox for synchronous interaction
    set ${spname}(replybox) ${spname}_REPLY 
    }


# RCMD == Remote Commands like Abort

proc eq_server_S2F21_RCMD spname {
    global $spname
    set RCMD [set ${spname}(lastrmsg)]
    set Cmd [lindex $RCMD 1]
    set rc [eq_server_RCMD $spname $Cmd {}]
    # send reply if requested
    if { [string first R [set ${spname}(lastrSFR)]] > 0 } {
        $spname put S2F22 "U1 $rc"
        }
    }

# process S2F41 RCMD

# S2F41 {L:2 <RCMD> {L:n {L:2 <CPNAME> <CPVAL>} }
# reply
# S2F42 {L:2 <HCACK> {L:n {L:2 <CPNAME> <CPVAL>} }
#     <HCACK> {B 0 - ok, 1 bad command, 2 not now, 3 bad parameter, 4 ok-later}
#     L:n is to indicate bad parameters
# 
proc eq_server_S2F41_RCMD spname {
    global $spname
    set request [set ${spname}(lastrmsg)]
    if { [lindex $request 0] != "L:2" } {
        eq_S9_reply $spname 7 ;# bad data
        return
        }
    set RCMD [lindex $request 1]
    set Cmd [lindex $RCMD 1]
    set parmlist [lindex $request 2]
    set Ln [lindex $parmlist 0]
    set parmlist [lreplace $parmlist 0 0]
    #set argc [llength $parmlist]
    # check the parameters
    set badlist L
    set NameVals {}
    foreach item $parmlist {
        # {L:2 <CPNAME> <CPVAL>} == {L:2 {A:n NAME} {A:n VALUE}}
        rset $item "l2 {nt Name} {vt value}"
        if { $l2 != "L:2" } {
            eq_S9_reply $spname 7 ;# bad data
            return
            }
        set name [string tolower $Name]
        if { [string index $nt 0] != "A" } {
            lappend badlist [list L:2 [list $nt $Name] {B 1}]  ;# bad name
            continue
            }
        # verify names and values
        # example logic
        if { $name == "ppexecname" } {
            # a good name, so look at the value
            # we expect Ascii, blank is ok - means deselect recipe
            if { [string index $nt 0] != "A" } {
                lappend badlist [list L:2 [list $nt $Name] {B 3}]  ;# bad format
                continue
                }
            # trim blanks from beginning and end
            set value [string trim $value]
            # see if the recipe exists as a file - assume subdir recipes below pwd
            set relative_pathname [file join recipes $value]
            if { ![file exists $relative_pathname] } {
                lappend badlist [list L:2 [list $nt $Name] {B 2}]  ;# bad value
                continue
                }
            }\
        elseif { $Name == "ExampleArgName"} {
            # ... your validation of $value
            }
        lappend NameVals [list $Name $value]
        }
    if { [llength $badlist] > 1 } {
        set HCACK "B 3"   ;# bad parameter
        $spname put S2F42 [list L:2 $HCACK $badlist]
        return
        }
    set rc [eq_server_RCMD $spname $Cmd $NameVals]
    # special logic for code 3 - bad argument(s)
    # a proper reply is coerced 
    if { [lindex $rc 0] == "3" } {
        if { [llength $parmlist] == 0 } {
            mbx put ${spname}_ERROR "RCMD code 3 but no arguments to fault"
            $spname put S2F42 [list L:2 {B 1} L]
            return
            }
        # additional args are pairs 
        set badlist L
        foreach pair [lreplace $rc 0 0] {
            vset $pair "subscript badcode"
            if { $badcode != "1" && $badcode != "2" && $badcode != "3" } {
                mbx put ${spname}_ERROR "RCMD code 3 - bad argument error code $badcode"
                set badcode 2  ;# bad value
                }
            if { [catch {set subscript [expr $subscript]}] } {
                mbx put ${spname}_ERROR "RCMD code 3 - bad subscript $subscript"
                set subscript 0
                }
            if { $subscript < 0 || $subscript > [expr [llength $parmlist]-1] } {
                mbx put ${spname}_ERROR "RCMD code 3 - bad subscript $subscript"
                set subscript 0
                }
            set item [lindex $parmlist $subscript]
            rset $item "l2 {nt Name} {vt value}"
            lappend badlist [list L:2 [list $nt $Name] [list B $badcode]]
            }
        set HCACK "B 3"   ;# bad parameter
        $spname put S2F42 [list L:2 $HCACK $badlist]
        }
    set HCACK "B $rc"
    $spname put S2F42 [list L:2 $HCACK L]
    }

######################### eq_server_RCMD #####################################
######################### eq_server_RCMD #####################################
######################### eq_server_RCMD #####################################
#
# dispatch Remote Commands to the equipment controller using DMH
#
proc eq_server_RCMD {spname Cmd NameVals} {
    global $spname
    set prevstate [set ${spname}(process_state)]
    # validate Cmd
    #set cmd [string tolower $Cmd]
    #if { $cmd != "select" && $cmd != "start" && $cmd != "stop" && $cmd != "resume"\
 && "$cmd" != "pause" && $cmd != "abort" && $cmd != "completed" } { return 1 }
    # validate that the cmd is appropriate in the current state
    # initiate the new action
    # per GEM the controller should reject commands that affect processing
    # when the control_mode is LOCAL - return 2
    # uncomment next line if all RCMDS affect processing
    # if { [set ${spname}(control_mode)] == "LOCAL" } { return 2 }

    # send command to equipment controller
    set replies [mbx_do_xact ${spname}_RCMD "$Cmd $NameVals" [set ${spname}(replybox)]]
    set reply [lindex $replies 0]
    if { $reply == "TIMEOUT" } {
       mbx put ${spname}_ERROR "RCMD timeout - $Cmd $NameVals" 
       return 1 
       }

    # simple reply values 0,1,2,4
    set reply [string trim $reply]
    if { $reply == "0" || $reply == "1" || $reply == "2" || $reply == "4" } {
        return $reply 
        }
    # If you return 3, you need to return which argument(s) is (are) in error
    # and for what reason: 1== bad name, 2== bad value
    # return one or more pairs {<0-based list subscript> <reason_code>}
    # eg "3 {1 2}" means 2nd argument was faulty because of bad value
    # Use code "1" and not code "3" if missing expected arguments
    catch {
        if { [lindex $reply 0] == "3" } {
            return $reply
            }
        }
    # implementation error
    mbx put ${spname}_ERROR "RCMD reply was not proper: $reply"
    return 1
    }

############################## eq_server_ECV_update ###################
############################## eq_server_ECV_update ###################
############################## eq_server_ECV_update ###################
#
# the host has updated a parameter - send a notification message
#
proc eq_server_ECV_update {notice table cols keys ct etxt rows} {
    vset [lindex $rows 0] $cols
    # now have spname, varID and varvalue
    global $spname
    if { [info exists ${spname}(ECVHostChange)] && \
            [set ${spname}(ECVHostChange)] == 1 } {
        # this was host initiated -
        # tell the equipment controller/GUI
        set reply [SQL "select varname from ei_variable where spname='$spname'\
 and varID='$varID'"]
        set varname [lindex [lindex [lindex $reply 6] 0] 0]
        mbx put ${spname}_PARAMETER [list set $varname $varvalue]
        }
    }  


############################# eq_server_operator_alert #################
############################# eq_server_operator_alert #################
############################# eq_server_operator_alert #################
#
# Alerts are related to spooling status
#
proc eq_server_operator_alert {spname MSGID args} {
    mbx put ${spname}_ALERT "$MSGID $args"
    }

############################ eq_server_term_display ####################
############################ eq_server_term_display ####################
############################ eq_server_term_display ####################

# host asks to display message
# S10F3[R] {L:2 {B TID} <TEXT>
# S10F5[R] {L:2 {B TID} {L:N <TEXT>...}}
proc eq_server_term_disp spname {
    global $spname
    set request [set ${spname}(lastrmsg)]
    set R [expr [string first R [set ${spname}(lastrSFR)]] > 0]
    set F3 [expr [string first 3 [set ${spname}(lastrSFR)]] > 0]
    
    if $F3 {
        rset $request {L2 {tTID TID} {tTEXT TEXT}}
        }\
    else {
        set LN [lindex $request 2]
        set TEXT ""
        if { [llength $LN] > 1 } { 
            set TEXTs [lreplace $LN 0 0] 
            foreach line $TEXTs { append TEXT $line\n }
            set TEXT [string trimright $TEXT \n]
            }
        }
    
    mbx put ${spname}_TERMINAL "DISPLAY $TEXT"
 
    if $R {
        if $F3 { $spname put S10F4 "B 0" }\
        else { $spname put S10F6 "B 0" }
        }
 
    }
    
############################### eq_server_put ###########################
############################### eq_server_put ###########################
############################### eq_server_put ###########################
#
# send a message with a callback, 
# when the callback executes send a DMH message to the other process
#
proc eq_server_put {spname sf msg boxname} {
    $spname put $sf $msg [list eq_server_put_cb $boxname]
    }

# condition =   send_failure | send_complete | receive_failure 
proc eq_server_put_cb {boxname port sf condition description} {
    mbx put $boxname [list $port $sf $condition $description]
    }


################################ eq_server_vartrace #####################
################################ eq_server_vartrace #####################
################################ eq_server_vartrace #####################

# the remote client wants to listen to certain array element changes
# such as comm_state

proc eq_server_vartrace {spname elments boxname} {
    global $spname
    foreach sub $elments {
        trace variable ${spname}($sub) w [list eq_server_vartrace_cb $boxname]
        # send the current value to the caller 
        eq_server_vartrace_cb $boxname $spname $sub w
        }
    }

proc eq_server_vartrace_cb {_boxname _name1 _name2 _op} {
    catch {
        global $_name1
        set _value [set ${_name1}($_name2)]
        mbx put $_boxname [list $_name1 $_name2 $_value]
        }
    }

################################ eq_server_slaveexit #####################
################################ eq_server_slaveexit #####################
################################ eq_server_slaveexit #####################
#
# If the DMH client connection of the caller is lost, exit.
# A mailbox argument that the client is using to receive 
# is specified to identify the client connection.
# This is used when the external process is the one who starts us, and
# normally terminates us.  The Tcl process only lives for the remote client.
# There are times during development when you exit into a debugger and the
# normal exit logic does not execute, so logic like this is useful.
#
# This procedure is usually called by a DMH message sent by a remote client.
#
proc eq_server_slaveexit {boxname} {
    set sockhandle {}
    catch {
        set sockhandle [set [dmh_var mh_waitclient $boxname]]
        proc mh_app_lostclient {handle flag} "if { \$handle == \"$sockhandle\" } exit"
        }
    return $sockhandle
    }
            
################################ eq_server_tabwin #######################
################################ eq_server_tabwin #######################
################################ eq_server_tabwin #######################

# if Tk is functional, create/raise the hub table window
# this is used for development and debugging
#
proc eq_server_tabwin { } {
    global env tcl_version
    if { [info commands winfo] != "winfo" } { return "Tk is not available" }
    if { [info commands hub_tabwin] != "hub_tabwin" } {
        if { [info exists env(DMH_BIN)] } {
            set p $env(DMH_BIN) 
            } \
        else {set p /usr/local/bin }
        set hub hub[join [split $tcl_version .] {}]
        source [file join $p $hub]
        } 
     if { ![winfo exists .status] } { hub_tabwin }
     wm deiconify .
     raise .
     hub_table_refresh
     }

  
