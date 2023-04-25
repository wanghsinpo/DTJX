# dmh_gets
# Simple string entry dialog
# modified from  Tk 4.0 dialog.tcl
# does regular expression check
#
# Author: Ed Hume, Hume Integration Software

#
# tk_dialog:
#
# This procedure displays a dialog box, allows text input, 
# and waits for the Ok or Cancel button in the dialog
# to be invoked, then returns the entered text or ""
# global dmh_gets(button) is set to "Ok" or "Cancel" 
#
# Arguments:
# title -	Title to display in dialog's decorative frame.
# prompt -	Message to display in dialog.
# txt_default   default answer
# checkpat      regexp validation pattern 
namespace eval ::dmh {
proc dmh_gets {title prompt txt_default {checkpat .*} {w .dmh_gets}} {
    variable dmh_gets
    set bitmap question

    # 1. Create the top-level window, a generic string input dialog
  
    catch {destroy $w}
    toplevel $w -class Dialog
    wm title $w $title
    wm iconname $w Dialog
    wm protocol $w WM_DELETE_WINDOW { }
    # fix for wm transient becoming buggy in windows tk 8.3
    dmh_transient $w [winfo toplevel [winfo parent $w]]
    frame $w.top 
    pack $w.top -side top -fill both
    frame $w.bot 
    pack $w.bot -side bottom -fill both

    # 2. Fill the top part with bitmap and message.

    label $w.msg -wraplength 3i -justify left -text $prompt \
	    -font -Adobe-Times-Medium-R-Normal--*-180-*-*-*-*-*-*
    pack $w.msg -in $w.top -side right -expand 1 -fill both -padx 3m -pady 3m
    if {$bitmap != ""} {
	label $w.bitmap -bitmap $bitmap
	pack $w.bitmap -in $w.top -side left -padx 3m -pady 3m
    }

    # 2.1 Add entryfield
    entry $w.e -relief sunken -width 60
    pack $w.e -side top -expand 1 -fill x -padx 3m -pady 3m
    bind $w.e <Return> [list set ::dmh::dmh_gets(button) Ok]

    if { [llength $txt_default] } { $w.e insert 0 $txt_default }
    

    # 3. Create a row of buttons at the bottom of the dialog.
    set args {Ok Cancel}
    set default Ok

    set i 0
    foreach but $args {
	button $w.button$i -text $but -command [list set ::dmh::dmh_gets(button) $but]
	if {$i == $default} {
	    frame $w.default -relief sunken -bd 1
	    raise $w.button$i $w.default
	    pack $w.default -in $w.bot -side left -expand 1 -padx 3m -pady 2m
	    pack $w.button$i -in $w.default -padx 2m -pady 2m
	    bind $w <Return> "$w.button$i flash; set ::dmh::dmh_gets(button) $but"
	} else {
	    pack $w.button$i -in $w.bot -side left -expand 1 \
		    -padx 3m -pady 2m
	}
	incr i
    }

    # 4. Withdraw the window, then update all the geometry information
    # so we know how big it wants to be, then center the window in the
    # display and de-iconify it.

    wm withdraw $w
    update idletasks
    set x [expr [winfo screenwidth $w]/2 - [winfo reqwidth $w]/2 \
	    - [winfo vrootx [winfo parent $w]]]
    set y [expr [winfo screenheight $w]/2 - [winfo reqheight $w]/2 \
	    - [winfo vrooty [winfo parent $w]]]
    wm geom $w +$x+$y
    wm deiconify $w

    # 5. Set a grab and claim the focus too.

    set oldFocus [focus]
    set oldGrab [grab current $w]
    if {$oldGrab != ""} {
	set grabStatus [grab status $oldGrab]
    }
    grab $w
    tkwait visibility $w

    focus $w.e

    # 6. Wait for the user to respond, then restore the focus and
    # return the index of the selected button.  Restore the focus
    # before deleting the window, since otherwise the window manager
    # may take the focus away so we can't redirect it.  Finally,
    # restore any grab that was in effect.
  while 1 {
      vwait ::dmh::dmh_gets(button)       
      if { $dmh_gets(button) == "Cancel" } { set text "" ; break }
 
      set text [$w.e get]
      set fullmatch ""
      regexp $checkpat $text fullmatch
      if { $text != $fullmatch } {
          tk_dialog .dlg_get "$title Data Validation" \
 "Your text entry should match the pattern specified by \"$checkpat\"" \
 error 0 Dismiss
          continue
          }
      break
      }
    destroy $w
    if {$oldGrab != ""} {
	if {$grabStatus == "global"} {
	    grab -global $oldGrab
	} else {
	    grab $oldGrab
	}
    }

    catch {focus $oldFocus}
    return $text 	;# global dmh_gets(button) is "Ok" or "Cancel"
}
} ;# namespace
