# $Header: /usr/cvsroot/tcllib84/dmh_stat.tcl,v 1.2 2004/04/20 12:52:06 hume Exp $
#
# Licensed and Supported Material
# (C)Copyright 1995, 1999 Hume Integration Software
# All Rights Reserved
#
# $Log: dmh_stat.tcl,v $
# Revision 1.2  2004/04/20 12:52:06  hume
# invokes new inspect
#
# Revision 1.1.1.1  2002/10/06 17:21:35  hume
# From previous version with changes for new ::dmh namespace and lset -> vset
#
# Revision 1.3  2001/11/15 17:14:17  hume
# Updated company name.
#
# Revision 1.2  2001/09/12 03:02:48  hume
# Tweaked message rate format and header/report spacing.
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
# Revision 1.5  1999/05/06 21:55:22  hume
# Replaced use of menubuttons to have accelerator keys work on NT.
#
# Revision 1.4  1999/01/19 19:47:58  hume
# Added Header and Log cvs tags.
#
namespace eval ::dmh {
# high resolution time in seconds.fraction
proc dmh_stat_time {} {
    foreach {secs micros} [localtime 11] {}
    return [expr $secs + $micros/1.0e6]
    }

#
#
# DMH status window code that can be used by the server and by
# a remote client
#
proc mh_statuswin {} {
    global tcl_platform tcl_version tk_library 
    foreach v {mh_group mh_msgs_Qed mh_refresh_time mh_msgs_in mh_msgs_out\
 mh_statwin_stat mh_xfer_clock mh_xfer_total mh_xfer_rate} { variable $v }
    if { ![info exists tk_library] } { return }
    if { ![info exists mh_group] } { return }
    set w .mh_status
    if { ![winfo exists $w] } {
        toplevel $w
        wm title $w "Distributed Message Hub $mh_group - Status"
        wm iconname $w "$mh_group Status"

        set lb $w.fl.list

        menu $w.menu -tearoff 0 -relief raised -borderwidth 2
        $w configure -menu $w.menu

        set m $w.menu.bW
        $w.menu add cascade -label Window -menu $m -underline 0
        menu $m -tearoff 0
        $m add command -label "Refresh" -underline 0 -command ::dmh::mh_statuswin
        $m add separator
        $m add command -label "Dismiss" -underline 0 -command "destroy $w"

        set m $w.menu.bM
        $w.menu add cascade -label Mailbox -menu $m -underline 0
        menu $m -tearoff 0
        $m add command -label "View..." -underline 0 -command [list ::dmh::mh_sw_box_view $lb]
        $m add command -label "Inspect..." -underline 0 -command [list ::dmh::mh_sw_box_inspect $lb]
        $m add command -label "Get" -underline 0 -command [list ::dmh::mh_sw_box_get $lb]
        $m add separator
        $m add command -label "Flush" -underline 0 -command [list ::dmh::mh_sw_box_flush $lb]
        $m add separator
        $m add command -label "Close" -underline 0 -command [list ::dmh::mh_sw_box_close $lb]

       
        set m $w.menu.bC
        $w.menu add cascade -label Client -menu $m -underline 0
        menu $m -tearoff 0
        $m add command -label "Ping" -underline 0 -command [list ::dmh::mh_sw_cli_ping $lb]
        $m add command -label "Identify" -underline 0 -command [list ::dmh::mh_sw_cli_id $lb]
        $m add command -label "Disconnect" -underline 0 -command [list ::dmh::mh_sw_cli_close $lb]
        $m add command -label "Terminate" -underline 0 -command [list ::dmh::mh_sw_cli_kill $lb]

        set ct 0
        foreach rec { \
          {"Messages Received:" mh_msgs_in 12}\
          {"Messages Sent:" mh_msgs_out 12}\
          {"Messages Queued:" mh_msgs_Qed 12}\
          {"Refreshed At:" mh_refresh_time 20}} {
            vset $rec "txt var width"
            frame $w.f$ct
            label $w.f$ct.l -text $txt -anchor e -width 20
            label $w.f$ct.l2 -textvariable ::dmh::$var -anchor w -width $width
            pack $w.f$ct.l $w.f$ct.l2 -side left
            pack $w.f$ct -side top -fill x -anchor w
            incr ct
            }
        label $w.ll -anchor w -font fixed \
 -text "                       Mailbox       CtIn       CtOut   Count   Client"
        pack $w.ll -side top -expand 0 -fill x 

        frame $w.fl
        frame $w.fr

        set lb $w.fl.list

        frame $w.fr.u -bd 2 -relief ridge
        label $w.fr.u.l1 -text Mailbox -width 12
        label $w.fr.u.l2 -text Actions -width 12
        button $w.fr.u.b1 -text "View" -command [list ::dmh::mh_sw_box_view $lb]
        button $w.fr.u.b2 -text "Flush &\nClose" -command [list ::dmh::mh_sw_box_flush $lb 1]
        pack $w.fr.u.l1 $w.fr.u.l2 -side top -fill x
        pack $w.fr.u.b1 $w.fr.u.b2 -side top -ipadx 2m -fill x -pady 1m

        frame $w.fr.l -bd 2 -relief ridge
        label $w.fr.l.l1 -text Client -width 12
        label $w.fr.l.l2 -text Actions -width 12
        button $w.fr.l.b1 -text "Ping"  -command [list ::dmh::mh_sw_cli_ping $lb]
        button $w.fr.l.b2 -text "Identify" -command [list ::dmh::mh_sw_cli_id $lb]
        pack $w.fr.l.l1 $w.fr.l.l2 -side top -fill x
        pack $w.fr.l.b1 $w.fr.l.b2 -side top -ipadx 2m -fill x -pady 1m

        pack $w.fr.u $w.fr.l -side top -fill x -pady 1m -padx 2m
        pack $w.fr -side right -fill y

        scrollbar $w.fl.scroll -relief sunken -command [list $w.fl.list yview]
        
        listbox $w.fl.list -yscroll [list $w.fl.scroll set] -relief sunken \
           -setgrid 1 -font fixed -xscroll [list $w.fl.scrollx set]\
           -width 60 -height 12
        scrollbar $w.fl.scrollx -relief sunken -command [list $w.fl.list xview] \
           -orient horizontal
        pack $w.fl.scroll -side right -fill y
        pack $w.fl.scrollx -side bottom -fill x
        pack $w.fl.list -side left -expand yes -fill both
        pack $w.fl -side top -expand yes -fill both

        frame $w.b
        button $w.b.r -text Refresh -command ::dmh::mh_statuswin
        button $w.b.ok -text Dismiss -command [list destroy $w]
        pack $w.b -side top -fill x -pady 2m
        pack $w.b.r -side left -padx 10m -ipadx 2m
        pack $w.b.ok -side right -padx 10m -ipadx 2m

        label $w.s -textvariable ::dmh::mh_statwin_stat -anchor w -width 65
        pack $w.s -side top -fill x
        if { ![info exists mh_xfer_clock] } {
            set mh_xfer_clock [localtime 2]
            set mh_xfer_total 0
            }
        wm geometry $w "75x14" 
        }\
    else { wm deiconify $w ; raise $w ; catch {focus $w} }

    set lb $w.fl.list
    # for refresh usage, save scroll and selection 
    set yview [$lb yview]
    set curselection [$lb curselection]
    set mh_statwin_stat ""
    set data [mh_server_status $tcl_version]
    # only a disconnected remote client should ever see the next line.
    if { $data == "" } { 
        set mh_statwin_stat "COMMUNICATION FAILED - STATUS NOT AVAILABLE" 
        set error 1
        }\
    else { set error 0 }
    set mh_refresh_time [localtime 9]

    set last_xfer_clock $mh_xfer_clock
    set last_xfer_total $mh_xfer_total
    set mh_xfer_clock [dmh_stat_time]
    set mh_xfer_total [expr {$mh_msgs_in + $mh_msgs_out}]
    set seconds [expr {$mh_xfer_clock - $last_xfer_clock}]
    if { $seconds > 0 } {
        set mh_xfer_rate [expr {double($mh_xfer_total - $last_xfer_total)/$seconds}]
        if { !$error } { 
            set mh_statwin_stat [format " Message Transfer Rate:  %.1f/sec over last %.2f seconds" $mh_xfer_rate $seconds]
            }
        }
    set mh_msgs_Qed [expr {$mh_msgs_in - $mh_msgs_out}]
    # linked var bug workaround, force a refresh (needed at server)
    set mh_msgs_in $mh_msgs_in
    set mh_msgs_out $mh_msgs_out
    $lb delete 0 end
    set ct 0
    foreach row $data {
       if { $ct == 0 } { 
           vset $row "x1 x2 x3 x4 version"
           set ct 1  
           continue 
           }
       if { $version < 7.4 } {
           vset $row "box count client"
           $lb insert end [format "%26s %7s   %s" $box $count $client]
           }\
       else {
           vset $row "box ctI ctO count client"
           $lb insert end [format "%30s %10s %10s %7s    %s" $box $ctI $ctO $count $client]
           }
       }
    # on refresh restore scroll position and selection 
    catch {
        $lb yview moveto [lindex $yview 0]
        # select first item only
        foreach item $curselection {$lb selection set $item ; break }
        }
    }


proc mh_sw_get_box lb {
    variable mh_statwin_stat
    set msg "Select a row that shows a mailbox before choosing this action."
    set select [lindex [$lb curselection] 0]
    if { $select == "" } {
        set mh_statwin_stat $msg
        return ""
        }\
    else { set mh_statwin_stat "" }
    set text [$lb get $select]
    set box [lindex $text 0]
    if { ![llength $box] || [string first " " $box] >= 0 } {
        set mh_statwin_stat $msg
        set box ""
        }
    return $box
    }

proc mh_sw_get_client lb {
    variable mh_statwin_stat
    set msg "Select a row that shows a client connection\
 before choosing this action."
    set select [lindex [$lb curselection] 0]
    if { $select == "" } {
        set mh_statwin_stat $msg
        return ""
        }\
    else { set mh_statwin_stat "" }
    set text [$lb get $select]
    set len [llength $text]
    # version differences:
    # box ct client
    # box ctI ctO ct client
    if { $len == 3 || $len == 5 } {
        set client [lindex $text end]
        }\
    else { set client "" }
    if { $client == "" } {
        set mh_statwin_stat $msg
        }
    return $client
    }

proc mh_text_display {w txt title} {
   toplevel $w
   wm title $w $title
   button $w.ok -text Dismiss -command "destroy $w"
   text $w.t -relief raised -bd 2 -yscrollcommand "$w.s set" -setgrid true \
      -font fixed
   scrollbar $w.s -relief flat -command "$w.t yview"
   pack $w.ok -side bottom -fill x
   pack $w.s -side right -fill y
   pack $w.t -expand yes -fill both
   $w.t insert 0.0 $txt
   }

proc mh_sw_box_flush {lb {close 0}} {
   set box [mh_sw_get_box $lb]
   if { [llength $box] } {
       dmh flush $box
       if $close {
           dmh close $box
           }
       mh_statuswin
       }
   }

proc mh_sw_box_get lb {
   set box [mh_sw_get_box $lb]
   if { ![llength $box] } return
   variable mh_statwin_stat
   set text [dmh get $box]
   mh_statuswin
   set mh_statwin_stat $text
   }

proc mh_sw_box_close lb {
   set box [mh_sw_get_box $lb]
   if { [llength $box] } {
       dmh close $box
       mh_statuswin
       }
    }

proc mh_sw_box_view lb {
   set box [mh_sw_get_box $lb]
   if { ![llength $box] } return
   set text [mh_sw_box_view_data $box]
   set win .b[join [split $box "!@,.:~$?"] ""]
   catch { destroy $win }
   mh_text_display $win $text "Mailbox $box"
   }

proc mh_sw_box_inspect lb {
   global tcl_version
   variable mh_group 
   set box [mh_sw_get_box $lb]
   if { ![llength $box] } return
   set select [lindex [$lb curselection] 0]
   set client ""
   if { $select != "" } {
        set text [$lb get $select]
        set len [llength $text]
        # version differences:
        # box ct client
        # box ctI ctO ct client
        if { $len == 3 || $len == 5 } {
            set client [lindex $text end]
            }
        }
   if { $client == "" } {
       tk_dialog .mh_status.popup "Inspect"\
 "Select a row that shows a mailbox with a client connection\
  before choosing this action." info 0 Dismiss
       return
       }
   if { [string first _RPC $box] < 0 } {
       if { $box == "DBM" || $box == "DATAHUB" || $box == "ENGDB" } {
           set pick 1
           }\
       else {
           set pick [tk_dialog .mh_status.popup "Inspect"\
 "Inspect will not work unless mailbox $box processes\
 DMH messages as server commands." warning 1\
 "Cancel" "Inspect $box"]
           }
       }\
   else { 
       set pick [tk_dialog .mh_status.popup "Inspect"\
 "Please confirm that you wish to run the inspect\
 application with the target of $box" questhead 1\
 Cancel "Inspect $box"]
      }
   if { $pick == "1" } {
       #set name dmh[join [split $tcl_version .] {}]_inspect
       set name inspect
       set rc [catch {exec $name $box@$mh_group &} text]
       if { $rc } {
           tk_dialog .mh_status.popup "Inspect"\
 "We could not start the $name application - $text"\
 error 0 Dismiss
           }
       }
   }


proc mh_sw_cli_ping lb {
    set client [mh_sw_get_client $lb]
    if { $client != "" } {
        set rc [mh_ping_client $client]
        mh_statuswin
        variable mh_statwin_stat
        if { $client == "__me__" } { 
            if { $rc == "" || $rc == "0" } {
                set mh_statwin_stat "The server is alive."
                }\
            else {
                set mh_statwin_stat "The server is not connected."
                }
            }\
        else { 
            if { $rc } {
                set mh_statwin_stat "Client $client is not connected."
                }\
            else {
                set mh_statwin_stat "Client $client is alive."
                }
            }
        }
    }
} ;# namespace
