#---------------------------------------------------------------------
# $Date: 2006/08/28 11:48:16 $             $ $
#---------------------------------------------------------------------
# 
#
#                     MODULE  : testermsg.tcl
#
#---------------------------------------------------------------------
#
#        (c) Copyright Keysight Technologies, 2000,2002,2015
#
#---------------------------------------------------------------------
#
#  CONTENTS:   This file defines a series of tcl functions used to
#              format the messages between SPECS and the Distributed
#              Message Hub (GEM_OUT).
#
#---------------------------------------------------------------------
#
# Development Information:
#
#  Language Written in:  Tcl/Tk     
#  
#
######################################################################

 

# ******************************************************************
# Description:
#                this function sends a message 
#                to the datahub
#
#
#
# INPUTS:  message
#
# OUTPUTS: none
#
# ******************************************************************
proc {Send_MSG}  { mailbox msg }  {
   
   if { [catch {  mbx put $mailbox $msg } catch_error] } {
   
     global errorInfo
     
     logErrors "ERROR: MODULE TESTERMSG.TCL : mbx put $mailbox failed returned : {$catch_error} : \n {$errorInfo}"
      
     return -1
     
   }
   
}
 
 
# ******************************************************************
# Description:
#                this function sends a message 
#                to the datahub
#
#
#
# INPUTS:  message
#
# OUTPUTS: none
#
# ******************************************************************
proc {Send_MSG_Reply}  { mailbox rplymbx msg  }  {
   
   if { [catch {  mbx putr $mailbox $rplymbx $msg } catch_error] } {
   
     global errorInfo
     
     logErrors "ERROR: MODULE TESTERMSG.TCL : mbx put $mailbox failed returned : {$catch_error} : \n {$errorInfo}"
      
     return -1
     
   }
   
}
 
 
# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatAbort { } {

set msg "CMD ABORT {L L}"

return $msg
}


# ******************************************************************
# Description:
#              
#             
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatPJAbort { StartTestPortID } {

set msg "\
CMD PJABORT {L \
                   {L {A PortID} {A $StartTestPortID}} \
                }"
return $msg
}


# ******************************************************************
# Description:
#              
#             
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatCJAbort { StartTestPortID } {

set msg "\
CMD CJABORT {L \
                   {L {A PortID} {A $StartTestPortID}} \
                }"
return $msg
}


# ******************************************************************
# Description: Addition for Tiger
#              Jan.10.2001
#              Keisuke Nakano
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatCancelMeas { StartTestPortID } {

set msg "\
CMD CANCEL-MEAS {L \
                   {L {A PortID} {A $StartTestPortID}} \
                }"
return $msg
}


# ******************************************************************
# Description: Addition for Tiger
#              Jan.10.2001
#              Keisuke Nakano
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatChangeOCRStatus { RequestedOCRState } {

set msg "\
CMD CHANGE-OCR-STATE {L \
                        {L {A RequestedOCRState} {A $RequestedOCRState}} \
                     }"
return $msg
}


# ******************************************************************
# Description:
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatCloselot { StartTestPortID } {

set msg "\
CMD CLOSE-LOT {L \
                 {L {A PortID} {A $StartTestPortID}} \
              }"
return $msg
}

proc formatProberStatus { StartTestPortID } {

set msg "\
INFO ProberStatus {L \
                 {L {A PortID} {A $StartTestPortID}} \
                 {L {A HCACK} {A 0x00}} \
              }"
return $msg
}


# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatPause { } {

set msg "CMD PAUSE {L L}"

return $msg
}

 
# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatRecipe_Tune_OK { StartTestPortID CompileErrorCode} {

set msg "EVENT Recipe_Tuned_OK {L\
  {L {A PortID} {A $StartTestPortID}} \
  {L {A PPBadCompileCode} {A \"$CompileErrorCode\"}} \
}"
return $msg

return $msg
}

 
# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatRecipe_Tune_Failed { StartTestPortID CompileErrorCode} {

set msg "EVENT Recipe_Tuned_Failed {L \
  {L {A PortID} {A $StartTestPortID}} \
  {L {A PPBadCompileCode} {A \"$CompileErrorCode\"}} \
}"

return $msg
}


# ******************************************************************
# Description:
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatPPSelect {  StartTestPortID \
		       WaferSpecFileName \
		       DieSpecFileName \
		       TestPlanName \
		       ProbeSpecFileName \
		       LimitFileName \
		       MddefFileName \
		       ProbeRecipeFileName \
		       CarrierID \
		       LotID \
                       OperatorID \
		       PPExecName \
		       ProductID \
		       WaferList \
		       TestSpecFileName \
		       DieTestSpecName \
                       IWCondition \
                       IWNumOfDies \
                       IWDieLabel \
                       IWJudgeRule \
                       IWJudgeTLevel \
                       BWCondition \
                       BWNumOfWafs \
                       BWWafID \
                       BWJudgeRule \
                       BWJudgeTLevel \
                       PJECondition \
                       PJEJudgeRule \
                       PJEJudgeTLevel \
                       RecipeFName \
                       TestCondFName \
                       CondLevel \
                       WaferTest \
                       AdaptiveMethod \
                       MeasLibName \
                       DeviceLibName \
                       PRJobID \
                       CtrlJobID } { 

set msg "\
CMD PP-SELECT   {L \ 
                   {L {A PortID}                   {A $StartTestPortID}} \
		   {L {A WaferSpecFileName}        {A $WaferSpecFileName}} \
		   {L {A DieSpecFileName}          {A $DieSpecFileName}} \
		   {L {A TestPlanName}             {A $TestPlanName}} \
		   {L {A ProbeSpecFileName}        {A $ProbeSpecFileName}} \
		   {L {A LimitFileName}            {A $LimitFileName}} \
		   {L {A MddefFileName}            {A $MddefFileName}} \
		   {L {A ProbeRecipeFileName}      {A $ProbeRecipeFileName}} \
		   {L {A LotID}                    {A $LotID}} \
		   {L {A CarrierID}                {A $CarrierID}} \
                   {L {A OperatorID}               {A $OperatorID}} \
		   {L {A PPExecName}               {A $PPExecName}} \
		   {L {A ProductID}                {A $ProductID}} \
		   {L {A WaferList}                {A $WaferList}} \
		   {L {A TestSpecFileName}         {A $TestSpecFileName}} \
		   {L {A DieTestSpecName}          {A $DieTestSpecName}} \
                   {L {A IWCondition}              {A $IWCondition}} \
                   {L {A IWNumOfDies}              {A $IWNumOfDies}} \
                   {L {A IWDieLabel}               {A $IWDieLabel}} \
                   {L {A IWJudgeRule}              {A $IWJudgeRule}} \
                   {L {A IWJudgeTLevel}            {A $IWJudgeTLevel}} \
                   {L {A BWCondition}              {A $BWCondition}} \
                   {L {A BWNumOfWafs}              {A $BWNumOfWafs}} \
                   {L {A BWWafID}                  {A $BWWafID}} \
                   {L {A BWJudgeRule}              {A $BWJudgeRule}} \
                   {L {A BWJudgeTLevel}            {A $BWJudgeTLevel}} \
                   {L {A PJECondition}             {A $PJECondition}} \
                   {L {A PJEJudgeRule}             {A $PJEJudgeRule}} \
                   {L {A PJEJudgeTLevel}           {A $PJEJudgeTLevel}} \
                   {L {A RecipeFName}              {A $RecipeFName}} \
                   {L {A TestCondFName}            {A $TestCondFName}} \
                   {L {A CondLevel}                {A $CondLevel}} \
                   {L {A WaferTest}                {A $WaferTest}} \
                   {L {A AdaptiveMethod}           {A $AdaptiveMethod}} \
                   {L {A MeasLibName}              {A $MeasLibName}} \
                   {L {A DeviceLibName}            {A $DeviceLibName}} \
                   {L {A PRJobID}                  {A $PRJobID}} \
                   {L {A CtrlJobID}                {A $CtrlJobID}} \
                }"
return $msg
}

# ******************************************************************
# Description:
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatEXTRACT-PROBER-RECIPE { StartTestPortID \
                    $RecipeFName \
                    PPExecName } {

set msg "\
CMD EXTRACT-PROBER-RECIPE {L \
              {L {A PortID}     {A $StartTestPortID}} \
              {L {A RecipeFName}     {A $RecipeFName}} \
              {L {A PPExecName}  {A $PPExecName}} \
           }"

return $msg
}


# ******************************************************************
# Description:
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatRetest { StartTestPortID \
                    WaferList } {

set msg "\
CMD RETEST {L \
              {L {A PortID}     {A $StartTestPortID}} \
              {L {A WaferList}  {A $WaferList}} \
           }"

return $msg
}


# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatResume { } {

set msg "CMD RESUME {L L}"

return $msg
}


# ******************************************************************
# Description: Addition for Tiger
#              Jan.10.2001
#              Keisuke Nakano
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatRunContinuity { } {

set msg "CMD RUN-CONTINUITY {L L}"

return $msg
}


# ******************************************************************
# Description: Addition for Tiger
#              Jan.10.2001
#              Keisuke Nakano
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatRunDiagnostic { } {

set msg "CMD RUN-DIAGNOSTICS {L \
              {L {A SelectTest}     {A $SelectTest}} \
           }"
return $msg
}


# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatStart { StartTestPortID } {

set msg "\
CMD START {L \ 
             {L {A PortID} {A $StartTestPortID}} \
          }"
return $msg
}


# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatStop { } {

set msg "CMD STOP {L L}"

return $msg
}


# ******************************************************************
# Description:
#
#
#
#
#*******************************************************************
# Description:
#               
#
# INPUTS: Alarm id
#
# OUTPUTS: formatted message
#
#*******************************************************************
proc formatAlarm { ALARM_TXT \
		   ALARM_ID \
		   ALARM_MSG} {

set msg " \
ALARM $ALARM_TXT {L \
 {L {A AlarmID}         {A $ALARM_ID}} \
 {L {A AlarmDetails}    {A \"$ALARM_MSG\"}} \
}"

return $msg
}


#*******************************************************************
# Description:
#               
#
#
#
# INPUTS: NONE
#
# OUTPUTS: formatted message
#
#*******************************************************************
proc formatStartInit { } {

set msg " EVENT StartInit {L L} "

return $msg
}


#*******************************************************************
# Description:
#               
#
#
#
# INPUTS: NONE
#
# OUTPUTS: formatted message
#
#*******************************************************************
proc formatInitComplete { EquipmentSerialID \
                          MDLN \
                          SOFTREV \
                          ProbeCardTypeFound \
                          TestBoardID \
                          NextExecutionLevel \
                          NextExecutionRule} {

set msg " \
EVENT InitComplete  {L \
 {L {A EquipmentSerialID}   {A $EquipmentSerialID}} \
 {L {A MDLN}                {A $MDLN}} \
 {L {A SOFTREV}             {A $SOFTREV}} \
 {L {A ProbeCardTypeFound}  {A $ProbeCardTypeFound}} \
 {L {A TestBoardID}         {A $TestBoardID}} \
 {L {A ExecutionLevel}   {A $NextExecutionLevel}} \
 {L {A ExecuteAttribute}    {A $NextExecutionRule}} \
}"

return $msg
}


# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
# Note: Delete CarrierID from this message because CarrierID comes
#       from CarrierIDVerification. ('01/09/20)
#
# ******************************************************************
proc formatRecipeVerified { LotID \
		       StartTestPortID \
		       OperatorID \
		       PPExecName \
		       WaferSpecFileName \
		       ProbeSpecFileName \
		       DieSpecFileName \
		       ProductID \
		       ProcessName \
                       RequiredProbeCardType \
		       WaferList \
		       TestFileDependentParameters \
		       TestPlanName \
		       LimitFileName \
		       MddefFileName \
		       CurrentOCRState \
		       ProbeCardTypeFound \
		       TestBoardID \
		       DieTestList \
		       TestSpec \
		       CarrierID \
                       CompileErrorCode} {  

set msg "\
EVENT RecipeVerified {L \
  {L {A LotID}                       {A $LotID}} \
  {L {A PortID}                      {A $StartTestPortID}} \
  {L {A OperatorID}                  {A $OperatorID}} \
  {L {A PPExecName}                  {A $PPExecName}} \
  {L {A WaferSpecFileName}           {A $WaferSpecFileName}} \
  {L {A ProbeSpecFileName}           {A $ProbeSpecFileName}} \
  {L {A DieSpecFileName}             {A $DieSpecFileName}} \
  {L {A ProductID}                   {A $ProductID}} \
  {L {A ProcessName}                 {A $ProcessName}} \
  {L {A RequiredProbeCardType}       {A $RequiredProbeCardType}} \
  {L {A WaferList}                   {A $WaferList}} \
  {L {A TestFileDependentParameters} {A $TestFileDependentParameters}} \
  {L {A TestPlanName}                {A $TestPlanName}} \
  {L {A LimitFileName}               {A $LimitFileName}} \
  {L {A MddefFileName}               {A $MddefFileName}} \
  {L {A CurrentOCRState}             {A $CurrentOCRState}} \
  {L {A ProbeCardTypeFound}          {A $ProbeCardTypeFound}} \
  {L {A TestBoardID}                 {A $TestBoardID}} \
  {L {A DieTestList}                 {A $DieTestList}} \
  {L {A TestSpecFileName}            {A $TestSpec}} \
  {L {A PPBadCompileCode} {A \"$CompileErrorCode\"}} \
}"

return $msg
}


# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatLotStart { StartTestPortID \
		      LotID \
		      LotStartTime \
		      RetestWafers \
		      CurrentOCRState } {

set msg "\
EVENT LotStart  {L \
  {L {A PortID}           {A $StartTestPortID}} \
  {L {A LotID}            {A $LotID}} \
  {L {A LotStartTime}     {A $LotStartTime}} \
  {L {A LotEndTime}       {A 0}} \
  {L {A RetestWafers}     {A $RetestWafers}} \
  {L {A CurrentOCRState}  {A $CurrentOCRState}} \ 
}"
return $msg
}


# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatExtractProberRecipe { StartTestPortID \
                                 ProberRecipeFileName } {

set msg "\
EVENT ProberRecipeFileName  {L \
  {L {A PortID}           {A $StartTestPortID}} \
  {L {A ProberRecipeFileName} {A $ProberRecipeFileName}} \
}"
return $msg
}


# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatProberRecipe { StartTestPortID \
                          LotID \
                          ProberRecipeFileName } {

set msg "\
EVENT ProberRecipe  {L \
  {L {A PortID}               {A $StartTestPortID}} \
  {L {A LotID}                {A $LotID}} \
  {L {A ProberRecipeFileName} {A $ProberRecipeFileName}} \
}"
return $msg
}


# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatProberRecipeTune { StartTestPortID \
                          LotID \
                          ProberRecipeFileName } {

set msg "\
EVENT ProberRecipeTune  {L \
  {L {A PortID}               {A $StartTestPortID}} \
  {L {A LotID}                {A $LotID}} \
  {L {A ProberRecipeFileName} {A $ProberRecipeFileName}} \
}"
return $msg
}


# ******************************************************************
# Description:
#	SubLotSlotStartTime -> SubLotStartTime 01/10/11
#
#
#
# INPUTS:
#p
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatSubLotStart { StartTestPortID \
		         SubLotID \
                         WaferSlotUnderTest \
			 WaferSlotStartTime \
			 CurrentWaferResultFile \
			 DatalogConfig
			 CurrentOCRState} {

set msg "\
EVENT SubLotStart  {L \
  {L {A PortID}                 {A $StartTestPortID}} \
  {L {A SubLotID}               {A $SubLotID}} \	
  {L {A WaferSlotUnderTest}     {A $WaferSlotUnderTest}} \
  {L {A SubLotStartTime}        {A $WaferSlotStartTime}} \
  {L {A CurrentWaferResultFile} {A $CurrentWaferResultFile}} \
  {L {A DatalogConfig}          {A $DatalogConfig}} \
  {L {A CurrentOCRState}        {A $CurrentOCRState}} \
}"
return $msg
}


# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatDieStart { StartTestPortID \
                      CurrentDieFileName \
                      DiePosXUnderTest \
		      DiePosYUnderTest \
		      DieStartTime  } {

set msg "\
EVENT DieStart  {L \
  {L {A PortID}                 {A $StartTestPortID}} \
  {L {A CurrentDieFileName}     {A $CurrentDieFileName}} \
  {L {A DiePositionXUnderTest}  {A $DiePosXUnderTest}} \
  {L {A DiePositionYUnderTest}  {A $DiePosYUnderTest}} \
  {L {A DieStartTime}           {A $DieStartTime}} \
}"
return $msg
 
}

# ******************************************************************
# Description:
# 	LastDieEndTime -> DieEndTime 01/10/11
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************

proc formatDieEnd   { StartTestPortID \
                      ResultOfLastDie \
                      DieEndTime  } {

set msg "\
EVENT DieEnd  {L \
 {L {A PortID}                 {A $StartTestPortID}} \
 {L {A ResultOfLastDie}        {A $ResultOfLastDie}} \
 {L {A DieEndTime}         {A $DieEndTime}} \
}"
return $msg
}


# ******************************************************************
# Description:
#	SublotEndTime -> SubLotEndTime 01/10/11
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatSubLotComplete { StartTestPortID \
                            SublotEndTime \
			    ResultOfLastSublot} {

set msg "\
EVENT SubLotComplete  {L \
  {L {A PortID}              {A $StartTestPortID}} \
  {L {A SubLotEndTime}       {A $SublotEndTime}} \
  {L {A ResultOfLastSubLot}  {A $ResultOfLastSublot}} \
}"
return $msg
}


# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatPendingComplete { StartTestPortID \
                             PendingCompleteTime \
                             NextExecutionLevel \
                             NextExecutionRule } {

set msg "\
EVENT PendingComplete {L \
  {L {A PortID}               {A $StartTestPortID}} \
  {L {A PendingCompleteTime}  {A $PendingCompleteTime}} \
  {L {A ExecutionLevel}   {A $NextExecutionLevel}} \
  {L {A ExecuteAttribute}    {A $NextExecutionRule}} \
}"
return $msg
}


# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatLotComplete { StartTestPortID \
                         NextExecutionLevel \
                         NextExecutionRule \
                         LotEndTime } {

set msg "\
EVENT LotComplete {L \
  {L {A PortID}      {A $StartTestPortID}} \
  {L {A ExecutionLevel}   {A $NextExecutionLevel}} \
  {L {A ExecuteAttribute}    {A $NextExecutionRule}} \
  {L {A LotEndTime}  {A $LotEndTime}} \
}"
return $msg
}


# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatIdleNotReady { } {

set msg "EVENT IdleNotReady {L L}"

return $msg
}


# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatIdleReady { } {

set msg "EVENT IdleReady {L L}"

return $msg
}


#*******************************************************************
# Description:
#               
#
#
#
# INPUTS: NONE
#
# OUTPUTS: formatted message
#
#*******************************************************************
proc formatPPBadCompile { StartTestPortID CompileErrorCode } {

set msg " \
EVENT PPBadCompile  {L \
  {L {A PortID} {A $StartTestPortID}} \
  {L {A PPBadCompileCode} {A \"$CompileErrorCode\"}} \
}"
return $msg
}


# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatReset { } {

set msg "EVENT Reset  {L L}"

return $msg
}

 
# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatStopped {} {

set msg "EVENT Stopped  {L L}"

return $msg
}


#*******************************************************************
# Description:
#               
#
# INPUTS: NONE
#
# OUTPUTS: formatted message
#
#*******************************************************************
proc formatAborted { } {

set msg "EVENT Aborted   {L L}"

return $msg
}


# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatPJAbortStart { StartTestPortID } {

set msg "\
EVENT PJAbortStart {L \
  {L {A PortID}      {A $StartTestPortID}} \
}"
return $msg
}


# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatPJAborted { StartTestPortID } {

set msg "\
EVENT PJAborted {L \
  {L {A PortID}      {A $StartTestPortID}} \
}"
return $msg
}



# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatCJAborted { StartTestPortID } {

set msg "\
EVENT CJAborted {L \
  {L {A PortID}      {A $StartTestPortID}} \
}"
return $msg
}


# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatRequestStart { StartTestPortID} {

set msg "\
EVENT RequestStart {L \
  {L {A PortID}      {A $StartTestPortID}} \
}"
return $msg
}


# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatPJPauseRequest { StartTestPortID RequestReason RequestValue} {

set msg "\
EVENT PJPauseRequest {L \
  {L {A PortID}      {A $StartTestPortID}} \
  {L {A PJPauseReason}      {A $RequestReason}} \
  {L {A PJPauseValue}      {A $RequestValue}} \
}"
return $msg
}


# ******************************************************************
# Description:
#
#
#
#
# INPUTS:
#
# OUTPUTS: formatted message
#
# ******************************************************************
proc formatCJPauseRequest { StartTestPortID RequestReason RequestValue} {

set msg "\
EVENT CJPauseRequest {L \
  {L {A PortID}      {A $StartTestPortID}} \
  {L {A CJPauseReason}      {A $RequestReason}} \
  {L {A CJPauseValue}      {A $RequestValue}} \
}"
return $msg
}



#****************************************************e***************
# Description:
#               
#
# INPUTS: NONE
#
# OUTPUTS: formatted message
#
#*******************************************************************
proc formatPaused { } {

set msg "EVENT Paused {L L}"

return $msg
}


#*******************************************************************
# Description:
#               
#
# INPUTS: NONE
#
# OUTPUTS: formatted message
#
#*******************************************************************
proc formatResumed { } {

set msg "EVENT Resumed {L L}"

return $msg
}


#*******************************************************************
# Description:
#               
#
# INPUTS: NONE
#
# OUTPUTS: formatted message
#
#*******************************************************************
proc formatAlarmCleared { } {

set msg "EVENT AlarmCleared {L L}"

return $msg
}


#*******************************************************************
# Description:
#               
#
# INPUTS: NONE
#
# OUTPUTS: formatted message
#
#*******************************************************************
proc formatNewOcrState { CurrentOCRState } {

set msg "\
EVENT NEW-OCR-STATE  {L \
  {L {A CurrentOCRState}  {A $CurrentOCRState}} \ 
}"
return $msg
}


#*******************************************************************
# Description:
#               
#
#
#
# INPUTS: NONE
#
# OUTPUTS: formatted message
#
#*******************************************************************
proc formatLotCancel { PortID NextExecutionLevel NextExecutionRule CompileErrorCode} {

set msg " \
EVENT LotCancel  {L \
  {L {A PortID} {A $PortID}} \
  {L {A ExecutionLevel}   {A $NextExecutionLevel}} \
  {L {A ExecuteAttribute}    {A $NextExecutionRule}} \
  {L {A PPBadCompileCode} {A \"$CompileErrorCode\"}} \
}"
return $msg
}


proc formatLotFinish { PortID CompileErrorCode} {

set msg " \
EVENT LotFinish  {L \
  {L {A PortID} {A $PortID}} \
  {L {A PPBadCompileCode} {A \"$CompileErrorCode\"}} \
}"
return $msg
}

# ******************************************************************
# Description: Update VGEM Not List Type Variable 
#              and Send Event to the Host
#
# INPUTS: Ceid
#         VarName
#         VarData
# OUTPUTS: 
#
# ******************************************************************
proc formatUpdVar {  Ceid \
                       VarName \
                       VarData } {

set msg "\

EVENT DataUpdate  {L \
  {L {A ToHostCEID}   {A $Ceid}} \
  {L {A UpdVarName} {A \"$VarName\"}} \
  {L {A UpdVarData}  {A \"$VarData\"}} \
}"

return $msg
}


# ******************************************************************
# Description: Update VGEM List Type Variable 
#              and Send Event to the Host
#
# INPUTS: Ceid
#         VarName
#         VarData
# OUTPUTS: 
#
# ******************************************************************
proc formatUpdListVar {  Ceid \
                       VarName \
                       VarData } {

set msg "\

EVENT DataListUpdate  {L \
  {L {A ToHostCEID}   {A $Ceid}} \
  {L {A UpdVarName} {A \"$VarName\"}} \
  {L {A UpdVarData}  {A \"$VarData\"}} \
}"

return $msg
}


# ******************************************************************
# Description: Display User Line on LMP
#
# INPUTS: DispNth
#         DispLabel
#         DispValue
#         DispFgc
#         DispBgc
# OUTPUTS: 
#
# ******************************************************************
proc formatDispLine {  DispNth \
                       DispLabel \
                       DispValue \
                       DispFgc \
                       DispBgc } {

set msg "\

EVENT UpdateDisp  {L \
  {L {A DisplayLine}   {A $DispNth}} \
  {L {A DisplayLabel}  {A \"$DispLabel\"}} \
  {L {A DisplayValue}  {A \"$DispValue\"}} \
  {L {A DisplayBgc}  {A \"$DispBgc\"}} \
  {L {A DisplayFgc}  {A \"$DispFgc\"}} \
}"

return $msg
}

# ******************************************************************
# Description: Display VGEM Value on LMP
#
# INPUTS: DispNth
#         DispLabel
#         DispVar
#         DispFgc
#         DispBgc
# OUTPUTS: 
#
# ******************************************************************
proc formatDispVar  {  DispNth \
                       DispLabel \
                       DispVar \
                       DispFgc \
                       DispBgc } {

set msg "\

EVENT DispVar  {L \
  {L {A DisplayLine}   {A $DispNth}} \
  {L {A DisplayLabel}  {A \"$DispLabel\"}} \
  {L {A DisplayVariable}  {A \"$DispVar\"}} \
  {L {A DisplayBgc}  {A \"$DispBgc\"}} \
  {L {A DisplayFgc}  {A \"$DispFgc\"}} \
}"

return $msg
}

# ******************************************************************
# Description: Clear a line on LMP
#
# INPUTS: DispNth
#
# OUTPUTS: 
#
# ******************************************************************
proc formatClearLine { DispNth } {

set msg "\

EVENT ClearDisp  {L \
  {L {A DisplayLine}   {A $DispNth}} \
}"
return $msg
}


#proc formatDiagSuccess {  CEID \
#                          PortID \
#                          CarrierID } {
#
#set msg "\
#
#EVENT UpdateDisp  {L \
#  {L {A DisplayLine}   {A 1}} \
#  {L {A DisplayLabel}  {A \"Carrier ID\"}} \
#  {L {A DisplayValue}  {A $PortID}} \
#  {L {A DisplayBgc}  {A Red}} \
#  {L {A DisplayFgc}  {A Yellow}} \
#}"
#return $msg
#}
#
#*******************************************************************

proc GOINIT { } {

    mbx init GEMMBX
    mbx whenmsg GEM_IN {mbx put GEM_reply "//c 0"; mbx whenmsg again}
    mbx put GEM_OUT [formatReset]
    mbx put GEM_OUT [formatSpecsStarted 1 2 3 4 5]
}

proc GO0 { } {
    mbx put GEM_OUT [formatStartButtonPressed]
    puts "<press SELECT button on GEMHOST>"
}

proc GO1 {} {
    mbx put GEM_OUT [formatRecipeVerified]
    puts "<press START button on GEMHOST>"
}

proc GO2 {} {
    mbx put GEM_OUT [formatOnLotStart 1 2 3 4]
}
    
proc GO3 {} {
    mbx put GEM_OUT [formatOnWaferStart 1 2 3 4 5 6 7]
    mbx put GEM_OUT [formatOnDieStart 1 2 3 4 5 6 7 8]
    mbx put GEM_OUT [formatOnDieEnd 1 2 3 4 5 6 7 8]
    mbx put GEM_OUT [formatOnDieStart 1 2 3 4 5 6 7 8]
    mbx put GEM_OUT [formatOnDieEnd 1 2 3 4 5 6 7 8]
    mbx put GEM_OUT [formatOnWaferEnd 1 2 3 4 5 6 7]
}

proc GO4 {} {
    mbx put GEM_OUT [formatOnLotEnd 1 2 3 4]
    puts "<press STOP button on GEMHOST>"
}

proc GO5 {} {
    mbx put GEM_OUT [formatStopped]
}

proc GO_INIT { } {
    mbx init GEMMBX
}

proc GO_PPSELECT { } {
    mbx put GEM_IN [formatPPSelect 1 w d t p l r caid lotid\
				mondo watch prodid \
1,|2,|3,|4,|5,|6,|7,|8,|9,|10,|11,|12,|13,|14,|15,|16,|17,|18,|19,|20,|21,|22,|23,|24,|25,\
				testspec dietest ]
}

proc GO_PROBER { } {
    mbx put GEM_IN [formatProberStatus 1]
}

proc GO_START { } {
    mbx put GEM_IN [formatStart 1]
}
