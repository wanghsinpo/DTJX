# $Header: /usr/cvsroot/gem/host/vfei_mach_cmd.tcl,v 1.3 2002/11/01 15:57:14 hume Exp $
#
# $Log: vfei_mach_cmd.tcl,v $
# Revision 1.3  2002/11/01 15:57:14  hume
# Changed lset usage to vset usage, using dmh_import, and dmh_var for Tcl 8.4
# compatibility.
#
# Revision 1.2  1999/06/11 15:16:16  hume
# Added VFEI Machine Command HELLO.
#
# Revision 1.1  1997/08/08 21:00:10  hume
# Made mods to promote ease of customization using custom directory.
#

# process the VFEI MACH_CMD

proc ei_vfei_MACH_CMD {spname va} {
    global $va
    if { ![info exists ${va}(CMD_TYPE)] } {
        return [ei_vfei_cmd_ack $va VFEI_MISSING_PARAM]
        }
    # get configured transaction
    set VFEIname VFEI_MCMD_[set ${va}(CMD_TYPE)]
    set reply [SQL "select varvalue from ei_variable where\
 spname='$spname' and VFEIname='$VFEIname'"]
    set template [lindex [lindex [lindex $reply 6] 0] 0]
    if { $template == "" } { 
        return [ei_vfei_cmd_ack $va VFEI_CMD_NOT_SUPPORTED]
        }
    set reply [eval [concat secs_xact $spname $template]]
    if { $reply == "TIMEOUT" } { return [ei_vfei_cmd_ack $va $reply] }
    # any real reply means success
    return [ei_vfei_cmd_ack $va {} 0]
    }

proc ei_vfei_MACH_CMDS spname {
    set reply [SQL "select VFEIname,description from ei_variable where \
 spname='$spname' and varclass='VFEI_MCMD'"]
    set result {}
    foreach row [lindex $reply 6] {
        vset $row "name desc"
        lappend result [list [substr $name VFEI_MCMD_ {}] $desc]
        }
    return $result
    }
