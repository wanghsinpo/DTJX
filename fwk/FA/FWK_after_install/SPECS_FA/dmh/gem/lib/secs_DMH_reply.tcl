# $Header: /usr/cvsroot/gem/lib/secs_DMH_reply.tcl,v 1.2 2002/11/19 17:50:59 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 2002 Hume Integration Software
# All Rights Reserved
#
# $Log: secs_DMH_reply.tcl,v $
# Revision 1.2  2002/11/19 17:50:59  hume
# Updated for Tcl 8.4 compatibility.
#
# Revision 1.1  2002/06/12 15:28:59  hume
# A call for DMH clients to receive a SECS reply as an asynchronous DMH reply.
#
#

# secs_DMH_reply - generic send a SECS message and then relay the SECS reply message
#   as a DMH message system reply.  This procedure is a convenient way for
#   external processes to control SECS conversations using DMH messages.
#   This procedure can be useful for either the host or equipment roles.
#
#   Assumptions:
#      - the SECS stream and function is a primary message, sent with a reply requested.
#      - the caller is specifying a DMH reply mailbox as one of the arguments, or
#        as the replybox when sending the message.
#      - the caller will only receive a single DMH reply message from the SECS reply
#        or from the failure to obtain a reply. 
# 
#        The DMH reply message will be one of:
#           $spname(lastrmsg) - the successful TSN message
#           "TIMEOUT BAD_SEND"
#           "TIMEOUT NO_REPLY"
#           "TIMEOUT REJECTED"
#           "TIMEOUT ABORTED"
#
#      - The caller should be mindful of the technique used to initiate the procedure 
#        execution, since a reply message from the procedure initiation is possibly 
#        obtained.  Don't let a reply from the invocation be confused with a reply from
#        the SECS reply.
#
#   Example, from POSIX C code:
#
#     /* not asking for procedure invocation reply */
#     reply = dmh_send(dmh, "gemhost_RPC", "secs_DMH_reply gemhost S1F1R {} MYREPLY", NULL);
#     if ( reply ) {
#         /* error - cannot send invocation */
#         }
#     else {
#         /* wait for SECS message reply or TIMEOUT */
#         reply = dmh_timedReceive(dmh, "MYREPLY", 0);
#         if ( strncmp(reply, "TIMEOUT", 7) == 0 ) {
#             /* error handling */
#             }
#         else {
#             /* success */
#             }
#         } 
#         
#   
# This procedure uses asynchronous mechanisms, that are safe for re-entrant
# execution. 
#
#
proc secs_DMH_reply {spname sfr {tsn {}} {replybox @defaulted@}} {
    global $spname 
 
    # the default DMH reply mailbox is $mbxreply
    if { $replybox == "@defaulted@" } {
        set replybox [set [dmh_var mbxreply]]  ;# causes an error if DMH has not been used
        }
    # if you are using this call, you should be setup for a DMH reply
    set mh_group_var [dmh_var mh_group]
    if { ![info exists $mh_group_var] || [set $mh_group_var] == {} } {
        error "DMH is not in use - reply cannot be sent"
        }
    if { $replybox == {} || $replybox == "NULL" } {
        error "No DMH reply mailbox specified"
        }
        
    # you should be asking for a SECS reply message
    if { [string first R [string toupper $sfr]] < 0 } { 
        #error "Programming error - no reply requested in $sfr"
        append sfr R 
        }

    $spname put $sfr $tsn [list secs_DMH_reply_cb $replybox] -whenreply \
 "mbx put $replybox \[set ${spname}(lastrmsg)\]"


    # clear the last receive so the failure reason is easy to see
    set ${spname}(lastrSFR) ""
 
    # you could DoXact( ) to see the successful initiation
    # and receive the SECS reply in a separate replybox, or as the 
    # second DMH reply message.
    return [list secs_DMH_reply initiated for $spname $sfr $replybox]
    }


# SECS callback to forward failure messages
#
proc secs_DMH_reply_cb {replybox spname sfr reason description} {
    global $spname
    if { $reason == "send_complete" } return  ;# successful progress
    # here on failed send, abort reply, or T3 timeout on receive
    if { $reason == "send_failure" } { 
        mbx put $replybox "TIMEOUT BAD_SEND"
        return
        }
    if { $reason == "receive_failure" } { 
        if { [set ${spname}(lastrSFR)] == "" } { 
            mbx put $replybox "TIMEOUT NO_REPLY"
            }\
        elseif { [string first S9 [set ${spname}(lastrSFR)]] == 0} {
            mbx put $replybox "TIMEOUT REJECTED"
            }\
        else { ;# F0 abort
            # an abort is seen by the -whenreply code
            # so setup message data for the -whenreply send
            #mbx put $replybox "TIMEOUT ABORTED"
            set ${spname}(lastrmsg) "TIMEOUT ABORTED"
            }
        return
        }
    # there are no other $reason values....
    error "unknown reason $reason"
    }

