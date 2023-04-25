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
  Name : FA_LIMBLD
  Vers : 1
  Desc : This algorithm generates Limit File dynamically.
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
  3 Tpl_dir         S    -        Testplan file directory         
  4 Lim_dir         S    -        Limit file directory            
  5 Tpl             S    -        Test Plan name to read          
  6 Lim             S    -        Limit file name to write        

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
FA_LIMBLD(INTEGER Rev_flag,STRING Brk_chr,STRING Tpl_dir,STRING Lim_dir,STRING Tpl,STRING Lim,INTEGER *Status,STRING *Error,INTEGER *Ndetail,STRING *Detail)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/
        STRING  cmd,err;
        char    t_cmd[4096];
        char    t[4096], l[4096];
	char	*pt=NULL, *pl=NULL, *last;
        FILE    *fp;
	INTEGER	Stat;


        sprintf(cmd, "/opt/SPECS/sys/bin/limbuild");
        sprintf(err, "/usr/tmp/limbld.err");

	FA_CHK_FILES(Rev_flag, Tpl_dir, Tpl, "tpl", Brk_chr, &Stat);
	if (Stat<-1) goto File_check_err;
	FA_CHK_FILES(Rev_flag, Lim_dir, Lim, "lim", Brk_chr, &Stat);
	if (Stat<-3) goto File_check_err;
	if ((pt = (char *)strdup(Tpl)) == NULL) goto Sys_err;
	pt = (char *)strtok_r(pt, Brk_chr, &last);
	if ((pl = (char *)strdup(Lim)) == NULL) goto Sys_err;
	pl = (char *)strtok_r(pl, Brk_chr, &last);

        sprintf(t, "%s%s%s%s", Tpl_dir,
                Tpl_dir[strlen(Tpl_dir)-1]=='/' ? "" : "/", pt,
		strstr(pt, ".tpl")==NULL ? ".tpl" : "");
        sprintf(l, "%s%s%s%s", Lim_dir,
                Lim_dir[strlen(Lim_dir)-1]=='/' ? "" : "/", pl,
		strstr(pl, ".lim")==NULL ? ".lim" : "");

        sprintf(t_cmd, "%s %s > %s 2> %s", cmd, t, l, err);

/* fprintf(stdout, "%s\n", t_cmd); */

        if (system(t_cmd) == 0){
                *Status=0;
		*Ndetail = 0;
                strcpy(*Error,"");
        }
        else {
                *Status=-1;
                strcpy(*Error,"ERROR");
                if ((fp = fopen(err, "r")) == NULL) goto Sys_err;
		*Ndetail = 0;
		while (fgets(l, sizeof(l), fp) != NULL){
			if (*Ndetail < 10){
				strcpy(Detail[*Ndetail], l);
				*Ndetail = *Ndetail + 1;
			}
		}
                fclose(fp);
        }
/*
	printf("FA_LIMBLD\n");
	printf(" < Status\t=%d\n", *Status);
	printf(" < Error\t=%s\n", *Error);
	printf(" < Ndetail\t=%d\n", *Ndetail);
*/	
	sprintf(t_cmd, "rm %s", err);
	system(t_cmd);
	if (pt != NULL) free(pt);
	if (pl != NULL) free(pl);
	return;

File_check_err:
	*Status=-1;
	*Ndetail = 0;
	sprintf(*Error, "File_check_error %d", Stat);
	if (pt != NULL) free(pt);
	if (pl != NULL) free(pl);
	return;

Sys_err:
        *Status=-2;
	*Ndetail = 0;
        strcpy(*Error,strerror(errno));
	if (pt != NULL) free(pt);
	if (pl != NULL) free(pl);
        return;

/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
