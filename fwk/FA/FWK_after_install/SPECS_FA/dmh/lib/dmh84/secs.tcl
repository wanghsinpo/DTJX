# $Header: /usr/cvsroot/tcllib84/secs.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
#
# SECS Tcl library code to support secsport and hsms commands
# 
# $Log: secs.tcl,v $
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.2  2000/12/13 21:05:13  hume
# Added cvs tags and revised comments in secs.tcl, updated SnFm descriptions.
#

namespace eval ::dmh {

# 
# Install the built-in SECS message handlers 
# This procedure is called by the secsport and hsms creation code.
#
proc secsport_whenmsg_init sp {
   # current time request
   $sp whenmsg S2F17 "secs_S2F18 $sp"
   # binary echo request
   $sp whenmsg S2F25 "$sp put S2F26 \[set ${sp}(lastrmsg)\] ; $sp whenmsg again"
   }

# send the current time as ASCII YYMMDDHHMMSS
# this is pre Y2K code - look at the GEM software
# for a better example
proc secs_S2F18 sp {
   $sp whenmsg again ;# re-arm for next time
   set _ts [string range [localtime 9] 2 end]  
   set _ts [join [split $_ts "- :"] ""]
   $sp put S2F18 "A $_ts"
   }

#
# Here is an example of how to send a stream 9 reply
#
proc secsport_S9_reply {sp fn} {
    $sp put S9F$fn "B [$sp lastheader]"
    }

} ;# namespace
