# rebuild the tclIndex
tclIndex: *.tcl
	dmh_wish -notk -tclargs "auto_mkindex . *.tcl" exit

pkgIndex.tcl: init.tcl
	dmh84 -tclargs "package forget dmh ; pkg_mkIndex -verbose . init.tcl" exit

