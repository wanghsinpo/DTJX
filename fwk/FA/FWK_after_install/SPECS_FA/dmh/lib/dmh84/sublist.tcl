# $Header: /usr/cvsroot/tcllib84/sublist.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
#
# $Log: sublist.tcl,v $
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
# Revision 1.2  1997/10/24 00:54:42  hume
# Fixed problem with action always preserving arguments.
#
# Revision 1.1.1.1  1997/10/03 02:31:41  hume
# From tcllib42 with edits.
#
# Revision 1.1  1997/07/01 12:13:25  hume
# New generic dialogs created for GEM model application.
#

namespace eval ::dmh {

# generic choose a subset list dialog
#
proc dmh_sublist {prompt all_list sublist action \
 {items Items} {title "List Subset Choice"} {w ""}} {
    if { $w == "" } {
        variable dmh_id
        if { ![info exists dmh_id] } { set dmh_id 0 }
        incr dmh_id
        set w .dmh_sl${dmh_id}
        }
    catch {destroy $w}
    toplevel $w
    wm title $w $title
    message $w.msg -text $prompt -anchor w -aspect 1200
    pack $w.msg -side top -fill x
    frame $w.f
    pack $w.f -side top -expand 1 -fill both
    frame $w.f.l
    frame $w.f.c
    frame $w.f.r
    pack $w.f.l -side left -expand 1 -fill both
    pack $w.f.c -side left -fill y
    pack $w.f.r -side right -expand 1 -fill both
    label $w.f.l.l -text "Possible $items" -anchor w
    pack $w.f.l.l -side top -fill x
    scrollbar $w.f.l.sy -relief sunken -command "$w.f.l.lb yview"
    pack $w.f.l.sy -side right -fill y
    listbox $w.f.l.lb -yscroll "$w.f.l.sy set" -relief sunken \
 -selectmode extended
    pack $w.f.l.lb -side left -expand 1 -fill both

    label $w.f.c.s -text " " 
    pack $w.f.c.s -side top -fill x -pady 10m
    button $w.f.c.c -text ">> Choose >>" -command [list ::dmh::dmh_sublist_b c $w] -width 12
    button $w.f.c.r -text "<< Remove <<" -command [list ::dmh::dmh_sublist_b r $w] -width 12
    pack $w.f.c.c $w.f.c.r -side top -padx 1m -pady 4m

    label $w.f.r.l -text "Chosen $items" -anchor w
    pack $w.f.r.l -side top -fill x
    scrollbar $w.f.r.sy -relief sunken -command "$w.f.r.lb yview"
    pack $w.f.r.sy -side right -fill y
    listbox $w.f.r.lb -yscroll "$w.f.r.sy set" -relief sunken \
 -selectmode extended
    pack $w.f.r.lb -side left -expand 1 -fill both

    frame $w.z
    pack $w.z -side top -fill x
    button $w.z.ok -text Ok \
 -command [list ::dmh::dmh_sublist_ok $w $action] -width 8
    button $w.z.can -text Dismiss -command "destroy $w" -width 8
    pack $w.z.ok $w.z.can -side left -padx 30m -pady 4m

    set all ""
    foreach item $all_list {
        if { [lsearch -exact $sublist $item] < 0 } {
            lappend all $item
            }
        }
    eval [concat $w.f.r.lb insert 0 $sublist]
    eval [concat $w.f.l.lb insert 0 $all]    
    catch {grab set $w}
    return $w
    }

proc dmh_sublist_b {token w} {
    set lb_all $w.f.l.lb
    set lb_sub $w.f.r.lb
    if { $token == "c" } { ;# choose
        set piks [lsort -integer -decreasing [$lb_all curselection]]
        }\
    else {
        set piks [lsort -integer -decreasing [$lb_sub curselection]]
        }
    if { $piks == "" } {
         tk_dialog $w.popup "Sublist Usage" "Select items from the\
 appropriate list before indicating your action." error 0 Dismiss
         return
         }
    if { $token == "c" } { ;# choose
       foreach pik $piks {
           set item [$lb_all get $pik]
           $lb_sub insert end $item
           $lb_all delete $pik
           }
       }\
    else {
       foreach pik $piks {
           set item [$lb_sub get $pik]
           $lb_all insert end $item
           $lb_sub delete $pik
           }
        }
    }

proc dmh_sublist_ok {w action} {
    set lb_sub $w.f.r.lb
    set max [$lb_sub size]
    set sublist ""
    for {set i 0} {$i < $max} {incr i} {
        lappend sublist [$lb_sub get $i]
        }
    lappend action $sublist
    after 1 "destroy $w"
    after 1 [list namespace eval ::dmh $action]
    }

} ;# namespace
