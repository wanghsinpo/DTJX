# (C) Copyright Agilent Technologies, Inc. 2001-2003.
# All Rights are reserved.
#
# Copying Or Other Reproduction Of This Program Except For Archival Purposes
# Is Prohibited Without The Prior Written Consent Of Agilent Technologies.
#

# $Log: proberMessages.tcl,v $
# Revision 1.10  2003/10/30 21:23:42  fauser
# Fixed code to not send STOP command to prober when a CJAbort is sent in the
# settingup state.  In this case the job has not been created on the prober
# and the prober will nack this command.
# jtaylor 10/30/2003
#
# Revision 1.9  2003/07/07 16:50:03  fauser
# Changed code in buildListOfSlots proc to always query the equipment for
# prober recipe name.
#
# Revision 1.8  2003/04/25 21:11:11  pierre
# Release 3b16 - See README file for all details
#
# Revision 1.7  2003/04/21 19:13:10  pierre
# Release 3b15 - See README file for details
#
# Revision 1.6  2003/04/03 08:24:45  pierre
# Release 3b13 - See README file for all details
#
# Revision 1.5  2003/03/25 10:34:49  pierre
# Release 3b12 - See README file details
#
# Revision 1.4  2003/03/13 22:25:28  pierre
# Release 3b11 - Added support for CMD EXTRACT-PROBER-RECIPE
# 	       and fixed the TSK S16F23 tuning scenario when SlotList is specified
#
# Revision 1.3  2003/02/10 22:22:08  pierre
# 1) Added new regression test scripts for tel and tsk
#    to test CJABORT and PJABORT in all port states
#
# 2) Modified triggers.csv and transitions.csv (tel and tsk)
#    to support PJ and CJ ABORT.
# 														   3) Modified stream16.tcl, proberMessages.tcl (tel and tsk)
#    to better support PJ and CJ ABORT (proc abortCJJOB,PendingCompletePJCheck,
#    PRJobAborted and PRJobAborted_STANDBY).
#
# Revision 1.2  2003/01/09 22:16:26  pierre
# Added code to support the upcoming S2F49 JOBCREATE SLOT-RECIPE parameter
#   


##############################################################################
# Proc name:  manual_abort 
#
# Desc:       This proc is used internally for debugging purposes.
#             It allows sending an S2F49 ABORT command
#
# Parameters: 
#               port id
#
#
# Return:       0 = success -1 = failure
# Change log: 
#
# pgauthier March 29 2003 Initial Release
# 
##############################################################################
proc manual_abort { PortID } {

   set carrierid [getCarrierForPort $PortID]
   
   set request "L \
                  {U2 1} \
                  {A $carrierid} \
                  {A ABORT} \
                  {L \
                  }"  
 
    
   set reply [safe_secs_xact GEMPROBER S2F49R $request]
   set failure [safe_secs_xact_failure $reply]
   if { $failure != "" } {
	set msg "S2F49 prober transaction ABORT failed: $failure"
	SendTerminalServicesMsg $msg Prober
	return -1 
   }
   
   # good reply  =>>>  L:2 {B:1 0x00} {L:0}
 
   rset $reply { L2
                 {B code}
                 L
               } 
               
   if { ($code != "0x00") && ($code != "0x04")} {
        set msg "S2F49 prober transaction ABORT error: return code = $code"
	SendTerminalServicesMsg $msg Prober   
	return -1
   } 
   
   return 0

}


##############################################################################
# Proc name:  manual_stop 
#
# Desc:       This proc is used internally for debugging purposes.
#             It allows sending an S2F49 STOP command
#
# Parameters: 
#               port id
#
#
# Return:       0 = success -1 = failure
# Change log: 
#
# pgauthier March 29 2003 Initial Release
# jtaylor   Oct 29 2003   Added code to check if we were stopping from the
#                         settingup state, in this case we do not send STOP
#                         to prober.
# 
##############################################################################
proc manual_stop { PortID } {

   set PrevPortState [lindex [eq_VV_item GEMPORT PreviousPortStateName$PortID varname] 1] 
   if {$PrevPortState == "SETTINGUP"} {
     return 0
   }

   set carrierid [getCarrierForPort $PortID]
   
   set request "L \
                  {U2 1} \
                  {A $carrierid} \
                  {A STOP} \
                  {L \
                  }"  
    
   set reply [safe_secs_xact GEMPROBER S2F49R $request]
   set failure [safe_secs_xact_failure $reply]
   if { $failure != "" } {
	set msg "S2F49 prober transaction STOP failed: $failure"
	SendTerminalServicesMsg $msg Prober
	return -1 
   }
   
   # good reply  =>>>  L:2 {B:1 0x00} {L:0}
 
   rset $reply { L2
                 {B code}
                 L
               } 
               
   if { ($code != "0x00") && ($code != "0x04")} {
        set msg "S2F49 prober transaction STOP error: return code = $code"
	SendTerminalServicesMsg $msg Prober   
	return -1
   } 
   
   return 0

}
 

##############################################################################
# Proc name:  ControlJobProberAbort 
#
# Desc:       This proc sends a S2F49 message to the prober to abort the current
#             job running on port 1 or 2.
#
# Parameters: 
#                
#
#
# Return:       0 = success -1 = failure
# Change log: 
# pgauthier Jan 8 2003 Initial Release
# pgauthier Mar 17 2003 Changed ABORT for STOP with no port specifier
# pgauthier Mar 28 2003 Now only allow ABORT in ALARMPAUSED case.
# pgauthier April 21 2003  Removed ControlJobProberAbort flag 
#                          since it would defeat the S16F27 SAVEJOBS action
# pgauthier April 25 2003  Added PortID parameter to JobCancelTester
# jtaylor   October 29, 2003  Check to see if we are in SETTINGUP state.  In
#                             this case we will not send STOP to prober.
##############################################################################

proc ControlJobProberAbort { spname } {

   global GEMPORT 
   global JobQueue
   global DATATYPE VGEM

   upvar 2 PortID PortID
   
   #used in PendingCompletePJCheck to delete all process jobs
   #we removed it since it would defeat the SAVEJOBS action
   #on S16F27. Jobs are destroyed anyway upon S16F27 so this flag
   #is not needed anymore
   #set VGEM(ControlJobProberAbort_${PortID}) 1

   set PortState [getCurrentState GEMPORT Port $PortID]
   set equipstate [lindex [eq_VV_item GEMPORT ProcessStateName varname] 1] 
   
   # We will not require a job stop if we are aborting in the SETTINGUP state
   # This will need to be re-addressed as we see the possibility of alarms
   # from the prober in settingup state.  Right now we assume that the CJAbort 
   # is the result of a tester alarm.  The job has not been created yet on the
   # prober.
   
   set PortState [getCurrentState GEMPORT Port $PortID]
   if {$PortState == "SETTINGUP"} {
     return 0
   }

   
   #we want to send ABORT only from ALARMPAUSED
   #CJABORT performs the transition to ABORTING
   #and this proc is called as a postproc after the transition occured
   if {$equipstate != "ABORTING"} {
     return 0
   }
   
   ProberStop GEMPROBER
   
   
   ################ Cancel Job #############################
   #
   
   JobCancelTester GEMPORT $PortID
    
   
   return 0

}


##############################################################################
# Proc name:  buildListOfSlotProberRecipes
#
# Desc:       This proc builds a list of the prober recipes to be included
#             in the new S2F49 JOBCREATE parameter. This proc is called
#             from proc JobCreate.
#
# Parameters: 
#               port (1 or 2)
#
#
# Return:       L {A ProberRecipeFileName_slot1} .. {A ProberRecipeFileName_slot25}
#               or null if no recipe was found
# Change log: 
# pgauthier Jan 9 2003 Initial Release
# pgauthier Mar 17 2003 Added a 46 bytes padding to each value in SLOT-RECIPE
# pgauthier Mar 28 2003 Added a check if the process job list was null
# pgauthier April 1 2003 Added check for a prober recipe = null
# jtaylor   July  2 2003 Added code to make sure required prefix 'MAS/MAS' was
#                        present for all prober recipe entries.
# jtaylor   July  3 2003 Changed code to always check for prober recipe using
#                        EXTRACT-PROBER-RECIPE. 
# N.Yoshimura Feb 9 2007 Bug Fix EXTRACT-PROBER-RECIPE access key 
#                        ProberRecieFileName
##############################################################################

proc  buildListOfSlotProberRecipes { port } {

   global GEMPORT 
   
   #initialize a slot array for 25 wafers
   #each item is associated with a prober recipe file name
   for {set i 1} {$i <=25} {incr i} {
     set slot_array($i) ""
   }
  
   #get the control job associated to the specified port
   set cj [getControlJobForPort $port] 
   
   #get a list of process jobs associated with the control job
   set pj_list [QgetList $cj]
   
   if {$pj_list == ""} {
      return ""
   }
   
   foreach pj $pj_list {

      #get a list of slots associated with the process job
      #we need to get attribute PRMtlNameList
      #Example: PRMtlNameList {L:2 {A:8 CarrierA} {L:3 {U1:1 1} {U1:1 13} {U1:1 5}}}
      
      # ex. L:2 {A:8 CarrierA} {L:3 {U1:1 1} {U1:1 13} {U1:1 5}}
      set prmtlnamelist [lindex [getProcessJobAttribute $pj PRMtlNameList] 0]
      # ex. L:3 {U1:1 1} {U1:1 13} {U1:1 5}
      set slotlist [lindex $prmtlnamelist 2]
      #get rid of leading L
      set slotlist [lrange $slotlist 1 end]

      
      set recipeid     [getProcessJobAttribute $pj RecID]
      set recipemethod [getProcessJobAttribute $pj PRRecipeMethod]
      set RecipeFName  [getPjRecipeAttribute $pj ProberRecipeFileName]

      
      set prober_recipe_filename ""
      set prober_recipe_filename [getProberRecipeFileName $port $RecipeFName $recipeid]
	 if {$prober_recipe_filename == ""} {
	    return ""
	 }
      
      foreach slot $slotlist {
         set slot_number [lindex $slot 1] 
         set slot_array($slot_number) $prober_recipe_filename 
      }
      
   
   }
   
   # {slot lotid waferid} {slot lotid waferid} ...
   set completeWaferList [getWaferList [getCarrierForPort $port]]
   
   set formattedSlotList "L"
   
   for {set i 1} {$i <=25} {incr i} {
     if {[set slot_array($i)] == ""} {
        set space " "
	
	set foundGoodWafer 0
	foreach wafer $completeWaferList { 
	  set slotid [lindex $wafer 0]
	  if {$slotid == $i } {
	    set foundGoodWafer 1
	    break
	  }
	}
	  
	if {$foundGoodWafer == 1} {
	  lappend formattedSlotList "A:46 \"[string_pad $prober_recipe_filename 46]\""
	} else {
	  lappend formattedSlotList "A:46 \"[string repeat $space 46]\""
	}
        
     } else {

        lappend formattedSlotList "A:46 \"[string_pad [set slot_array($i)] 46]\""
     }
   }
   return $formattedSlotList

}

 


##############################################################################
# Proc name:  getProberRecipeFileName
#
# Desc:       This proc returns a prober recipe file name by sending
#             a CMD EXTRACT-PROBER-RECIPE to SPECS and reading the
#             ProberRecipeFileName updated on EVENT ProberRecipeFileName
#
#             EVENT ProberRecipeFileName calls a proc XXXXX that puts
#             a message in mailbox PROBER_RECIPE_FILE_NAME. 
#
# Parameters: 
#               PortID       :  port 1 or 2
#               RecipeFName  :  SPECS 3.0 Master Recipe FileName
#               recipeid     :  recipeid entry in RecipeFName
#
#
# Return:       prober recipe file name (variable ProberRecipeFileName)
# Change log: 
# pgauthier Jan 9 2003 Initial Release 
# pgauthier April 1 2003 Added support for port id
##############################################################################

proc getProberRecipeFileName { PortID RecipeFName recipeid } {

   global VGEM
   set plist [list L]
   set param [list L [list A PortID] [list A $PortID]]
   lappend plist $param
   set param [list L [list A RecipeFName] [list A $RecipeFName]]
   lappend plist $param
   set param [list L [list A PPExecName] [list A $recipeid]]
   lappend plist $param

   #make sure the mailbox is empty before making a request to the tester
   #mbx flush PROBER_RECIPE_FILE_NAME

   set VGEM(WaitProberRecipeFileName_${PortID}) 0

   Tell_Tester_RCMD GEMPORT EXTRACT-PROBER-RECIPE 0 $plist $PortID
   
   while { 1 } {

   set tsx $VGEM(WaitProberRecipeFileName_${PortID})
    
   if { $tsx == 1 } {
       break
       } 
   wait 100
   } 
   
   set prober_recipe [getVarByName GEMPORT ProberRecipeFileName$PortID]

   set VGEM(WaitProberRecipeFileName_${PortID}) 0
   
   return $prober_recipe

}
