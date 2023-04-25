/*---------------------------------------------------------------------
 * $Date: 2021/07/02 07:51:13 $             $ $
 *---------------------------------------------------------------------
 **********************************************************************
 *
 *                     MODULE  : facomcore.c
 *
 *---------------------------------------------------------------------
 *
 *        (c) Copyright Keysight Technologies, 2000,2015
 *
 *---------------------------------------------------------------------
 *
 *  CONTENTS: This is an example that shows how to embed Tcl
 *            and the dmh inside a c program.
 *
 *
 *
 *---------------------------------------------------------------------
 *
 * Summary of Features:
 *
 *  [ ] GUI                     [ ] MAN page
 *  [ ] Command Line            [ ] User Documentation
 *  [ ] User Procedure          [ ] User Training Material Available
 *  [ ] Test Function
 *  [ ] Report Formatter
 *  [ ] Data Bridge
 *
 * Development Information:
 *
 * DATE : Feb 27 2001 K.Nakano  LYNX Revision 0.1
 *
 **********************************************************************
 *---------------------------------------------------------------------
 *
 *
 *     
 *
 *
 **********************************************************************/
 
#include <time.h>
#include <string.h>
#include <SPECS.h>
#include <tcl.h>
#include "facomcore.h"

static Tcl_Interp *interp=NULL; 

static int read_message_from_host(void);
static int parse_reply_mailbox(char *hostreply);
static int parse_command_mailbox(char *hostcommand);
static int parse_parms_mailbox(void);
static int parse_parm_from_message(char *, char *);

static int parse_waferlist(char *, char **, char **);
static int parse_dietstlist(char *, char **, char **);

static int build_waferlist(int , char **, char **, char *);
static int build_dietstlist(int , char **, char **, char *);

static char waflistMode[2]="1";
static int print_msg(char *);
static int print_imsg(int);

#define CMD_LEN    4096    /* Length of Command */
#define LIST_LEN   1024    /* Length of WaferList */
#define LISTMLIB_LEN  2048    /* Length of VarList */
#define LISTTCO_LEN  4096    /* Length of VarList */
#define LISTVAR_LEN  4096    /* Length of VarList */
 
void print_tmesg(void)
{
  char *tmesg;
  FILE *fp;

  time_t ct=time(NULL);
  struct tm *lst=localtime(&ct);

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    if((fp=fopen("/usr/tmp/tcl_message.log","r"))==0) {
      return;
    }

  fclose(fp);
  }
  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    if((fp=fopen("/usr/tmp/tcl_message.log","a"))==0) {
      return;
    }
    tmesg=(char *)Tcl_GetVar(interp,"mesg",TCL_GLOBAL_ONLY) ;
    fprintf(fp, "%04d-%02d-%02d %02d:%02d:%02d <<<[%s]\n",
            1900+lst->tm_year, 1+lst->tm_mon, lst->tm_mday,
            lst->tm_hour, lst->tm_min, lst->tm_sec, tmesg);
    fclose(fp);
  }
}
 
int Tcl_AppInit( Tcl_Interp* interp )
{

  int status ;
  char * auto_path ;
  char * libdir ;
   
  char dmhlibpath[512] ;
  char command[256] ;
  const char *lockf = "/opt/SPECS/sys/tmp/pkey_lockf";

  status = Tcl_Init(interp) ;

  if (status != TCL_OK) {
    return TCL_ERROR ;
       
  }
    
 
  /* data hub messaging system */
    
  /* check first if the environment variable
     DMH_LIBRARY has been defined */
         
  if(getenv("DMH_LIBRARY") == NULL)
#ifdef __hpux
    strcpy(dmhlibpath,"/opt/SPECS_FA/dmh/lib/dmh83") ; 
#elif __linux
    strcpy(dmhlibpath,"/opt/SPECS_FA/dmh/lib/dmh84") ;
#endif
  else
    strcpy(dmhlibpath,getenv("DMH_LIBRARY")) ;
    
  Tcl_SetVar(interp, "dmh_library", dmhlibpath, TCL_GLOBAL_ONLY);
    
  /* add it to the auto_path so unknown Tcl procs are found */
  auto_path = (char *)Tcl_GetVar(interp, "auto_path", TCL_GLOBAL_ONLY|TCL_LEAVE_ERR_MSG);
    
  if ( !auto_path) return TCL_ERROR; 
    
  Tcl_VarEval(interp, "uplevel #0 {if { [lsearch -exact $auto_path {",
              dmhlibpath, "} ] < 0 } { lappend auto_path {", dmhlibpath,
              "} }}", (char *)NULL);
  strcpy(command,"package require dmh") ;
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: dmh package initialization failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return TCL_ERROR ;
  }

#ifdef __linux
  strcpy(command, "dmh_import");
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: dmh package initialization failed. dmh_import\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return TCL_ERROR ;
  } 
#endif

  Tcl_ResetResult(interp);
  if(access(lockf, 0) == 0){
      remove(lockf);
  }
  return TCL_OK;
   
}

/* EVENT StartInit */
int gemSendStartInit(void)
{
  char command[CMD_LEN] ;

/*
fprintf(stdout, "SendStartInit \n");
*/  
  
  strcpy(command,"Send_MSG GEM_OUT [formatStartInit]") ;
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatStartInit] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatStartInit]") ;
    Tcl_Eval(interp,command);
    print_tmesg();
  }
  return 0;
}


/* EVENT InitComplete */
int gemSendInitComplete(char *EquipSerialID, 
                        char *MDLN,
                        char *SOFTREV,
                        char *PCTypeFound,
                        char *TestBoardID,
                        char *Execlevel,
                        char *Execattrib)
{
  char command[CMD_LEN] ;
  STRING myEquipSerialID ;
  STRING myMDLN;
  STRING mySOFTREV;
  STRING myPCTypeFound;
  STRING myTestBoardID;
  STRING myExeclevel;
  STRING myExecattrib;
/*
fprintf(stdout, "SendInitComplete %s\n%s\n%s\n%s\n%s \n",
			EquipSerialID, MDLN, SOFTREV, PCTypeFound, TestBoardID);
*/  
  strcpy(myEquipSerialID, EquipSerialID);
  strcpy(myMDLN, MDLN);
  strcpy(mySOFTREV, SOFTREV);
  strcpy(myPCTypeFound, PCTypeFound);
  strcpy(myTestBoardID, TestBoardID);
  strcpy(myExeclevel, Execlevel);
  strcpy(myExecattrib, Execattrib);
  Tcl_SetVar(interp, "glob_EquipSerialID"   , myEquipSerialID  , TCL_GLOBAL_ONLY) ; 
  Tcl_SetVar(interp, "glob_MDLN"            , myMDLN           , TCL_GLOBAL_ONLY) ; 
  Tcl_SetVar(interp, "glob_SOFTREV"         , mySOFTREV        , TCL_GLOBAL_ONLY) ; 
  Tcl_SetVar(interp, "glob_PCTypeFound"     , myPCTypeFound    , TCL_GLOBAL_ONLY) ; 
  Tcl_SetVar(interp, "glob_TestBoardID"     , myTestBoardID    , TCL_GLOBAL_ONLY) ; 
  Tcl_SetVar(interp, "glob_Execlevel"     , myExeclevel    , TCL_GLOBAL_ONLY) ; 
  Tcl_SetVar(interp, "glob_Execattrib"     , myExecattrib    , TCL_GLOBAL_ONLY) ; 

  strcpy(command,"Send_MSG GEM_OUT [formatInitComplete $glob_EquipSerialID $glob_MDLN $glob_SOFTREV $glob_PCTypeFound $glob_TestBoardID $glob_Execlevel $glob_Execattrib]");  

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatInitComplete] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatInitComplete $glob_EquipSerialID $glob_MDLN $glob_SOFTREV $glob_PCTypeFound $glob_TestBoardID $glob_Execlevel $glob_Execattrib]");  
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}

void change_string(char *string1, char *string2, char *key1, char *key2)
{
        char mystring[LIST_LEN];
        char mykey1[1];
        char mykey2[1];
        int  i;

        strcpy(mystring,string1);
        strcpy(mykey1,key1);
        strcpy(mykey2,key2);

/*
        printf("mystring = %s\n",mystring);
        printf("mykey1   = %s\n",mykey1);
        printf("mykey2   = %s\n",mykey2);
*/

        i = 0;
        while(*string1++) {
                i++;
                if (mystring[i] == *mykey1) {
                        mystring[i] = *mykey2;
                }
        }
        strcpy(string2,mystring);
}


/* EVENT RecipeVerified */
int gemSendRecipeVerified(char *StartTestPID,
			  char *LotID,
                          char *OperatorID,
                          char *PPExecName,
                          char *WaferSpec,
                          char *ProbeSpec, 
                          char *DieSpec, 
                          char *ProductID, 
                          char *ProcessName, 
                          char *RequiredPCType,
                          char *WaferList,
                          char *TestFilePar,
                          char *TestPlanName,
                          char *LimitFile,
                          char *MddefFile,
                          char *CurrentOCRState,
                          char *PCTypeFound,
                          char *TestBoardID,
                          char *DieTestList,
                          char *TestSpec,
                          char *CarrierID,
                          char *BadCode)

{
  char command[CMD_LEN] ;
  STRING myStartTestPID ;
  STRING myOperatorID ;
  STRING myPPExecName ;
  STRING myWaferSpec ;
  STRING myProbeSpec ;
  STRING myDieSpec ;
  STRING myProductID ; 
  STRING myProcessName ; 
  STRING myRequiredPCType ;
  STRING myWaferList ;
  STRING myWaferList_org ;
  STRING myTestFilePar ;
  STRING myTestPlanName ;
  STRING myLimitFile ;
  STRING myMddefFile ;
  STRING myCurrentOCRState ;
  STRING myPCTypeFound ;
  STRING myTestBoardID ;
  STRING myDieTestList;
  STRING myDieTestList_org;
  STRING myTestSpec;
  STRING myCarrierID;
  STRING myLotID;
  STRING myBadCode;

/*
  fprintf(stdout, "SendRecipeVerified %s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s \n",
			StartTestPID, OperatorID, PPExecName, WaferSpec, ProbeSpec, DieSpec, ProductID, ProcessName,
			RequiredPCType, WaferList, TestFilePar, TestPlanName, LimitFile, MddefFile, CurrentOCRState, PCTypeFound, TestBoardID,
			DieTestList, TestSpec, CarrierID);
*/

  strcpy(myStartTestPID, StartTestPID) ;
  strcpy(myOperatorID, OperatorID) ;
  strcpy(myPPExecName, PPExecName) ;
  strcpy(myWaferSpec, WaferSpec) ;
  strcpy(myProbeSpec, ProbeSpec) ;
  strcpy(myDieSpec, DieSpec) ;
  strcpy(myProductID, ProductID) ; 
  strcpy(myProcessName, ProcessName) ; 
  strcpy(myRequiredPCType, RequiredPCType) ;
  strcpy(myWaferList_org, WaferList) ;
  change_string(myWaferList_org,myWaferList," ",",");
  strcpy(myTestFilePar, TestFilePar) ;
  strcpy(myTestPlanName, TestPlanName) ;
  strcpy(myLimitFile, LimitFile) ;
  strcpy(myMddefFile, MddefFile) ;
  strcpy(myCurrentOCRState, CurrentOCRState) ;
  strcpy(myPCTypeFound, PCTypeFound) ;
  strcpy(myTestBoardID, TestBoardID) ;
  strcpy(myDieTestList_org, DieTestList) ;
  change_string(myDieTestList_org,myDieTestList," ",",");
  strcpy(myTestSpec, TestSpec) ;
  strcpy(myCarrierID, CarrierID) ;
  strcpy(myLotID, LotID) ;
  strcpy(myBadCode, BadCode) ;

  Tcl_SetVar(interp, "glob_StartTestPID"   , myStartTestPID   , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_OperatorID"     , myOperatorID     , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_PPExecName"     , myPPExecName     , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_WaferSpec"      , myWaferSpec      , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_ProbeSpec"      , myProbeSpec      , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_DieSpec"        , myDieSpec        , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_ProductID"      , myProductID      , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_ProcessName"    , myProcessName    , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_RequiredPCType" , myRequiredPCType , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_WaferList"      , myWaferList      , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_TestFilePar"    , myTestFilePar    , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_TestPlanName"   , myTestPlanName   , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_LimitFile"      , myLimitFile      , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_MddefFile"      , myMddefFile      , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_CurrentOCRState"   , myCurrentOCRState   , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_PCTypeFound"    , myPCTypeFound    , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_TestBoardID"    , myTestBoardID    , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_DieTestList"    , myDieTestList    , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_TestSpec"       , myTestSpec       , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_CarrierID"      , myCarrierID      , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_LotID"          , myLotID          , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_BadCode"          , myBadCode          , TCL_GLOBAL_ONLY) ;

  strcpy(command, "Send_MSG GEM_OUT [formatRecipeVerified $glob_LotID $glob_StartTestPID $glob_OperatorID $glob_PPExecName $glob_WaferSpec $glob_ProbeSpec $glob_DieSpec $glob_ProductID $glob_ProcessName $glob_RequiredPCType $glob_WaferList $glob_TestFilePar $glob_TestPlanName $glob_LimitFile $glob_MddefFile $glob_CurrentOCRState $glob_PCTypeFound $glob_TestBoardID $glob_DieTestList $glob_TestSpec $glob_CarrierID $glob_BadCode]"); 

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatRecipeVerified] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command, "set mesg [formatRecipeVerified $glob_LotID $glob_StartTestPID $glob_OperatorID $glob_PPExecName $glob_WaferSpec $glob_ProbeSpec $glob_DieSpec $glob_ProductID $glob_ProcessName $glob_RequiredPCType $glob_WaferList $glob_TestFilePar $glob_TestPlanName $glob_LimitFile $glob_MddefFile $glob_CurrentOCRState $glob_PCTypeFound $glob_TestBoardID $glob_DieTestList $glob_TestSpec $glob_CarrierID $glob_BadCode]"); 

    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}

/* gemGetNowTime */
void gemGetNowTime(char *NowTime)
{

  time_t ct=time(NULL);
  struct tm *lst=localtime(&ct);

  sprintf(NowTime,"%4d%02d%02d%02d%02d%02d",
        1900+lst->tm_year,
        1+lst->tm_mon,
        lst->tm_mday,
        lst->tm_hour,
        lst->tm_min,
        lst->tm_sec);
}


/* EVENT LotStart */
int gemSendLotStart(char *StartTestPID,
                    char *LotID,
                    char *RetestWafers,
                    char *CurrentOCRState )
{
  char command[CMD_LEN] ; 
  STRING myStartTestPID ;
  STRING myLotID;
  char myRetestWafers[LIST_LEN] ;
  STRING myCurrentOCRState ;
  STRING myTime;

/*
fprintf(stdout, "SendLotStart %s\n%s\n%s\n%s\n",
			StartTestPID, LotID, RetestWafers, CurrentOCRState);
*/
  strcpy(myStartTestPID, StartTestPID);
  strcpy(myLotID, LotID) ;
  strcpy(myRetestWafers, RetestWafers);
  strcpy(myCurrentOCRState, CurrentOCRState);
  gemGetNowTime(myTime);

  Tcl_SetVar(interp, "glob_StartTestPID" , myStartTestPID  , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_LotID"        , myLotID         , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_RetestWafers" , myRetestWafers  , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_CurrentOCRState" , myCurrentOCRState  , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_StartTime"    , myTime          , TCL_GLOBAL_ONLY) ;

  strcpy(command, "Send_MSG GEM_OUT [formatLotStart $glob_StartTestPID $glob_LotID [clock seconds] $glob_RetestWafers $glob_CurrentOCRState ]"); 
/*
  strcpy(command, "Send_MSG GEM_OUT [formatLotStart $glob_StartTestPID $glob_LotID $glob_StartTime $glob_RetestWafers $glob_CurrentOCRState ]"); 
*/

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatLotStart] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command, "set mesg [formatLotStart $glob_StartTestPID $glob_LotID [clock seconds] $glob_RetestWafers $glob_CurrentOCRState ]"); 
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}                                       



/* EVEN ProberRecipe */
int gemSendProberRecipe(char *StartTestPID,
                        char *LotID,
                        char *ProberRecipe)
{
  char command[CMD_LEN] ;
  STRING myStartTestPID ;
  STRING myLotID;
  STRING myProberRecipe ;
  char *ttt;
/*
fprintf(stdout, "SendProberRecipe %s\n%s\n%s\n",
			StartTestPID, LotID, ProberRecipe );
*/

  strcpy(myStartTestPID, StartTestPID);
  strcpy(myLotID, LotID);
  strcpy(myProberRecipe, ProberRecipe);

  Tcl_SetVar(interp, "glob_StartTestPID" , myStartTestPID  , TCL_GLOBAL_ONLY) ; 
  Tcl_SetVar(interp, "glob_LotID"        , myLotID         , TCL_GLOBAL_ONLY) ; 
  Tcl_SetVar(interp, "glob_ProberRecipe" , myProberRecipe  , TCL_GLOBAL_ONLY) ; 

  strcpy(command,"Send_MSG GEM_OUT [formatProberRecipe $glob_StartTestPID $glob_LotID $glob_ProberRecipe ]");

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatProberRecipe] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatProberRecipe $glob_StartTestPID $glob_LotID $glob_ProberRecipe ]");
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}

/* EVEN ProberRecipeTune */
int gemSendProberRecipeTune(char *StartTestPID,
                        char *LotID,
                        char *ProberRecipe)
{
  char command[CMD_LEN] ;
  STRING myStartTestPID ;
  STRING myLotID;
  STRING myProberRecipe ;
  char *ttt;
/*
fprintf(stdout, "SendProberRecipeTune %s\n%s\n%s\n",
			StartTestPID, LotID, ProberRecipe );
*/

  strcpy(myStartTestPID, StartTestPID);
  strcpy(myLotID, LotID);
  strcpy(myProberRecipe, ProberRecipe);

  Tcl_SetVar(interp, "glob_StartTestPID" , myStartTestPID  , TCL_GLOBAL_ONLY) ; 
  Tcl_SetVar(interp, "glob_LotID"        , myLotID         , TCL_GLOBAL_ONLY) ; 
  Tcl_SetVar(interp, "glob_ProberRecipe" , myProberRecipe  , TCL_GLOBAL_ONLY) ; 

  strcpy(command,"Send_MSG GEM_OUT [formatProberRecipeTune $glob_StartTestPID $glob_LotID $glob_ProberRecipe ]");

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatProberRecipeTune] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatProberRecipeTune $glob_StartTestPID $glob_LotID $glob_ProberRecipe ]");
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}


/* EVEN ExtractProberRecipe */
int gemSendExtractProberRecipe(char *PortID, char *ProberRecipe)
{
  char command[CMD_LEN] ;
  STRING myPortID ;
  STRING myProberRecipe ;
  char *ttt;

  strcpy(myProberRecipe, ProberRecipe);
  strcpy(myPortID, PortID);

  Tcl_SetVar(interp, "glob_ProberRecipe" , myProberRecipe  , TCL_GLOBAL_ONLY) ; 
  Tcl_SetVar(interp, "glob_PortID" , myPortID  , TCL_GLOBAL_ONLY) ; 

  strcpy(command,"Send_MSG GEM_OUT [formatExtractProberRecipe $glob_PortID $glob_ProberRecipe ]");

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatExtractProberRecipe] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatExtractProberRecipe $glob_PortID $glob_ProberRecipe ]");
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}


/* EVENT SublotStart */
int gemSendSubLotStart(char *StartTestPID,
                       char *SubLotID,
                       char *WaferSlot,
                       char *CurrWaferResult,
                       char *DatalogConfig,
                       char *OCRState)
{
  char command[CMD_LEN] ;
  STRING myStartTestPID ;
  STRING mySubLotID ;
  STRING myWaferSlot ;
  STRING myCurrWaferResult ;
  STRING myDatalogConfig ;
  STRING myOCRState ;
  STRING myTime;
/*
fprintf(stdout, "SendSubLotStart %s\n%s\n%s\n%s\n%s\n%s\n",
			StartTestPID, SubLotID, WaferSlot, CurrWaferResult, DatalogConfig, OCRState);
*/

  strcpy(myStartTestPID, StartTestPID) ;
  strcpy(mySubLotID, SubLotID) ;
  strcpy(myWaferSlot, WaferSlot) ;
  strcpy(myCurrWaferResult, CurrWaferResult) ;
  strcpy(myDatalogConfig, DatalogConfig) ;
  strcpy(myOCRState, OCRState) ;
  gemGetNowTime(myTime);

  Tcl_SetVar(interp, "glob_StartTestPID"    , myStartTestPID    , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_SubLotID"        , mySubLotID        , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_WaferSlot"       , myWaferSlot       , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_CurrWaferResult" , myCurrWaferResult , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_DatalogConfig"   , myDatalogConfig   , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_OCRState"        , myOCRState   , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_StartTime"       , myTime            , TCL_GLOBAL_ONLY) ;

  strcpy(command,"Send_MSG GEM_OUT [formatSubLotStart $glob_StartTestPID $glob_SubLotID $glob_WaferSlot [clock seconds] $glob_CurrWaferResult $glob_DatalogConfig $glob_OCRState]"); 

/*
  strcpy(command,"Send_MSG GEM_OUT [formatSubLotStart $glob_StartTestPID $glob_SubLotID $glob_WaferSlot $glob_StartTime $glob_CurrWaferResult $glob_DatalogConfig $glob_OCRState]"); 
*/

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatSubLotStart] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatSubLotStart $glob_StartTestPID $glob_SubLotID $glob_WaferSlot [clock seconds] $glob_CurrWaferResult $glob_DatalogConfig $glob_OCRState]"); 
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}                                       


/* EVENT DieStart */
int gemSendDieStart(char *StartTestPID,
                    char *CurrDieFile,
                    char *DiePositionX,
                    char *DiePositionY)

{
  char command[CMD_LEN];
  STRING myStartTestPID ;
  STRING myCurrDieFile ;
  STRING myDiePositionX ;
  STRING myDiePositionY ;
  STRING myTime;
/*
fprintf(stdout, "SendDieStart %s\n%s\n%s\n%s\n",
			StartTestPID, CurrDieFile, DiePositionX, DiePositionY);
*/

  strcpy(myStartTestPID, StartTestPID) ;
  strcpy(myCurrDieFile,  CurrDieFile) ;
  strcpy(myDiePositionX, DiePositionX) ;
  strcpy(myDiePositionY, DiePositionY) ;
  gemGetNowTime(myTime);

  Tcl_SetVar(interp, "glob_StartTestPID"      , myStartTestPID    , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_CurrDieFile"       , myCurrDieFile     , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_DiePositionX"      , myDiePositionX    , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_DiePositionY"      , myDiePositionY    , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_StartTime"         , myTime            , TCL_GLOBAL_ONLY) ;

  strcpy(command,"Send_MSG GEM_OUT [formatDieStart $glob_StartTestPID $glob_CurrDieFile $glob_DiePositionX $glob_DiePositionY [clock seconds]]" );  

/*
  strcpy(command,"Send_MSG GEM_OUT [formatDieStart $glob_StartTestPID $glob_CurrDieFile $glob_DiePositionX $glob_DiePositionY $glob_StartTime]" );  
*/

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatDieStart] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatDieStart $glob_StartTestPID $glob_CurrDieFile $glob_DiePositionX $glob_DiePositionY [clock seconds]]" );  
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}                                       


/* EVENT DieEnd */
int gemSendDieEnd(char *StartTestPID,
                  char *ResultOfLastDie)

{
  char command[CMD_LEN];
  STRING myStartTestPID ;
  STRING myResultOfLastDie ;
  STRING myTime;
/*
fprintf(stdout, "SendDieEnd %s\n%s\n",
			StartTestPID, ResultOfLastDie);
*/

  strcpy(myStartTestPID, StartTestPID);
  strcpy(myResultOfLastDie ,ResultOfLastDie);
  gemGetNowTime(myTime);

  Tcl_SetVar(interp, "glob_StartTestPID"    , myStartTestPID    , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_ResultOfLastDie" , myResultOfLastDie , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_EndTime"         , myTime            , TCL_GLOBAL_ONLY) ;

  strcpy(command,"Send_MSG GEM_OUT [formatDieEnd $glob_StartTestPID $glob_ResultOfLastDie [clock seconds]]" ); 

/*
  strcpy(command,"Send_MSG GEM_OUT [formatDieEnd $glob_StartTestPID $glob_ResultOfLastDie $glob_EndTime]" ); 
*/

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatDieEnd] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatDieEnd $glob_StartTestPID $glob_ResultOfLastDie [clock seconds]]" ); 
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}                                       


/* EVENT SubLotComplete */
int gemSendSubLotComplete(char *StartTestPID,
                          char *ResultOfLastSublot)

{
  char command[CMD_LEN];
  STRING myStartTestPID ;
  STRING myResultOfLastSublot ;
  STRING myTime;
/*
fprintf(stdout, "SendSubLotComplete %s\n%s\n",
			StartTestPID, ResultOfLastSublot);
*/

  strcpy(myStartTestPID, StartTestPID);
  strcpy(myResultOfLastSublot ,ResultOfLastSublot);
  gemGetNowTime(myTime);

  Tcl_SetVar(interp, "glob_StartTestPID"        , myStartTestPID        , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_ResultOfLastSublot"  , myResultOfLastSublot  , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_EndTime"             , myTime                , TCL_GLOBAL_ONLY) ;

  strcpy(command,"Send_MSG GEM_OUT [formatSubLotComplete $glob_StartTestPID [clock seconds] $glob_ResultOfLastSublot]" ); 

/*
  strcpy(command,"Send_MSG GEM_OUT [formatSubLotComplete $glob_StartTestPID $glob_EndTime $glob_ResultOfLastSublot]" ); 
*/

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatSubLotComplete] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatSubLotComplete $glob_StartTestPID [clock seconds] $glob_ResultOfLastSublot]" ); 
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}                                       


/* EVENT PendingComplete */
int gemSendPendingComplete(char *StartTestPID ,char *ExecutionLevel ,char *ExecuteAttribute)

{
  char command[CMD_LEN];
  STRING myStartTestPID ,myNextExecutionLevel ,myNextExecutionRule;
  STRING myTime;
/*
fprintf(stdout, "SendPendingComplete %s\n",
			StartTestPID);
*/

  strcpy(myStartTestPID, StartTestPID);
  strcpy(myNextExecutionLevel, ExecutionLevel);
  strcpy(myNextExecutionRule, ExecuteAttribute);
  gemGetNowTime(myTime);

  Tcl_SetVar(interp, "glob_StartTestPID"   , myStartTestPID   , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_EndTime"        , myTime           , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_NextExecutionLevel"   , myNextExecutionLevel   , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_NextExecutionRule"   , myNextExecutionRule   , TCL_GLOBAL_ONLY) ;

  strcpy(command,"Send_MSG GEM_OUT [formatPendingComplete $glob_StartTestPID [clock seconds] $glob_NextExecutionLevel $glob_NextExecutionRule]") ;

/*
  strcpy(command,"Send_MSG GEM_OUT [formatPendingComplete $glob_StartTestPID $glob_EndTime ]") ;
*/

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatPendingComplete] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatPendingComplete $glob_StartTestPID [clock seconds] $glob_NextExecutionLevel $glob_NextExecutionRule]") ;
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}                                       


/* EVENT LotComplete */
int gemSendLotComplete(char *StartTestPID,char *Execlevel, char *Execattrib)

{
  char command[CMD_LEN];
  STRING myStartTestPID ;
  STRING myExeclevel ;
  STRING myExecattrib ;
  STRING myTime;
/*
fprintf(stdout, "SendLotComplete %s\n",
			StartTestPID);
*/

  strcpy(myStartTestPID, StartTestPID);
  strcpy(myExeclevel, Execlevel);
  strcpy(myExecattrib, Execattrib);
  gemGetNowTime(myTime);

  Tcl_SetVar(interp, "glob_StartTestPID"   , myStartTestPID   , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_Execlevel"   , myExeclevel   , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_Execattrib"   , myExecattrib   , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_EndTime"        , myTime           , TCL_GLOBAL_ONLY) ;

  strcpy(command,"Send_MSG GEM_OUT [formatLotComplete $glob_StartTestPID $glob_Execlevel $glob_Execattrib [clock seconds] ]") ;

/*
  strcpy(command,"Send_MSG GEM_OUT [formatLotComplete $glob_StartTestPID $glob_Execlevel $glob_Execattrib $glob_EndTime ]") ;
*/

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatLotComplete] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatLotComplete $glob_StartTestPID $glob_Execlevel $glob_Execattrib [clock seconds] ]") ;
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}                                       


/* EVENT PPBadCompile */
int gemSendPPBadCompile(char *StartTestPID, char *Status)

{
  char command[CMD_LEN];
  STRING myStartTestPID ;
  STRING myStatus ;
/*
fprintf(stdout, "SendPPBadCompile %s\n",
			StartTestPID);
*/

  strcpy(myStartTestPID, StartTestPID);
  strcpy(myStatus, Status);

  Tcl_SetVar(interp, "glob_StartTestPID"  , myStartTestPID  , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_Status"  , myStatus  , TCL_GLOBAL_ONLY) ;

  strcpy(command,"Send_MSG GEM_OUT [formatPPBadCompile $glob_StartTestPID $glob_Status]");

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatPPBadCompile] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatPPBadCompile $glob_StartTestPID $glob_Status]");
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}

/* EVENT PJPauseRequest */
int gemSendPJPauseRequest(char *PortID, char *RequestReason, char *RequestValue)

{
  char command[CMD_LEN];
  STRING myStartTestPortID;
  STRING myRequestReason ;
  STRING myRequestValue ;
/*
fprintf(stdout, "SendPJPauseRequest %s %s\n",
			RequestReason,RequestValue);
*/

  strcpy(myStartTestPortID, PortID);
  strcpy(myRequestReason, RequestReason);
  strcpy(myRequestValue, RequestValue);

  Tcl_SetVar(interp, "glob_StartTestPortID"  , myStartTestPortID  , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_RequestReason"  , myRequestReason  , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_RequestValue"  , myRequestValue  , TCL_GLOBAL_ONLY) ;

  strcpy(command,"Send_MSG GEM_OUT [formatPJPauseRequest $glob_StartTestPortID $glob_RequestReason $glob_RequestValue]");

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatPJPauseRequest] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatPJPauseRequest $glob_StartTestPortID $glob_RequestReason $glob_RequestValue]") ;
    Tcl_Eval(interp,command);
    print_tmesg();
  }

 return 0;
}                                       

/* EVENT RequestStart */
int gemSendRequestStart(char *PortID)

{
  char command[CMD_LEN];
  STRING myStartTestPortID;

  strcpy(myStartTestPortID, PortID);

  Tcl_SetVar(interp, "glob_StartTestPortID"  , myStartTestPortID  , TCL_GLOBAL_ONLY) ;

  strcpy(command,"Send_MSG GEM_OUT [formatRequestStart $glob_StartTestPortID]");

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatRequestStart] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatRequestStart $glob_StartTestPortID]") ;
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}                                       


/* EVENT CJPauseRequest */
int gemSendCJPauseRequest(char *PortID, char *RequestReason, char *RequestValue)

{
  char command[CMD_LEN];
  STRING myStartTestPortID;
  STRING myRequestReason ;
  STRING myRequestValue ;
/*
fprintf(stdout, "SendCJPauseRequest %s %s\n",
			RequestReason,RequestValue);
*/

  strcpy(myStartTestPortID, PortID);
  strcpy(myRequestReason, RequestReason);
  strcpy(myRequestValue, RequestValue);

  Tcl_SetVar(interp, "glob_StartTestPortID"  , myStartTestPortID  , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_RequestReason"  , myRequestReason  , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_RequestValue"  , myRequestValue  , TCL_GLOBAL_ONLY) ;

  strcpy(command,"Send_MSG GEM_OUT [formatCJPauseRequest $glob_StartTestPortID $glob_RequestReason $glob_RequestValue]");

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatCJPauseRequest] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatCJPauseRequest $glob_StartTestPortID $glob_RequestReason $glob_RequestValue]") ;
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}                                       

                                        

/* EVENT Recipe_Tune_OK */
int gemSendRecipe_Tune_OK(char* StartTestPID, char* BadCode)

{
  char command[CMD_LEN];
  STRING myStartTestPID ;
  STRING myBadCode ;

  strcpy(myStartTestPID, StartTestPID);
  strcpy(myBadCode, BadCode);

  Tcl_SetVar(interp, "glob_StartTestPID"  , myStartTestPID  , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_BadCode"  , myBadCode  , TCL_GLOBAL_ONLY) ;
/*
fprintf(stdout, "SendRecipe_Tune_OK\n");
*/

  strcpy(command,"Send_MSG GEM_OUT [formatRecipe_Tune_OK $glob_StartTestPID $glob_BadCode]");

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatRecipe_Tune_OK] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatRecipe_Tune_OK $glob_StartTestPID $glob_BadCode]") ;
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}                                       
                                        

/* EVENT Recipe_Tune_Failed */
int gemSendRecipe_Tune_Failed(char* StartTestPID,char* Status)

{
  char command[CMD_LEN];
  STRING myStartTestPID ;
  STRING myStatus ;

  strcpy(myStartTestPID, StartTestPID);
  strcpy(myStatus, Status);

  Tcl_SetVar(interp, "glob_StartTestPID"  , myStartTestPID  , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_Status"  , myStatus  , TCL_GLOBAL_ONLY) ;
/*
fprintf(stdout, "SendRecipe_Tune_Failed\n");
*/

  strcpy(command,"Send_MSG GEM_OUT [formatRecipe_Tune_Failed $glob_StartTestPID $glob_Status]");

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatRecipe_Tune_Failed] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatRecipe_Tune_Failed $glob_StartTestPID $glob_Status]") ;
    Tcl_Eval(interp,command);
    print_tmesg();
  }

 return 0;
}                                       


/* EVENT Reset */
int gemSendReset(void)
{
  char command[CMD_LEN] ;
/*
fprintf(stdout, "SendReset \n");
*/
  strcpy(command,"Send_MSG GEM_OUT [formatReset]") ;
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatReset] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatReset]") ;
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}                                       


/* EVENT Stopped */
int gemSendStopped(void)
{
  char command[CMD_LEN] ;
/*
fprintf(stdout, "SendStopped \n");
*/
  strcpy(command,"Send_MSG GEM_OUT [formatStopped]") ;
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatStopped] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatStopped]") ;
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}                                       


/* EVENT Stopped */
int gemSendAborted(void)
{
  char command[CMD_LEN] ;
/*
fprintf(stdout, "SendAborted \n");
*/
  strcpy(command,"Send_MSG GEM_OUT [formatAborted]") ;
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatAborted] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatAborted]") ;
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}                                       

/* EVENT PJAbortStart */
int gemSendPJAbortStart(char* PortID)
{
  char command[CMD_LEN] ;
  STRING myStartTestPortID;
  /*
  fprintf(stdout, "SendPJAbortStart \n");
  */
  strcpy(myStartTestPortID, PortID);

  Tcl_SetVar(interp, "glob_StartTestPortID"  , myStartTestPortID  , TCL_GLOBAL_ONLY) ;
  strcpy(command,"Send_MSG GEM_OUT [formatPJAbortStart $glob_StartTestPortID]") ;
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatPJAbortStart] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatPJAbortStart $glob_StartTestPortID]") ;
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}


/* EVENT PJAborted */
int gemSendPJAborted(char* PortID)
{
  char command[CMD_LEN] ;
  STRING myStartTestPortID;
/*
fprintf(stdout, "SendPJAborted \n");
*/
  strcpy(myStartTestPortID, PortID);

  Tcl_SetVar(interp, "glob_StartTestPortID"  , myStartTestPortID  , TCL_GLOBAL_ONLY) ;
  strcpy(command,"Send_MSG GEM_OUT [formatPJAborted $glob_StartTestPortID]") ;
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatPJAborted] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatPJAborted $glob_StartTestPortID]") ;
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}                                       


/* EVENT CJAborted */
int gemSendCJAborted(char* PortID)
{
  char command[CMD_LEN] ;
  STRING myStartTestPortID ;
/*
fprintf(stdout, "SendCJAborted \n");
*/
  strcpy(myStartTestPortID, PortID);

  Tcl_SetVar(interp, "glob_StartTestPortID"  , myStartTestPortID  , TCL_GLOBAL_ONLY) ;
  strcpy(command,"Send_MSG GEM_OUT [formatCJAborted $glob_StartTestPortID]") ;
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatCJAborted] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatCJAborted $glob_StartTestPortID]") ;
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}                                       


/* EVENT Paused */
int gemSendPaused(void)
{
  char command[CMD_LEN] ;
/*
fprintf(stdout, "SendPaused \n");
*/
  strcpy(command,"Send_MSG GEM_OUT [formatPaused]") ;
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatPaused] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatPaused]") ;
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}                                       


/* EVENT Resumed */
int gemSendResumed(void)
{
  char command[CMD_LEN] ;
/*
fprintf(stdout, "SendResumed \n");
*/
  strcpy(command,"Send_MSG GEM_OUT [formatResumed]") ;
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatResumed] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatResumed]") ;
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}                                       


/* EVENT AlarmCleared */
int gemSendAlarmCleared(void)
{
  char command[CMD_LEN] ;
  strcpy(command,"Send_MSG GEM_OUT [formatAlarmCleared]") ;
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatAlarmCleared] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatAlarmCleared]") ;
    Tcl_Eval(interp,command);
    print_tmesg();
  }

   return 0;
}                                       

/**********************************************************************
*
* EVENT FORWARD From SPECS To HOST
*
**********************************************************************/

int gemSendUpdVar(char *Ceid, char *VarName, char *VarData)
{
  char command[CMD_LEN] ;
  STRING myCeid ;
  STRING myVarName ;
  STRING myVarData ;


  /*
  fprintf(stdout, "SendUpdVar:\n %s\n %s\n %s\n",
			Ceid, VarName, VarData);
  */


  strcpy(myCeid,    Ceid);
  strcpy(myVarName, VarName);
  strcpy(myVarData, VarData);

  Tcl_SetVar(interp, "glob_Ceid",    myCeid     , TCL_GLOBAL_ONLY) ; 
  Tcl_SetVar(interp, "glob_VarName",  myVarName   , TCL_GLOBAL_ONLY) ; 
  Tcl_SetVar(interp, "glob_VarData",  myVarData   , TCL_GLOBAL_ONLY) ;

  strcpy(command,"Send_MSG GEM_OUT [formatUpdVar $glob_Ceid $glob_VarName $glob_VarData]");

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatUpdVar] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatUpdVar $glob_Ceid $glob_VarName $glob_VarData]");
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}

int gemSendUpdListVar(char *Ceid, char *VarName, char *VarNum, char **VarData)
{
  char command[CMD_LEN] ;
  char VarList_org[LISTVAR_LEN];
  STRING myCeid ;
  STRING myVarName ;
  STRING myVarData ;
  int  i, dnum;


  
  fprintf(stdout, "SendUpdListVar:\n %s\n %s\n %s\n",
			Ceid, VarName, VarNum);
 

  strcpy(myCeid,    Ceid);
  strcpy(myVarName, VarName);
  
  dnum=atoi(VarNum);
  if (dnum > 0) {
    sprintf(VarList_org,"{L ");
    for(i=0;i<dnum;i++) {
      strcat(VarList_org,"{A ");
      strcat(VarList_org,VarData[i]);
      if(i<dnum-1) {
        strcat(VarList_org,"} ");
      } 
      else {
        strcat(VarList_org,"}}");
      }
    }
  } else {
    sprintf(VarList_org,"{}");
  }
  fprintf(stdout, "Vardata:\n %s\n",VarList_org);

  Tcl_SetVar(interp, "glob_Ceid",    myCeid     , TCL_GLOBAL_ONLY) ; 
  Tcl_SetVar(interp, "glob_VarName",  myVarName   , TCL_GLOBAL_ONLY) ; 
  Tcl_SetVar(interp, "glob_VarData",  VarList_org   , TCL_GLOBAL_ONLY) ;

  strcpy(command,"Send_MSG GEM_OUT [formatUpdListVar $glob_Ceid $glob_VarName $glob_VarData]");

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatUpdListVar] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatUpdListVar $glob_Ceid $glob_VarName $glob_VarData]");
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}


/**********************************************************************
*
* User String & VGEM Variables Displayment on LMP 
*
**********************************************************************/


int gemSendDispLine(char *LineNth, char *DispLabel, char *DispValue, char *DispFgc, char *DispBgc)
{
  char command[CMD_LEN] ;
  STRING myLineNth ;
  STRING myDispLabel ;
  STRING myDispValue ;
  STRING myDispFgc ;
  STRING myDispBgc ;


  /*
  fprintf(stdout, "SendDispLine %s\n%s\n%s\n%s\n%s\n",
			LineNth, DispLabel, DispValue, DispFgc, DispBgc );
  */


  strcpy(myLineNth,   LineNth);
  strcpy(myDispLabel, DispLabel);
  strcpy(myDispValue, DispValue);
  strcpy(myDispFgc,   DispFgc);
  strcpy(myDispBgc,   DispBgc);

  Tcl_SetVar(interp, "glob_LineNth",    myLineNth     , TCL_GLOBAL_ONLY) ; 
  Tcl_SetVar(interp, "glob_DispLabel",  myDispLabel   , TCL_GLOBAL_ONLY) ; 
  Tcl_SetVar(interp, "glob_DispValue",  myDispValue   , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_DispFgc",    myDispFgc     , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_DispBgc",    myDispBgc     , TCL_GLOBAL_ONLY) ;

  strcpy(command,"Send_MSG GEM_OUT [formatDispLine $glob_LineNth $glob_DispLabel $glob_DispValue $glob_DispFgc $glob_DispBgc]");

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatDispLine] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatDispLine $glob_LineNth $glob_DispLabel $glob_DispValue $glob_DispFgc $glob_DispBgc]");
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}

int gemSendDispVar(char *LineNth, char *DispLabel, char *DispVar, char *DispFgc, char *DispBgc)
{
  char command[CMD_LEN] ;
  STRING myLineNth ;
  STRING myDispLabel ;
  STRING myDispVar ;
  STRING myDispFgc ;
  STRING myDispBgc ;


  /*
  fprintf(stdout, "SendDispLineess %s\n%s\n%s\n%s\n%s\n",
			LineNth, DispLabel, DispVar, DispFgc, DispBgc );
  */


  strcpy(myLineNth,   LineNth);
  strcpy(myDispLabel, DispLabel);
  strcpy(myDispVar,   DispVar);
  strcpy(myDispFgc,   DispFgc);
  strcpy(myDispBgc,   DispBgc);

  Tcl_SetVar(interp, "glob_LineNth",    myLineNth     , TCL_GLOBAL_ONLY) ; 
  Tcl_SetVar(interp, "glob_DispLabel",  myDispLabel   , TCL_GLOBAL_ONLY) ; 
  Tcl_SetVar(interp, "glob_DispVar",    myDispVar     , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_DispFgc",    myDispFgc     , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_DispBgc",    myDispBgc     , TCL_GLOBAL_ONLY) ;

  strcpy(command,"Send_MSG GEM_OUT [formatDispVar $glob_LineNth $glob_DispLabel $glob_DispVar $glob_DispFgc $glob_DispBgc]");

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatDispVar] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatDispVar $glob_LineNth $glob_DispLabel $glob_DispVar $glob_DispFgc $glob_DispBgc]");
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}


int gemSendClearLine(char *LineNth)
{
  char command[CMD_LEN] ;
  STRING myLineNth ;
/*
fprintf(stdout, "SendClearLine %s\n", LineNth );
*/

  strcpy(myLineNth,   LineNth);

  Tcl_SetVar(interp, "glob_LineNth",    myLineNth     , TCL_GLOBAL_ONLY) ; 

  strcpy(command,"Send_MSG GEM_OUT [formatClearLine $glob_LineNth]");

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatClearLine] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatClearLine $glob_LineNth]");
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}




/* EVEN ProberRecipeTune */

/* ALARM */
int gemSendAlarm(char *Alarm_txt, char *Alarm_id, char *ErrorMsg)
{
  STRING myAlarm_txt;
  STRING myAlarm_id;
  STRING myErrorMsg;
  char command[CMD_LEN];

/*
fprintf(stdout, "SendAlarm %s\n%s\n%s\n", 
		Alarm_txt, Alarm_id, ErrorMsg);
*/

  strcpy(myAlarm_txt,Alarm_txt);
  strcpy(myAlarm_id,Alarm_id);
  strcpy(myErrorMsg,ErrorMsg);

  Tcl_SetVar(interp, "glob_Alarmtxt" , myAlarm_txt , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_Alarmid"  , myAlarm_id  , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_ErrorMsg" , myErrorMsg  , TCL_GLOBAL_ONLY) ;

  strcpy(command,"Send_MSG GEM_OUT [formatAlarm $glob_Alarmtxt $glob_Alarmid $glob_ErrorMsg]");
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatAlarm] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatAlarm $glob_Alarmtxt $glob_Alarmid $glob_ErrorMsg]");
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}


/* EVENT SetOcr */
int gemSendSetOcrMode(char *CurrentOCRState )
{
  char command[CMD_LEN] ; 
  STRING myCurrentOCRState ;

/*
fprintf(stdout, "SendSetOcrMode %s\n",
		CurrentOCRState);
*/

  strcpy(myCurrentOCRState, CurrentOCRState);

  Tcl_SetVar(interp, "glob_CurrentOCRState" , myCurrentOCRState  , TCL_GLOBAL_ONLY) ;

  strcpy(command, "Send_MSG GEM_OUT [formatNewOcrState $glob_CurrentOCRState ]"); 

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatNewOcrState] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }
  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command, "set mesg [formatNewOcrState $glob_CurrentOCRState ]"); 
    Tcl_Eval(interp,command);
    print_tmesg(); 
  }

  return 0;
}                                       

/* EVENT Idleready */
int gemSendIdleready(void)

{
  char command[CMD_LEN];

  strcpy(command,"Send_MSG GEM_OUT [formatIdleReady]");

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatIdleReady] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatIdleReady]") ;
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}                                       

/* EVENT Idlenotready */
int gemSendIdlenotready(void)

{
  char command[CMD_LEN];

  strcpy(command,"Send_MSG GEM_OUT [formatIdleNotReady]");

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatIdleNotReady] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatIdleNotReady]") ;
    Tcl_Eval(interp,command);
    print_tmesg();
  }

 return 0;
}                                       



                                        

int gemInit(void)
{
  char command[CMD_LEN] ;
  FILE *fp;
   
  time_t ct=time(NULL);
  struct tm *lst=localtime(&ct);

  if(interp == NULL) {
      interp = Tcl_CreateInterp();

      if(Tcl_AppInit(interp) == TCL_ERROR) {
          fprintf(stderr,"\n***ERROR: Tcl init failed\n");
          return -1;
      }

      if(getenv("SPECS_FA_PATH") == NULL)
          sprintf(command, "source /opt/SPECS_FA/fapt/facomcore/testermsg.tcl");
      else
          sprintf(command, "source %s/fapt/facomcore/testermsg.tcl", getenv("SPECS_FA_PATH"));

      if(Tcl_Eval(interp,command) == TCL_ERROR) {
          fprintf(stderr,"\n***ERROR: source testermsg.tcl failed\n");
          fprintf(stderr,"%s\n", interp->result);
          return -1;
      }
  }
 
  strcpy(command,"mbx init GEMMBX") ;
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: mbx init GEMMBX failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 

  if (access("/var/opt/SPECS/log/prober.log", 0)==0) {
    fp=fopen("/var/opt/SPECS/log/prober.log", "r");

    if (fp!=0) {
        fclose(fp);
        fp=fopen("/var/opt/SPECS/log/prober.log", "a");
        fprintf(fp, "%04d-%02d-%02d %02d:%02d:%02d [Init SGI]\n",
                1900+lst->tm_year, 1+lst->tm_mon, lst->tm_mday,
                lst->tm_hour, lst->tm_min, lst->tm_sec);
        fclose(fp);
    }
  }

  return 0 ;
}


/* EVENT LotCancel */
int gemSendLotCancel(char *PortID,
                     char *Execlevel,
                     char *Execattrib,
                     char *BadCode)

{
  char command[CMD_LEN];
  STRING myPortID ;
  STRING myExeclevel ;
  STRING myExecattrib ;
  STRING myBadCode ;

/*
fprintf(stdout, "SendLotCancel %s\n",
		PortID);
*/

  strcpy(myPortID, PortID);
  strcpy(myExeclevel, Execlevel);
  strcpy(myExecattrib, Execattrib);
  strcpy(myBadCode, BadCode);

  Tcl_SetVar(interp, "glob_PortID"  , myPortID  , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_Execlevel"  , myExeclevel  , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_Execattrib"  , myExecattrib  , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_BadCode"  , myBadCode  , TCL_GLOBAL_ONLY) ;

  strcpy(command,"Send_MSG GEM_OUT [formatLotCancel $glob_PortID $glob_Execlevel $glob_Execattrib $glob_BadCode]");

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatLotCancel] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }

  if (access("/usr/tmp/tcl_message.log", 0)==0) {
    strcpy(command,"set mesg [formatLotCancel $glob_PortID $glob_Execlevel $glob_Execattrib $glob_BadCode]");
    Tcl_Eval(interp,command);
    print_tmesg();
  }

  return 0;
}

/* EVENT LotFinish */
int gemSendLotFinish(char *PortID, char *BadCode)

{
  char command[CMD_LEN];
  STRING myPortID ;
  STRING myBadCode ;

/*
fprintf(stdout, "SendLotFinish %s\n",
		PortID);
*/

  strcpy(myPortID, PortID);
  strcpy(myBadCode, BadCode);

  Tcl_SetVar(interp, "glob_PortID"  , myPortID  , TCL_GLOBAL_ONLY) ;
  Tcl_SetVar(interp, "glob_BadCode"  , myBadCode  , TCL_GLOBAL_ONLY) ;

  strcpy(command,"Send_MSG GEM_OUT [formatLotFinish $glob_PortID $glob_BadCode]");

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [formatLotFinish] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }
  return 0;
}

/***************************************************************************/
/*  gemMsgCount                                                            */
/*                    Routine used to determin if messages are in          */
/*                    mailbox.                                             */
/*                                                                         */
/*  returns:  count of messages in GEM_IN mailbox                          */
/***************************************************************************/

int gemMsgCount(void)
{
  char command[CMD_LEN] ;
  char *msgcount;
  int msg_count;

  strcpy(command,"set Tcl_msgcount [mbx count GEM_IN ]");
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [gemMsgCount] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 
  strcpy(command,"set Tcl_count [lindex $Tcl_msgcount 2] ");
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [gemMsgCount] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 
  msgcount = (char *)Tcl_GetVar(interp,"Tcl_count",TCL_GLOBAL_ONLY) ;
  if( msgcount == NULL) {
    fprintf(stderr,"\n***ERROR: Tcl_GetVar in gemMsgCount failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 
  msg_count = atoi(msgcount) ;
  return msg_count;
}   /*---  Endofo gemMsgCount ---*/

/***************************************************************************/
/*  gemCount                                                               */
/*                    Routine used to determin if messages are in          */
/*                    mailbox.                                             */
/*                                                                         */
/*  returns:  count of messages in mailbox                                 */
/***************************************************************************/

int gemCount(char *rplymbx)
{
  char command[CMD_LEN] ;
  char *msgcount;
  int msg_count;

  strcpy(command,"set Tcl_msgcount [mbx count ");
  strcat(command,rplymbx);
  strcat(command,"]"); 

  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: message count failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 
  strcpy(command,"set Tcl_count [lindex $Tcl_msgcount 2] ");
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [gemCount] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 
  msgcount = (char *)Tcl_GetVar(interp,"Tcl_count",TCL_GLOBAL_ONLY) ;
  if( msgcount == NULL) {
    fprintf(stderr,"\n***ERROR: Tcl_GetVar in gemCount failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 
  msg_count = atoi(msgcount) ;
  return msg_count;
}   /*---  Endofo gemMsgCount ---*/



/***************************************************************************/
/*  gemReplyOK                                                             */
/*                    Routine used to send command acknowledgement         */
/*                    to the secsgem interface process.  This              */
/*                    acknowledgement is used when command is OK.          */
/*                                                                         */
/***************************************************************************/

int gemReplyOK(char *rplymbx, double timeout)
{

  char command[CMD_LEN] ;
  int pending;
  time_t start_t=time(NULL);
  double delay_t;
  FILE *fp;

  time_t ct=time(NULL);
  struct tm *lst=localtime(&ct);

  strcpy(command,"set Tcl_hostresponse [mbx put ");
  strcat(command,rplymbx);
  strcat(command," \"//c 0 \"]"); 
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [message ack] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    if (access("/var/opt/SPECS/log/prober.log", 0)==0) {
      fp=fopen("/var/opt/SPECS/log/prober.log", "r");
      if (fp!=0) {
          fclose(fp);
          fp=fopen("/var/opt/SPECS/log/prober.log", "a");
          fprintf(fp, "\n%04d-%02d-%02d %02d:%02d:%02d ***ERROR: Send_MSG [message ack] failed\n",
                  1900+lst->tm_year, 1+lst->tm_mon, lst->tm_mday,
                  lst->tm_hour, lst->tm_min, lst->tm_sec);
          fclose(fp);
      }
  }
    return -1; 
  } 
        
  for (;;)  {
    pending=gemCount(rplymbx);
    print_imsg(pending);          /*****  for debug *****/
    if (pending < 1) break;
    delay_t = time(NULL)-start_t;
    if (delay_t > timeout) return -1;
    sleep(1);
  }   

  if (access("/var/opt/SPECS/log/prober.log", 0)==0) {
    fp=fopen("/var/opt/SPECS/log/prober.log", "r");
    if (fp!=0) {
        fclose(fp);
        fp=fopen("/var/opt/SPECS/log/prober.log", "a");
        fprintf(fp, "%04d-%02d-%02d %02d:%02d:%02d [host<---ACK]\n",
                1900+lst->tm_year, 1+lst->tm_mon, lst->tm_mday,
                lst->tm_hour, lst->tm_min, lst->tm_sec);
        fclose(fp);
    }
  }

  return 0;
}  /*--- End of gemReplyOK ---*/

/***************************************************************************/
/*  gemReplyNotOK                                                          */
/*                    Routine used to send command acknowledgement         */
/*                    to the secsgem interface process.  This              */
/*                    acknowledgement is used when command is not OK.      */
/*                                                                         */
/***************************************************************************/

int gemReplyNotOK(char *rplymbx)
{

  char command[CMD_LEN] ;
  FILE *fp;

  time_t ct=time(NULL);
  struct tm *lst=localtime(&ct);

  strcpy(command,"set Tcl_hostresponse [mbx put ");
  strcat(command,rplymbx);
  strcat(command," \"//c 1 \"]"); 
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [message nack] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 

  if (access("/var/opt/SPECS/log/prober.log", 0)==0) {
    fp=fopen("/var/opt/SPECS/log/prober.log", "r");
    if (fp!=0) {
        fclose(fp);
        fp=fopen("/var/opt/SPECS/log/prober.log", "a");
        fprintf(fp, "%04d-%02d-%02d %02d:%02d:%02d [host<---NACK]\n",
                1900+lst->tm_year, 1+lst->tm_mon, lst->tm_mday,
                lst->tm_hour, lst->tm_min, lst->tm_sec);
        fclose(fp);
    }
  }

  return 0;
}  /*--- End of gemReplyNotOK ---*/


/*************************************************************************/
/* gemGetParam */
/*************************************************************************/
int gemGetParam(char *hosttoken, int line)

{
  char command[CMD_LEN];
  char *mytoken;
  FILE *fp;
  
  /* Modified back to original code by Masa Feb/10 */
  sprintf(command,"set glob_LotID [lindex [lindex [lindex $Tcl_hostparameters %d] 2] 1]",line);
  /* sprintf(command,"set glob_LotID [lindex [lindex [lindex $Tcl_hostparameters %d] 2] 1]",line+2); modified */
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Tcl_Eval in gemGetParam failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1;
  }

  mytoken = (char *)Tcl_GetVar(interp,"glob_LotID",TCL_GLOBAL_ONLY) ;
  if( mytoken == NULL) {
    fprintf(stderr,"\n***ERROR: Tcl_GetVar in gemGetParam failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }

  strcpy(hosttoken, mytoken);
  return 0;
}


/*************************************************************************/
/* gemGetItem */
/*************************************************************************/
int gemGetItem(char *itemname)

{
  int i;
  int line;
  char myitemname[128];
  char *mytoken;
  char command[CMD_LEN];
  FILE *fp;
  
  strcpy(myitemname,itemname);
  for( i=1; i<=20; i++) {
    
    /* Move back to the original code by Masa Feb/10 */
    sprintf(command,"set glob_LotID [lindex [lindex [lindex $Tcl_hostparameters %d] 1] 1]",i); 
    /* sprintf(command,"set glob_LotID [lindex [lindex [lindex $Tcl_hostparameters %d] 1] 1]",i+2);  modified */
    if(Tcl_Eval(interp,command) == TCL_ERROR) {
      fprintf(stderr,"\n***ERROR: Tcl_Eval n gemGetItem failed\n") ;
      fprintf(stderr,"%s\n", interp->result) ; 
      return -1;
    }
    mytoken = (char *)Tcl_GetVar(interp,"glob_LotID",TCL_GLOBAL_ONLY) ;
    if( mytoken == NULL) {
      fprintf(stderr,"\n***ERROR: Tcl_GetVar in gemGetItem failed\n") ;
      fprintf(stderr,"%s\n", interp->result) ;
      return -1;
    }
    if (strcmp(mytoken, myitemname)==0) {
      line = i;
      return line;
    }
  }
  return -1;
}


void gemReadPPSelectList(char *FileName, int number, char *ItemName)
{
        STRING RecipeName;
        STRING buffer;
        char snum[16];
        FILE *fp;
        char *Token1,*Token2;
        char *fred;
        int  slen;
        int  i;               /* Increment for lines by Masa (Feb/10) */

        sprintf(ItemName,"");
        sprintf(snum,"%d",number);
        strcpy(RecipeName,FileName);
        if ((fp = fopen(RecipeName,"r")) == 0) {
                strcpy(ItemName,"Error");
                return;
        }

        /********** modified by Masa Feb/10 **************************/ 
        i=0; 
          while (fgets(buffer,256,fp) != NULL) {        /* Read one line */
            if (buffer[0]!='#') {               /* Skip comment line */
                i++;                            /* Start at 1 */
                fred=(char *)strtok(buffer," ");/* Delete space */
                Token1=(char *)strtok(fred,",");/* Extract number */
                if (strcmp(Token1, snum)==0) {  /* Item is found */
                    strcpy(ItemName,(char *)strtok(NULL,"\n")); /* Copy name */ 
                }
            }
        }
        /********** modified by Masa Feb/10 **************************/ 

#if 0
        while (fgets(buffer,256,fp) != NULL) {
                Token1=strtok(buffer,",");
                fred=Token1;
                while (*fred==' ') fred++;
                Token1=fred;
                slen=strlen(Token1);
                if (slen>1) {
                        fred=fred+slen;
                        fred--;
                        while (*fred==' ') fred--;
                        fred++;
                        *fred='\0';
                }

                Token2=strtok(NULL,",");
                fred=Token2;
                while (*fred==' ') fred++;
                Token2=fred;
                slen=strlen(Token2);
                if (slen>1) {
                        fred=fred+slen;
                        fred--;
                        while (*fred==' ' || *fred=='\n') fred--;
                        fred++;
                        *fred='\0';
                }
                if (strcmp(Token1,snum)==0) {
                        strcpy(ItemName,Token2);
                        break;
                }
        }
#endif
        fclose(fp);
        return;
}

/*************************************************************************/
/*  gemUpdVar                                                            */
/*       Update VGEM Non List Type Variable                              */
/*                                                                       */
/*************************************************************************/
int gemUpdVar(char *Ceid, char *VarName, char *VarData, int *Status)
{

  *Status=-1;
  *Status=gemSendUpdVar(Ceid,VarName,VarData);
}
  
/*************************************************************************/
/*  gemUpdListVar                                                        */
/*       Update VGEM List Type Variable                                  */
/*                                                                       */
/*************************************************************************/
int gemUpdListVar(char *Ceid, char *VarName, char *VarNum, char **VarData, int *Status)
{

  *Status=-1;
  *Status=gemSendUpdListVar(Ceid,VarName,VarNum,VarData);
}
  
/*************************************************************************/
/*  gemLmpDisp                                                           */
/*       LMP Displayment update command to VGEM                          */
/*                                                                       */
/*************************************************************************/
int gemLmpDisp(char *event, char *Lnth, char *Dlabel, char *Dval, char *Dfgc, char *Dbgc, int *Status)
{
  
  int i,j;
  int len;
  char label[256];
  char value[256];

  *Status=-1;
  if (strcmp(event,"DISPLINE")==0)  {
        len=strlen(Dlabel);
        j=0;
        for(i=0;i<len;i++) {
          if(Dlabel[i] != '\"' && Dlabel[i] != '\'' && Dlabel[i] != '{' && Dlabel[i] != '}') {
            label[j]=Dlabel[i];
            j++;
          }
        }
        label[j]='\0';
        len=strlen(Dval);
        j=0;
        for(i=0;i<len;i++) {
          if(Dval[i] != '\"' && Dval[i] != '\'' && Dval[i] != '{' && Dval[i] != '}') {
            value[j]=Dval[i];
            j++;
          }
        }
        value[j]='\0';
 	*Status=gemSendDispLine(Lnth,label,value,Dfgc,Dbgc);
  }
  else if (strcmp(event,"DISPVAR")==0)  {
        len=strlen(Dlabel);
        j=0;
        for(i=0;i<len;i++) {
          if(Dlabel[i] != '\"' && Dlabel[i] != '\'' && Dlabel[i] != '{' && Dlabel[i] != '}') {
            label[j]=Dlabel[i];
            j++;
          }
        }
        label[j]='\0';
 	*Status=gemSendDispVar(Lnth,label,Dval,Dfgc,Dbgc);
  }
  else if (strcmp(event,"CLEARLINE")==0)  {
 	*Status=gemSendClearLine(Lnth);
  }
  return 0;	
}

/*************************************************************************/
/*  gemSendEvent                                                         */
/*                  Routine used to send command to host                 */
/*                                                                       */
/*************************************************************************/
int gemSendEvent(char *event,
		 char **parms,
		 int *status)
{
  int  i;
  char WaferList_org[LIST_LEN];
  char DieTest_org[LIST_LEN];
  STRING	Die,Tst;
  FILE *fp;

  time_t ct=time(NULL);
  struct tm *lst=localtime(&ct);

  if (access("/var/opt/SPECS/log/prober.log", 0)==0) {
    fp=fopen("/var/opt/SPECS/log/prober.log", "r");
    if (fp!=0) {
        fclose(fp);
        fp=fopen("/var/opt/SPECS/log/prober.log", "a");
        fprintf(fp, "%04d-%02d-%02d %02d:%02d:%02d [host<---EVENT %s]\n",
                1900+lst->tm_year, 1+lst->tm_mon, lst->tm_mday,
                lst->tm_hour, lst->tm_min, lst->tm_sec, event);
        fclose(fp);
    }
  }
  
  *status=-1;
  /*=========================================================================*/
  /* EVENT DIEEND */
  /*=========================================================================*/
  if (strcmp(event,"DIEEND")==0)  {
 	*status=gemSendDieEnd(parms[IDX_PORTID],parms[IDX_RESULT_LASTDIE]); 
  }

  /*=========================================================================*/
  /* EVENT DIESTART */
  /*=========================================================================*/
  else if (strcmp(event,"DIESTART")==0)  {
 	*status=gemSendDieStart(parms[IDX_PORTID],parms[IDX_C_DIE_FILE], parms[IDX_DIE_POS_X], parms[IDX_DIE_POS_Y]); 
  }

  /*=========================================================================*/
  /* EVENT ABORT */
  /*=========================================================================*/
  else if (strcmp(event,"ABORTED")==0)  {
 	*status=gemSendAborted(); 
  }

  /*=========================================================================*/
  /* EVENT PJABORTSTART */
  /*=========================================================================*/
  else if (strcmp(event,"PJABORTSTART")==0)  {
        *status=gemSendPJAbortStart(parms[IDX_PORTID]);
  }

  /*=========================================================================*/
  /* EVENT PJABORTED */
  /*=========================================================================*/
  else if (strcmp(event,"PJABORTED")==0)  {
 	*status=gemSendPJAborted(parms[IDX_PORTID]); 
  }

  /*=========================================================================*/
  /* EVENT CJABORTED */
  /*=========================================================================*/
  else if (strcmp(event,"CJABORTED")==0)  {
 	*status=gemSendCJAborted(parms[IDX_PORTID]); 
  }

  /*=========================================================================*/
  /* EVENT ALARM */
  /*=========================================================================*/
  else if (strcmp(event,"ALARM")==0)  {
 	*status=gemSendAlarm(parms[IDX_ALARM_TXT], parms[IDX_ALARM_ID], parms[IDX_ALARM_DETAILS]);  
  }

  /*=========================================================================*/
  /* EVENT INITCOMP */
  /*=========================================================================*/
  else if (strcmp(event,"INITCOMP")==0)  {
 	*status=gemSendInitComplete(parms[IDX_EQ_ID],parms[IDX_EQ_TYPE],
				 parms[IDX_SOFT_REV], parms[IDX_F_PROBCARD], parms[IDX_TSTBOARD_ID],parms[IDX_EXECUTIONLEVEL],parms[IDX_EXECUTEATTRIBUTE]);
  }

  /*=========================================================================*/
  /* EVENT LOTCANCEL */
  /*=========================================================================*/
  else if (strcmp(event,"LOTCANCEL")==0)  {
 	*status=gemSendLotCancel(parms[IDX_PORTID],parms[IDX_EXECUTIONLEVEL],parms[IDX_EXECUTEATTRIBUTE],parms[IDX_STATUS]);
  }

  /*=========================================================================*/
  /* EVENT LOTFINISH */
  /*=========================================================================*/
  else if (strcmp(event,"LOTFINISH")==0)  {
 	*status=gemSendLotFinish(parms[IDX_PORTID],parms[IDX_STATUS]);	
  }

  /*=========================================================================*/
  /* EVENT LOTEND */
  /*=========================================================================*/
  else if (strcmp(event,"LOTEND")==0)  {
 	*status=gemSendLotComplete(parms[IDX_PORTID],parms[IDX_EXECUTIONLEVEL],parms[IDX_EXECUTEATTRIBUTE]);
  }

  /*=========================================================================*/
  /* EVENT LOTSTART */
  /*=========================================================================*/
  else if (strcmp(event,"LOTSTART")==0)  {
 	*status=gemSendLotStart(parms[IDX_PORTID], parms[IDX_LOTID], parms[IDX_RETEST_WFR],
				parms[IDX_C_OCR_STATE]);
  }

  /*=========================================================================*/
  /* EVENT PENDINGCOMP */
  /*=========================================================================*/
  else if (strcmp(event,"PENDINGCOMP")==0)  {
 	*status=gemSendPendingComplete(parms[IDX_PORTID],parms[IDX_EXECUTIONLEVEL],parms[IDX_EXECUTEATTRIBUTE]);
  }

  /*=========================================================================*/
  /* EVENT PAUSED */
  /*=========================================================================*/
  if (strcmp(event,"PAUSED")==0)  {
 	*status=gemSendPaused();
  }

  /*=========================================================================*/
  /* EVENT PPBADCOMPILE */
  /*=========================================================================*/
  else if (strcmp(event,"PPBADCOMPILE")==0)  {
 	*status=gemSendPPBadCompile(parms[IDX_PORTID], parms[IDX_STATUS]);
  }
  
  /*=========================================================================*/
  /* EVENT Recipe_Tune_OK */
  /*=========================================================================*/
  else if (strcmp(event,"PP-RCPTUNEOK")==0)  {
 	*status=gemSendRecipe_Tune_OK(parms[IDX_PORTID],parms[IDX_STATUS]);
  }

  /*=========================================================================*/
  /* EVENT Recipe_Tune_Failed */
  /*=========================================================================*/
  else if (strcmp(event,"PP-RCPTUNENG")==0)  {
 	*status=gemSendRecipe_Tune_Failed(parms[IDX_PORTID], parms[IDX_STATUS]);
  }

  /*=========================================================================*/
  /* EVENT PROBERRCP */
  /*=========================================================================*/
  else if (strcmp(event,"PROBERRCP")==0)  {
 	*status=gemSendProberRecipe(parms[IDX_PORTID], parms[IDX_LOTID], parms[IDX_PRB_RECIPE]);
  }

  /*=========================================================================*/
  /* EVENT EXTRACT-PROBERRCP */
  /*=========================================================================*/
  else if (strcmp(event,"PROBERRCP-EXTRACT")==0)  {
 	*status=gemSendExtractProberRecipe(parms[IDX_PORTID], parms[IDX_PRB_RECIPE]);
  }

  /*=========================================================================*/
  /* EVENT PROBERRCPTUNE */
  /*=========================================================================*/
  else if (strcmp(event,"PROBERRCPTUNE")==0)  {
 	*status=gemSendProberRecipeTune(parms[IDX_PORTID], parms[IDX_LOTID], parms[IDX_PRB_RECIPE]);
  }
  
  /*=========================================================================*/
  /* EVENT RCPVERIFIED */
  /*=========================================================================*/
  else if (strcmp(event,"RCPVERIFIED")==0)  {
	build_waferlist(C_WAFERLIST_MAX, &parms[IDX_WFR_EXIST], &parms[IDX_WFR_ID], WaferList_org);
	if (sscanf(parms[IDX_DIETST_NUM], "%d", &i) != 1) return -1;
	if (i <= 1){
		strcpy(DieTest_org, "");
		strcpy(Die, parms[IDX_DIE]);
		strcpy(Tst, parms[IDX_TST]);
	}
	else {
		build_dietstlist(i, &parms[IDX_DIE], &parms[IDX_TST], DieTest_org);
		strcpy(Die, "");
		strcpy(Tst, "");
	}
 	*status=gemSendRecipeVerified(parms[IDX_PORTID], 
					parms[IDX_LOTID], 
					parms[IDX_OPEID], 
					parms[IDX_PPEXEC],
					parms[IDX_WAF], 
					parms[IDX_PRB], 
					Die, 
					parms[IDX_PRODUCTID],
					parms[IDX_PROCESSID], 
					parms[IDX_R_PROBCARD], 
					WaferList_org,
					parms[IDX_TSTFILE_PARAMS], 
					parms[IDX_TPL], 
					parms[IDX_LIM],
					parms[IDX_MDD],
					parms[IDX_C_OCR_STATE], 
					parms[IDX_F_PROBCARD], 
					parms[IDX_TSTBOARD_ID],
					DieTest_org, 
					Tst, 
					parms[IDX_CARRIERID],
                                        parms[IDX_STATUS]);
  }
  
  /*=========================================================================*/
  /* EVENT PJPAUSEREQUEST */
  /*=========================================================================*/
  else if (strcmp(event,"PJPAUSEREQUEST")==0)  {
 	*status=gemSendPJPauseRequest(parms[IDX_PORTID],parms[IDX_REQUESTREASON], parms[IDX_REQUESTVALUE]);
  }
  /*=========================================================================*/
  /* EVENT REQUESTSTART */
  /*=========================================================================*/
  else if (strcmp(event,"REQUESTSTART")==0)  {
 	*status=gemSendRequestStart(parms[IDX_PORTID]);
  }
  
  /*=========================================================================*/
  /* EVENT CJPAUSEREQUEST */
  /*=========================================================================*/
  else if (strcmp(event,"CJPAUSEREQUEST")==0)  {
 	*status=gemSendCJPauseRequest(parms[IDX_PORTID],parms[IDX_REQUESTREASON], parms[IDX_REQUESTVALUE]);
  }
  	
  /*=========================================================================*/
  /* EVENT RESET */
  /*=========================================================================*/
  else if (strcmp(event,"RESET")==0)  {
 	*status=gemSendReset();
  }
  
  /*=========================================================================*/
  /* EVENT RESUMED */
  /*=========================================================================*/
  else if (strcmp(event,"RESUMED")==0)  {
 	*status=gemSendResumed();
  }
  
  /*=========================================================================*/
  /* EVENT STARTINIT */
  /*=========================================================================*/
  else if (strcmp(event,"STARTINIT")==0)  {
 	*status=gemSendStartInit();
  }
  
  /*=========================================================================*/
  /* EVENT INIT */
  /*=========================================================================*/
  else if (strcmp(event,"INIT")==0)  {
 	*status=gemInit();
  }
  
  /*=========================================================================*/
  /* EVENT STOPPED */
  /*=========================================================================*/
  else if (strcmp(event,"STOPPED")==0)  {
 	*status=gemSendStopped();
  }
  
  /*=========================================================================*/
  /* EVENT WAFEREND */
  /*=========================================================================*/
  else if (strcmp(event,"WAFEREND")==0)  {
 	*status=gemSendSubLotComplete(parms[IDX_PORTID], parms[IDX_WFR_RESULT]);
  }
  
  /*=========================================================================*/
  /* EVENT WAFERSTART */
  /*=========================================================================*/
  else if (strcmp(event,"WAFERSTART")==0)  {
 	*status=gemSendSubLotStart(parms[IDX_PORTID], parms[IDX_SUBLOT_ID], parms[IDX_WFR_SLOT],
					parms[IDX_RESULT_FILE], parms[IDX_LOG], parms[IDX_C_OCR_STATE]);
  }
  
  /*=========================================================================*/
  /* EVENT OCRMODE */
  /*=========================================================================*/
  else if (strcmp(event,"OCRMODE")==0)  {
 	*status=gemSendSetOcrMode(parms[IDX_C_OCR_STATE]);
  }
  
  /*=========================================================================*/
  /* EVENT SET-COMPATIMODE */
  /*=========================================================================*/
  else if (strcmp(event,"SET-COMPATIMODE")==0)  {
        strcpy(waflistMode,parms[IDX_COMPATIMODE]);
        *status=0;
  }

  
  /*=========================================================================*/
  /* EVENT IDLEREADY */
  /*=========================================================================*/
  else if (strcmp(event,"IDLEREADY")==0)  {
 	*status=gemSendIdleready();
  }
  
  /*=========================================================================*/
  /* EVENT IDLENOTREADY */
  /*=========================================================================*/
  else if (strcmp(event,"IDLENOTREADY")==0)  {
 	*status=gemSendIdlenotready();
  }


  return 0;	
}

int build_waferlist(int count, char **exists, char **ids, char *list)
{
	int	i;
	int	exist;
	int	init=0;

	strcpy(list, "");
	for (i=0;i<count;i++){
		if (sscanf(exists[i], "%d", &exist) != 1) return -1;
		if (exist == 1){
			sprintf(list,"%s%s%d%c%s", list, init==0 ? "" : C_WAFERLIST_BRK1, i+1, C_WAFERLIST_BRK2, ids[i]);
			if (init==0) init=1;
		}
	}
	return 0;
}

int build_dietstlist(int count, char **die, char **tst, char *list)
{
	int	i;

	strcpy(list, "");
	for (i=0;i<count;i++){
		sprintf(list,"%s%s%s%c%s", list, i>0 ? C_DIETSTLIST_BRK1 : "", die[i], C_DIETSTLIST_BRK2, tst[i]);
	}
	return 0;
}
/*************************************************************************/
/*************************************************************************/
/*  gemGetCmd                                                            */
/*                  Routine used to receive command from host            */
/*                                                                       */
/*************************************************************************/
int gemGetCmd(char *cmd, 
	      char *rply,
	      char **parms)
{
  char command[CMD_LEN] ;
  STRING ItemName;
  STRING FileName;
  char WaferList_org[LIST_LEN];
  char DieTest_org[LIST_LEN];
  char SVVarList_org[LISTVAR_LEN];
  char MLibList_org[LISTMLIB_LEN];
  char TcoList_org[LISTTCO_LEN];
  char *hostparameters;
  char *msgcount;
  char *hosttoken;
  char *hostreply;
  char *hostmessage;
  char prbevent_value[LIST_LEN];
  int msg_count;
  int i,msg_found;
  int ans;
  int line[20];
  float d;
  time_t ts,te;
  int ret;
  FILE *fp;

  time_t ct=time(NULL);
  struct tm *lst=localtime(&ct);

/*
for (i=0;i<5;i++) printf("%p\n", parms[i]);
strcpy(cmd, "COMMAND");
strcpy(parms[0],"1");
strcpy(parms[2],"GET-LOTID");
strcpy(parms[25],"RCP-LOTID");
return;
*/
  if (gemMsgCount()<1)  {
    strcpy(cmd,"NULL");
    return 0;
  }

 /*************************************************************************/
 /*******    Read command from host   *************************************/
 /*************************************************************************/


  ret = 0;
  ret = read_message_from_host();
  if (ret != 0) return ret;

  /*----------------------------------------------------------------------*/
  /*                                                                      */
  /*   At this time the response is in the local string 'hostresponse'    */
  /*   and we will use Tcl to parse out the required parameters.          */
  /*                                                                      */
  /*----------------------------------------------------------------------*/

  /* Host reply */
  ret = parse_reply_mailbox(rply);
  if (ret != 0) return ret;

  /* Host command */
  ret = parse_command_mailbox(cmd);
  if (ret != 0) return ret;

  /* Host parameters */
  ret = parse_parms_mailbox();
  if (ret != 0) return ret;

  if (access("/var/opt/SPECS/log/prober.log", 0)==0) {
    fp=fopen("/var/opt/SPECS/log/prober.log", "r");
    if (fp!=0) { 
        fclose(fp);
        fp=fopen("/var/opt/SPECS/log/prober.log", "a");
        fprintf(fp, "%04d-%02d-%02d %02d:%02d:%02d [host--->CMD %s]\n",
                1900+lst->tm_year, 1+lst->tm_mon, lst->tm_mday,
                lst->tm_hour, lst->tm_min, lst->tm_sec, cmd);
        fclose(fp);
    }
  }

  ret = 0;
  /*=========================================================================*/
  /* CMD ABORT */
  /*=========================================================================*/
  if (strcmp(cmd,"ABORT")==0)  {
  
  }

  /*=========================================================================*/
  /* CMD CJABORT */
  /*=========================================================================*/
  else if (strcmp(cmd,"CJABORT")==0)  {
    parse_parm_from_message("PortID", parms[IDX_PORTID]);
  }

  /*=========================================================================*/
  /* CMD PJABORT */
  /*=========================================================================*/
  else if (strcmp(cmd,"PJABORT")==0)  {
    parse_parm_from_message("PortID", parms[IDX_PORTID]);
  }

  /*=========================================================================*/
  /* CMD CANCEL-MEAS */
  /*=========================================================================*/
  else if (strcmp(cmd,"CANCEL-MEAS")==0)  {
    parse_parm_from_message("PortID", parms[IDX_PORTID]);
  }

  /*=========================================================================*/
  /* CMD CLOSE-LOT */
  /*=========================================================================*/
  else if (strcmp(cmd,"CLOSE-LOT")==0)  {
    parse_parm_from_message("PortID", parms[IDX_PORTID]);
  }

  /*=========================================================================*/
  /* CMD CLOSE-CASSETTE */
  /*=========================================================================*/
  else if (strcmp(cmd,"CLOSE-CASSETTE")==0)  {
    parse_parm_from_message("PortID", parms[IDX_PORTID]);
  }

  /*=========================================================================*/
  /* CMD PAUSE */
  /*=========================================================================*/
  else if (strcmp(cmd,"PAUSE")==0)  {
  
  }

  /*=========================================================================*/
  /* INFO AlarmCreared */
  /*=========================================================================*/
  else if (strcmp(cmd,"AlarmCleared")==0)  {
  
  }

  /*======================================================================*/
  /* CMD PP-SELECT */
  /*======================================================================*/

  else if (strcmp(cmd, "PP-SELECT")==0) {
    /* 1:String of  parameter name, 2:Paramter name */ 
    strcpy(WaferList_org, "");
    strcpy(DieTest_org, "");
    strcpy(MLibList_org, "");
    strcpy(TcoList_org, "");
    parse_parm_from_message("OperatorID", parms[IDX_OPEID]);
    parse_parm_from_message("ProberRecipeFileName", parms[IDX_PRB_RECIPE]);
    parse_parm_from_message("TestPlanName", parms[IDX_TPL]);
    parse_parm_from_message("LimitFileName", parms[IDX_LIM]);
    parse_parm_from_message("MddefFileName", parms[IDX_MDD]);
    parse_parm_from_message("WaferList", WaferList_org);
    i=parse_waferlist(WaferList_org, &parms[IDX_WFR_EXIST], &parms[IDX_WFR_ID]);
    sprintf(parms[IDX_WFR_NUM], "%d", 25);
    parse_parm_from_message("WaferSpecFileName", parms[IDX_WAF]);
    parse_parm_from_message("PortID", parms[IDX_PORTID]);
    parse_parm_from_message("LotID", parms[IDX_LOTID]);
    parse_parm_from_message("ProbeSpecFileName", parms[IDX_PRB]);
    parse_parm_from_message("CarrierID", parms[IDX_CARRIERID]);
    parse_parm_from_message("ProductID", parms[IDX_PRODUCTID]);
    parse_parm_from_message("DieSpecFileName", parms[IDX_DIE]); 
    parse_parm_from_message("TestSpecFileName", parms[IDX_TST]); 
    parse_parm_from_message("PPExecName",parms[IDX_PPEXEC]);
    parse_parm_from_message("DieTestSpecNames", DieTest_org);
    i=0;
    if (strcmp(DieTest_org,"")!=0) 
    	i=parse_dietstlist(DieTest_org, &parms[IDX_DIE], &parms[IDX_TST]);
    sprintf(parms[IDX_DIETST_NUM], "%d", i);
    parse_parm_from_message("RequiredProbeCardType", parms[IDX_R_PROBCARD]);
    parse_parm_from_message("IWCondition", parms[IDX_IWCONDITION]);
    parse_parm_from_message("IWNumOfDies", parms[IDX_IWNUMOFDIE]);
    parse_parm_from_message("IWDieLabel", parms[IDX_IWDIELABEL]);
    parse_parm_from_message("IWJudgeRule", parms[IDX_IWJUDGERULE]);
    parse_parm_from_message("IWJudgeTLevel", parms[IDX_IWJUDGETLEVEL]);
    parse_parm_from_message("BWCondition", parms[IDX_BWCONDITION]);
    parse_parm_from_message("BWNumOfWafs", parms[IDX_BWNUMOFWAF]);
    parse_parm_from_message("BWWafID", parms[IDX_BWWAFID]);
    parse_parm_from_message("BWJudgeRule", parms[IDX_BWJUDGERULE]);
    parse_parm_from_message("BWJudgeTLevel", parms[IDX_BWJUDGETLEVEL]);
    parse_parm_from_message("PJECondition", parms[IDX_PJEBWCONDITION]);
    parse_parm_from_message("PJEJudgeRule", parms[IDX_PJEBWJUDGERULE]);
    parse_parm_from_message("PJEJudgeTLevel", parms[IDX_PJEBWJUDGETLEVEL]);
    parse_parm_from_message("RecipeFName", parms[IDX_RECIPEFNAME]);
    parse_parm_from_message("TestCondFName", parms[IDX_TESTCONDFNAME]);
    parse_parm_from_message("CondLevel", parms[IDX_CONDLEVEL]);
    parse_parm_from_message("AdaptiveMethod", parms[IDX_ADAPTIVEMETHOD]);
    parse_parm_from_message("MeasLibName", parms[IDX_MEASLIBNAME]);
    parse_parm_from_message("DeviceLibName", parms[IDX_DEVICELIBNAME]);
    parse_parm_from_message("WaferTest", parms[IDX_WAFERTEST]);
    parse_parm_from_message("MeasLibNames", MLibList_org);
    i=0;
    if (strcmp(MLibList_org,"")!=0) 
    	i=parse_measliblist(MLibList_org, &parms[IDX_MEASLIB_LIST]);
    sprintf(parms[IDX_MEASLIB_NUM], "%d", i);
    parse_parm_from_message("PRJobID", parms[IDX_PRJOBID]);
    parse_parm_from_message("CtrlJobID", parms[IDX_CTRLJOBID]);
    parse_parm_from_message("TcoFNames", TcoList_org);
    i=0;
    if (strcmp(TcoList_org,"")!=0) 
    	i=parse_tcolist(TcoList_org, &parms[IDX_TCO_LIST]);
    sprintf(parms[IDX_TCO_NUM], "%d", i);


  }

  /*======================================================================*/
  /* CMD PP-RECIPETUNE */
  /*======================================================================*/

  else if (strcmp(cmd, "PP-RECIPETUNE")==0) {
    /* 1:String of  parameter name, 2:Paramter name */ 
    strcpy(WaferList_org, "");
    strcpy(DieTest_org, "");
    strcpy(MLibList_org, "");
    strcpy(TcoList_org, "");
    parse_parm_from_message("OperatorID", parms[IDX_OPEID]);
    parse_parm_from_message("TestPlanName", parms[IDX_TPL]);
    parse_parm_from_message("LimitFileName", parms[IDX_LIM]);
    parse_parm_from_message("MddefFileName", parms[IDX_MDD]);
    parse_parm_from_message("WaferList", WaferList_org);
    i=parse_waferlist(WaferList_org, &parms[IDX_WFR_EXIST], &parms[IDX_WFR_ID]);
    sprintf(parms[IDX_WFR_NUM], "%d", 25);
    parse_parm_from_message("WaferSpecFileName", parms[IDX_WAF]);
    parse_parm_from_message("PortID", parms[IDX_PORTID]);
    parse_parm_from_message("LotID", parms[IDX_LOTID]);
    parse_parm_from_message("ProbeSpecFileName", parms[IDX_PRB]);
    parse_parm_from_message("CarrierID", parms[IDX_CARRIERID]);
    parse_parm_from_message("ProductID", parms[IDX_PRODUCTID]);
    parse_parm_from_message("DieSpecFileName", parms[IDX_DIE]); 
    parse_parm_from_message("TestSpecFileName", parms[IDX_TST]); 
    parse_parm_from_message("PPExecName",parms[IDX_PPEXEC]);
    parse_parm_from_message("DieTestSpecNames", DieTest_org);
    i=1;
    if (strcmp(DieTest_org,"")!=0)
    	i=parse_dietstlist(DieTest_org, &parms[IDX_DIE], &parms[IDX_TST]);
    sprintf(parms[IDX_DIETST_NUM], "%d", i);
    parse_parm_from_message("RequiredProbeCardType", parms[IDX_R_PROBCARD]);
    parse_parm_from_message("IWCondition", parms[IDX_IWCONDITION]);
    parse_parm_from_message("IWNumOfDies", parms[IDX_IWNUMOFDIE]);
    parse_parm_from_message("IWDieLabel", parms[IDX_IWDIELABEL]);
    parse_parm_from_message("IWJudgeRule", parms[IDX_IWJUDGERULE]);
    parse_parm_from_message("IWJudgeTLevel", parms[IDX_IWJUDGETLEVEL]);
    parse_parm_from_message("BWCondition", parms[IDX_BWCONDITION]);
    parse_parm_from_message("BWNumOfWafs", parms[IDX_BWNUMOFWAF]);
    parse_parm_from_message("BWWafID", parms[IDX_BWWAFID]);
    parse_parm_from_message("BWJudgeRule", parms[IDX_BWJUDGERULE]);
    parse_parm_from_message("BWJudgeTLevel", parms[IDX_BWJUDGETLEVEL]);
    parse_parm_from_message("PJECondition", parms[IDX_PJEBWCONDITION]);
    parse_parm_from_message("PJEJudgeRule", parms[IDX_PJEBWJUDGERULE]);
    parse_parm_from_message("PJEJudgeTLevel", parms[IDX_PJEBWJUDGETLEVEL]);
    parse_parm_from_message("RecipeFName", parms[IDX_RECIPEFNAME]);
    parse_parm_from_message("TestCondFName", parms[IDX_TESTCONDFNAME]);
    parse_parm_from_message("CondLevel", parms[IDX_CONDLEVEL]);
    parse_parm_from_message("AdaptiveMethod", parms[IDX_ADAPTIVEMETHOD]);
    parse_parm_from_message("WaferTest", parms[IDX_WAFERTEST]);
    parse_parm_from_message("MeasLibNames", MLibList_org);
    i=0;
    if (strcmp(MLibList_org,"")!=0) 
    	i=parse_measliblist(MLibList_org, &parms[IDX_MEASLIB_LIST]);
    sprintf(parms[IDX_MEASLIB_NUM], "%d", i);

    parse_parm_from_message("TcoFNames", TcoList_org);
    i=0;
    if (strcmp(TcoList_org,"")!=0) 
    	i=parse_tcolist(TcoList_org, &parms[IDX_TCO_LIST]);
    sprintf(parms[IDX_TCO_NUM], "%d", i);
    /* !!! Caution !!!
       Cannot use next parameters for PP-Recipetune 
            ** /opt/SPECS/sys/config/sysconf:MULTIPLE_MEASLIB=FALSE
                    ProberRecipeFileName, MeasLibName, DeviceLibName,
                    MeasLibNames and TcoFNames

            ** /opt/SPECS/sys/config/sysconf:MULTIPLE_MEASLIB=TRUE
                                    and 
               FA_TSK300.fwk/FA_TELP12.fwk flag:FA_MULTIMEAS_MODE=1
                                    and
               FA_TSK300.fwk/FA_TELP12.fwk flag:FA_MEASLOAD_MODE=1
                    ProberRecipeFileName, MeasLibName and DeviceLibName

               This means, if MEALITPLE_MEASLIB=TRUE and FA_MULTIMEAS_MODE=1 
               and FA_MEASLOAD_MODE=1
                 MeasLibNames is available to use in PP-RECIPETUNE
    */
  }

  /*=========================================================================*/
  /* CMD RETEST */
  /*=========================================================================*/
  else if (strcmp(cmd,"RETEST")==0)  {
    parse_parm_from_message("PortID", parms[IDX_PORTID]);
    parse_parm_from_message("WaferList", WaferList_org);
    i=parse_waferlist(WaferList_org, &parms[IDX_WFR_EXIST], &parms[IDX_WFR_ID]);
    sprintf(parms[IDX_WFR_NUM], "%d", 25);
  }

  /*=========================================================================*/
  /* CMD RESUME */
  /*=========================================================================*/
  else if (strcmp(cmd,"RESUME")==0)  {
  
  }

  /*=========================================================================*/
  /* CMD START */
  /*=========================================================================*/
  else if (strcmp(cmd,"START")==0)  {
    parse_parm_from_message("PortID", parms[IDX_PORTID]);
  }

  /*=========================================================================*/
  /* CMD STOP */
  /*=========================================================================*/
  else if (strcmp(cmd,"STOP")==0)  {
  
  }

  /*=========================================================================*/
  /* CMD CHANGE-OCR-STATE */
  /*=========================================================================*/
  else if (strcmp(cmd,"CHANGE-OCR-STATE")==0)  {
    parse_parm_from_message("RequestedOCRState", parms[IDX_R_OCR_STATE]);
  }

  /*=========================================================================*/
  /* INFO ProberStatus */
  /*=========================================================================*/
  else if (strcmp(cmd,"ProberStatus")==0)  {
    parse_parm_from_message("PortID", parms[IDX_PORTID]);
    parse_parm_from_message("HCACK", parms[IDX_HCACK]);
  }
  
  /*=========================================================================*/
  /* CMD REMOTE */
  /*=========================================================================*/
  else if (strcmp(cmd,"REMOTE")==0)  {
  
  }

  /*=========================================================================*/
  /* CMD LOCAL */
  /*=========================================================================*/
  else if (strcmp(cmd,"LOCAL")==0)  {
  
  }

  /*=========================================================================*/
  /* CMD OFFLINE */
  /*=========================================================================*/
  else if (strcmp(cmd,"OFFLINE")==0)  {
  
  }

  /*=========================================================================*/
  /* CMD RUN-DIAGNOSTICS */
  /*=========================================================================*/
  else if (strcmp(cmd,"RUN-DIAGNOSTICS")==0)  {
    parse_parm_from_message("SelectTest", parms[IDX_DIAGNOSTICS]);
  }

  /*=========================================================================*/
  /* CMD EXTRACT-PROBER-RECIPE */
  /*=========================================================================*/

  else if (strcmp(cmd, "EXTRACT-PROBER-RECIPE")==0) {
    parse_parm_from_message("PortID", parms[IDX_PORTID]);
    parse_parm_from_message("RecipeFName", parms[IDX_RECIPEFNAME]);
    parse_parm_from_message("PPExecName",parms[IDX_PPEXEC]);
  }

  /*=========================================================================*/
  /* CMD DATAUPDATE  Updated ECV Non List Data */
  /*=========================================================================*/

  else if (strcmp(cmd, "DATAUPDATE")==0) {
    parse_parm_from_message("SV_UPDNAME", parms[IDX_SV_UPDNAME]);
    parse_parm_from_message("SV_VAL", parms[IDX_SV_VAL]);
  }

  /*=========================================================================*/
  /* CMD LDATAUPDATE Updated ECV List Data */
  /*=========================================================================*/

  else if (strcmp(cmd, "LDATAUPDATE")==0) {
    parse_parm_from_message("SV_UPDNAME", parms[IDX_SV_UPDNAME]);
    parse_parm_from_message("SV_VAL", SVVarList_org);
    ret=parse_svvallist(SVVarList_org, &parms[IDX_SV_VAL]);
    sprintf(parms[IDX_SVLIST_NUM], "%d", ret);
    if (access("/var/opt/SPECS/log/prober.log", 0)==0) {
      fp=fopen("/var/opt/SPECS/log/prober.log", "r");

    if (fp!=0) {
        fclose(fp);
        fp=fopen("/var/opt/SPECS/log/prober.log", "a");
        fprintf(fp, "%04d-%02d-%02d %02d:%02d:%02d LDATAUPDATE Called.",
                1900+lst->tm_year, 1+lst->tm_mon, lst->tm_mday,
                lst->tm_hour, lst->tm_min, lst->tm_sec);
        for (i= 0; i<ret; i++) {
          fprintf(fp, "    parms[IDX_SV_VAL+%d]=%s\n", i, parms[IDX_SV_VAL+i]);
        }
        fclose(fp);
    }
    }
  }

  /*=========================================================================*/
  /* CMD RUN-INITIALIZE */
  /*=========================================================================*/
  else if (strcmp(cmd,"RUN-INITIALIZE")==0)  {

  }

  else if (strcmp(cmd, "RunDiag")==0) {
    parse_parm_from_message("CMS_CARRIER_ID", prbevent_value);
    if (access("/var/opt/SPECS/log/prober.log", 0)==0) {
      fp=fopen("/var/opt/SPECS/log/prober.log", "r");
      if (fp!=0) { 
        fclose(fp);
        fp=fopen("/var/opt/SPECS/log/prober.log", "a");
        fprintf(fp, "%04d-%02d-%02d %02d:%02d:%02d PRBEVENT Value = %s\n",
                1900+lst->tm_year, 1+lst->tm_mon, lst->tm_mday,
                lst->tm_hour, lst->tm_min, lst->tm_sec, prbevent_value);
        fclose(fp);
      }
    }
  }

  return ret;

}
/*--- End of gemGetCmd ---*/
int
parse_waferlist(char *list, char **indexs, char **ids)
{
	char	buf[10];
        char    *p, *brk;
        char    *last, *pp[C_WAFERLIST_MAX];
        int     i=0, indx, wafcnt;

        if ((p=(char *)strdup(list)) == NULL) return -1;

	for (i=0; i<C_WAFERLIST_MAX; i++){
		strcpy(indexs[i],"0");
		strcpy(ids[i],"");
	}
	i=0;
        wafcnt=0;
        for (pp[i]=(char *)strtok_r(p, C_WAFERLIST_BRK1, &last); pp[i]!=NULL && i<C_WAFERLIST_MAX;i++) {
                if ((brk = (char *)strchr(pp[i], C_WAFERLIST_BRK2)) != NULL){
                        strncpy(buf, pp[i], brk-pp[i]);
                        buf[brk-pp[i]] = '\0';
			if (sscanf(buf, "%d", &indx)!=1) {
                           free(p);
                           return -1;
                        }
			if (indx < 0 || indx > C_WAFERLIST_MAX) {
                           free(p);
                           return -1;
                        }
                        if (strcmp(waflistMode,"1")==0){
				strcpy(indexs[indx-1],"1");
			        strcpy(ids[indx-1], ++brk);
			}else{
				sprintf(indexs[wafcnt],"%d",indx);
			        strcpy(ids[wafcnt], ++brk);
                                wafcnt++;
			}
                }
                else {
			free(p);
			return -1;
		}
                if(i < C_WAFERLIST_MAX-1) {
		  pp[i+1]=(char *)strtok_r(NULL, C_WAFERLIST_BRK1, &last);
                }
        }

        free(p);
        return 0;
}

int
parse_dietstlist(char *list, char **die, char **tst)
{
        char    *p, *brk;
        char    *last, *pp[C_DIETSTLIST_MAX];
        int     i=0;
        int     len;

        if ((p=(char *)strdup(list)) == NULL) return -1;

	for (i=0; i<C_DIETSTLIST_MAX; i++){
		strcpy(die[i],"");
		strcpy(tst[i],"");
	}
	i=0;
        for (pp[i]=(char *)strtok_r(p, C_DIETSTLIST_BRK1, &last); pp[i]!=NULL && i<C_DIETSTLIST_MAX; i++) {
                if ((brk = (char *)strchr(pp[i], C_DIETSTLIST_BRK2)) != NULL){
                        len = brk-pp[i];
                        if( len < 256) {
                          strncpy(die[i], pp[i], len);
                          *((char *)die[i]+len) = '\0';
                        }
                        else {
                          strncpy(die[i], pp[i], 255);
                          *((char *)die[i]+255) = '\0';
                        }
                        len=strlen((char*)(brk+1));
                        if(len < 256) {
			  strcpy(tst[i], ++brk);
                        }
                        else {
                          strncpy(tst[i], ++brk, 255);
                          *((char *)tst[i]+255) = '\0';
                        }
                }
                else {
                        free(p);
			return -1;
                }
                if(i < C_DIETSTLIST_MAX-1) {
	          pp[i+1]=(char *)strtok_r(NULL, C_DIETSTLIST_BRK1, &last);
                }
        }

        free(p);
        return i;
}

int
parse_measliblist(char *list, char **var)
{
        char    *p;
        char    *last, *pp[C_MEASLIBLIST_MAX];
        int     i=0;
        int     len;
        FILE *fp;
  
        time_t ct=time(NULL);
        struct tm *lst=localtime(&ct);

        if ((p=(char *)strdup(list)) == NULL) return -1;

	for (i=0; i<C_MEASLIBLIST_MAX; i++){
		strcpy(var[i],"");
	}
	i=0;
        for (pp[i]=(char *)strtok_r(p, C_MEASLIBLIST_BRK1, &last); pp[i]!=NULL && i<C_MEASLIBLIST_MAX; i++) {
                len = strlen(pp[i]);
                if (access("/var/opt/SPECS/log/prober.log", 0)==0) {
                  fp=fopen("/var/opt/SPECS/log/prober.log", "r");
                  if (fp!=0) { 
                    fclose(fp);
                    fp=fopen("/var/opt/SPECS/log/prober.log", "a");
                    fprintf(fp, "%04d-%02d-%02d %02d:%02d:%02d [host--->CMD %s:%d]\n",
                            1900+lst->tm_year, 1+lst->tm_mon, lst->tm_mday,
                            lst->tm_hour, lst->tm_min, lst->tm_sec, pp[i], len);
                    fclose(fp);
                  }
                }
                if( len < 256) {
                  strncpy(var[i], pp[i], len);
                  *((char *)var[i]+len) = '\0';
                }
                else {
                  strncpy(var[i], pp[i], 255);
                  *((char *)var[i]+255) = '\0';
                }
                if(i < C_MEASLIBLIST_MAX-1) {
	          pp[i+1]=(char *)strtok_r(NULL, C_MEASLIBLIST_BRK1, &last);
                }
        }

        free(p);
        return i;
}

int
parse_tcolist(char *list, char **var)
{
        char    *p;
        char    *last, *pp[C_TCOLIST_MAX];
        int     i=0;
        int     len;

        if ((p=(char *)strdup(list)) == NULL) return -1;

	for (i=0; i<C_TCOLIST_MAX; i++){
		strcpy(var[i],"");
	}
	i=0;
        for (pp[i]=(char *)strtok_r(p, C_TCOLIST_BRK1, &last); pp[i]!=NULL && i<C_TCOLIST_MAX; i++) {
                len = strlen(pp[i]);
                if( len < 255) {
                  strncpy(var[i], pp[i], len);
                  *((char *)var[i]+len) = '\0';
                }
                else {
                  strncpy(var[i], pp[i], 255);
                  *((char *)var[i]+255) = '\0';
                }
                if(i < C_TCOLIST_MAX-1) {
	          pp[i+1]=(char *)strtok_r(NULL, C_TCOLIST_BRK1, &last);
                }
        }

        free(p);
        return i;
}

int
parse_svvallist(char *list, char **var)
{
        char    *p;
        char    *last, *pp[C_SVVALLIST_MAX];
        int     i=0;
        int     len;

        if ((p=(char *)strdup(list)) == NULL) return -1;

	for (i=0; i<C_SVVALLIST_MAX; i++){
		strcpy(var[i],"");
	}
	i=0;
        for (pp[i]=(char *)strtok_r(p, C_SVVALLIST_BRK1, &last); pp[i]!=NULL && i<C_SVVALLIST_MAX; i++) {
                len = strlen(pp[i]);
                if( len < 32) {
                  strncpy(var[i], pp[i], len);
                  *((char *)var[i]+len) = '\0';
                }
                else {
                  strncpy(var[i], pp[i], 32);
                  *((char *)var[i]+32) = '\0';
                }
                if(i < C_SVVALLIST_MAX-1) {
	          pp[i+1]=(char *)strtok_r(NULL, C_SVVALLIST_BRK1, &last);
                }
        }

        free(p);
        return i;
}


int
parse_parm_from_message(char * myitemname, char * parm)
{
  char command[CMD_LEN];
  char *mytoken;
  char *cnum;
  int  i, num;

  /* Count the number of the items in the list */
  sprintf(command,"set num_items [llength $Tcl_hostparameters]"); 
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Tcl_Eval n gemGetItem failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1;
  }
  cnum = (char *)Tcl_GetVar(interp,"num_items",TCL_GLOBAL_ONLY) ;
  if( cnum == NULL) {
    fprintf(stderr,"\n***ERROR: Tcl_GetVar in gemGetItem failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ;
    return -1;
  }

  num = atoi(cnum);  /* The number of items */
  strcpy(parm, "\0");

  for( i=1; i<=num; i++) {
    sprintf(command,"set parm_name [lindex [lindex [lindex $Tcl_hostparameters %d] 1] 1]",i); 
    if(Tcl_Eval(interp,command) == TCL_ERROR) {
      fprintf(stderr,"\n***ERROR: Tcl_Eval n gemGetItem failed\n") ;
      fprintf(stderr,"%s\n", interp->result) ; 
      return -1;
    }
    mytoken = (char *)Tcl_GetVar(interp,"parm_name",TCL_GLOBAL_ONLY) ;
    if( mytoken == NULL) {
      fprintf(stderr,"\n***ERROR: Tcl_GetVar in gemGetItem failed\n") ;
      fprintf(stderr,"%s\n", interp->result) ;
      return -1;
    }
    /* If there is a same parameter name, its value is extracted */
    if (strcmp(mytoken, myitemname)==0) {
      sprintf(command,"set parm_val [lindex [lindex [lindex $Tcl_hostparameters %d] 2] 1]",i); 
      if(Tcl_Eval(interp,command) == TCL_ERROR) {
        fprintf(stderr,"\n***ERROR: Tcl_Eval n gemGetItem failed\n") ;
        fprintf(stderr,"%s\n", interp->result) ; 
        return -1;
      }
      mytoken = (char *)Tcl_GetVar(interp,"parm_val",TCL_GLOBAL_ONLY) ;
      if( mytoken == NULL) {
        fprintf(stderr,"\n***ERROR: Tcl_GetVar in gemGetItem failed\n") ;
        fprintf(stderr,"%s\n", interp->result) ;
        return -1;
      }
      strcpy(parm, mytoken);
      return 0;
    }
  }
  return 0;
}


int 
read_message_from_host(void)
{
  char command[CMD_LEN];
  char *res;
  char cmd[CMD_LEN];

  strcpy(command,"set Tcl_hostresponse [mbx get GEM_IN ]");
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [gemGetCmd] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 
  
  res = (char *)Tcl_GetVar(interp,"Tcl_hostresponse",TCL_GLOBAL_ONLY) ;
  if( res == NULL) {
    fprintf(stderr,"\n***ERROR: Tcl_GetVar in gemGetCmd failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 

  strcpy(cmd, res);
  print_msg(cmd);

  return 0;
}

int
parse_reply_mailbox(char *reply)
{
  char command[CMD_LEN];
  char *rep;

  strcpy(command,"set Tcl_hostrplymbx [lindex $Tcl_hostresponse 1 ]");
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [gemGetCmd] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 
  rep = (char *)Tcl_GetVar(interp,"Tcl_hostrplymbx",TCL_GLOBAL_ONLY) ;
  if( rep == NULL) {
    fprintf(stderr,"\n***ERROR: Tcl_GetVar in gemGetCmd failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 

  strcpy(reply, rep);
  return 0;
}

int
parse_command_mailbox(char *hcmd)
{
  char command[CMD_LEN];
  char *cm;

  strcpy(command,"set Tcl_hostcommand [lindex [lindex $Tcl_hostresponse 0] 1 ]");
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [gemGetCmd] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 
 
  cm = (char *)Tcl_GetVar(interp,"Tcl_hostcommand",TCL_GLOBAL_ONLY) ;
  if( cm == NULL) {
    fprintf(stderr,"\n***ERROR: Tcl_GetVar in gemGetCmd failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 

  strcpy(hcmd, cm);
  return 0;
}


int
parse_parms_mailbox(void)
{
  char command[CMD_LEN];
  char *parms;

  strcpy(command, \
      "set Tcl_hostparameters [lindex [lindex $Tcl_hostresponse 0] 2]" \
      );      /* {CMD <command> {L {L {A <name>} {A <value>}} } } Rply */
              /* Modified by Masa (Feb/10) */
  /* strcpy(command,"set Tcl_hostparameters [lindex $Tcl_hostresponse 0]"); modified */
  if(Tcl_Eval(interp,command) == TCL_ERROR) {
    fprintf(stderr,"\n***ERROR: Send_MSG [gemGetCmd] failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 
  parms = (char *)Tcl_GetVar(interp,"Tcl_hostparameters",TCL_GLOBAL_ONLY) ;
  if( parms == NULL) {
    fprintf(stderr,"\n***ERROR: Tcl_GetVar in gemGetCmd failed\n") ;
    fprintf(stderr,"%s\n", interp->result) ; 
    return -1; 
  } 

  return 0;
}


/* Debug code by Masa Feb/10 */
int
print_msg(char * msg)
{
  FILE *fp;

  time_t ct=time(NULL);
  struct tm *lst=localtime(&ct);

  if((fp=fopen("/usr/tmp/tcl_message.log","r"))==0) {
    return -1;
  }
  fclose(fp);
  fp=fopen("/usr/tmp/tcl_message.log","a");
  fprintf(fp, "%04d-%02d-%02d %02d:%02d:%02d >>>[%s]\n",
          1900+lst->tm_year, 1+lst->tm_mon, lst->tm_mday,
          lst->tm_hour, lst->tm_min, lst->tm_sec, msg);
  fclose(fp);
  return 0;
}

int
print_imsg(int i)
{
  char msg[32];
  sprintf(msg, "%d", i);
  return print_msg(msg);
}

