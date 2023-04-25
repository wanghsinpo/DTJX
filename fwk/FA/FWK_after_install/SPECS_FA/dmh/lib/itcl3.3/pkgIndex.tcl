# Tcl package index file, version 1.0
if {[package provide Tcl] < 8.4} return
package ifneeded Itcl 3.3 [list load [file join $dir "libitcl3.3.so"] Itcl]
