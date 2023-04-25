/****** <BEGIN> INCLUDE FILES *********** DON'T EDIT FROM <BEGIN> TO <END> ***/
#include <stdio.h>
#include <stdlib.h>
#include <SPECS.h>
#include <ALGUTIL.h>
#include <TOOLCTRL.h>
#include <CALDB.h>
#include <UTILITY.h>
#include <PROBER.h>
/****** <END>   INCLUDE FILES *********** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : FA_CHK_REV
  Vers : 1
  Desc : Read configuration parameter and apply them.
       :   SPECS2.5: Added special parameters.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Session         S    -        Direcory of file                
  2 Kinds           S    -        MEAS:MeasurementLib TST:Testerli

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -        0:OK -1:ERR                     
  2 Filename        S    -                                        
  3 Rev             S    -                                        
  4 Path            S    -                                        
  5 BasicPath       S    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_CHK_REV(STRING Session,STRING Kinds,INTEGER *Status,STRING *Filename,STRING *Rev,STRING *Path,STRING *BasicPath)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/
	

        INTEGER targetarea=0,counter,rescmp=0,filearea=0,revarea=0,i,i2;
	char	buf[256],cmd[4096];
	char	filename[256],rev[256],*pot=NULL;
	FILE	*fp;


	*Status=0;
        sprintf(cmd,"/opt/SPECS/sys/bin/tplstat -S %s",Session);
        if ((fp = popen(cmd,"r")) == NULL) goto Sys_err;
        counter = 0;
        for ( ;;){
          ++counter;
          if (fgets(buf, sizeof(buf), fp)==NULL) goto Eof;
          buf[strlen(buf)-1]='\0';
          if (counter == 1){
            rescmp = strcmp(buf,Session);
            if ( rescmp == 0){
              targetarea = 1;
              if(strcmp(Kinds,"MEAS")==0){
                filearea   = 10;
                revarea    = 11;
              }else if (strcmp(Kinds,"TST")==0){
                filearea   = 13;
                revarea    = 14;
              }else if (strcmp(Kinds,"PRB")==0){
                filearea   = 16;
                revarea    = 17;
              }else if (strcmp(Kinds,"UTL")==0){
                filearea   = 19;
                revarea    = 20;
              }else if (strcmp(Kinds,"DEV")==0){
                filearea   = 22;
                revarea    = 23;
              }else{
                goto Param_err;
              }
            }
          }else if (counter == 25){
            rescmp = strcmp(buf,Session);
            if ( rescmp == 0){
              targetarea = 2;
              if(strcmp(Kinds,"MEAS")==0){
                filearea   = 34;
                revarea    = 35;
              }else if (strcmp(Kinds,"TST")==0){
                filearea   = 37;
                revarea    = 38;
              }else if (strcmp(Kinds,"PRB")==0){
                filearea   = 40;
                revarea    = 41;
              }else if (strcmp(Kinds,"UTL")==0){
                filearea   = 43;
                revarea    = 44;
              }else if (strcmp(Kinds,"DEV")==0){
                filearea   = 46;
                revarea    = 47;
              }else{
                goto Param_err;
              }
            }
          }else if (counter == 49){
            rescmp = strcmp(buf,Session);
            if ( rescmp == 0){
              targetarea = 3;
              if(strcmp(Kinds,"MEAS")==0){
                filearea   = 58;
                revarea    = 59;
              }else if (strcmp(Kinds,"TST")==0){
                filearea   = 61;
                revarea    = 62;
              }else if (strcmp(Kinds,"PRB")==0){
                filearea   = 64;
                revarea    = 65;
              }else if (strcmp(Kinds,"UTL")==0){
                filearea   = 67;
                revarea    = 68;
              }else if (strcmp(Kinds,"DEV")==0){
                filearea   = 70;
                revarea    = 71;
              }else{
                goto Param_err;
              }
            }
          }else if (counter == 73){
            rescmp = strcmp(buf,Session);
            if ( rescmp == 0){
              targetarea = 4;
              if(strcmp(Kinds,"MEAS")==0){
                filearea   = 82;
                revarea    = 83;
              }else if (strcmp(Kinds,"TST")==0){
                filearea   = 85;
                revarea    = 86;
              }else if (strcmp(Kinds,"PRB")==0){
                filearea   = 88;
                revarea    = 89;
              }else if (strcmp(Kinds,"UTL")==0){
                filearea   = 91;
                revarea    = 92;
              }else if (strcmp(Kinds,"DEV")==0){
                filearea   = 94;
                revarea    = 95;
              }else{
                goto Param_err;
              }
            }
          }
         /* */
          if ( counter == filearea ){
            strcpy(filename,buf);
          }else if ( counter == revarea ){
            strcpy(rev,buf);
            break;
          }
        } 
        if (targetarea == 0)goto Sys_err;
        for(i=strlen(filename);i>=0;i--){
          if (filename[i] == '/'){
            break;
          }
        }
        strncpy((char*)BasicPath,filename,i);
        (*BasicPath)[i]='\0';
        strcpy((char*)Path,filename);
        strcpy((char*)Filename,filename+i+1);
        strcpy((char*)Rev,rev);
	pclose(fp);
/*
        printf("Path= %s\n",Path);
        printf("Filename= %s\n",Filename);
        printf("Rev= %s\n",Rev);
        printf("BasicPath= %s\n",BasicPath);
*/
	return;

Eof:
	*Status = -6;
	if (fp != NULL) pclose(fp);
	return;
Sys_err:
	*Status = -9;
	if (fp != NULL) pclose(fp);
	return;
Param_err:
        *Status = -1;
	if (fp != NULL) pclose(fp);
        printf("Parameter error!! Kinds = %s is not supported.\n",Kinds);
        return;
/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
