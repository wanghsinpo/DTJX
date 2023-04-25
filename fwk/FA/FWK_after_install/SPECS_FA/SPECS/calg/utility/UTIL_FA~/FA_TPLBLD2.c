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
#include <errno.h>
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : FA_TPLBLD2
  Vers : 1
  Desc : This algorithm generates Test Plan dynamically.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Rev_flag        I    -        0:Revision Control not available
  2 Brk_chr         S    -        Connection char between filename
  3 Waf_dir         S    -        Wafer spec search directory     
  4 Prb_dir         S    -        Probe spec search directory     
  5 Die_dir         S    -        Die spec search directory       
  6 Tst_dir         S    -        Test spec search directory      
  7 Mod_dir         S    -        Test spec search directory      
  8 Tpl_dir         S    -        TestPlan directory              
  9 Waf             S    -        Wafer spec name to read         
 10 Prb             S    -        Probe spec name to read         
 11 Die             S    128      Die spec name to read           
 12 Tst             S    128      Test spec name to read          
 13 Mod             S    128      Module spec name to read        
 14 Tpl             S    -        Test Plan name to write         
 15 Meas            S    -        Measurement lib                 
 16 Tester          S    -        Tester lib                      
 17 Prober          S    -        Prober lib                      
 18 Utility         S    -        Utility lib                     
 19 Device          S    -        Device lib                      

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -        Command status                  
  2 Error           S    -        Error message                   
  3 Ndetail         I    -        # of lines of detail error messa
  4 Detail          S    10       detailed error message          

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_TPLBLD2(INTEGER Rev_flag,STRING Brk_chr,STRING Waf_dir,STRING Prb_dir,STRING Die_dir,STRING Tst_dir,STRING Mod_dir,STRING Tpl_dir,STRING Waf,STRING Prb,STRING *Die,STRING *Tst,STRING *Mod,STRING Tpl,STRING Meas,STRING Tester,STRING Prober,STRING Utility,STRING Device,INTEGER *Status,STRING *Error,INTEGER *Ndetail,STRING *Detail)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

#define	DIE_TST_MAX_NUM	128
#define	MOD_SIZE	128

	INTEGER	Stat;
	STRING	cmd, err;
	STRING	fulltpl;
	char	t_cmd[4096];
	char	opt[4096], optdie[4096],optdt[4096];
	char	wdir[4096],pdir[4096],ddir[4096],tdir[4096];
	char	*pw=NULL, *pp=NULL, *ptpl=NULL, *last, *pt=NULL, *pd=NULL;
	int	tstflg[DIE_TST_MAX_NUM];
	int	i,j;
	FILE	*fp;

	*Ndetail = 0;
	sprintf(cmd, "/opt/SPECS/sys/bin/tplbuild");

        FA_CHK_FILES(Rev_flag, Waf_dir, Waf, "waf", Brk_chr, &Stat);
        if (Stat<-1) {
	    *Status = -11;
            goto File_check_err2;
        }
        FA_CHK_FILES(Rev_flag, Prb_dir, Prb, "prb", Brk_chr, &Stat);
        if (Stat<-1) {
	    *Status = -12;
            goto File_check_err2;
        }
        FA_CHK_FILES(Rev_flag, Tpl_dir, Tpl, "tpl", Brk_chr, &Stat);
        if (Stat<-3) goto File_check_err;
        if ((pw = (char *)strdup(Waf)) == NULL) goto Sys_err;
        pw = (char *)strtok_r(pw, Brk_chr, &last);
        if ((pp = (char *)strdup(Prb)) == NULL) goto Sys_err;
        pp = (char *)strtok_r(pp, Brk_chr, &last);
        if ((ptpl = (char *)strdup(Tpl)) == NULL) goto Sys_err;
        ptpl = (char *)strtok_r(ptpl, Brk_chr, &last);
	if ((pd = (char *)malloc(sizeof(STRING))) == NULL) goto Sys_err;
	if ((pt = (char *)malloc(sizeof(STRING))) == NULL) goto Sys_err;

	sprintf(wdir, "%s%s", Waf_dir, Waf_dir[strlen(Waf_dir)-1]=='/' ? "" : "/");
	sprintf(pdir, "%s%s", Prb_dir, Prb_dir[strlen(Prb_dir)-1]=='/' ? "" : "/");
	sprintf(ddir, "%s%s", Die_dir, Die_dir[strlen(Die_dir)-1]=='/' ? "" : "/");
	sprintf(tdir, "%s%s", Tst_dir, Tst_dir[strlen(Tst_dir)-1]=='/' ? "" : "/");

	sprintf(opt, "-waf %s%s -prb %s%s ", wdir, pw, pdir, pp);

        
        for (i = 0; i < MOD_SIZE; i++) {
            if (strcmp(Mod[i], "") == 0) {
                break;
            }
            FA_CHK_FILES(Rev_flag, Mod_dir, Mod[i], "mod", Brk_chr, &Stat);
            if (Stat<-1) {
	        *Status = -15;
                goto File_check_err2;
            }
            strcat(opt, " -mod ");
            strcat(opt, Mod[i]);
        }
        if(strcmp(Meas,"")!=0){
          strcat(opt, " -m ");
          strcat(opt, Meas);
        }
        if(strcmp(Tester,"")!=0){
          strcat(opt, " -t ");
          strcat(opt, Tester);
        }
        if(strcmp(Prober,"")!=0){
          strcat(opt, " -p ");
          strcat(opt, Prober);
        }
        if(strcmp(Utility,"")!=0){
          strcat(opt, " -u ");
          strcat(opt, Utility);
        }
        if(strcmp(Device,"")!=0){
          strcat(opt, " -dvl ");
          strcat(opt, Device);
        }

	for (i=0;i<DIE_TST_MAX_NUM;i++) tstflg[i] = 1;
	strcpy(optdie, "");
	strcpy(optdt, "");

	for (i=0; i<DIE_TST_MAX_NUM; i++){
		if (strcmp(Die[i],"")!=0 && strcmp(Tst[i],"")!=0 && tstflg[i]!=0){
        		FA_CHK_FILES(Rev_flag, Die_dir, Die[i], "die", Brk_chr, &Stat);
        		if (Stat<-1) {
			    *Status = -13;
		            goto File_check_err2;
			}
        		FA_CHK_FILES(Rev_flag, Tst_dir, Tst[i], "tst", Brk_chr, &Stat);
        		if (Stat<-1) {
			    *Status = -14;
		            goto File_check_err2;
			}
        		strcpy(pd,Die[i]);
        		pd = (char *)strtok_r(pd, Brk_chr, &last);
        		strcpy(pt,Tst[i]);
        		pt = (char *)strtok_r(pt, Brk_chr, &last);
			sprintf(optdie, "%s -die %s%s", optdie, ddir, pd);
			sprintf(optdt, "%s -tst %s%s %s%s", optdt, ddir, pd, tdir, pt);
			if (i<DIE_TST_MAX_NUM) {
				for (j=i+1; j<DIE_TST_MAX_NUM; j++){
					if (strcmp(Die[i],Die[j])==0 && tstflg[j]==1){
        					FA_CHK_FILES(Rev_flag, Tst_dir, Tst[j], "tst", Brk_chr, &Stat);
			        		if (Stat<-1) {
						    *Status = -14;
					            goto File_check_err2;
						}
        					strcpy(pt,Tst[j]);
        					pt = (char *)strtok_r(pt, Brk_chr, &last);
						sprintf(optdt, "%s,%s%s", optdt, tdir, pt);
						tstflg[j] = 0;
					}
				}
			}
		}
	}
	sprintf(err, "/usr/tmp/tplbld");
	sprintf(fulltpl, "%s%s%s%s", Tpl_dir, Tpl_dir[strlen(Tpl_dir)-1]=='/' ? "" : "/", ptpl,
					strstr(ptpl, ".tpl")==NULL ? ".tpl" : "");

	sprintf(t_cmd, "%s %s %s %s > %s 2> %s", cmd, opt, optdie, optdt , fulltpl, err);
/*
fprintf(stdout, "%s\n", t_cmd);
*/
	if (system(t_cmd)==0){
		*Status=0;
		strcpy(*Error,"");
	}
	else {
		*Status=-1;
		strcpy(*Error,"ERROR");
		if ((fp = fopen(err, "r")) == NULL) goto Sys_err;
		*Ndetail = 0;
		while (fgets(opt, sizeof(opt), fp) != NULL){
			if (*Ndetail < 10){
				strcpy(Detail[*Ndetail], opt);
				*Ndetail = *Ndetail + 1;
			}
		}
		fclose(fp);
	}
/*
	printf("FA_TPLBLD\n");
	printf(" > Waf\t=%s\n", Waf);
	printf(" > Prb\t=%s\n", Prb);
	printf(" > Die\t=%s\n", Die);
	printf(" > Tst\t=%s\n", Tst);
	printf(" > Tpl\t=%s\n", Tpl);
	printf(" < Status\t=%d\n", *Status);
	printf(" < Error\t=%s\n", *Error);
	printf(" < Ndetail\t=%d\n", *Ndetail);
	printf(" < Detail\t=\n");
*/
	sprintf(t_cmd, "rm %s", err);
	system(t_cmd);
	if (pw != NULL) free(pw);
	if (pp != NULL) free(pp);
	if (ptpl != NULL) free(ptpl);
	if (pd != NULL) free(pd);
	if (pt != NULL) free(pt);

	return;

File_check_err:
        *Status=-1;
File_check_err2:
        sprintf(*Error, "File_check_error %d", Stat);
	if (pw != NULL) free(pw);
	if (pp != NULL) free(pp);
	if (ptpl != NULL) free(ptpl);
	if (pd != NULL) free(pd);
	if (pt != NULL) free(pt);
        return;

Sys_err:
        *Status=-2;
        strcpy(*Error,strerror(errno));
	if (pw != NULL) free(pw);
	if (pp != NULL) free(pp);
	if (ptpl != NULL) free(ptpl);
	if (pd != NULL) free(pd);
	if (pt != NULL) free(pt);
        return;


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
