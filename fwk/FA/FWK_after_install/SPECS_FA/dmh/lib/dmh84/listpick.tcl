# $Header: /usr/cvsroot/tcllib84/listpick.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
#
# $Log: listpick.tcl,v $
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
# Revision 1.1  1997/07/01 12:13:25  hume
# New generic dialogs created for GEM model application.
#
namespace eval ::dmh {

# generic pick an item from a list modal dialog

proc dmh_listpick {list prompt action {title "List Selection"} {w ""}} {
    if { $w == "" } {
        variable dmh_id
        if { ![info exists dmh_id] } { set dmh_id 0 }
        incr dmh_id
        set w .dmh_lp${dmh_id}
        }
    catch {destroy $w}
    toplevel $w
    wm title $w $title
    message $w.msg -text $prompt -anchor w -aspect 400
    pack $w.msg -side top -fill x
    frame $w.f
    pack $w.f -side top -expand 1 -fill both
    listbox $w.f.lb -yscroll "$w.f.sy set" -relief sunken -setgrid 1\
 -selectmode browse
    scrollbar $w.f.sy -relief sunken -command "$w.f.lb yview"
    pack $w.f.sy -side right -fill y
    pack $w.f.lb -side left -expand 1 -fill both
    eval [concat $w.f.lb insert 0 $list]
    frame $w.z
    pack $w.z -side top -fill x
    button $w.z.ok -text Ok \
 -command [list ::dmh::dmh_listpick_ok $w $action] -width 8
    button $w.z.can -text Dismiss -command "destroy $w" -width 8
    pack $w.z.ok $w.z.can -side left -padx 5m -pady 2m
    $w.f.lb selection set 0
    $w.f.lb activate 0
    catch {grab set $w}
    return $w
    }

proc dmh_listpick_ok {w action} {
    set lb $w.f.lb
    set index [$lb curselection]
    if { $index == "" } {
        tk_dialog $w.popup "List Selection" \
 "Indicate your choice by selecting it before pressing Ok." error 0 Dismiss
        return
        }
    lappend action [$lb get $index]
    after 1 "destroy $w ; $action"
    }

} ;# namespace    
