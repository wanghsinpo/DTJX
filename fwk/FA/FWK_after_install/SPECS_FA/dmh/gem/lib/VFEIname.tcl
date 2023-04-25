# $Header: /usr/cvsroot/gem/lib/VFEIname.tcl,v 1.4 2001/11/15 17:03:50 hume Exp $
#
# Licensed and Supported Software
# (C)Copyright 1997 Hume Integration Software
# All Rights Reserved
#
# $Log: VFEIname.tcl,v $
# Revision 1.4  2001/11/15 17:03:50  hume
# Changed Hume Integration Services to Hume Integration Software.
#
# Revision 1.3  2000/10/10 18:29:43  hume
# Filter non-alphanumeric characters from system created VFEI variable names.
#
# Revision 1.2  1999/04/09 20:36:57  hume
# VFEI does not like white space and conflicts with CMD, MID, TID, MTY need
# to be avoided if these tokens are used as variable names.
#
# Revision 1.1.1.1  1997/07/01 13:39:51  hume
# New SECS/VFEI/GEM application.
#
        
#
# Translation of E5 and GEM variable names to VFEI names.
# eg., PPExecName ---> PP_EXEC_NAME
#
# Do not tell the authors of VFEI that their names are
# easily computed, or they will change them all in the
# next release!
#
proc VFEIname varID {
    # anything thats not a normal identifier character or dash, replace with underscore
    # (includes internal whitespace, slashes, colons, etc)
    regsub -all {[^A-Za-z0-9-]} [string trim $varID] "_" varID 
    # add underscore to UpperLower boundaries
    regsub -all {[A-Z][a-z]} $varID _& varID
    # replace multiple underscores with single
    regsub -all {_[_]+} $varID "_" VFEIname
    set VFEIname [string trim [string toupper $VFEIname] _]
    # now map exceptions
    # MID as a variable conflicts with MID as the machine ID
    switch -exact $VFEIname {
       ESTABLISH_COMMUNICATIONS_TIMEOUT {
           set VFEIname COM_TIMER
           }
       MDLN { set VFEIname EQ_MODEL_ID }
       PREVIOUS_PROCESS_STATE { set VFEIname PREV_PROC_STATE }
       SOFTREV { set VFEIname EQ_SOFT_VER }
       MID { set VFEIname MATERIAL_ID } 
       CMD { set VFEIname CMD_VAR } 
       TID { set VFEIname TID_VAR } 
       MTY { set VFEIname MTY_VAR } 

       default { }
       }
    return $VFEIname
    }
