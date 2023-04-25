# $Header: /usr/cvsroot/gem/equip/eq_spool.tcl,v 1.13 2005/03/20 15:37:37 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1999 Hume Integration Software
# All Rights Reserved
#
# $Log: eq_spool.tcl,v $
# Revision 1.13  2005/03/20 15:37:37  hume
# Added features to make persistent saving of dynamic reports configurable.
#
# Revision 1.12  2004/08/20 19:52:07  hume
# Added return values to eq_spool_add.
#
# Revision 1.11  2002/11/21 15:36:00  hume
# Revised the spooling initialization to guard against corrupted spool file
# data.  If bad data, a timestamped copy is made and the operator is alerted.
#
# Revision 1.10  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.9  2001/11/15 17:03:49  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.8  2001/01/24 23:42:32  hume
# Updated the 12/3/00 change of eq_VV_item to be foregiving of the format of
# string values by using them directly, as was done before 12/3/00, but the
# change breaks string values that were reformatted to be single lists.
#
# Revision 1.7  2000/12/16 16:08:12  hume
# Added new streams to spooling, decided to send offline event after S1F16
#
# Revision 1.6  2000/08/18 14:35:49  hume
# Added spname as an argument to the operator_alert proc.
#
# Revision 1.5  1999/05/27 21:41:31  hume
# Added comment to previous edit.
#
# Revision 1.4  1999/05/27 21:34:32  hume
# Host unload of an empty spool would not deactive spooling immediately.
#
# Revision 1.3  1999/01/22 15:51:46  hume
# Added missing GEM events and variable to provide event descriptions.
#
# Revision 1.2  1999/01/14 16:05:21  hume
# Had an extra reply to the purge message.
#
# Revision 1.1  1999/01/12 22:41:33  hume
# Added spooling functionality.
#


# spool file
# We use an SQL file in the subdirectory "spooldata".
# The file is only used to restore state on shutdown and restart.
# Spooling uses in-memory data.
# You may want to set the upper limit on SpoolMax so only a few meg
# of memory can be used.  The hub has no problem with tens of thousands
# of table rows.
#
# return pathname of spool file (result is relative to pwd)
proc eq_spoolfile {spname} {
     # updated to support multiple equipment instances
     if { $spname == "gemsim" } {
         return [file join spooldata spooldata.sql]
         }
     return [file join spooldata spooldata_${spname}.sql]
     }


#
# received S2F43 to control spooling
#
# Spooling does not occur unless turned on by this message.
#
# store list of on messages in variable SpoolStreamFns as SnFm SjFk ...
#    Sn means all primaries in Sn are spooled
# any message type not listed is "off"
# 
# Per the standard, S1 cannot be spooled, secondary messages cannot be spooled
# ALL other primarys can be spooled
#    This sounds flakey since many primaries are realtime and transactional.
#    However, it winds up being needed in the context when the host has
#    come back online and the spool is being unloaded, new messages have
#    to go to the end of the spool file instead of being thrown away, or
#    interrupting the one message transaction at a time requirement.
#    The equipment vendor needs to think twice about offering spooling since
#    there is no control over when the messages are actually delivered.
#    Is your equipment safe today if host replies from messages sent yesterday 
#    are being received?  Maybe you should restrict which messages can be
#    spooled to insure proper process operation.
#
#  If you want to be GEM compliant, it is your job to use proc eq_checked_put
#  to send any non-S1 primary messages that originate in your code so 
#  they can be spooled.  This application fully complies with using
#  eq_checked_put.
#  
# Most people only care about the spooling of data reports and alarms:
# S5F1 S6F1 S6F3 S6F9 S6F11 S6F13
# The context of running while the spool is unloading becomes non-important
# for a modern HSMS interface that can unload thousands of messages in
# a few seconds.
#
proc eq_spool_control spname {
    global $spname
    # expect L:m {L:2 {U1 <S>} {L:n {U1 <f1>} ...}} ...
    set onlist ""
    set Lm_reply ""
    set RSPACK "B 0"	;# part of success reply
    set msg [set ${spname}(lastrmsg)]
    set Lm [lindex $msg 0]
    set msg [lreplace $msg 0 0]
    foreach clause $msg {
        rset $clause "L2 {tS Stream} Ln"
        if { $tS != "U1:1" } {
            # cheapest way to make sure $Stream is a number
            eq_S9_reply $spname 7
            return
            }
        if { $Stream == 1 } { 
            set RSPACK "B 1"	;# rejected setup, not allowed
            lappend Lm_reply [list L:3 {U1 1} {B 1} L:0]
            continue
            }
        if { $Stream > 17 } { 
            set RSPACK "B 1"	;# rejected setup, unknown stream
            lappend Lm_reply "L:3 {U1 $Stream} {B 2} L:0"
            continue
            }
        if { $Ln == "L:0" } {
            # all primes are spooled in this stream
            lappend onlist S${Stream}
            }\
        else {
            set Ln [lreplace $Ln 0 0]
            foreach fn $Ln {
                vset $fn "tF F"
                # must be number - enforce data type
                if { $tF != "U1:1" } {
                    eq_S9_reply $spname 7
                    return
                    }
                # must be odd
                set one [expr $F % 2]
                if { $one != "1" } {
                    set RSPACK "B 1"
                    lappend Lm_reply "L:3 {U1 $Stream} {B 4} {L {U1 $F}}"
                    continue
                    }
                # lets not fuss about exactly which fn - if we have not
                # implemented it (yet), so what.  Save that host wants it spooled.
                lappend onlist S${Stream}F${F}
                }
            }
        }
    # if the data was ok, save the new spool specification
    if { $RSPACK == "B 0" } {
        SQL "update ei_variable set varvalue='$onlist' where spname='$spname'\
 and varname='SpoolStreamFns'"
        }
    # now reply
    set reply [list L:2 $RSPACK [concat L $Lm_reply]]
    $spname put S2F44 $reply
    }

    

# called after the variable table exists
# initialize the spooling logic
# must restore spooling state from last time
# we use an SQL file in the subdirectory "spooldata"
proc eq_spool_init spname {
    global $spname
    set ${spname}(spooling_state) INACTIVE
    set ${spname}(spooling_sequence) 0
    # create a table to hold spooled data - we will mirror it
    # to the file system for startup after power loss
    # being a table we can remote inspect/manipulate it
    # the length of the data field limits the size of a 
    # spooled message.
    SQL "create table ei_spool_data (spname varchar(32),\
 ts varchar(26), sequence int, sfr varchar(10), \
 data varchar(100000), primary key(spname,ts))"
    # read in spool data from last time
    # this includes ei_variable entries related to spooling
    #   which includes the state of S2F43 filtering
    set file [eq_spoolfile $spname]
    if { [file exists $file] } {
         SQL "include $file"
         # if we have any spooled messages, we will make
         # sure our count is accurate and set the spooling state active
         set reply [SQL "select sequence from ei_spool_data\
 where spname='$spname'"] 
         # set count to 0, change if proper spooled data is found
         SQL "update ei_variable set varvalue='0' where \
 spname='$spname' and varname='SpoolCountActual'"
         set ct [lindex $reply 4]
         if { $ct > 0 } {
             # validate the data by looking at min and max
             # and making sure there are no duplicate sequence numbers
             # multiple instances of the program running could corrupt the file
             set rows [lindex $reply 6]
             set max_sequence [lindex [lindex $rows 0] 0]
             set min_sequence $max_sequence
             set baddata 0
             foreach row $rows {
                 set seq [lindex $row 0]
                 if { $seq > $max_sequence } { set max_sequence $seq }
                 if { $seq < $min_sequence } { set min_sequence $seq }
                 if { [info exists saw_seq($seq)] } { set baddata 1 ; break }
                 set saw_seq($seq) 1
                 }
             if { $max_sequence - $min_sequence + 1 != $ct } { set baddata 1 }
             if { !$baddata } {
                 # the sequence is used to implement MaxSpool
                 set ${spname}(spooling_sequence) $max_sequence
                 set ${spname}(spooling_state) ACTIVE
                 SQL "update ei_variable set varvalue='$ct' where \
 spname='$spname' and varname='SpoolCountActual'"
                 }\
             else {
                 # an unusual situation we hope - spool data is not valid
                 # leave SpoolCountActual at 0 if it exists
                 # scrub in-memory rows
                 SQL "delete from ei_spool_data where spname='$spname'"
                 # rename the corrupt file for possible examination
                 set newname ${file}.corrupt_[join [split [localtime 9] { :}] {}]
                 catch {file rename $file $newname} 
                 set errtext "Saved spool messages were improperly sequenced and are not being used."
                 catch { eq_operator_alert $spname SPOOL_DATA_DISCARDED $errtext }
                 }
             }
	 }

    # in case the persistent file was not there or damaged, create the variables
    # that we use for spooling
    eq_spool_vars $spname

    # initialize for spooling persistence 
    # this rewrites the spooldata file in its most compact form
    eq_spool_persistence_init $spname

    # open a subscription so that if the Spool parameters are changed,
    # our variable copies are synched
    #   OverWriteSpool SpoolMax SpoolStreamFns
    set subname spool_parms_update	;# shared for all spname
    SQL "open sub $subname to ei_variable update proc=eq_spool_parms varvalue \
where varname='OverWriteSpool' or varname='SpoolMax' or varname='SpoolStreamFns'"
    }

# called by subscription when 
# OverWriteSpool, SpoolMax, or SpoolStreamFns is changed
# for convenience, we copy these values into our array
proc eq_spool_parms {notice tab cols keys ct err data} {
    vset [lindex $data 0] $cols
    # you always get keys - spname varID
    global $spname
    set varname [lindex [lindex [lindex [SQL "select varname from ei_variable where spname='$spname' and varID='$varID'"] 6] 0] 0]
    if { [info exists ${spname}($varname)] } {
        set ${spname}($varname) $varvalue
        }
    }
   

# if persistence is not there, make sure we have the spooling variables
# that we are supposed to have
proc eq_spool_vars spname {
    set ID_TSN U4
    set cols \
 "varID varname description varclass value_TSN varmethod varvalue"
    set data [list \
      [list 870 SpoolCountActual \
 "the actual # of msgs queued" \
 SV U4 {expr $varvalue} 0]\
      [list 871 SpoolCountTotal \
 "the total # of msgs spooled and/or discarded"\
 SV U4 {expr $varvalue} 0]\
      [list 872 SpoolFullTime \
 "the Clock from the time the spool last became full"\
 SV A:16 {return $varvalue} 1995010100000000]\
      [list 873 SpoolStartTime \
 "the Clock from the time spooling last became active"\
 SV A:16 {return $varvalue} {}]\
      [list 877 SpoolStreamFns \
 "the list of SnFm message types that are spooled, set by S2F43"\
 SV A {return $varvalue} {}]\
      ]

    foreach record $data {
        vset $record $cols
        set reply [SQL "insert into ei_variable (spname,[join $cols ,],ID_TSN)\
 values ('$spname', '$varID', '$varname', '$description', \
 '$varclass', '$value_TSN', '$varmethod', '$varvalue', '$ID_TSN')"]
        }

    set cols "varID varname description varclass value_TSN\
 varmethod varvalue ECMIN ECMAX ECDEF units"
    set data [list \
      [list 874 MaxSpoolTransmit  \
 "max. # of spooled msgs per S6F23 reply, 0=no limit"\
  ECV U4 {expr $varvalue} 0 0 32000 0 {}]\
      [list 875 SpoolMax  \
 "max number of messages spooled"\
  ECV U4 {expr $varvalue} 10000 0 100000 10000 {}]\
      [list 876 OverWriteSpool \
 "true=circular spool buffering, false=stop spooling when buffer full"\
  ECV TF {expr $varvalue} 0 0 1 0 {}]\
      ]
    foreach record $data {
        vset $record $cols
        set reply [SQL "insert into ei_variable (spname,[join $cols ,],ID_TSN)\
 values ('$spname', '$varID','$varname', '$description',\
 '$varclass', '$value_TSN', '$varmethod', '$varvalue', '$ECMIN', '$ECMAX',\
 '$ECDEF', '$units', '$ID_TSN')"]
        }
    }

    
          

# sync up the file system/subscription/persistence logic
# with the current state of spooling
proc eq_spool_persistence_init {spname} {
    global $spname
    set subname spool_$spname
    SQL "close sub $subname to ei_variable"
    SQL "close sub $subname to ei_spool_data"
    catch { close [set ${spname}(spool_fid)] }
    # create the spooldata subdirectory if needed
    # and then open the journalling file
    set file [eq_spoolfile $spname]
    set dir [file dirname $file]
    set rc [catch {
        file mkdir $dir ;# not error if already there 
        set ${spname}(spool_fid) [open $file w]
        } errtext ]
    if { $rc } {
        # we could not create our directory or open our file for writing
        catch { eq_operator_alert $spname SPOOLING_NOT_PERSISTENT $errtext }
        # hopefully we are running as a demo
        return SPOOLING_NOT_PERSISTENT
        }
    # open sync'd subs to write data
    # we dynamically define a proc in order to pass the spname argument
    proc eq_spool_w_$spname "sql {spname $spname}" { sq_spool_write $spname $sql}
    SQL "open sub $subname to ei_variable insert update delete sync create\
 sqlproc=eq_spool_w_$spname * where spname='$spname' and varname like '%Spool%'"
    SQL "open sub $subname to ei_spool_data insert update delete sync create\
 sqlproc=eq_spool_w_$spname * where spname='$spname'"
    # copy table entries into object - eg SpoolCountActual, SpoolCountTotal
    # this logic needed on resumption of spooling at power-up
    set reply [SQL "select varname,varvalue from ei_variable\
 where spname='$spname' and varname like '%Spool%'"]
    set rows [lindex $reply 6]
    foreach row $rows { 
        vset $row "varname varvalue"
        set ${spname}($varname) $varvalue
        }
    return ""
    }

# called by subscription to write spool data and status
# to the persistent file
proc sq_spool_write {spname sql} {
    global $spname
    # we should not need to open and close the file each time
    # if we flush the output stream
    catch {
        puts [set ${spname}(spool_fid)] $sql
        flush [set ${spname}(spool_fid)]
        }
    }


# called on communication failure
# or after failed send of spoolable message
#
# make sure spooling is active
# if new transition to spooling
#    zero SpoolCountActual
#    zero SpoolCountTotal
#    set SpoolStartTime
#    "alert operator that spooling is active"
#
proc eq_spool_activate {spname} {
    global $spname
    if { [set ${spname}(spooling_state)] == "INACTIVE" } {
        # fresh transition to spooling
        set ${spname}(spooling_sequence) 0
        SQL "update ei_variable set varvalue='0' where \
 spname='$spname' and (varname='SpoolCountActual' or varname='SpoolCountTotal')"
        set clock [secs_CLOCK $spname]
        SQL "update ei_variable set varvalue='$clock' where \
 spname='$spname' and varname='SpoolStartTime'"
        set ${spname}(spooling_state) "ACTIVE"
        set reply [SQL "select varname,varvalue from ei_variable\
 where spname='$spname' and varname like '%Spool%'"]
        set rows [lindex $reply 6]
        foreach row $rows { 
            vset $row "varname varvalue"
            set ${spname}($varname) $varvalue
            }
        # if we are configured to spool any messages, we alert the operator
        # that spooling has started
        if { [llength [set ${spname}(SpoolStreamFns)]] > 0 } {
            catch { eq_operator_alert $spname SPOOLING_ACTIVATED }
            } 
        # Spooling Activated event
        # Since we may be in the process of adding a message to the spool, 
        # and this will be another added message,
        # lets create the event in background after we return to avoid
        # possible re-entrancy problems or improper ordering.
        after 1 [list eq_gem_event $spname 4080]
        return 1
        }
    return 0
    }


# Make sure our spooling state is active
# If the passed message should be spooled, spool it
# 8/20/04 - added return values "SPOOLED" or "DISCARDED"

proc eq_spool_add {spname sfr data} {
    global $spname
    if { [set ${spname}(spooling_state)] == "INACTIVE" } {
        eq_spool_activate $spname
        }
    set SF [string trimright [string toupper $sfr] R]
    set S [substr $SF {} F]
    # consult S2F43 data in SpoolStreamFns to see if spooled
    if { ![info exists ${spname}(SpoolStreamFns)] } {return DISCARDED}
    # look for Sn or for SnFm in list
    if { [lsearch -exact [set ${spname}(SpoolStreamFns)] $SF] < 0 && \
       [lsearch -exact [set ${spname}(SpoolStreamFns)] $S] < 0 } { return DISCARDED}
    # this msg should be spooled
    incr ${spname}(SpoolCountTotal)
    SQL "update ei_variable set varvalue='[set ${spname}(SpoolCountTotal)]'\
 where spname='$spname' and varname='SpoolCountTotal'"
    if { [set ${spname}(SpoolCountActual)] >= [set ${spname}(SpoolMax)] } {
        if { [set ${spname}(SpoolFullTime)] < [set ${spname}(SpoolStartTime)] } {
            # new transition to full
            set ${spname}(SpoolFullTime) [secs_CLOCK $spname]
            SQL "update ei_variable set varvalue='[set ${spname}(SpoolFullTime)]'\
 where spname='$spname' and varname='SpoolFullTime'"
            catch { eq_operator_alert $spname SPOOLING_FULL }
            }
        if { ![set ${spname}(OverWriteSpool)] } {return DISCARDED}
        # previous msg has sequence $spooling_sequence
        set oldest [expr [set ${spname}(spooling_sequence)] - [set ${spname}(SpoolMax)]+1]
        # <= allows for dynamic, self-correcting change of SpoolMax
        SQL "delete from ei_spool_data where spname='$spname' and sequence<=$oldest"
        set ${spname}(SpoolCountActual) [expr [set ${spname}(SpoolMax)] - 1]
        }
    # usual append or overwrite
    incr ${spname}(SpoolCountActual)
    incr ${spname}(spooling_sequence)
    SQL "update ei_variable set varvalue='[set ${spname}(SpoolCountActual)]'\
 where spname='$spname' and varname='SpoolCountActual'"
    regsub -all ' $data '' data	;# probably not needed
    SQL "insert into ei_spool_data (spname,ts,sequence,sfr,data) values (\
 '$spname','[localtime 15]', [set ${spname}(spooling_sequence)],'$sfr', '$data')"
    return SPOOLED
    }


#
# received S6F23 to request or purge spool data
#
proc eq_spool_request {spname} {
    global $spname
    # expect U1:1 0 to transmit, 1 to purge
    # reply B 0 ok, 1 busy, 2 no spool data
    vset [set ${spname}(lastrmsg)] "tRSDC RSDC"
    if { $RSDC == "1" } {
        # purge
        set rc [eq_spool_purge $spname]
        $spname put S6F24 "B $rc"
        return
        }
    if { $RSDC == "0" } {
        # the standard rules
        #   - transmit up to MaxSpoolTransmit (0 means no limit)
        #   - only 1 open reply from host at a time
        #   - decrement SpoolCountActual as you go
        if { [set ${spname}(spooling_state)] == "INACTIVE" } {
            $spname put S6F24 "B 2"
            return
            }
        # compute a range of sequence numbers to transmit
        set oldest [expr [set ${spname}(spooling_sequence)] - [set ${spname}(SpoolCountActual)] + 1]
        set MaxSpoolTransmit [lindex [lindex [lindex [SQL "select varvalue\
 from ei_variable where spname='$spname' and varname='MaxSpoolTransmit'"] 6] 0] 0]
        if { $MaxSpoolTransmit == "" } { set MaxSpoolTransmit 0 }
        # set max to maximum sequence number to send or to 0 meaning no limit 
        if { $MaxSpoolTransmit > 0  } { set max [expr { $oldest + $MaxSpoolTransmit - 1}] }\
        else { set max 0 }
        if { [set ${spname}(SpoolCountActual)] == "0" } {
            eq_spool_emptied $spname 0
            }\
        else {
            after 1 [list eq_spool_xmit $spname $oldest $max]
            }
        $spname put S6F24 "B 0"
        return
        }
    }


# a separate proc to purge the spool so it can be called 
# from a UI
# returns 0 if data found to purge
#         2 no data
proc eq_spool_purge {spname {alert_is_ok 1}} {
    set reply [SQL "delete from ei_spool_data where spname='$spname'"]
    # suppress the operator alert if nothing was deleted
    if { [string first "//c 0" $reply] >= 0 } { set alert 1 ; set rc 0}\
    else { set alert 0 ; set rc 2}
    eq_spool_emptied $spname [expr $alert_is_ok && $alert]
    return $rc
    }

#
# transmit a range of sequenced messages from the spool,
# one at a time
# removing as we go
#
proc eq_spool_xmit {spname oldseq maxseq} {
    global $spname
    set reply [SQL "select sfr,data from ei_spool_data where spname='$spname'\
 and sequence=$oldseq"]
    vset [lindex [lindex $reply 6] 0] "sfr data"
    if { $sfr == "" } {
        # its not there so we must have been purged
        # or the host has overlapped xmit requests
        return
        }
    if { [string first R [string toupper $sfr]] < 0 } {
        # no reply
        $spname put $sfr $data [list eq_spool_xmit_put_cb $oldseq $maxseq]
        }\
    else {
        $spname put $sfr $data eq_spool_xmit_putr_cb -whenreply [list eq_spool_xmit_reply_cb $spname $oldseq $maxseq]
        }
    }

#
# no reply spool transmit completed
#
proc eq_spool_xmit_put_cb {oldseq maxseq spname sfr reason desc} {
    global $spname
    if { $reason == "send_complete" } {
        eq_spool_xmit_next $spname $oldseq $maxseq
        return
        }
    if { $reason == "send_failure" } {
        # Spool Transmit Failure event
        eq_gem_event $spname 4083
        return
        }
    }

# send with reply spool transmit callback
proc eq_spool_xmit_putr_cb {spname sfr reason desc} {
    global $spname
    if { $reason == "send_failure" } {
        # Spool Transmit Failure event
        eq_gem_event $spname 4083
        return
        }
    }


#
# the oldest spooled message has been unloaded
#
# remove from spool, decrement count, possibly start the next xmit
#
proc eq_spool_xmit_next {spname oldseq maxseq} {
    global $spname
    if { [string first "//c 0" [SQL "delete from ei_spool_data where spname='$spname'\
 and sequence=$oldseq"]] >= 0 } {
        incr ${spname}(SpoolCountActual) -1
        SQL "update ei_variable set varvalue='[set ${spname}(SpoolCountActual)]'\
 where spname='$spname' and varname='SpoolCountActual'"
        if { [set ${spname}(SpoolCountActual)] == "0" } {
            eq_spool_emptied $spname
            return
            }
        incr oldseq
        if { $oldseq <= $maxseq || $maxseq == 0 } {
            eq_spool_xmit $spname $oldseq $maxseq
            }
        }
    }
        
#
#
# See file "spool_xmit_reply_cb.tcl" for the reply receiving logic to 
# the spooled message send.  Having a separate file makes it possible
# to customize just this procedure.
#
    

#
# called when the spool is purged or emptied by transmission
#
proc eq_spool_emptied {spname {alert 1}} {
    global $spname
    SQL "update ei_variable set varvalue='0' where spname='$spname'\
 and varname='SpoolCountActual'"
    set ${spname}(SpoolCountActual) 0
    set ${spname}(spooling_state) "INACTIVE"
    set ${spname}(spooling_sequence) 0
    # compact/sync persistence file
    eq_spool_persistence_init $spname
    if { $alert } { catch { eq_operator_alert $spname SPOOLING_TERMINATED }}
    # start and stop time and total from last spooling still exist
    # Spooling Deactivated event
    eq_gem_event $spname 4081
    }

