# $Header: /usr/cvsroot/tcllib84/dmh_win_shrink.tcl,v 1.1.1.1 2002/10/06 17:21:35 hume Exp $
#
# $Log: dmh_win_shrink.tcl,v $
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
# Revision 1.1  1998/01/07 04:34:14  hume
# Adds scrollbars to windows that are bigger than screen.
#
#
#
namespace eval ::dmh {
# Shrink a dialog that is too tall or too wide for the screen by repacking the
# widgets onto a scrollable canvas
#
# Intended for windows that were built in horizontal strips packed
# against the top
#
proc dmh_win_shrink w {
    update idletasks
    set pady 80	;# leave room for window manager bar or menu
    set padx 10 
    set hmax [expr [winfo screenheight $w] - $pady]
    set wmax [expr [winfo screenwidth $w] - $padx]
    if { [winfo reqheight $w] > $hmax } {
       set sy 1 } else {set sy 0}
    if { [winfo reqwidth $w] > $wmax } {
       set sx 1 } else {set sx 0}
    if { !$sx && !$sy } {return {0 0}}
    wm withdraw $w
    # frame to hold canvas and scrollbars
    set frame $w.dwsf
    set canvas $w.dwsc
    frame $frame ; lower $frame
    canvas $canvas -scrollregion {0 0 0 0} \
        -yscrollcommand "$canvas.sby set"\
        -xscrollcommand "$canvas.sbx set"
    lower $canvas
    foreach widget [winfo children $w] {
        if { $widget == $frame } continue
        if [catch {pack info $widget} pi] continue
        pack forget $widget
        # get rid of "-in <win>"
        set pi [lreplace $pi 0 1]
        # repack in frame
        eval [concat pack $widget -in $frame -side top $pi]
        }
    $canvas create window 0 0 -window $frame -anchor nw
    scrollbar $canvas.sby -command "$canvas yview" -relief sunken -orient vertical
    scrollbar $canvas.sbx -command "$canvas xview" -relief sunken -orient horizontal
    if $sy {pack $canvas.sby -side right -fill y}
    if $sx {pack $canvas.sbx -side bottom -fill x}
    pack $canvas -side top -expand 1 -fill both
    update idletasks
    $canvas config -scrollregion [$canvas bbox all] 
    # compute sizes to request
    if {$sy} {
        if {$sx} {
            # there will be both scroll bars
            set wrw $wmax
            set wrh $hmax
            }\
        else {
            # y scrollbar
            # no x scrollbar
            # required width should include vertical scrollbar and borders
            set wrw [expr [winfo reqwidth $frame] + [winfo reqwidth $canvas.sby] + 6]
            set wrh $hmax
            } 
        }\
    else {
        # no y scrollbar
        # x scrollbar
        set wrw $wmax
        set wrh [expr [winfo reqheight $frame] + [winfo reqheight $canvas.sbx] + 6]
        }
    set xleft [expr $wmax/2 - $wrw/2  - [winfo vrootx [winfo parent $w]]]
    set ytop [expr $hmax/2 - $wrh/2 - [winfo vrooty [winfo parent $w]]]
    wm geometry $w ${wrw}x${wrh}+${xleft}+${ytop}
    wm deiconify $w
    raise $w
    return [list $sx $sy]
    }
    
} ;# namespace    
