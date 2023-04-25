# $Header: /usr/cvsroot/gem/host/rcmd.tcl,v 1.4 2002/11/19 01:52:07 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: rcmd.tcl,v $
# Revision 1.4  2002/11/19 01:52:07  hume
# Added logic to the processing of rcmd arguments to be allow for
# not having surrounding braces with string values.
#
# Revision 1.3  2002/08/14 20:52:54  hume
# Substitution in ei_rcmd was processing backslash sequences and spoiling
# DOS filenames.  Default RCMD_PP-SELECT configuration variable entry
# improperly used quotes around data argument instead of braces, causing
# backslashes to be processed and spoiling DOS filenames.
#
# Revision 1.2  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#


# rcmd == remote command
# Verb is some command like "abort" that the
# equipment S2F41 or S2F21 understands as a command
# or that we understand and cause to happen
#
# Existing standards do not nail down any standard behavior
#  or command specifics.
#
# S2F41 optional arguments are {<CPNAME> <CPVAL>} pairs
#
# ei_rcmd gemhost pp-select {{A PPExecName} {A MyRecipe}}
# ei_rcmd gemhost start
# 
# we reply back with the integer CMDA code or ERROR
# 0 = ok
# 1 = no such command
# 2 = not now
# TIMEOUT = comm failure,  TIMEOUT, or abort
proc ei_rcmd {spname verb args} {
    global $spname
    set varID RCMD_[string toupper $verb]
    set reply [SQL "select varvalue from ei_variable where\
 spname='$spname' and varID='$varID'"]
    set template [lindex [lindex [lindex $reply 6] 0] 0]
    if { $template == "" } { set template "S2F41R {L:2 {A $verb} L}" }
    # here is a compromise, we take the {CPNAME CPVAL} argument
    # structure and substitute the $CPVAL
    # most equipment does not handle S2F41
    foreach arg $args {
        rset $arg {{tCPNAME CPNAME} {tCPVAL CPVAL}}
        # regsub causes an undesired substitution of backslashes so we use string
        set index [string first %s $template]
        if { $index < 0 } break

        # Strings values need to appear as a single argument to the type code, so if they
        # contain whitespace or characters like backslashes, the template should specify 
        # surrounding braces.  We will help out templates that do not provide
        # surrounding braces, since no braces are used for numeric arguments that can be
        # scalars or vectors. 
        set ch [string index [string toupper $tCPVAL] 0]
        if { ($ch == "A" || $ch == "V") && [string index $template [expr {$index-1}]] != "\{" } {
            set template \
 [string range $template 0 [expr {$index-1}]][list ${CPVAL}][string range $template [expr {$index+2}] end]
            }\
        else {
            set template \
 [string range $template 0 [expr {$index-1}]]${CPVAL}[string range $template [expr {$index+2}] end]
            }
        }
    # expect CMDA {I1 i} or {U1 i} return $i  
    # TIMEOUT result passes through unchanged
    set reply [eval [concat secs_xact $spname $template]]
    set llen [llength $reply]
    if { $llen == 2 } { 
       # treat this like S2F22 <CMDA>
       set reply [expr [lindex $reply 1]]
       }\
    elseif { $llen == 3 } {
       # treat this like S2F42 {L:2 <HCACK> {L:n...}}
       set reply [expr [lindex [lindex $reply 1] 1]]
       }
    return $reply
    }


    
