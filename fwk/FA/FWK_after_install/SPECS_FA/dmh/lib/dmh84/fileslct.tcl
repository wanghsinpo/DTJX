# $Header: /usr/cvsroot/tcllib84/fileslct.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
# Licensed Material, Do not redistribute
# Copyright(C) 1995 Hume Integration Software
# $Log: fileslct.tcl,v $
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.4  2001/11/15 17:14:17  hume
# Updated company name.
#
# Revision 1.3  2000/06/20 19:59:14  hume
# Fixes for wm transient bugginess on Windows.
#
# Revision 1.2  2000/03/15 16:42:45  hume
# Added a modal lock during refresh.
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
# Revision 1.3  1999/05/26 13:35:52  hume
# Needed check for blank filename.
#
# Revision 1.2  1999/04/16 20:16:33  hume
# Directories not listed on other drives.
#
# Revision 1.1.1.1  1997/10/03 02:31:41  hume
# From tcllib42 with edits.
#
# Revision 1.3  1997/06/24 11:15:16  hume
# Default path was one level high - think file dirname behavior changed.
#
# Revision 1.2  1997/05/31 14:33:23  hume
# Revised use of tk_dialog - created as child of toplevel parent in case root
# window is iconified, it still shows up.  Deleted obsolete tk_MenuBar calls.
#
# Revision 1.1.1.1  1997/02/11 14:26:54  hume
# For Tk 4.2
#
# Revision 1.1.1.1  1996/07/10 02:01:15  hume
# Reorganized and modified for Tk4.0 dp3.3.
#
# Revision 1.1  1996/04/02  02:48:21  hume
# Renamed for strict ISO-9660 CD-ROM file systems.
#
# Revision 1.1  1996/01/31  12:45:58  hume
# Added file selection proc fileselect.
#

namespace eval ::dmh {
# This file selection dialog is portable between Unix, WinNT and Mac
# On systems that uses drives, the user can select a drive designation 
# from a set of radiobuttons.
# You can have multiple instances active if you set the modal argument to 0.
# The dialog is resizeable and it does not exec processes to do its work.
# Also, the processes current working directory is not changed.
# Finally, you can call it with a startpath, such as the file found last time,
# to show a specific directory.  The default starting place is the current
# working directory.

# To support the hubclient, this dialog is usable for remote file systems
# when "pwd" "glob" and "file" are changed to refer to the remote file system
# We cannot use tcl_platform in this usage.

package require Tk 8.4

proc fileselect {{startpath ""} {pattern *} {title Open} {on_ok puts}\
 {on_cancel "#"} {modal 1}} {
    variable _fs_ctr
    if { ![info exists _fs_ctr] } { set _fs_ctr 0 }
    incr _fs_ctr
    set var fsd_${_fs_ctr}
    variable $var
    set ${var}(pattern) $pattern
    # are drives used?
    set ${var}(drive) ""
    set pwd [set ${var}(pwd) [pwd]]
    if { [string match ?:/* $pwd ] } {
        set use_drives 1
        set ${var}(drive) [string range $pwd 0 1]
        }\
    else  { set use_drives 0 }
    if { $startpath == "" } {
        # on NT and Unix, want path to end in /
        if { [file isdirectory $pwd/] } {
            set startpath $pwd/
            } \
        else {
            set startpath $pwd
            }
        }
    if { [string match ?:/* $startpath] } {
        set ${var}(drive) [string range $startpath 0 1]
        set startpath [string range $startpath 2 end]
        }
    if { ![file isdirectory [set ${var}(drive)]$startpath] } {
        set ${var}(filename) [file tail $startpath]
        set ${var}(path) [file dirname $startpath]
        }\
    else { 
        set ${var}(filename) "" 
        set ${var}(path) [file dirname [file join $startpath x]]
        }
    set w .$var
    toplevel $w
    wm title $w $title
    wm minsize $w 10 10
    frame $w.ff
    frame $w.fd 
    pack $w.ff $w.fd -side left -expand yes -fill both -padx 3m -pady 3m
    frame $w.fb
    pack $w.fb -side right 
    label $w.ff.l0 -text "File Name:" -anchor w
    pack $w.ff.l0 -side top -anchor w
    entry $w.ff.e -textvariable ::dmh::${var}(filename) -relief sunken
    pack $w.ff.e -side top -fill x -pady 2m
    frame $w.ff.f
    pack $w.ff.f -side top -expand yes -fill both
    scrollbar $w.ff.f.vs -relief sunken -command "$w.ff.f.lb yview"
    scrollbar $w.ff.f.hs -relief sunken -command "$w.ff.f.lb xview"\
 -orient horizontal
    pack $w.ff.f.hs -side bottom -fill x
    pack $w.ff.f.vs -side right -fill y
    listbox $w.ff.f.lb -relief sunken -yscroll "$w.ff.f.vs set" -setgrid 1\
 -selectmode single -width 20 -xscroll "$w.ff.f.hs set"
    pack $w.ff.f.lb -side left -expand yes -fill both
    label  $w.ff.l1 -text "Pattern:"
    pack $w.ff.l1 -side top -anchor w
    entry $w.ff.e1 -textvariable ::dmh::${var}(pattern) -relief sunken
    pack $w.ff.e1 -side top -anchor w

    label $w.fd.l0 -text "Directories:" -anchor w
    pack $w.fd.l0 -side top -anchor w
    label $w.fd.l1 -anchor w -textvariable ::dmh::${var}(path)
    pack  $w.fd.l1 -side top -anchor w -fill x -pady 2m
    frame $w.fd.f
    pack $w.fd.f -side top -expand yes -fill both
    scrollbar $w.fd.f.vs -relief sunken -command "$w.fd.f.lb yview"
    scrollbar $w.fd.f.hs -relief sunken -command "$w.fd.f.lb xview"\
 -orient horizontal
    pack $w.fd.f.hs -side bottom -fill x
    pack $w.fd.f.vs -side right -fill y
    listbox $w.fd.f.lb -relief sunken -yscroll "$w.fd.f.vs set" -setgrid 1\
 -selectmode single -width 32 -xscroll "$w.fd.f.hs set"
    pack $w.fd.f.lb -side left -expand yes -fill both

    if { $use_drives } {
        if { [set ${var}(drive)] == "" } {
            set ${var}(drive) [string range $pwd 0 1]
            }
        label $w.fd.l2 -text Drive: -anchor w
        pack $w.fd.l2 -side top -anchor w
        foreach d {a c d e f g h i j k l m n o p q r s t u v w x y z} {
            if { $d == "a" || [file isdirectory $d:/] } {
                radiobutton $w.fd.b$d -text $d: -value $d: \
-command [list ::dmh::fileselect_drvpick $var $d:] -relief flat 
                pack $w.fd.b$d -side top -ipadx 2m -anchor w
                }
            }
        }\
    else { set ${var}(drive) "" }
    
    button $w.fb.ok -text Ok -command [list ::dmh::fileselect_ok $var $on_ok] -width 10
    button $w.fb.can -text Cancel -command [list ::dmh::fileselect_can $var $on_cancel] -width 10
    pack $w.fb.ok  $w.fb.can -side top -padx 2m -pady 5m
    
    bind $w.fb.ok <Destroy> "+ unset ::dmh::$var"
    bind $w.fd.f.lb <Double-Button-1> [list ::dmh::fileselect_dirpick $var $w.fd.f.lb]

    bind $w.ff.f.lb <1> "::tk::ListboxBeginSelect %W \[%W index @%x,%y\] ;
 if { \[%W selection includes \[%W index @%x,%y\]\] } { ::dmh::fileselect_filepick $var $w.ff.f.lb }"
    bind $w.ff.f.lb <space> "::tk::ListboxBeginSelect %W \[%W index @%x,%y\] ;
 if { \[%W selection includes \[%W index @%x,%y\]\] } { ::dmh::fileselect_filepick $var $w.ff.f.lb }"
    bind $w.ff.f.lb <Select> "::tk::ListboxBeginSelect %W \[%W index @%x,%y\] ;
 if { \[%W selection includes \[%W index @%x,%y\]\] } { ::dmh::fileselect_filepick $var $w.ff.f.lb }"
    
    if { $modal } {
        catch { grab $w ; focus $w }
        }
    fileselect_refresh $var
    }

proc fileselect_dirpick {var lb} {
    variable $var
    set index [lindex [$lb curselection] 0]
    set text [$lb get $index]
    set ${var}(path) $text
    fileselect_refresh $var
    }

proc fileselect_filepick {var lb} {
    variable $var
    set index [lindex [$lb curselection] 0]
    set text [$lb get $index]
    set ${var}(filename) $text
    }

proc fileselect_drvpick {var d} {
    variable $var
    set ${var}(drive) $d
    if { ![file isdirectory $d[set ${var}(path)]] } {
        set ${var}(path) "/"
        set ${var}(filename) ""
        }
    fileselect_refresh $var
    }

# verb := lock | update | release
#
proc fileselect_focus {verb win {msg ""} {title "Performing Refresh"}} {
    if { $verb == "lock" } {
        if { [winfo exists $win] } { return 1 }
        }
    if { $verb == "release" } { return [catch {destroy $win}] }
    if { [winfo exists $win] } {
        $win.m configure -text $msg
        set rc 1
        }\
   else {
        toplevel $win
        dmh_transient $win [winfo toplevel [winfo parent $win]]
        message $win.m -text $msg -aspect 800
        pack $win.m -padx 5m -pady 5m
        set rc 0
        }
    wm title $win $title
    wm withdraw $win ; wm deiconify $win ; update idletasks
    catch { grab $win ; focus $win }
    return $rc
    }


proc fileselect_refresh var {
    variable $var
    set w .$var
    fileselect_focus lock $w.lock "Refreshing File Selection display...."
    set drive [set ${var}(drive)]
    set path [set ${var}(path)]
    set dir [lsort [glob -nocomplain [file join ${drive}${path} *]]]
    # make sure dir list is not empty so we always have an ancestor dir path
    if { $dir == "" } { lappend dir [file join ${drive}${path} .]}
    set lbd $w.fd.f.lb
    set lbf $w.ff.f.lb
    $lbd delete 0 end
    $lbf delete 0 end

    # parse the ancestor dir path
    set plist ""
    set pitem [lindex $dir 0]
    set pitem [string range $pitem [string length $drive] end]
    while {1} {
        set pitem [file dirname $pitem]
        if { $pitem == "" } break
        if { [lsearch -exact $plist $pitem] >= 0} break
        lappend plist $pitem
        }
    foreach p $plist {
        $lbd insert 0 $p
        }

    foreach item $dir {
        # get rid of drive on all items
        set text [string range $item [string length $drive] end]
        # get rid of path for file items
        set tail [file tail $item]
        if { $tail == "." || $tail == "" } continue
        if { [file isdirectory $item] } {
            $lbd insert end $text
            }\
        else {
            if { [string match [set ${var}(pattern)] $tail] } {
                $lbf insert end $tail
                }
            }
        }
    fileselect_focus release $w.lock 
    }

proc fileselect_can {var on_cancel} {
    set w .$var
    uplevel #0 $on_cancel
    destroy $w
    }

proc fileselect_ok {var ok_action} {
    variable $var
    set w .$var
    foreach sub {drive path filename} {
        set $sub [set ${var}($sub) [string trim [set ${var}($sub)]]]
        }
    if { ![string compare $filename ""] } {
        tk_dialog $w.popup "File Specification Dialog"\
 "A File Name must be specified." error 0 Dismiss 
        return
        }
    if { $drive != "" } {
        if { ![file isdirectory $drive/] } {
            tk_dialog $w.popup "File Specification Dialog"\
 "Drive specification \"$drive\" is not valid" error 0 Dismiss 
            return
            }
        }
    if { ![file isdirectory ${drive}${path}] } {
        tk_dialog $w.popup "File Specification Dialog"\
 "Path specification \"${drive}${path}\" is not valid." error 0 Dismiss
        return
        }
    set abs [file join ${drive}${path} ${filename}]
    lappend ok_action $abs
    uplevel #0 $ok_action
    destroy $w
    }

} ;# namespace    
