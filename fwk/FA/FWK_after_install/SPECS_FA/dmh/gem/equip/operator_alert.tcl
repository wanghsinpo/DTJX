# $Header: /usr/cvsroot/gem/equip/operator_alert.tcl,v 1.4 2002/11/21 15:36:00 hume Exp $
#
# called in contexts when the standard says the operator should
# be alerted
#
# DO NOT code a modal interaction such as using tk_dialog
#

# possible MSGIDs (use grep to verify)
#
#   SPOOLING_NOT_PERSISTENT $errtext
#   SPOOLING_ACTIVATED
#   SPOOLING_FULL
#   SPOOLING_TERMINATED
#
# $Log: operator_alert.tcl,v $
# Revision 1.4  2002/11/21 15:36:00  hume
# Revised the spooling initialization to guard against corrupted spool file
# data.  If bad data, a timestamped copy is made and the operator is alerted.
#
# Revision 1.3  2000/11/16 19:59:18  hume
# Added cvs tags.
#
#
proc eq_operator_alert {spname MSGID args} {
    set text "[localtime 9]: The ALERT of $MSGID has occurred."
    if { $args != "" } { append text "  ($args)\n" }
    append text \n\nExplanation:\n"
  switch -exact $MSGID {
        SPOOL_DATA_DISCARDED {
    append text "The spooled messages that were previously saved for later\n"
    append text "retrieval by the host are improperly numbered, and will not\n"
    append text "be used.  This is not expected to occur, and should be\n"
    append text "brought to the attention of the equipment vendor.\n"
    append text "A timestamped copy of the corrupt file has been made.\n"
            }
        SPOOLING_NOT_PERSISTENT {
    append text "The spooling system could not create a directory or file\n"
    append text "to save spooled data that is supposed to be persistent.\n" }
        SPOOLING_ACTIVATED {
    append text "The connection to the host is down and messages are now being\n"
    append text "saved into the spooling area for later retrieval by the host.\n" }
        SPOOLING_FULL {
    append text "The maximum number of spooled messages have been saved.\n"
    append text "Older data is being overwritten or newer data is being discarded.\n" }
        SPOOLING_TERMINATED {
    append text "Good News - spooling of messages is no longer occuring.\n" }
        default {
    append text "The software developers neglected to create a proper explanation.\n"
            }
        }
    
    # see $dmh_library/showtext.tcl
    dmh_show_text $text "Operator Alert" 
    }
