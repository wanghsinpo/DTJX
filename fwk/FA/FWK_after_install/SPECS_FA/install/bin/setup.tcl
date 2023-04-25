# 
# DMH installation script for NT and Unix
#
# Assumptions:
#   Running from "this" directory
#   Runnable dmh_wish on CD, at ./usr/local/bin
#   Runnable unzip on CD, at ./usr/local/bin
#   Extract files from .zip archives 
#       faster
#       long names and alphabetic case are preserved
#       do not have subdirectory limitations 
#   

proc mktopwin {} {
 
    global checked env tcl_platform isNT base client dest_path code_path doc_path SGI
    global rtl_host rtl_codes rtl_type rtl_file
    set def_dir [file join SPECS_FA dmh]
    if { $tcl_platform(os) == "Windows NT" } { 
	set isNT 1 
	set dest_path [file join $env(SystemDrive)/ "Program Files" $def_dir]
    } else {
	set isNT 0 
	set dest_path [file join /opt $def_dir]
     }

     set code_path $dest_path

     set base [pwd]
     
     set doc_path [file join $dest_path gem html]
     
     set checked(sgi) 0
     set checked(doc) 0
     set checked(license) 0
     set checked(pgroup) 0
     set rtl_host [dmh::dp_hostname]
     set rtl_type Temporary
     set rtl_file $rtl_host
     set lb .f.fr.fl.l
     if { $isNT } {
         set checked(setenv) 1
     }  else {
	 set checked(setenv) 0
     }
     
     wm title . "SPECS-FA 3.0 License Setup"
     wm resizable . 0 0

     message .m -text {
 You can install a temporary license\
 now, until you have your permanent codes.
     } -aspect 600 -relief groove -padx 5m -pady 4m

     message .g -text {Temporary licenses expire in 30 days.  Warning - proprietary commands\
 are disabled in a running application when the license expires.
     } -aspect 750 -relief groove -padx 5m -pady 4m
     pack .m .g -side top -padx 2m -pady 2m

     frame .h
     pack .h -side top -expand 1 -fill x -padx 2m -pady 2m
     label .h.l  -text "Hostname:" -anchor e -fg White
     pack  .h.l  -side left -padx 2m
     entry .h.e  -relief sunken -textvariable rtl_host
     pack  .h.e  -side left 


     frame .y
     pack .y -side top -expand 1 -fill x -padx 2m -pady 2m
     label .y.bl -text "Install License:" -anchor w -fg White
     pack .y.bl -side left -padx 2m -pady 2m

     radiobutton .y.bt -text "Temporary License" -variable rtl_type\
 -value Temporary -relief flat -command change_state
     radiobutton .y.br -text "Permanent Hardware-Key License" -variable rtl_type\
 -value Permanent2 -relief flat -command change_state
#     radiobutton .y.bp -text "Permanent Software-Key License" -variable rtl_type\
# -value Permanent1 -relief flat -command change_state
#     pack .y.bt .y.br .y.bp -side top -pady 2m -anchor w -padx 4m
     pack .y.bt .y.br -side top -pady 2m -anchor w -padx 4m
#     pack .y.bt -side top -pady 2m -anchor w -padx 4m

     frame .y.fc
     pack .y.fc -side top -expand 1 -fill x -padx 2m -pady 2m
     label .y.fc.l -text "Permanent License codes:" -anchor e -width 25
     pack .y.fc.l -side left 
     entry .y.fc.e -background gray76 -relief sunken -textvariable rtl_codes -width 24 -state disabled
     pack .y.fc.e -side left


     set license [list $rtl_type $rtl_file]
     if { $license != "" } {
         dmh::vset $license "rtl_type rtl_host rtl_codes"
         }\
     else {
         set rtl_type Temporary
         set rtl_host [dmh::dp_hostname]
         set rtl_codes ""
     }
     frame .f
     pack .f -side top -expand 1 -fill both
     frame .f.fl
     pack .f.fl -side top -expand yes -fill both
     frame .f.fr
     pack .f.fr -side top -expand yes -fill both -padx 4m
     
     set packlist ""
     
#     if { [info command dmh_encode] == "dmh_encode" } {
	 message .f.fr.m -relief groove -aspect 1000 -padx 5m -pady 4m -text "You must install runtime licenses\
		 to use SPECS-FA."
	 pack .f.fr.m -side top 
	 set checked(license) 1
	 message .f.fr.cb -aspect 1000 -anchor w -text "Install Runtime License(s).:"
	 pack .f.fr.cb -side top -anchor w -pady 1m -fill x
	 
	 label .f.fr.l -text "Licenses to be installed" -anchor w
	 pack .f.fr.l -side top -expand 1 -fill x -padx 4m
	 frame .f.fr.fl 
	 frame .f.fr.fr
	 pack .f.fr.fl -side left -expand yes -padx 2m -fill x
	 pack .f.fr.fr -side left -expand yes 
	 listbox .f.fr.fl.l -relief sunken -yscroll ".f.fr.fl.y set"\
		 -xscroll ".f.fr.fl.x set" -selectmode single
	 if { [info exists env(DMH_LIBRARY_INSTALLED)] && [file readable [file join $env(DMH_LIBRARY_INSTALLED) licenses.txt]] } {
	     .f.fr.fl.l insert 0 [list Migrate [file join $env(DMH_LIBRARY_INSTALLED) licenses.txt]]
	 } elseif {[info exists env(DMH_LIBRARY)] && [file readable [file join $env(DMH_LIBRARY) licenses.txt]] } {
	     .f.fr.fl.l insert 0 [list Migrate [file join $env(DMH_LIBRARY) licenses.txt]]
	 } elseif { [file readable /usr/local/lib/dmh84/licenses.txt] } {
	     .f.fr.fl.l insert 0 "Migrate /usr/local/lib/dmh84/licenses.txt"
	 } elseif { [file readable /usr/local/lib/dmh83/licenses.txt] } {
	     .f.fr.fl.l insert 0 "Migrate /usr/local/lib/dmh83/licenses.txt"
	 } elseif { [file readable /usr/local/lib/dmh82/licenses.txt] } {
	     .f.fr.fl.l insert 0 "Migrate /usr/local/lib/dmh82/licenses.txt"
	 } elseif { [file readable /usr/local/lib/dmh81/licenses.txt] } {
	     .f.fr.fl.l insert 0 "Migrate /usr/local/lib/dmh81/licenses.txt"
	 } elseif { [file readable /usr/local/lib/dmh80/licenses.txt] } {
	     .f.fr.fl.l insert 0 "Migrate /usr/local/lib/dmh80/licenses.txt"
	 } elseif { [file readable /usr/local/lib/dmh42/licenses.txt] } {
	     .f.fr.fl.l insert 0 "Migrate /usr/local/lib/dmh42/licenses.txt"
	 } elseif { [file readable /usr/local/bin/.dmh_license] } {
	     .f.fr.fl.l insert 0 "Migrate /usr/local/bin/.dmh_license"
	 } else {
             if { [info command dmh_encode] == "dmh_encode" } {
	         .f.fr.fl.l insert 0 "Temporary [dmh::dp_hostname]"
	     }
	 }
	 scrollbar .f.fr.fl.y -takefocus 0 -relief sunken -command ".f.fr.fl.l yview"
	 scrollbar .f.fr.fl.x -takefocus 0 -relief sunken -command ".f.fr.fl.l xview"\
		 -orient horizontal
	 pack .f.fr.fl.x -side bottom -fill x
	 pack .f.fr.fl.y -side right -fill y
	 pack .f.fr.fl.l -side left -expand 1 -fill both
	 
         set index [$lb curselection]
         button .f.fr.fr.b1 -text "Add..." -command [list rtl_edit_ok $lb $license $index]
	# button .f.fr.fr.b1 -text "New..."  -command "rtl new .f.fr.fl.l"
	 button .f.fr.fr.b2 -text "Edit.." -command "rtl ed .f.fr.fl.l"
	 button .f.fr.fr.b3 -text "Remove"  -command "rtl rm .f.fr.fl.l"
         pack .f.fr.fr.b1 .f.fr.fr.b3 -side top \
                 -ipadx 1m -ipady 2m -pady 2m -expand 1

	 pack .f.fr.fr.b3 -expand 1 -fill x
#     } else {
#	 set checked(license) 0
#     }
     
     frame .bot
     pack .bot -side bottom -expand yes -fill x
     button .bot.ok -text Install -command install_ok 
     button .bot.cancel -text " Exit  " -command "destroy ."
     pack .bot.ok .bot.cancel -side left -padx 30m -ipadx 4m -pady 5m -ipady 1m
     focus .bot.ok
     
     wm_center .
 }
 
proc wm_center w {
    wm withdraw $w
    update idletasks
    set x [expr [winfo screenwidth $w]/2 - [winfo reqwidth $w]/2  ]
    set y [expr [winfo screenheight $w]/2 - [winfo reqheight $w]/2 ]
    wm geom $w +$x+$y
    wm deiconify $w
}
 
proc set_path {type} {
    upvar ${type}_path type_path
    set types {{{Directory Choice} {*} }}
    set pathname [tk_getSaveFile -parent . -filetypes $types -initialfile use_this_directory\
	    -title "Choose Installation Directory" -initialdir "$type_path"]
    if { [llength $pathname] == 0 } return
    set path [file dirname $pathname]
    set type_path $path
}

proc set_rtl_file {} {
    global rtl_file
    set types {{{License File} {licenses.txt} } {{All Files} *}}
    set pathname [tk_getOpenFile -parent .rtl -filetypes $types -initialfile licenses.txt\
	    -title "Choose License File for Migration" -initialdir [file dirname $rtl_file]]
    if { [llength $pathname] == 0 } return
    set rtl_file $pathname
}

# For NT, fix auto_load paths that reference ./usr/local... and do not
# work when we cd
# the "shell" fails to expand TCL_LIBRARY=./usr/local/bin etc
# and there is no decent way to construct a proper environment
proc fix_auto_path {} {
    global auto_path auto_index 
    set p ""
    set pwd [pwd]
    foreach path $auto_path {
        if { [string first ./ $path] == 0 } {
            set path $pwd[string range $path 1 end]
	}
        lappend p $path
    }
    set auto_path $p
    foreach sub [array names auto_index] {
        set value [set auto_index($sub)]
        if { [string first "source ./" $value] == 0 } {
            set value "source $pwd[string range $value 8 end]"
	}
        set auto_index($sub) $value
    }
}


proc change_state {} {
   global rtl_type rtl_codes

   if { $rtl_type == "Temporary" } {
     .y.fc.e configure -state disabled
     .f.fr.fr.b1 configure -state normal
     .f.fr.fr.b3 configure -state normal
     .h.e configure -state normal
   } elseif { $rtl_type == "Permanent1" } {
     .y.fc.e configure -state normal
     .f.fr.fr.b1 configure -state normal
     .f.fr.fr.b3 configure -state normal
     .h.e configure -state normal
   } elseif { $rtl_type == "Permanent2" } {
     .y.fc.e configure -state normal
     .f.fr.fr.b1 configure -state disabled
     .f.fr.fr.b3 configure -state disabled
     .h.e configure -state disabled
   }
   set rtl_codes ""

}

proc show_license {file {h 24} {w 80}} {
    if { [file readable $file] } {
        wm withdraw .
        set fid [open $file r]
        set text [read $fid]
        close $fid
        set w [dmh_show_txt $text "Software License Terms" $h $w]
        wm_center $w
	
        tkwait window $w
        wm deiconify .
        catch { raise . ; focus . }
    }
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
              tk_dialog .p "Edit License" "Choose a license from the\
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
proc can_w {} {
    destroy .rtl
    wm deiconify .
}

proc rtl_edit_ok {lb oldlicense oldindex} {
    global rtl_host rtl_codes rtl_type isNT rtl_file
    if { $rtl_type == "Migrate" } {
        if { ![file readable $rtl_file] } {
            if { $isNT } { set eg "c:/usr/local/lib/dmh80/licenses.txt"}\
            else { set eg "/usr/local/lib/dmh80/licenses.txt"}
            tk_dialog .p "Migrate File" "The pathname\
 \"$rtl_file\" cannot be read.  Specify the full\
 pathname of your existing dmh_license file such as \"$eg\""\
 error 0 Dismiss
            return
            }
        set license [list $rtl_type $rtl_file]
        }\
  else {
    set rtl_host [string trim $rtl_host]
    if { $rtl_host == "" || [llength $rtl_host] != 1} {
        tk_dialog .p "License Host" "You need to specify\
 the hostname of the computer that will run the programs.\
  Enter exactly what you obtain by executing \"hostname\"\
 at the command line." error 0 Dismiss
        return
        }
    set rtl_codes [string trim $rtl_codes]
    if { $rtl_type == "Temporary" } { 
       set rtl_codes "" 
    } elseif { $rtl_type == "Permanent1" } { 
        set len [string length $rtl_codes]
        set fullmatch " "
        regexp {[0-9]+} $rtl_codes fullmatch
        if { $len != 11 || [string compare $fullmatch $rtl_codes] } {
            tk_dialog .p "Permanent Softkey Codes" "The Permanent\
 license codes that you have entered are not formatted properly.\
 The entry should be 11 numeric characters." error 0 Dismiss
            return
            }
        }
        set license "$rtl_type $rtl_host $rtl_codes"
    }
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


proc show_status {msg} {
    global isNT
    set w .sstatus
    set title "Installation Status"
    if { [winfo exists $w] } {
        $w.m configure -text $msg
        update
        dmh::wait 1000
        return
        }
    toplevel $w
    wm title $w $title
    message $w.m -text $msg -aspect 800
    pack $w.m -padx 6m -pady 6m
    update
    dmh::wait 1000
    }


proc install_ok {} {
    global checked dest_path code_path doc_path isNT env client base tcl_platform exec_input_path SGI
    global rtl_codes rtl_type
    .bot.ok configure -state disabled -cursor watch
    update idletasks

    if { $rtl_type == "Permanent2" } {
        set len [string length $rtl_codes]
        set fullmatch " "
        regexp {[0-9,a-z,A-Z,\-]+} $rtl_codes fullmatch
        if { $len != 24 || [string compare $fullmatch $rtl_codes] } {
            tk_dialog .p "Permanent Hardware-key License Installation" "The Permanent\
 license codes that you have entered are not formatted properly.\
 The entry should be 24 alphanumeric & '-' characters.\nxxxx-xxxx-xxxx-xxxx-xxxx" error 0 Dismiss
            set rtl_codes ""
            .bot.ok configure -state normal -cursor ""
            return
        }
	show_status "Installing Hardkey License..."
	exec /opt/SPECS_FA/install/bin/setcode $rtl_codes 
        .bot.ok configure -state normal -cursor ""
        catch { destroy .sstatus }
        tk_dialog .pop "Permanent Hardware-Key License Installation" "The installation completed successfully." info 0 Ok
        if { [winfo exists .si] } { raise .si ; focus .si }
    } else {
    
    if {!($checked(sgi)) && !($checked(doc)) && !($checked(license))} {
	set dialogMessage "You have not checked any option.  Nothing to install."
	tk_dialog .p "Installation Check" $dialogMessage error 0 Dismiss
	.bot.ok configure -state normal -cursor ""
	return
    }
    
    # Save the SGI and documentation paths that the user entered.
    set orig_dest_path $dest_path
    set orig_code_path $code_path
    set orig_doc_path $doc_path
    
    # Trim trailing spaces and slashes from the paths and "tcl-ize" any NT format.
    set dest_path [string trim $dest_path]
    regsub -all \\\\ $dest_path / dest_path
    set dest_path [string trimright $dest_path /]
    set code_path [string trim $code_path]
    regsub -all \\\\ $code_path / code_path
    set code_path [string trimright $code_path /]
    set doc_path [string trim $doc_path]
    regsub -all \\\\ $doc_path / doc_path
    set doc_path [string trimright $doc_path /]
    
    if {$checked(sgi)} { 
	if {[string length $dest_path] == 0} {
	    set dialogMessage "You must specify a directory for the SECS/GEM Installation."
	    tk_dialog .p "Installation Check" $dialogMessage error 0 Dismiss
	    .bot.ok configure -state normal -cursor ""
	    return
	}
    }
    
    if {$checked(license)} { 
	if {[string length $dest_path] == 0} {
	    set dialogMessage "You must specify a directory for the license Installation."
	    tk_dialog .p "Installation Check" $dialogMessage error 0 Dismiss
	    .bot.ok configure -state normal -cursor ""
	    return
	}
    }
    
    if {$checked(sgi)} { 
	if {[string length $code_path] == 0} {
	    set dialogMessage "You must specify a directory for the C Code Installation."
	    tk_dialog .p "Installation Check" $dialogMessage error 0 Dismiss
	    .bot.ok configure -state normal -cursor ""
	    return
	}
    }
    
    if { $checked(doc) && ([string length $doc_path] == 0) } {
	set dialogMessage "You must specify a directory for the Documentation Installation."
        tk_dialog .p "Installation Check" $dialogMessage error 0 Dismiss
        .bot.ok configure -state normal -cursor ""
        return
    }
    
    if { $isNT } {
	# we want a drive to install SGI for NT
	# the drive has to make sense to install program group items
	# inside Tcl you use Unix path specs
	if {$checked(sgi)} {
	    if { [string first : $dest_path] != 1 || ![file isdirectory [string index $dest_path 0]:/]} {
		set dialogMessage    "For NT, the SECS/GEM Installation Path must begin with a"
		append dialogMessage " valid drive designation such as c:/"
		tk_dialog .p "Installation Check" $dialogMessage warning 0 Dismiss
		.bot.ok configure -state normal -cursor ""
		return
	    }
	}
	
	if {$checked(doc)} {
	    if { [string first : $doc_path] != 1 || ![file isdirectory [string index $doc_path 0]:/]} {
		set dialogMessage    "For NT, the Documentation Path must begin with a"
		append dialogMessage " valid drive designation such as c:/"
		tk_dialog .p "Installation Check" $dialogMessage warning 0 Dismiss
		.bot.ok configure -state normal -cursor ""
		return
	    }
	}

	# Build NT format of directories
	set nt_dest ""
	regsub -all / $dest_path \\ nt_dest
	set nt_dest "$nt_dest\\"
	
	set nt_code ""
	regsub -all / $code_path \\ nt_code
	set nt_code "$nt_code\\"
	
	set nt_doc ""
	regsub -all / $doc_path \\ nt_doc
	set nt_doc "nt_doc\\"
    } else {
        # we want an absolute path to install SGI for Unix
        if { [string first {./} $dest_path] == 0 } {
            set dest_path "[pwd]/[string range $dest_path 2 end]"
	} elseif { [string first / $dest_path] != 0 } {
	    set dialogMessage "The Installation Path must start with / or  ./"
	    tk_dialog .p "Installation Check" $dialogMessage warning 0 Dismiss
	    .bot.ok configure -state normal -cursor ""
	    return
	}
    }
    
    if { $isNT } {
        # trim right of / creates problem with c:/ 
        # [file isdirectory c:] is not valid
        if { [string length $dest_path] == 2 } { 
	    set dest_path $dest_path/
	}
        if { ( [string length $code_path] == 2 ) && \
		( [string index $code_path 1] == ":" ) } {
	    set code_path $code_path/
	}
        if { ( [string length $doc_path] == 2 ) && \
		( [string index $doc_path 1] == ":" ) } {
	    set doc_path $doc_path/
	}
    } else { 
        # trim right of / creates problem with root "/"
        if { $dest_path == "" && [string index $orig_dest_path 0] == "/" } {
            set dest_path "/"
	}
        if { $code_path == "" && [string index $orig_code_path 0] == "/" } {
            set code_path "/"
	}
        if { $doc_path == "" && [string index $orig_doc_path 0] == "/" } {
            set doc_path "/"
	}
    }

    set ev [set slp [set winst ""]]

    if { $checked(sgi) &&  ( \
	    ( !$isNT && ( $dest_path != "/usr/local" ) ) ||
            ( $isNT && !$checked(setenv) && ([string first :/usr/local $dest_path] != 1)) \
		    )} {
        if $isNT { 
            set P "set PATH=\"${dest_path}\\bin\";%PATH%"
	} else { 
            set P "PATH=\"${dest_path}/bin\":\$PATH"
	}
        switch $tcl_platform(os) {
	    "AIX"       {set ev LIBPATH }
	    SunOS       {set ev LD_LIBRARY_PATH}
	    Linux       {set ev LD_RUN_PATH }
	    HP-UX       {set ev SHLIB_PATH }
	    default     {  }
	}

        if { $ev != "" } {
	    set slp "$ev=\"${dest_path}/lib\""
	    set txt    "#\n"
	    append txt "# Copy to .profile, .xsession, .bashrc, etc\n"
	    append txt "# example setup for Tcl/Tk/DMH 8.4 installed in ${dest_path}\n"
	    append txt "#\n"
	    append txt "DMH_BIN=\"${dest_path}/bin\";export DMH_BIN\n"
	    append txt "PATH=\"\$DMH_BIN\":\$PATH;export PATH\n"
	    append txt "#\n"
	    append txt "# You must add lib directory to shared library search path\n"
	    append txt "# if Tcl/Tk shared libs are not copied to a system directory\n"
	    append txt "# or /usr/local/lib\n"
	    append txt "$ev=\"${dest_path}/lib\":\$$ev;export $ev\n"
	    set winst [dmh_show_txt $txt "Cut and Paste Profile Data" 20 80]
	    catch { puts "#Cut and Paste Profile Data\n$txt" }
	    dmh::wait 2000
	}

	if { [winfo exists $winst] } { 
	    set pop $winst.p 
	} else { 
	    set pop .p
	}

	set dialogMessage    "Your destination path is not the usual value (/usr/local)."
	append dialogMessage "  Each user should have the following environment variables set:"
	append dialogMessage "\n    DMH_BIN=\"${dest_path}/bin\""
	append dialogMessage "\n    $P"
	append dialogMessage "\n    $slp" 
	set pick [tk_dialog $pop "Non-Standard Installation Warning" $dialogMessage info 1 Ok "Go Back"]
	if { $pick == 1 } {
	    .bot.ok configure -state normal -cursor ""
	    catch { destroy $winst }
	    return
	}
    }

    if { $checked(license) } {
	set lb .f.fr.fl.l
	set imax [$lb size]
	if { $imax == 0 } {
	    set dialogMessage    "You must use the New button to specify one or more Runtime Licenses"
	    append dialogMessage " or choose not to install licenses."
	    tk_dialog .p "License Installation" $dialogMessage error 0 Dismiss
	    .bot.ok configure -state normal -cursor ""
	    return
	}
	
	for { set i 0 } { $i < $imax } { incr i } {
	    lappend license_records [$lb get $i]
	}
	
	set licfile licenses.txt
	set p [file join $dest_path lib dmh84 $licfile]
	
	if { [file readable $p] && ![file writable $p] } {
	    set dialogMessage "You lack permission to modify $p."
	    append dialogMessage "  You may have to login as root and try again." 
	    tk_dialog .p "License File" $dialogMessage error 0 Dismiss
	    .bot.ok configure -state normal -cursor ""
	    return
	}
	
    }
    
    # DIRECTORIES
    if {$checked(sgi)} {
	show_status "Creating directories..."

	mkdirpath $dest_path
	if { ![file isdirectory $dest_path] } {
	    if { $isNT } { set p $nt_dest } else { set p $dest_path }
	    set dialogMessage    "The directory $p does not exist and could not be created."
	    append dialogMessage "  Maybe you specified a read-only drive, or lack security permissions."
	    tk_dialog .p "Installation Check" $dialogMessage error 0 Dismiss
	    .bot.ok configure -state normal -cursor ""
	    catch { destroy .sstatus }
	    return
	}
	
	set sgi_bin_dir [file join $dest_path bin] 
	mkdirpath $sgi_bin_dir
	if { ![file isdirectory $sgi_bin_dir] } {
	    if { $isNT } { set p ${nt_dest}bin } else { set p $sgi_bin_dir}
	    set dialogMessage    "The directory $p does not exist and could not be created."
	    append dialogMessage "  Maybe you lack security permissions."
	    tk_dialog .popup "Installation Check" $dialogMessage error 0 Dismiss
	    .bot.ok configure -state normal -cursor ""
	    catch { destroy .sstatus }
	    return
	}

	set sgi_lib_dir [file join $dest_path lib] 
	mkdirpath $sgi_lib_dir
	if { ![file isdirectory $sgi_lib_dir] } {
	    if { $isNT } { set p ${nt_dest}lib } else { set p $sgi_lib_dir}
	    set dialogMessage    "The directory $p does not exist and could not be created."
	    append dialogMessage "  Maybe you lack security permissions."
	    tk_dialog .popup "Installation Check" $dialogMessage error 0 Dismiss
	    .bot.ok configure -state normal -cursor ""
	    catch { destroy .sstatus }
	    return
	}
	
	set sgi_gem_dir [file join $dest_path gem] 
	mkdirpath $sgi_gem_dir
	if { ![file isdirectory $sgi_gem_dir] } {
	    if { $isNT } { set p ${nt_dest}gem } else { set p $sgi_gem_dir}
	    set dialogMessage    "The directory $p does not exist and could not be created."
	    append dialogMessage "  Maybe you lack security permissions."
	    tk_dialog .popup "Installation Check" $dialogMessage error 0 Dismiss
	    .bot.ok configure -state normal -cursor ""
	    catch { destroy .sstatus }
	    return
	}
    
	
	set sgi_startup_dir [file join $sgi_gem_dir startup] 
	mkdirpath $sgi_startup_dir
	if { ![file isdirectory $sgi_startup_dir] } {
	    if { $isNT } { set p ${sgi_gem_dir}\\/tartup } else { set p $sgi_startup_dir}
	    set dialogMessage    "The directory $p does not exist and could not be created."
	    append dialogMessage "  Maybe you lack security permissions."
	    tk_dialog .popup "Installation Check" $dialogMessage error 0 Dismiss
	    .bot.ok configure -state normal -cursor ""
	    catch { destroy .sstatus }
	    return
	}

	mkdirpath $code_path
	if { ![file isdirectory $code_path] } {
	    if { $isNT } { set p ${nt_code}} else { set p $code_path}
	    set dialogMessage "The directory $p does not exist and could not be created."
	    tk_dialog .p "Installation Check" $dialogMessage error 0 Dismiss
	    .bot.ok configure -state normal -cursor ""
	    catch { destroy .sstatus }
	    return
	}
    }
    
    if { $checked(doc) } {
	mkdirpath $doc_path
	if { ![file isdirectory $doc_path]} {
	    if { $isNT } { set p ${nt_doc}lib\\dmh84 } else { set p $doc_path}
	    set dialogMessage    "The directory $p does not exist and could not be created."
	    append dialogMessage "  Maybe you lack security permissions."
	    tk_dialog .popup "Installation Check" $dialogMessage error 0 Dismiss
	    .bot.ok configure -state normal -cursor ""
	    catch { destroy .sstatus }
	    return
	}
    }
    
    if { $checked(license) } {
	set license_path [file join $dest_path lib dmh84]
	mkdirpath $license_path
	if { ![file isdirectory $license_path]} {
	    if { $isNT } { set p ${nt_dest}lib\\dmh84 } else { set p $license_path}
	    set dialogMessage    "The directory $p does not exist and could not be created."
	    append dialogMessage "  Maybe you lack security permissions."
	    tk_dialog .popup "Installation Check" $dialogMessage error 0 Dismiss
	    .bot.ok configure -state normal -cursor ""
	    catch { destroy .sstatus }
	    return
	}
    }

    if { $checked(sgi) } {
	show_status "Installing DMH files..."
	cd $dest_path
	
	unzip ${base}/bin.zip 
	unzip ${base}/lib.zip
	
	# take over generic names if prior version not there
	# we are in "usr/local" equivalent
	
	if { $isNT } {
	    if { ![file exists bin/dmh_wish.exe] } {
		show_status "Copying dmh84.exe to dmh_wish"
		file copy -force bin/dmh84.exe bin/dmh_wish.exe
		show_status "Copying datahub84 to datahub"
		file copy -force bin/datahub84.bat bin/datahub.bat
		show_status "Copying dmh84_inspect to dmh_inspect"
		file copy -force bin/dmh84_inspect.bat bin/dmh_inspect.bat
		show_status "Copying hub84client to hubclient"
		file copy -force bin/hub84client.bat bin/hubclient.bat
		show_status "Copying dmh84_SQLsrv to dmh_SQLsrv"
		file copy -force bin/dmh84_SQLsrv.bat bin/dmh_SQLsrv.bat
	    }
	} else {
	    if { ![file exists bin/dmh_wish] } {
		cd bin
		show_status "linking dmh84 to dmh_wish"
		exec ln -s dmh84 dmh_wish
		show_status "linking datahub84 to datahub"
		exec ln -s datahub84 datahub
		show_status "linking dmh84_inspect to dmh_inspect"
		exec ln -s dmh84_inspect dmh_inspect
		show_status "linking hub84client to hubclient"
		exec ln -s hub84client hubclient
		cd $dest_path
	    }
	}
	show_status "Installing SECS/GEM Interface files..."
	unzip ${base}/gem.zip
	cd gem 
	unzip ${base}/baseline.zip
        unzip ${base}/startup.zip
	source ${dest_path}/gem/startup/source_system.tcl
        read_settings "${dest_path}/gem/startup/client.ini"
        default_value SGI client baseline_client
        source_system [list baseline $SGI(client)]
        set client $SGI(client)
        
        unzip ${base}/${client}.zip
	
	show_status "setting permissions ..."
	if { !$isNT } {
	     exec mv ${dest_path}/gem/startup/start_secsgem ${dest_path}/gem/startup/ss
	     exec dos2unix ${dest_path}/gem/startup/ss > ${dest_path}/gem/startup/start_secsgem
	     exec mv ${dest_path}/gem/startup/client.ini ${dest_path}/gem/startup/ci
	     exec dos2unix ${dest_path}/gem/startup/ci > ${dest_path}/gem/startup/client.ini
	     exec mv ${dest_path}/gem/${client}/defaults.ini ${dest_path}/gem/${client}/di
	     exec dos2unix ${dest_path}/gem/${client}/di > ${dest_path}/gem/${client}/defaults.ini
	     exec rm -f ${dest_path}/gem/startup/ss ${dest_path}/gem/startup/ci ${dest_path}/gem/${client}/di
	     cd ${dest_path}
	     exec chmod -R +x . 
	     }
        

	show_status "Installing C programming files..."
	cd ${code_path}
	if {$isNT} {
	    if {[file exists ${base}/src_nt84.zip]} {
		unzip ${base}/src_nt84.zip
	    } else {
		show_status "C programming files not found"
	    }
	} else {
	    if {[file exists ${base}/src.zip]} {
		unzip ${base}/src.zip
	    } else {
		show_status "C programming files not found"
	    }
	}
    }
     
    # PROGRAM GROUP
    
    if { $checked(pgroup) } {
	show_status "Making Program Group..."
	makegroup "Tcl 8.4 - Tk 8.4 - DMH"
    }
     
    if { $checked(pgroup) } {
	if { $checked(sgi) } {
	    show_status "Making Program Items..."
	    set ulb "${nt_dest}bin\\"
	    set i_exe dmh84.exe	;# icon source
	    #        commandline description dir minimize iconexe icon	
	    additem "${ulb}dmh84.exe -f gemequip" "GEM Equipment" ${nt_dest}gem\\${client} 0 $i_exe 3
	    additem "${ulb}dmh84.exe -name datahub -msgargs \"source \$dmh_library/server.dmh\" \
		    -f hub84 \"set server=GEMMBX\" eof" "SECS/GEM Mbx Server" $ulb 0 $i_exe 1

	    additem "${ulb}dmh84.exe" "DMH Wish" $ulb 0 $i_exe 3
	    additem "${ulb}dmh84.exe -notk" "DMH Shell" $ulb 0 $i_exe 3

	    additem "${ulb}uninstall84.cmd" "Uninstall DMH" $ulb 0 $i_exe 3
	}
    }    

    # ENVIRONMENT
    #
    # DISPLAY PATH DMH_BIN 
    if { $checked(setenv) } {
	show_status "Registering environment variables..."
	global env
	if { [info exists env(COMPUTERNAME)] } {
	    set display $env(COMPUTERNAME) 
	} else {
	    if { [catch {dmh::dp_hostname} display] } { set display %COMPUTERNAME% }
	}
	regset DISPLAY $display:0.0
	# believe it or not an NT 4.0 machine at SEMATECH did not have
	# a machine or user PATH - maybe using protection s/w
	if { [catch {regset -machine path} mPath] } { set mPath ""}
	if { [catch {regset -user path} uPath] } { set uPath ""}
	set mpath [split [string tolower $mPath] \;]
	set upath [split [string tolower $uPath] \;]
	set ulb [string tolower ${nt_dest}bin]
	if { [lsearch -exact $mpath $ulb] < 0 && [lsearch -exact $upath $ulb] < 0 } {
	    if { $mPath == "" } { 
		set New_mPath $ulb 
	    } else { 
		set New_mPath "$mPath;$ulb" 
	    }
	    set rc [catch {regset -machine PATH $New_mPath}]
	    if { $rc } {
		if { $uPath == "" } {
		    set New_uPath $ulb 
		} else {
		    set New_uPath "$ulb;$uPath"
		}
		regset -user PATH $New_uPath
	    }
	    
	    # we compute the libraries from the executable location so
	    # we remove environment variables from prior versions that may conflict.
	    # the prior versions still work if they use the default paths
	    regset -delete DMH_BIN
	    regset DMH_BIN [file join $dest_path bin]
	    regset -delete TCL_LIBRARY 
	    regset -delete TK_LIBRARY
	    regset -delete DMH_LIBRARY
	    regset -announce
	}
    }
     
    if {$checked(doc)} {
	show_status "Copying Documentation..."
	cd $doc_path
	set doc_file [file join ${base} Users_guide.pdf]
	if {[file exists $doc_file]} {
	    file copy -force  $doc_file Users_guide.pdf
	}
    }

    if { $checked(license) } {
	show_status "Copying License Data..."
	cd [file join $dest_path lib dmh84]
	set text ""
	foreach rec $license_records {
	    dmh::vset $rec "type data"
	    if { $type == "Migrate" } {
		if { [file readable $data] } {
		    set fid [open $data r]
		    append text [read $fid]
		    close $fid
		}
	    }
	}
     	
	if { [file readable $licfile] } {
	    set fid [open $licfile r]
	    append text [read $fid]
	    close $fid
	}
	foreach rec $license_records {
	    dmh::vset $rec "type host codes"
	    if { $type == "Permanent1" } {
		append text "set dmh::dmh_license($host) $codes ;# permanent\n"
	        set fid [open $licfile w]
	        puts -nonewline $fid $text
	        close $fid
	    } elseif { $type == "Temporary" } {
		set codes [::dmh::dmh_encode 30 $host 3]
		set text "set dmh_license($host) $codes ;# temporary\n$text"
	        set fid [open $licfile w]
	        puts -nonewline $fid $text
	        close $fid
	    }
	}
	set fid [open $licfile w]
	puts -nonewline $fid $text
	close $fid
    }
    
    # Did we really need to supply system DLLs?
    # remove ours if they are older or identical
    if { $checked(sgi) && $isNT } {
	show_status "Checking system DLLs..."
	foreach file {MSVCRT40.DLL} {
	    set oname ${nt_dest}bin\\$file
	    if { [catch {file mtime $oname} our_t] } continue
	    set sname $env(SystemRoot)\\system32\\$file
	    if { [catch {file mtime $sname} system_t] } continue
	    if { $our_t <= $system_t } {
		file delete $oname 
	    } 
	}
    }
    
    .bot.ok configure -state normal -cursor ""
    catch { destroy .sstatus }
    tk_dialog .pop "Software-Key License Installation" "The installation completed successfully." info 0 Ok
    if { [winfo exists .si] } { raise .si ; focus .si }
   }
}

#
# connect to Progman Progman
# make a program group and display it
#
proc makegroup {groupname} {
    global hconv
    set hconv [dmh_dde connect progman progman]
    # try to make it a common group - user must be privileged
    set rc [catch {dmh_dde execute $hconv "\[CreateGroup(\"$groupname\",1)\]"}]
    if { $rc } {
        # failed - try to do it as user
        # if we fail here, assume it exists
        set rc [catch {dmh_dde execute $hconv "\[CreateGroup(\"$groupname\",0)\]"}]
    }
    # activate and display the group
    # 
    set rc [catch {dmh_dde execute $hconv "\[ShowGroup(\"$groupname\",1)\]"}]
    if { $rc } {
        tk_dialog .p "Program Manager Installation" "Program group installation failed" error 0 Exit
        exit 3
    }
}

#
# add a program item to the activated group
#
proc additem {cmd name {dir ""} {minimize 0} {exe ""} {iconindex 0}} {
    global hconv
    dmh_dde execute $hconv "\[AddItem($cmd,\"$name\",$exe,$iconindex,,,$dir,,$minimize)\]"
}

proc mkdirpath {dest_path} {
    global isNT
    #puts $dest_path
    set dest_path [string trimright $dest_path /]
    if { $dest_path == "" } return
    if { $isNT && ([string length $dest_path] == 2) && ([string first : $dest_path] == 1) } {
        return
        # [file isdirectory c:] is 0
    }
    if { ![file isdirectory $dest_path] } {
        mkdirpath [file dirname $dest_path]
        if { [catch { exec mkdir $dest_path } txt] } {
            global isNT
            if $isNT {
                regsub -all / $dest_path \\ sl_dest 
                catch { exec mkdir $sl_dest } txt
	    }
	}
    }
}

# unzip 5.11
# -o means overwrite destination files without prompting
# includes directory structure by default (older version needs -d)
proc unzip {zipfile args} {
    global isNT base
    set unzip $base/usr/local/bin/unzip
    if { [file exists $base/usr/local/bin/unzip.] } {
        set unzip $base/usr/local/bin/unzip. 
    }
    show_status "Unzipping $zipfile..."
    if $isNT { 
        append unzip .exe
        regsub -all \\\\ $unzip / unzip
        regsub -all \\\\ $zipfile / zipfile
        if { [catch { eval [concat exec $unzip -o $zipfile $args] } txt] } {
            show_status "unzip is not working - $txt"
	}
        return
    }
    if { [catch { eval [concat exec $unzip -o $zipfile $args] } txt] } {
        if { [string first warning $txt] < 0 } {
            # ld.so: warning: older lib message is suppressed
            error "unzip is not working - $txt"
	}
    } 
    show_status "Unzipping $zipfile...Done"
}

proc dmh_show_txt {text title {height 24} {width 80} {font fixed}\
 {parent {}} {Dismiss Dismiss}} {
    global dmh_ctr
    if { ![info exists dmh_ctr] } { set dmh_ctr 0 }
    set w $parent.dmh_st${dmh_ctr}
    incr dmh_ctr
    toplevel $w
    wm title $w $title
    frame $w.bot
    button $w.bot.ok -takefocus 1 -text $Dismiss -command "destroy $w"
    pack $w.bot  -side bottom -fill x
    text $w.t -yscrollcommand "$w.y set" -font $font \
        -wrap word -width $width -height $height -setgrid 1
    scrollbar $w.y -relief flat -command "$w.t yview"
    pack $w.y -side right -fill y
    pack $w.t -expand 1 -fill both
    $w.t insert 0.0 $text
    pack $w.bot.ok -anchor center -expand 1 -side left  -ipadx 2m -padx 25m -pady 5m 
    focus $w.bot.ok
    if { $parent != {}} {
        dmh_transient $w [winfo toplevel [winfo parent $w]]
        }
    return $w
    }

#################################################################
# Here starts the main line
#################################################################

if { $tcl_platform(platform) == "windows" } { fix_auto_path }

if { [file readable ../etc/copyright.msg] } { 
    show_license ../etc/copyright.msg 12 60
} else { 
    show_license licterms.txt 
}  

mktopwin

