rem Rebuild the tclIndex file so that unknown Tcl procedures are automatically 
rem found if this directory is added to the auto_path variable.
dmh_wish -notk -tclargs "auto_mkindex . *.tcl" exit
