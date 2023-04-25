# $Header: /usr/cvsroot/tcllib84/dmh_cmd_win.tcl,v 1.2 2005/03/22 20:17:42 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 2000, 2005 Hume Integration Software
# All Rights Reserved
#
# $Log: dmh_cmd_win.tcl,v $
# Revision 1.2  2005/03/22 20:17:42  hume
# Suse Linux 9.2 needed -size on font create of fixed.
#
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.6  2001/11/15 17:14:17  hume
# Updated company name.
#
# Revision 1.5  2000/03/15 15:55:17  hume
# Tweak to save and restore errorInfo.
#
# Revision 1.4  2000/03/15 15:46:17  hume
# Revised Delete/Clear menu based on Linux.
#
# Revision 1.3  2000/03/15 15:32:43  hume
# Tweaking source and include features.
#
# Revision 1.2  2000/03/15 14:23:28  hume
# No-confirm on exit for hubclient.
#
# Revision 1.1  2000/03/15 03:33:11  hume
# New consolidated hub and odbc console windows.
#
package require Tk 8.4

# A cross-platform console window for SQL or Tcl commands which
# can also be used in a hubclient for execution in the
# remote Datahub, or in the RxSQLsrv
namespace eval ::dmh {
proc dmh_cmd_win {cmd {server Datahub} {w ""}} {
    if { $w == "" } {
        set ch [string index $cmd 0]
        set w .hub$ch
        }
    if { [winfo exists $w] } {
        wm deiconify $w
        raise $w
        catch { focus $w }
        return
        }
    toplevel $w
    wm title $w "$server $cmd Command Console"
    wm iconname $w "$server\b$cmd Cmds"

    global tcl_platform env tcl_version

    if { ![info exists env(DMH_BIN)] } {
        set env(DMH_BIN) [file dirname [info nameofexecutable]] 
        }

    # no accomdation of macs
    set mod "Ctrl"
    set m [menu $w.menubar]
    $m add cascade -label File -menu $m.file -underline 0
    $m add cascade -label Edit -menu $m.edit -underline 0
    $m add cascade -label Help -menu $m.help -underline 0

    set m $w.menubar.file
    menu $m -tearoff 0
    set source_cmd [list ::dmh::dmh_cmd_win_source $w.console]
    set include_cmd [list ::dmh::dmh_cmd_win_include $w.console]
    $m add command -label "Source Tcl file..." -underline 0\
      -command [list ::dmh::fileselect {} {*.tcl} {Source Tcl File} $source_cmd]
    $m add command -label "Include SQL file..." -underline 0\
      -command [list ::dmh::fileselect {} {*.sql} {Include SQL File} $include_cmd]
    $m add command -label "Dismiss" -underline 0\
      -command "destroy $w"
    $m add command -label "Exit" -underline 0 -command [list ::dmh::cmd_win_confirm_exit $server $w]
    
    set m $w.menubar.edit
    menu $m -tearoff 0
    $m add command -label Cut -underline 2 -command "event generate $w.console <<Cut>>" -accel "$mod+X"
    $m add command -label "Copy" -underline 0 -command "event generate $w.console <<Copy>>" -accel "$mod+C"
    $m add command -label "Paste" -underline 1 -command "event generate $w.console <<Paste>>" -accel "$mod+V"

    $m add command -label "Delete" -underline 0 -command "event generate $w.console <<Clear>>" -accel "Del"
    $m add separator
    $m add command -label "Clear" -underline 1 -command "$w.console delete 0.0 end ; ::dmh::dmh_cmd_win_prompt $w.console"

    set m $w.menubar.help
    menu $m -tearoff 0
    $m add command -label {errorInfo} -command [list ::dmh::dmh_cmd_win_cmd $w.console {eval set errorInfo}]
    if { ![string compare $tcl_platform(platform) "windows"]} {
        $m add command -label {HTML documentation}\
  -command "exec cmd.exe /c [file join $env(DMH_BIN) .. html84 index.html] &"
        }
    $m add command -label "About..." -underline 0 -command "::dmh::dmh_cmd_win_about $w"
    
    $w configure -menu $w.menubar
    if {![string compare $tcl_platform(platform) "windows"]} { set font systemfixed }\
    else { set font fixed }
    text $w.console -yscrollcommand "$w.sb set" -setgrid true -font $font
    scrollbar $w.sb -command "$w.console yview"
    pack $w.sb -side right -fill both
    pack $w.console -fill both -expand 1 -side left

    dmh_cmd_win_bind $w.console


    $w.console tag configure stderr -foreground red
    $w.console tag configure stdin -foreground blue

    catch {focus $w.console}
    dmh_cmd_win_prompt $w.console
    $w.console mark set output [$w.console index "end - 1 char"]
    ::tk::TextSetCursor $w.console end
    $w.console mark set promptEnd insert
    $w.console mark gravity promptEnd left
   
    }
    
proc cmd_win_confirm_exit {server w} {
    # if we are a hubclient where SQL is a Tcl proc and not a command
    # we just exit without confirmation
    if { $server != "ODBC" && [info procs SQL] == "SQL" } {
        set choice 0
        }\
    else {
        # a server datahub or ODBC program
        set choice [tk_dialog $w.rusure "Confirm Exit"\
  "This action will shutdown the program and exit.  Please confirm." \
  questhead 1 Shutdown Cancel]
         }
    if { $choice == 0 } {
        catch { rename mh_app_lostserver {} }
        catch { mbx end }
        exit
        }
    }

proc dmh_cmd_win_record {w cmd} {
    history add $cmd
    if { $w == ".hubS.console" } {
         set result [SQL $cmd]
         }\
    else {
        set result [lindex [SQL [concat eval $cmd]] 0]
        }
    dmh_cmd_win_output $w stdout $result\n
    return {}
    }


proc dmh_cmd_win_about w {
    global tk_patchLevel 
    tk_messageBox -type ok -title "About Tcl/Tk/DMH" -message "Tcl/Tk 

Datahub Solution Development Kit
Copyright \251 2005 Hume Integration Software

Tcl [info patchlevel]
Tk $tk_patchLevel
DMH [package present dmh]"
    }


proc dmh_cmd_win_bind win {
    bindtags $win "$win Text . all"

    # Ignore all Alt, Meta, and Control keypresses unless explicitly bound.
    # Otherwise, if a widget binding for one of these is defined, the
    # <KeyPress> class binding will also fire and insert the character,
    # which is wrong.  Ditto for <Escape>.

    bind $win <Alt-KeyPress> {# nothing }
    bind $win <Meta-KeyPress> {# nothing}
    bind $win <Control-KeyPress> {# nothing}
    bind $win <Escape> {# nothing}
    bind $win <KP_Enter> {# nothing}

    bind $win <Tab> {
	::dmh::dmh_cmd_win_Insert %W \t
	focus %W
	break
    }
    bind $win <Return> {
	%W mark set insert {end - 1c}
	::dmh::dmh_cmd_win_Insert %W "\n"
	::dmh::dmh_cmd_win_Invoke %W
	break
    }
    bind $win <Delete> {
	if {[string compare [%W tag nextrange sel 1.0 end] ""]} {
	    %W tag remove sel sel.first promptEnd
	} elseif {[%W compare insert < promptEnd]} {
	    break
	}
    }
    bind $win <BackSpace> {
	if {[string compare [%W tag nextrange sel 1.0 end] ""]} {
	    %W tag remove sel sel.first promptEnd
	} elseif {[%W compare insert <= promptEnd]} {
	    break
	}
    }
    foreach left {Control-a Home} {
	bind $win <$left> {
	    if {[%W compare insert < promptEnd]} {
		::tk::TextSetCursor %W {insert linestart}
	    } else {
		::tk::TextSetCursor %W promptEnd
            }
	    break
	}
    }
    foreach right {Control-e End} {
	bind $win <$right> {
	    ::tk::TextSetCursor %W {insert lineend}
	    break
	}
    }
    bind $win <Control-d> {
	if {[%W compare insert < promptEnd]} {
	    break
	}
    }
    bind $win <Control-k> {
	if {[%W compare insert < promptEnd]} {
	    %W mark set insert promptEnd
	}
    }
    bind $win <Control-t> {
	if {[%W compare insert < promptEnd]} {
	    break
	}
    }
    bind $win <Meta-d> {
	if {[%W compare insert < promptEnd]} {
	    break
	}
    }
    bind $win <Meta-BackSpace> {
	if {[%W compare insert <= promptEnd]} {
	    break
	}
    }
    bind $win <Control-h> {
	if {[%W compare insert <= promptEnd]} {
	    break
	}
    }
    foreach prev {Control-p Up} {
	bind $win <$prev> {
	    ::dmh::dmh_cmd_win_history %W prev
	    break
	}
    }
    foreach prev {Control-n Down} {
	bind $win <$prev> {
	    ::dmh::dmh_cmd_win_history %W next
	    break
	}
    }
    bind $win <Insert> {
	catch {::dmh::dmh_cmd_win_Insert %W [selection get -displayof %W]}
	break
    }
    bind $win <KeyPress> {
	::dmh::dmh_cmd_win_Insert %W %A
	break
    }
    foreach left {Control-b Left} {
	bind $win <$left> {
	    if {[%W compare insert == promptEnd]} {
		break
	    }
	    ::tk::TextSetCursor %W insert-1c
	    break
	}
    }
    foreach right {Control-f Right} {
	bind $win <$right> {
	    ::tk::TextSetCursor %W insert+1c
	    break
	}
    }
    bind $win <<Cut>> {
        # Same as the copy event
 	if {![catch {set data [%W get sel.first sel.last]}]} {
	    clipboard clear -displayof %W
	    clipboard append -displayof %W $data
	}
	break
    }
    bind $win <<Copy>> {
 	if {![catch {set data [%W get sel.first sel.last]}]} {
	    clipboard clear -displayof %W
	    clipboard append -displayof %W $data
	}
	break
    }
    bind $win <<Paste>> {
	catch {
	    set clip [selection get -displayof %W -selection CLIPBOARD]
	    set list [split $clip \n\r]
	    ::dmh::dmh_cmd_win_Insert %W [lindex $list 0]
	    foreach x [lrange $list 1 end] {
		%W mark set insert {end - 1c}
		::dmh::dmh_cmd_win_Insert %W "\n"
		::dmh::dmh_cmd_win_Invoke %W
		::dmh::dmh_cmd_win_Insert %W $x
	    }
	}
	break
    }
    # middle mouse button Motifd style paste
    bind $win <ButtonRelease-2> {
        catch {::dmh::dmh_cmd_win_Insert %W [selection get -displayof %W]}
            break
        } 
    # but you may not have a three button mouse, so we also bind to
    # the right button - button 3 - like Quick-Edit on NT
    bind $win <ButtonRelease-3> {
        catch {::tk::ConsoleInsert %W [selection get -displayof %W]}
            break
        }
    }


proc dmh_cmd_win_Insert {w s} {
    if {[string equal $s ""]} { return }
    global errorInfo
    set save $errorInfo
    if {[catch {
	if {[$w compare sel.first <= insert] && [$w compare sel.last >= insert]} {
	    $w tag remove sel sel.first promptEnd
	    $w delete sel.first sel.last
            }
        }]} { set errorInfo $save }
    if {[$w compare insert < promptEnd]} { $w mark set insert end	 }
    $w insert insert $s {input stdin}
    $w see insert
    }

proc dmh_cmd_win_Invoke {w args} {
    set ranges [$w tag ranges input]
    set cmd ""
    if {[llength $ranges]} {
	set pos 0
	while {[string compare [lindex $ranges $pos] ""]} {
	    set start [lindex $ranges $pos]
	    set end [lindex $ranges [incr pos]]
	    append cmd [$w get $start $end]
	    incr pos
	}
    }
    if {[string equal $cmd ""]} {
	dmh_cmd_win_prompt $w
    } elseif {[info complete $cmd]} {
	$w mark set output end
	$w tag delete input
	dmh_cmd_win_record $w $cmd
	dmh_cmd_win_history $w reset
	dmh_cmd_win_prompt $w
    } else {
        dmh_cmd_win_prompt $w partial
    }
    $w yview -pickplace insert
    }

proc dmh_cmd_win_prompt {w {partial normal}} {
    if { $w == ".hubS.console" } { 
        set p1 "SQL> " 
        set p2 "+> " 
        }\
    else { 
        set p1 "Tcl> " 
        set p2 "+> " 
        }

    if {[string equal $partial "normal"]} {
	set temp [$w index "end - 1 char"]
	$w mark set output end
    	$w insert end $p1
    	}\
    else {
	set temp [$w index output]
	$w mark set output end
	$w insert end $p2
    	}
    $w mark set output $temp
    ::tk::TextSetCursor $w end
    $w mark set promptEnd insert
    $w mark gravity promptEnd left
   }

#
# Arguments:
# cmd -	Which action to take: prev, next, reset.

proc dmh_cmd_win_history {w cmd} {
    variable dmh
    if { ![info exists dmh($w,histNum)] } { set dmh($w,histNum) 1 }
    
    switch $cmd {
    	prev {
	    incr dmh($w,histNum) -1
	    if {[set dmh($w,histNum)] == 0} {
		set cmd {history event [expr {[history nextid] -1}]}
	    } else {
		set cmd "history event [set dmh($w,histNum)]"
	    }
    	    if {[catch {eval $cmd} cmd]} {
    	    	incr dmh($w,histNum)
    	    	return
    	    }
	    $w delete promptEnd end
    	    $w insert promptEnd $cmd {input stdin}
    	}
    	next {
	    incr dmh($w,histNum)
	    if {[set dmh($w,histNum)] == 0} {
		set cmd {history event [expr {[history nextid] -1}]}
	    } elseif {[set dmh($w,histNum)] > 0} {
		set cmd ""
		set dmh($w,histNum) 1
	    } else {
		set cmd "history event [set dmh($w,histNum)]"
	    }
	    if {[string compare $cmd ""]} {
		catch {eval $cmd} cmd
	    }
	    $w delete promptEnd end
	    $w insert promptEnd $cmd {input stdin}
    	}
    	reset {
    	    set dmh($w,histNum) 1
    	}
    }
}

#
# Arguments:
# dest -	The output tag to be used: either "stderr" or "stdout".
# string -	The string to be displayed.

proc dmh_cmd_win_output {w dest string} {
    $w insert output $string $dest
    $w see insert
    # ECH added logic to bound lines of output text
    variable console_max
    variable console_low
    if { ![info exists console_max] } {
        set console_max 2000
        set console_low 1600
        }
    if { [info exists ::dmh::dmh_${w}_after_handle] } return
    if { [$w index end] > $console_max } {
        # note that low bound and size are evaluated at the time of trim
        set ::dmh::dmh_${w}_after_handle \
 [after idle "$w delete 0.0 \[expr \[$w index end\] - \$::dmh::console_low\] ; \
 unset ::dmh::dmh_${w}_after_handle"]
        }
    }


#
# include file of SQL statements
#
proc dmh_cmd_win_include {w pathname} {
     if { $w == ".hubT.console" } {
         # Tcl console
         set cmd [list SQL [list include $pathname]]
         }\
     else {
         # SQL console
         set cmd [list include $pathname]
         }
    dmh_cmd_win_cmd $w $cmd
    }

#
# macro style execution - as if user typed command
#
proc dmh_cmd_win_cmd {w cmd} {
    dmh_cmd_win_Insert $w $cmd
    $w mark set insert {end - 1c}
    dmh_cmd_win_Insert $w "\n"
    dmh_cmd_win_Invoke $w
    }

#
# include Tcl file
#
proc dmh_cmd_win_source {w pathname} {
     set cmd [list source $pathname]
     dmh_cmd_win_cmd $w $cmd
    }

} ;# namespace
