# $Header: /usr/cvsroot/gem/host/vfei_resource.tcl,v 1.6 2002/07/23 14:08:07 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: vfei_resource.tcl,v $
# Revision 1.6  2002/07/23 14:08:07  hume
# Made small changes to accomodate recipe names with embedded spaces.
#
# Revision 1.5  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.4  1999/05/28 13:22:39  hume
# Bug fix for RES_ACTIVATE, RECIPE_TRANSFER reply was missing TYPE.
#
# Revision 1.3  1998/01/02 22:37:20  hume
# Bugfix in RESOURCE_QUERY.
#
# Revision 1.2  1998/01/02 17:51:40  hume
# Fixed bug in VFEI recipe upload.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#

# VFEI resource commands (recipes)


# Activate/Select a recipe
#
# TYPE == RECIPE | other
# RES_ID+
#
proc ei_vfei_RES_ACTIVATE {spname va} {
    global $va $spname
    foreach parm {TYPE RES_ID} {
        if { ![info exists ${va}($parm)] } { return [ei_vfei_cmd_ack $va VFEI_MISSING_PARAM] }
        set $parm [set ${va}($parm)]
        }
    if { $TYPE != "RECIPE" } {
        return [ei_vfei_cmd_ack $va VFEI_CMD_NOT_SUPPORTED]
        }
    # We do not distinguish between a recipe name with imbedded white space
    # and a VFEI array of recipe names.  In both cases we pass RESID as a single string.
    # PP-SELECT is a gem requirement
    set cmdargs [list {A PPExecName} [list A $RES_ID]]
    set reply [ei_rcmd $spname PP-SELECT $cmdargs]
    # HCACK value reply
    if { $reply == "0" || $reply == "TIMEOUT" } { return [ei_vfei_cmd_ack $va $reply] }
    return [ei_vfei_cmd_ack $va EQUIP_REQUEST_DENIED]
    }

#
# there are no standard notions of deallocating recipes or wafer maps, etc
# this command is ahead of its time
#
proc ei_vfei_RES_DEACTIVATE {spname va} {
    global $va
    foreach parm {TYPE RES_ID} {
        if { ![info exists ${va}($parm)] } { return [ei_vfei_cmd_ack $va VFEI_MISSING_PARAM] }
        set $parm [set ${va}($parm)]
        }
    # dummy operation
    return [ei_vfei_cmd_ack $va {}]
    }

#
#  there are no standard notions of deleting anything but recipes
#
proc ei_vfei_RES_DELETE {spname va} {
    global $va
    foreach parm {TYPE RES_ID} {
        if { ![info exists ${va}($parm)] } { return [ei_vfei_cmd_ack $va VFEI_MISSING_PARAM] }
        set $parm [set ${va}($parm)]
        }
    if { $TYPE != "RECIPE" } {
        return [ei_vfei_cmd_ack $va VFEI_CMD_NOT_SUPPORTED]
        }
    set reply [ei_recipe_delete $spname $RES_ID]
    # ACKC7 value
    if { $reply == "0" || $reply == "TIMEOUT" } { return [ei_vfei_cmd_ack $va $result] }
    if { $reply == "4" } { return [ei_vfei_cmd_ack $va EQUIP_RESOURCE_NOT_FND] } 
    return [ei_vfei_cmd_ack $va EQUIP_REQUEST_DENIED] ;# denied
    }


#
# reply message is a RES_LIST
#
proc ei_vfei_RES_QUERY {spname va} {
    global $va
    foreach parm {TYPE} {
        if { ![info exists ${va}($parm)] } { return [ei_vfei_cmd_ack $va VFEI_MISSING_PARAM] }
        set $parm [set ${va}($parm)]
        }
    foreach parm {FILE} {
        # not supported
        if { [info exists ${va}($parm)] } { return [ei_vfei_cmd_ack $va VFEI_CMD_NOT_SUPPORTED] }
        }
    if { $TYPE != "RECIPE" } {
        return [ei_vfei_cmd_ack $va VFEI_CMD_NOT_SUPPORTED]
        }
    set dirlist [ei_recipe_dir $spname]
    if { $dirlist == "TIMEOUT" } { return [ei_vfei_cmd_ack $va $dirlist] }
    if { [info exists ${va}(RES_ID)] } {
        # identify the ids in the list that exist on the equipment
        set outlist ""
        foreach id [set ${va}(RES_ID)] {
            if { [lsearch -exact $dirlist $id] >= 0 } {
                lappend outlist $id
                }
            }
        }\
    else { set outlist $dirlist }
    set msg [ei_vfei_cmd_ack $va 0]
    regsub CMD_ACK $msg RES_LIST msg
    append msg " TYPE/A=\"RECIPE\""
    set len [llength $outlist]
    append msg [format " RES_ID/A\[%d\]=\[\"[join $outlist {" "}]\"\]" $len]
    return $msg
    }

# the reply is a RES_TRANSFER
proc ei_vfei_RES_REQUEST {spname va} {
    global $va
    foreach parm {TYPE RES_ID} {
        if { ![info exists ${va}($parm)] } { 
            set txt [ei_vfei_cmd_ack $va VFEI_MISSING_PARAM] 
            regsub CMD_ACK $txt RES_TRANSFER txt
            return $txt
            }
        set $parm [set ${va}($parm)]
        }
    if { $TYPE != "RECIPE" } {
        # not supported
        set txt  [ei_vfei_cmd_ack $va VFEI_CMD_NOT_SUPPORTED]
        regsub CMD_ACK $txt RES_TRANSFER txt
        return $txt
        }
    if {[info exists ${va}(RES_FILE)] } {
        set RES_FILE [set ${va}(RES_FILE)]
        if { [catch {open $RES_FILE w} fid] } {
             set txt [ei_vfei_cmd_ack $va VFEI_FILE_IO_ERROR]
             regsub CMD_ACK $txt RES_TRANSFER txt
             return $txt
             }
        }
    # get the L:2 <ppid> <ppbody>
    set reply [ei_recipe_get $spname $RES_ID]
    if {$reply == "TIMEOUT" || $reply == ""} {
        set txt [ei_vfei_cmd_ack $va $reply]
        regsub CMD_ACK $txt RES_TRANSFER txt
        return $txt
        }
   set PPBODY [lindex $reply 2]
   set txt [ei_vfei_cmd_ack $va 0]
   regsub CMD_ACK $txt RES_TRANSFER txt
   append txt " TYPE/A=\"RECIPE\" RES_ID/A=\"$RES_ID\""
    if {[info exists ${va}(RES_FILE)] } {
       # writing the whole <PPBODY> {type value} pair
       puts -nonewline $fid $PPBODY
       close $fid
       append txt " RES_FILE/A=\"$RES_FILE\""
       return $txt
       }
    # we cheat and slip the SECS PPBODY type into the PPBODY
    # so we can always use it as a string
    regsub -all \" $PPBODY \\\" PPBODY
    set len [string length $PPBODY]
    append txt " RES_LENGTH/U4=$len"
    append txt " RES_BODY/A=\"$PPBODY\""
    return $txt
    }

#
#  this message is sending us a recipe to transfer to the equipment
#
proc ei_vfei_RES_TRANSFER {spname va} {
    global $va
    foreach parm {TYPE RES_ID} {
        if { ![info exists ${va}($parm)] } { return [ei_vfei_cmd_ack $va VFEI_MISSING_PARAM] }
        set $parm [set ${va}($parm)]
        }
    if { $TYPE != "RECIPE" } {
        # not supported
        return [ei_vfei_cmd_ack $va VFEI_CMD_NOT_SUPPORTED]
        }
    if { [info exists ${va}(RES_FILE)] } {
        set RES_FILE [set ${va}(RES_FILE)]
        if { [catch { open $RES_FILE r} fid] } {
            return [ei_vfei_cmd_ack $va VFEI_FILE_IO_ERROR]
            }
        set PPBODY [read $fid]
        close $fid
        }\
    elseif { [info exists ${va}(RES_BODY)] } {
        set PPBODY [set ${va}(RES_BODY)] 
        # we assume that the body is PPBODY - {type data}
        }\
    elseif {  [info exists ${va}(SOURCE)] } {
        # not supported
        return [ei_vfei_cmd_ack $va VFEI_CMD_NOT_SUPPORTED]
        }\
    else { return [ei_vfei_cmd_ack $va VFEI_MISSING_PARAM] } ;# missing parm
    set reply [ei_recipe_put $spname $RES_ID $PPBODY]
    if { $reply == "0" || $reply == "TIMEOUT" } { return [ei_vfei_cmd_ack $va $reply] }
    return [ei_vfei_cmd_ack $va EQUIP_REQUEST_DENIED]
    }

