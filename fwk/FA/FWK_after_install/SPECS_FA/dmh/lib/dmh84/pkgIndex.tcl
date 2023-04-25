# use dmh83 with Tcl8.3, use dmh84 with Tcl8.4
if { [package provide Tcl] < 8.4 } return
package ifneeded dmh 1.2 [list source [file join $dir init.tcl]]
