# $Header: /usr/cvsroot/tcllib84/showtext.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1995 Hume Integration Software
# All Rights Reserved
#
# a simple dialog to display text
#
# $Log: showtext.tcl,v $
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.3  2001/11/15 17:14:17  hume
# Updated company name.
#
# Revision 1.2  2000/06/20 19:59:14  hume
# Fixes for wm transient bugginess on Windows.
#
# Revision 1.1.1.1  2000/03/01 21:20:55  hume
# pkgindex only change.
#
# Revision 1.2  2000/01/14 22:16:54  hume
# New arguments to specify parent and replace button text.
#
# Revision 1.1.1.1  1999/10/05 00:58:06  hume
# Initial Tcl eight.two version.
#
# Revision 1.1.1.1  1999/07/02 18:48:37  hume
# Starting point for Tcl 8.1.
#
# Revision 1.2  1999/04/07 19:39:08  hume
# dmh_show_text returns window name for caller use.
#
# Revision 1.1.1.1  1997/10/03 02:31:41  hume
# From tcllib42 with edits.
#
# Revision 1.1.1.1  1997/02/11 14:26:54  hume
# For Tk 4.2
#
# Revision 1.1.1.1  1996/07/10 02:01:15  hume
# Reorganized and modified for Tk4.0 dp3.3.
#
namespace eval ::dmh {
#
proc dmh_show_text {text title {height 24} {width 80} {font fixed}\
 {parent {}} {Dismiss Dismiss}} {
    variable dmh_ctr
    if { ![info exists dmh_ctr] } { set dmh_ctr 0 }
    set w $parent.dmh_st${dmh_ctr}
    incr dmh_ctr
    toplevel $w
    wm title $w $title
    frame $w.bot
    button $w.bot.ok -text $Dismiss -command "destroy $w"
    pack $w.bot -side bottom -fill x
    text $w.t -yscrollcommand "$w.y set" -font $font \
        -wrap word -width $width -height $height -setgrid 1
    scrollbar $w.y -relief flat -command "$w.t yview"
    pack $w.y -side right -fill y
    pack $w.t -expand 1 -fill both
    $w.t insert 0.0 $text
    pack $w.bot.ok -side left -ipadx 2m -padx 25m -pady 5m 
    if { $parent != {}} {
        dmh_transient $w [winfo toplevel [winfo parent $w]]
        }
    return $w
    }

} ;# namespace
