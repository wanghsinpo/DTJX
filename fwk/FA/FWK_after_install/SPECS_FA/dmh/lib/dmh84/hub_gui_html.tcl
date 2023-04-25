# $Header: /usr/cvsroot/tcllib84/hub_gui_html.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
#
# A user interface to specify HTML file output for the Datahub.
#
# called from the HUB or hubclient GUI 
# 
namespace eval ::dmh {
# $Log: hub_gui_html.tcl,v $
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.2  2001/11/11 19:30:55  hume
# Simplified SQL "eval pwd" to pwd since hubclient does replace pwd.
#
# Revision 1.1  2001/10/20 19:28:30  hume
# Added HTML and XML output of SQL table data and schema data.
#
#
proc hub_gui_html {tablelist {cache hub_html}} {
    variable $cache
    set w .$cache
    #catch {destroy $w} ;# development
    set ${cache}(tablelist) $tablelist
    if { [winfo exists $w] }  { wm deiconify $w ; raise $w ; catch {focus $w} ; return }
    set ${cache}(w) $w
    toplevel $w
    wm title $w "Hume Datahub HTML Save"
    wm iconname $w "HTML Save"

    frame $w.f
    pack $w.f -side top -fill x
    frame $w.f.fl
    frame $w.f.fr
    pack $w.f.fl $w.f.fr -side left -expand 1 -fill both
    
    label $w.ts -text "Table Selection" -anchor w
    pack  $w.ts -side top -fill x -padx 4m -pady 1m -in $w.f.fl
    set cttables [llength $tablelist]
    if { $cttables > 0 } { set ${cache}(all_tables) 0 }\
    else { set ${cache}(all_tables) 1 }
    radiobutton $w.tsel -text "Selected [llength $tablelist] Table(s)" \
 -variable ::dmh::${cache}(all_tables) -value 0 -anchor w
    radiobutton $w.tall -text "All Tables" \
 -variable ::dmh::${cache}(all_tables) -value 1 -anchor w
    pack $w.tsel $w.tall -side top -fill x -padx 6m -pady 1m -in $w.f.fl

    label $w.ct -text "Document Contents" -anchor w
    pack  $w.ct -side top -fill x -padx 4m -pady 2m -in $w.f.fr
    foreach rec {{{Table of Contents} contents 1} {{Table Schema} schema 0} {{Table Data} data 1}} {
        foreach {lbl f v} $rec {}
        set ${cache}($f) $v
        checkbutton $w.$f -text $lbl -anchor w -variable ::dmh::${cache}($f)
        pack $w.$f -side top -fill x -padx 6m -pady 1m -in $w.f.fr
        }

    label $w.fi -text "Document File Output" -anchor w
    pack $w.fi -side top -fill x -padx 4m -pady 2m 
    set ${cache}(one_doc) 1
    radiobutton $w.rb1 -text "One combined Document" \
 -variable ::dmh::${cache}(one_doc) -value 1 -anchor w
    pack $w.rb1 -side top -fill x -padx 6m -pady 1m
    frame $w.fp 
    pack $w.fp -side top -expand 1 -fill x -padx 10m
    label $w.fp.l -text "Non-default pathname:" -width 22 -anchor e
    entry $w.fp.e -width 40 -textvariable ::dmh::${cache}(pathname)
    button $w.fp.b -text "Browse..." -command [list ::dmh::hub_gui_html_pathbrowse $cache]
    pack $w.fp.l $w.fp.e $w.fp.b -side left
    radiobutton $w.rbN -text "Per table documents" \
 -variable ::dmh::${cache}(one_doc) -value 0 -anchor w
    pack $w.rbN -side top -fill x -padx 6m -pady 1m
    frame $w.fd 
    pack $w.fd -side top -expand 1 -fill x -padx 10m
    label $w.fd.l -text "Non-default directory:" -width 22 -anchor e
    entry $w.fd.e -width 40 -textvariable ::dmh::${cache}(dir) 
    button $w.fd.b -text "Browse..." -command [list ::dmh::hub_gui_html_dirbrowse $cache]
    pack $w.fd.l $w.fd.e $w.fd.b -side left

    frame $w.z
    pack $w.z -side top -fill x
    button $w.z.ok -text Ok -command [list ::dmh::hub_gui_html_ok $cache] -width 10
    button $w.z.esc -text Cancel -command [list destroy $w] -width 10
    pack $w.z.ok $w.z.esc -side left -padx 16m -pady 4m
    bind $w.z.ok <Destroy> "+ unset ::dmh::$cache"
    }

# Must work from HUB or hubclient
proc hub_gui_html_pathbrowse cache {
    variable $cache
    set pathname [set ${cache}(pathname)]
    if { $pathname == {}} {
        set pathname [file join [pwd] snapshot[localtime 5]_[localtime 3].html]
        }
    fileselect $pathname {*.html} "HTML Save File..." [list set ::dmh::${cache}(pathname)]
    }

proc hub_gui_html_dirbrowse cache {
    variable $cache
    set dir [set ${cache}(dir)]
    if { $dir == {}} {
        set dir [pwd]
        }
    set pathname [file join $dir use_this_directory.html]
    fileselect $pathname {*.html} "HTML Save Directory..." [list ::dmh::hub_gui_html_dirset ${cache}]
    }

proc hub_gui_html_dirset {cache pathname} {
    variable $cache
    set ${cache}(dir) [file dirname $pathname]
    }
    
proc hub_gui_html_ok {cache} {
    variable $cache
    foreach f {all_tables contents data dir one_doc pathname schema tablelist w} {
        set $f [set ${cache}($f)]
        }
    if { $all_tables } { set tablelist * }
    if { $one_doc } { set path_or_dir $pathname }\
    else { set path_or_dir $dir }
    set cmd [list ::dmh::hub_html_save $one_doc $data $schema $contents 1 $tablelist\
 $path_or_dir]
    set cmd [list eval mh_eval $cmd]
    set reply [SQL $cmd]
    if { [llength $reply] == 1 } { set reply [lindex $reply 0] }
    foreach {rc data} $reply {}
    if { $rc == 0 } {
        foreach {tables ct} $data {}
        tk_dialog $w.popup "HTML Save Ok"\
 "Data for $ct tables was written to [join $tables \n]" info 0 Dismiss
        destroy $w
        return
        }
    tk_dialog $w.popup "HTML Save Error"\
 "An error occurred: $data" error 0 Dismiss
    }

} ;# namespace
