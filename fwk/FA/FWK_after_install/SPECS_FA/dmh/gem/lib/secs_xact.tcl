# $Header: /usr/cvsroot/gem/lib/secs_xact.tcl,v 1.3 2001/11/15 17:03:50 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: secs_xact.tcl,v $
# Revision 1.3  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.2  1997/09/08 18:10:44  hume
# Added warning about using secs_xat in a receive callback.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#

# secs_xact - generic send a SECS message and wait for reply or TIMEOUT 
#
#  You can safely use this command in the logic of User Interface actions,
#  DMH messages received, or SECS messages that are received from other
#  ports.  You can safely use this command several times in sequence, to
#  carry out related transactions.  You need to avoid executng this 
#  command again while you are already executing it; and as the paragraph 
#  below warns, you cannot use this command to cause "nesting" of the 
#  secsport receiving logic.
#
# IMPORTANT: You cannot safely use this command in the whenmsg callback
#  for a received SECS message (primary or reply) on the same port
#  that you just received the message on.  The code design expects your
#  callback logic to complete its processing and return, before it
#  receives on the port again.  You can use the "after" command to
#  safely invoke secs_xact in the background after your callback logic
#  returns.
#
# During the wait for a reply or TIMEOUT, events are processed, and 
# the application responds to message system and window inputs, 
# as well as sending and receiving other SECS messages
#
proc secs_xact {spname sfr {tsn ""}} {
    global $spname
    if { [info exists ${spname}(result)] && [set ${spname}(result)] == "pending" } {
        # If you want a synchronous programming model, 
        # you need to prevent reentry by disabling UI buttons or
        # creating a "wrapper" procedure that serializes access.
        # DMH message input features reentry protection.
        error "$spname is already waiting on a modal SECS transaction"
        }
    # you need to be asking for a reply message
    if { [string first R [string toupper $sfr]] < 0 } { 
        #error "Programming error - no reply requested in $sfr"
        append sfr R 
        }
    $spname put $sfr $tsn secs_put_callback -whenreply \
 "secs_reply_callback $spname"
    # If you set the pending value before the put command, 
    # you have to trap errors with the put statement and 
    # clear the pending value.  Its easier to do it after.
    set ${spname}(result) pending
    # clear the last receive so the failure reason is easy to see
    set ${spname}(lastrSFR) ""
    # the callbacks execute during the vwait
    vwait ${spname}(result)
    # return the data of your reply or the literal TIMEOUT
    # you will get TIMEOUT in all cases of failure including F0 abort
    # if you need to know more call secs_xact_failure
    return [set ${spname}(result)]
    }

#
# this call will tell you why TIMEOUT was returned on
# your last secs_xact 
#
# BAD_SEND - connection is down 
# REJECTED - stream 9 unknown stream or function reply
# ABORTED  - response was F0 abort
# NO_REPLY - the primary was sent ok but no reply came back (T3 timeout)
#
proc secs_xact_failure spname {
    global $spname
    if { [set ${spname}(reason)] == "send_failure" } { return BAD_SEND }
    if { [set ${spname}(lastrSFR)] == "" } { return NO_REPLY }
    if { [string first S9 [set ${spname}(lastrSFR)]] == 0} {return REJECTED}
    if { [set ${spname}(reason)] == "receive_failure" } { return ABORTED }
    return SUCCEEDED
    }



# generic put callback
# sets result array item which will wakeup caller who is 
# using "vwait" to wait on result
#
proc secs_put_callback {spname sfr reason description} {
    global $spname
    set ${spname}(reason) $reason
    if { $reason == "send_complete" } return
    # here on failed send, abort reply, or T3 timeout on receive
    set ${spname}(result) TIMEOUT
    }

# generic reply callback
# sets result item to reply data except if its already been set.
#
# It may already be set to TIMEOUT because of an F0 abort reply.
#
# On an abort reply,
#   the send callback gets notified of receive_failure,
#   and the reply callback also gets called with the SxF0 reply message.
#
proc secs_reply_callback spname {
    global $spname
    if { [set ${spname}(result)] != "pending" } return
    set ${spname}(result) [set ${spname}(lastrmsg)]
    }
