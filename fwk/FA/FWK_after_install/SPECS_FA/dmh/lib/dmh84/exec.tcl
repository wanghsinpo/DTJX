# $Header: /usr/cvsroot/tcllib84/exec.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
#
# $Log: exec.tcl,v $
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.1.1.1  2000/03/01 21:20:55  hume
# pkgindex only change.
#
# Revision 1.1.1.1  1999/10/05 00:58:06  hume
# Initial Tcl eight.two version.
#
# Revision 1.1.1.1  1999/07/02 18:48:37  hume
# Starting point for Tcl 8.1.
#
# Revision 1.1.1.1  1997/10/03 02:31:41  hume
# From tcllib42 with edits.
#
# Revision 1.1.1.1  1997/02/11 14:26:54  hume
# For Tk 4.2
#

# this file gets used on platforms such as the Mac where
# there is no exec command
proc exec {args} {
    global tcl_platform
    if { $args == "hostname" } { return [dp_hostname] }
    if { $args == "whoami" } { return mac_user }
    if { [lindex $args 0] == "uname" } { return $tcl_platform(os) }
    error "exec is not implemented"
    }
