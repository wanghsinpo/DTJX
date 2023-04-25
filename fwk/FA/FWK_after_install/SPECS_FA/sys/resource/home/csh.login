#!/usr/bin/csh

# Set up SPECS_FA environment

	setenv SPECS_FA_PATH /opt/SPECS_FA
	setenv DMH_DIR /opt/SPECS_FA/dmh

# Set up dmh Environment

	setenv DMH_BIN ${DMH_DIR}/bin
	setenv PATH ${PATH}:${DMH_BIN}
	setenv SHLIB_PATH ${DMH_DIR}/lib

	if ( `uname -s` == "HP-UX" ) then
		setenv DMH_LIBRARY ${DMH_DIR}/lib/dmh83
    		setenv TK_LIBRARY ${DMH_DIR}/lib/tk8.3
		setenv TCL_LIBRARY ${DMH_DIR}/lib/tcl8.3
	else
		setenv DMH_LIBRARY ${DMH_DIR}/lib/dmh84
    		setenv TK_LIBRARY ${DMH_DIR}/lib/tk8.4
		setenv TCL_LIBRARY ${DMH_DIR}/lib/tcl8.4
		if ( $?LD_LIBRARY_PATH ) then
			setenv LD_LIBRARY_PATH $LD_LIBRARY_PATH:/opt/SPECS_FA/dmh/lib
		else
			setenv LD_LIBRARY_PATH=/opt/SPECS_FA/dmh/lib
        	endif
	endif
