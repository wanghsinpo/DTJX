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
  Name : GET_VGEMDEFAULT
  Vers : 1
  Desc : Read configuration parameter and apply them.
       :   SPECS2.5: Added special parameters.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Rcpmode         S    -                                        
  2 Rcpfilename     S    -                                        
  3 Status          I    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
GET_VGEMDEFAULT(STRING *Rcpmode,STRING *Rcpfilename,INTEGER *Status)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

        INTEGER sz=4095, iloop, cnt, rcpfileflg=0, cmodeflg=0;
        STRING buf;
        char   *seekp;
        char   filename[4096],mode[4096];
        FILE   *fp;

        *Status=0;
        strcpy((char *)Rcpmode,"");
        strcpy((char *)Rcpfilename,"");
        if((fp=fopen("/opt/SPECS_FA/dmh/vgem/defaults.ini","r"))==0) {
          goto ERR_STATE;
        }
        while(fgets(buf, sizeof(STRING), fp)){
          if(buf[0]!='#'){
            if(strncmp(buf,"VGEM",4)==0){
              seekp=strstr(buf," RecipeFile ");
              if(seekp != NULL){
                cnt=0;
                for(iloop=12;iloop<=4095;iloop++){
                  if(*(seekp+iloop) =='\0'){
                    break;
                  }
                  if(*(seekp+iloop) !=' '){
                    filename[cnt]=*(seekp+iloop);
                    rcpfileflg=1;
                    cnt++;
                  }
                }
                filename[cnt-1]='\0';
              }
              seekp=strstr(buf," CompatibilityMode ");
              if(seekp != NULL){
                cnt=0;
                for(iloop=19;iloop<4095;iloop++){
                  if(*(seekp+iloop) =='\0'){
                    break;
                  }
                  if(*(seekp+iloop) !=' '){
                    mode[cnt]=*(seekp+iloop);
                    cmodeflg=1;
                    cnt++;
                  }
                }
                mode[cnt-1]='\0';
              }
            }
          }
        }
        fclose(fp);
        if(rcpfileflg == 1){
          strcpy((char *)Rcpfilename,filename);
        }else{
          goto ERR_RCPFILE;
        }
        if(cmodeflg == 1){
          strcpy((char *)Rcpmode,mode);
        }else{
          goto ERR_CMODE;
        }


/*
	printf("FA_GET_RCPNAME\n");
	printf(" < Rcpmode\t=%s\n", *Rcpmode);
	printf(" < Rcpfilename\t=%s\n", *Rcpfilename);
*/
	return;

ERR_STATE:
        *Status=-1;
        printf("FA_GET_RCPNAME ERR\n");
        return;
ERR_CMODE:
        *Status=-2;
        return;
ERR_RCPFILE:
        *Status=-3;
        return;




/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
