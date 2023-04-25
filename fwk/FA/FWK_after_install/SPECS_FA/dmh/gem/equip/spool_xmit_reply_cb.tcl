# $Header: /usr/cvsroot/gem/equip/spool_xmit_reply_cb.tcl,v 1.2 2001/11/15 17:03:50 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1999 Hume Integration Software
# All Rights Reserved
#
# $Log: spool_xmit_reply_cb.tcl,v $
# Revision 1.2  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.1  1999/01/22 15:52:30  hume
# Spool tranmit reply logic is separate file to ease customization.
#

# A reply has been received from a message transmitted from the spool
#
#  This reply logic is replacing the usual whenmsg logic (if any) for the
#     message sent from the spool.
#  An OEM may need to explicitly test for messages that he has added and
#  allowed to be spooled, so he can add logic to the reply coming in.
#  Replies to event reports and alarms are usually ignored anyway.
#
proc eq_spool_xmit_reply_cb {spname oldseq maxseq}   {
    #global $spname
    #set sfr [set ${spname}(lastrSFR)]
    #set data [set ${spname}(lastrmsg)]
    # switch on $sfr to handle reply from spooled message send
    # ...
    # now resume spool unload
    eq_spool_xmit_next $spname $oldseq $maxseq
    }

