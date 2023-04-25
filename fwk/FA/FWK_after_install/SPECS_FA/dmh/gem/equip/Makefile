
# rebuild the tclIndex file so that unknown Tcl procedures
# are automatically found if this directory is added to the
# auto_path variable.

tclIndex: *.tcl
	dmh_wish -notk -tclargs "auto_mkindex . *.tcl" exit
