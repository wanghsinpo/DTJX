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
  Name : FA_TPLFMT
  Vers : 1
  Desc : This algorithm alters Test Plan according to conditions specified by e
       : xternal file.
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
  3 Src_tpl_dir     S    -        Temporary file directory        
  4 Script_dir      S    -        Script file directory           
  5 Dst_tpl_dir     S    -        New Testplan file directory     
  6 Src_tpl         S    -        Temporay Testplan File to read  
  7 Script          S    -        Specified script file           
  8 Dst_tpl         S    -        Generated Testplan File to write

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -        Command status                  
  2 Error           S    -        Error message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_TPLFMT(INTEGER Rev_flag,STRING Brk_chr,STRING Src_tpl_dir,STRING Script_dir,STRING Dst_tpl_dir,STRING Src_tpl,STRING Script,STRING Dst_tpl,INTEGER *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/
	INTEGER	Stat;
	STRING	cmd,err;
	char	t_cmd[4096];
	char	Src[4096], Dst[4096], Scr[4096];
	char    Fmtscr[512];
	char    *ps=NULL, *pd=NULL, *last;
	FILE	*fp;

	sprintf(cmd, "/opt/SPECS/sys/bin/tplformat");
	sprintf(err, "/usr/tmp/tplfmt.err");

        FA_CHK_FILES(Rev_flag, Src_tpl_dir, Src_tpl, "tpl", Brk_chr, &Stat);
        if (Stat<-1) goto File_check_err;
	/*
        FA_CHK_FILES(Rev_flag, Dst_tpl_dir, Dst_tpl, "tpl", Brk_chr, &Stat);
        if (Stat<-3) goto File_check_err;
	*/
        if ((ps = (char *)strdup(Src_tpl)) == NULL) goto Sys_err;
        ps = (char *)strtok_r(ps, Brk_chr, &last);
        if ((pd = (char *)strdup(Dst_tpl)) == NULL) goto Sys_err;
        pd = (char *)strtok_r(pd, Brk_chr, &last);
		
	sprintf(Src, "%s%s%s%s", Src_tpl_dir,
		Src_tpl_dir[strlen(Src_tpl_dir)-1]=='/' ? "" : "/", ps,
		strstr(ps, ".tpl")==NULL ? ".tpl" : "");
	sprintf(Dst, "%s%s%s%s", Dst_tpl_dir,
		Dst_tpl_dir[strlen(Dst_tpl_dir)-1]=='/' ? "" : "/", pd,
		strstr(pd, ".tpl")==NULL ? ".tpl" : "");
	sprintf(Scr, "%s%s%s", Script_dir,
		Script_dir[strlen(Script_dir)-1]=='/' ? "" : "/", Script);

	sprintf(Fmtscr, "/usr/tmp/tplscr.tmp");
	FA_BLDSCR_TPL(Scr, Fmtscr, Status, Error);

/*	sprintf(t_cmd, "%s -cmd %s %s > %s 2> %s", cmd, Scr, Src, Dst, err);*/
	sprintf(t_cmd, "%s -cmd %s %s > %s 2> %s", cmd, Fmtscr, Src, Dst, err);

/* fprintf(stdout, "%s\n", t_cmd); */

	if (system(t_cmd) == 0){
                *Status=0;
                strcpy(*Error,"");
        }
        else {
                *Status=-1;
                if ((fp = fopen(err, "r")) == NULL) goto Sys_err;
                fgets(*Error, sizeof(STRING), fp);
                fclose(fp);
        }
/*
	printf("FA_TPLFMT\n");
	printf(" < Status\t=%d\n", *Status);
	printf(" < Error\t=%s\n", *Error);
*/	
	sprintf(t_cmd, "rm %s", err);
	system(t_cmd);
        if (ps != NULL) free(ps);
        if (pd != NULL) free(pd);
	return;

File_check_err:
        *Status=-1;
        sprintf(*Error, "File_check_error %d", Stat);
        if (ps != NULL) free(ps);
        if (pd != NULL) free(pd);
        return;

Sys_err:
        *Status=-2;
        strcpy(*Error,strerror(errno));
        if (ps != NULL) free(ps);
        if (pd != NULL) free(pd);
        return;


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
