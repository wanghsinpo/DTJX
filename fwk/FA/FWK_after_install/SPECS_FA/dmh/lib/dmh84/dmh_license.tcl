# $Header: /usr/cvsroot/tcllib84/dmh_license.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
#
#
namespace eval ::dmh {

# DMH License installation 
proc dmh_license {} {
    wm title . "DMH License Installation"
    frame .f 
    pack .f -side top -expand 1 -fill both
    message .f.m -aspect 600 -text "You must have one or more runtime licenses\
 installed to use the DMH programs."
    pack .f.m -side top 
    #set checked(license) 1
    #checkbutton .f.cb -text "Install Runtime License(s)."\
    #  -variable checked(license) -relief flat -anchor w
    #pack .f.cb -side top -anchor w -pady 5m
    
    label .f.l -text "Licenses to be installed" -anchor w
    pack .f.l -side top -expand 1 -fill x -padx 4m
    frame .f.fl 
    frame .f.fr
    pack .f.fl -side left -expand yes -fill both -padx 4m
    pack .f.fr -side left -expand 0 -fill y 
    listbox .f.fl.l -relief sunken -yscroll ".f.fl.y set"\
 -xscroll ".f.fl.x set" -selectmode single -width 32
    .f.fl.l insert 0 "Temporary [dp_hostname]"
    scrollbar .f.fl.y -relief sunken -command ".f.fl.l yview"
    scrollbar .f.fl.x -relief sunken -command ".f.fl.l xview"\
 -orient horizontal
    pack .f.fl.x -side bottom -fill x
    pack .f.fl.y -side right -fill y
    pack .f.fl.l -side left -expand 1 -fill both

    button .f.fr.b1 -text "New..."  -command [list ::dmh::rtl new .f.fl.l]
    button .f.fr.b2 -text "Edit..." -command [list ::dmh::rtl ed .f.fl.l]
    button .f.fr.b3 -text "Remove"  -command [list ::dmh::rtl rm .f.fl.l]
    pack .f.fr.b1 .f.fr.b2 .f.fr.b3 -side top \
 -ipadx 1m -ipady 2m -pady 2m -expand 1 -fill x

    frame .bot
    pack .bot -side bottom -expand yes -fill x
    button .bot.ok -text Install -command ::dmh::dmh_license_ok
    button .bot.cancel -text Exit -command "destroy ."
    pack .bot.ok .bot.cancel -side left -padx 10m -ipadx 4m -pady 5m -ipady 1m
    }

 proc dmh_license_ok {} {
    variable dmh_library 
    variable dmh_tmp_license
    set lb .f.fl.l
    set imax [$lb size]
    if { $imax == 0 } {
        tk_dialog .p "License Installation" \
 "You need to specify one or more Runtime Licenses using the New button."\
  error 0 Dismiss
       .bot.ok configure -state normal -cursor ""
       return
       }
    for { set i 0 } { $i < $imax } { incr i } {
        lappend license_records [$lb get $i]
        }

    set licpath [file join $dmh_library licenses.txt]

    # this could happen on a server mounted file
    if { [file readable $licpath] && ![file writable $licpath] } {
        tk_dialog .p "License File" "You lack permission\
 to modify $licpath.  Contact your system administrator." error 0 Dismiss
        .bot.ok configure -state normal -cursor ""
        return
        }
          
    if { [file readable $licpath] } {
        if [catch {open $licpath r} fid] {
            tk_dialog .p "File Open" "File $licpath\
 could not be opened.  It may be in use by another application,\
 or maybe you lack permissions to change it." error 0 Dismiss
            .bot.ok configure -state normal -cursor ""
            return
            }
        set text [read $fid]
        close $fid
        }\
    else { set text "" }
    foreach rec $license_records {
        vset $rec "type host codes"
        if { $type == "Permanent" } {
            append text "set dmh_license($host) $codes ;# permanent\n"
            }\
        elseif { $type == "Temporary" } {
            if { ![info exists dmh_tmp_license] } {
                tk_dialog .p "Temporary License" "The temporary license\
 has already been installed.  You cannot install\
 a temporary license except when prompted by a new installation."\
 error 0 Dismiss
                .bot.ok configure -state normal -cursor ""
                return
                }
            set codes $dmh_tmp_license
            set text "set dmh_license($host) $codes ;# temporary\n$text"
            }
        }
    if { [catch {open $licpath w} fid] } {
        tk_dialog .p "File Open" "File $licpath\
 could not be opened.  It may be in use by another application,\
 or maybe you lack permissions to change it." error 0 Dismiss
            .bot.ok configure -state normal -cursor ""
            return
            }
    puts -nonewline $fid $text
    close $fid
    .bot.ok configure -state normal -cursor ""
    tk_dialog .pop "DMH License Installation" "The DMH installation completed successfully." info 0 Ok
    catch {unset dmh_tmp_license}
    }


# runtime license listbox actions
 proc rtl {action lb} {
    switch -exact $action {
      new {
          rtl_editor $lb 
          }
      ed  {
          set index [$lb curselection]
          if { $index != "" } { 
              set txt [$lb get $index]
              rtl_editor $lb $txt $index
              }\
          else {  
              tk_dialog .p "Remove License" "Choose a license from the\
 list that you want to edit before pressing this button." info 0 Dismiss
              }
          
          }
      rm  {
          set index [$lb curselection]
          if { $index != "" } { $lb delete $index }\
          else {  
              tk_dialog .p "Remove License" "Choose a license from the\
 list that you want to remove before pressing this button." info 0 Dismiss
              }
          }
      }
   return
   }

# runtime license editor
 proc rtl_editor {lb {license ""} {index -1}} {
    set w .rtl
    catch { destroy $w }
    toplevel $w
    if { $license == "" } {
        wm title $w "New Runtime License"
        }\
    else { wm title $w "Edit Runtime License" }
    message $w.m -text {If you have purchased the product, obtain\
 your permanent license codes via e-mail to license@hume.com - see\
 the file "LICENSE.TXT".  You can install a temporary license\
 now, until you have your permanent codes.

 Temporary licenses expire in 30 days.  Warning - proprietary commands\
 are disabled in a running application when the license expires.

 } -aspect 400
    pack $w.m -side top -padx 2m
    frame $w.h
    pack $w.h -side top -expand 1 -fill x -padx 2m -pady 2m
    label $w.h.l -text "Hostname:" -anchor e
    pack $w.h.l -side left -padx 2m
    entry $w.h.e -relief sunken -textvariable ::dmh::rtl_host
    pack $w.h.e -side left 
    radiobutton $w.bt -text "Temporary License Installation" -variable ::dmh::rtl_type\
 -value Temporary -relief flat
    radiobutton $w.bp -text "Permanent License Installation" -variable ::dmh::rtl_type\
 -value Permanent -relief flat
    pack $w.bt $w.bp -side top -pady 2m -anchor w -padx 4m
    frame $w.fc
    pack $w.fc -side top -expand 1 -fill x -padx 2m -pady 2m
    label $w.fc.l -text "Permanent license codes:" -anchor e -width 25
    pack $w.fc.l -side left 
    entry $w.fc.e -relief sunken -textvariable ::dmh::rtl_codes
    pack $w.fc.e -side left
    frame $w.bot
    pack $w.bot -side bottom -expand yes -fill x
    button $w.bot.ok -text Ok -command [list ::dmh::rtl_edit_ok $lb $license $index]
    button $w.bot.cancel -text Cancel -command "destroy $w"
    pack $w.bot.ok $w.bot.cancel -side left -padx 10m -ipadx 4m -pady 5m -ipady 1m

    # Permanent <host> <codes>
    # Temporary <host>
    variable rtl_host 
    variable rtl_codes 
    variable rtl_type
    if { $license != "" } {
        vset $license "rtl_type rtl_host rtl_codes"
        }\
    else {
        set rtl_type Temporary
        set rtl_host [dp_hostname]
        set rtl_codes ""
        }
    grab .rtl
    }

 proc rtl_edit_ok {lb oldlicense oldindex} {
    variable rtl_host 
    variable rtl_codes 
    variable rtl_type
    set rtl_host [string trim $rtl_host]
    if { $rtl_host == "" || [llength $rtl_host] != 1} {
        tk_dialog .p "License Host" "You need to specify\
 the hostname of the computer that will run the programs.\
  Enter exactly what you obtain by executing \"hostname\"\
 at the command line." error 0 Dismiss
        return
        }
    set rtl_codes [string trim $rtl_codes]
    if { $rtl_type == "Temporary" } { set rtl_codes "" }\
    else {
        set len [string length $rtl_codes]
        set fullmatch " "
        regexp {[0-9]+} $rtl_codes fullmatch
        if { $len != 11 || [string compare $fullmatch $rtl_codes] } {
            tk_dialog .p "Permanent Codes" "The Permanent\
 license codes that you have entered are not formatted properly.\
 The entry should be 11 numeric characters." error 0 Dismiss
            return
            }
        }
    set license "$rtl_type $rtl_host $rtl_codes"
    if { $oldindex < 0 } {
        # create
        $lb insert end $license
        }\
    else {
        $lb delete $oldindex $oldindex
        $lb insert $oldindex $license
       }
    destroy .rtl
    }

} ;# namespace
