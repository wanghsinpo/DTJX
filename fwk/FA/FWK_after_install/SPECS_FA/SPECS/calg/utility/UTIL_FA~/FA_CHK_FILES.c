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
  Name : FA_CHK_FILES
  Vers : 1
  Desc : Description for this Algorithm spec.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Rev_flag        I    -        0:Revision Control not available
  2 Dir             S    -        Direcory of file                
  3 Filename_rev    S    -        Filename with revision number   
  4 Suffix          S    -        suffix of Filename              
  5 Brk_chr         S    -        Connection char between filename

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -        0:OK -1:ERR                     

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_CHK_FILES(INTEGER Rev_flag,STRING Dir,STRING Filename_rev,STRING Suffix,STRING Brk_chr,INTEGER *Status)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/
	
#define	TPLATTR	"/opt/SPECS/sys/bin/tplattr"
#define	CMD	"/opt/SPECS/sys/bin/revopen"

	INTEGER	Rev_mode,i;
	INTEGER	e,r,w,x;
	STRING	opt;
	char	full[4096],fullpath[4096];
	char	buf[4096];
	char	*p=NULL,*f,*rev,*file,*suf;
	char	*last;
	FILE	*fp;

	Rev_mode = 0;		/* 0:RevisionName 1:RevisionNumber */

	*Status=0;
	strcpy(opt, Rev_mode==0 ? " -a " : " -n ");
	if ((p = (char *)strdup(Filename_rev)) == NULL) goto Sys_err;

	f 	= (char *)strtok_r(p, Brk_chr, &last);
	rev	= (char *)strtok_r(NULL, Brk_chr, &last);
	file	= (char *)strtok_r(f, ".", &last);
	if ((suf = (char *)strtok_r(NULL, ".", &last)) == NULL)
		suf = (char *)Suffix;
	sprintf(full, "%s%s%s", Dir, Dir[strlen(Dir)-1]=='/' ? "" : "/", file);
	sprintf(fullpath, "%s.%s",full, suf);

	VERIFY_FILE(fullpath, "Normal", &e, &r, &w, &x);
	if ( e != 1 ) goto Permit_not_exist;
	if ( r != 1 ) goto Permit_read;
	if ( w != 1 ) goto Permit_write;

	if (strstr(Filename_rev, Brk_chr) == NULL) return;
	if (Rev_flag == 0) goto Rev_unable;

	sprintf(buf,"%s -a Vers -t %s %s 2> /dev/null", TPLATTR, suf, full);

	if ((fp = popen(buf, "r")) == NULL) goto Sys_err;
	if (fgets(buf, sizeof(buf), fp)==NULL) goto Eof;
	if (strlen(buf)<8) goto No_rev;
	pclose(fp);

	sprintf(buf, "%s %s %s -t %s %s 2> /dev/null", CMD, opt, rev, suf, full);
	if (system(buf) != 0) *Status = -7;
/*
 printf("%s\n",buf); 
	printf("FA_CHK_FILES\n");
	printf(" > Rev_flag\t=%d\n", Rev_flag);
	printf(" > Dir\t=%s\n", Dir);
	printf(" > Filename_rev\t=%s\n", Filename_rev);
	printf(" > Suffix\t=%s\n", Suffix);
	printf(" > Brk_chr\t=%s\n", Brk_chr);
	printf(" < Status\t=%d\n", *Status);
*/	
	if (p != NULL) free(p);

	return;

Permit_not_exist:
	*Status = -3;
	if (p != NULL) free(p);
	return;
Permit_read:
	*Status = -2;
	if (p != NULL) free(p);
	return;
Permit_write:
	*Status = -1;
	if (p != NULL) free(p);
	return;
Rev_unable:
	*Status = -4;
	if (p != NULL) free(p);
	return;
No_rev:
	*Status = -5;
	if (p != NULL) free(p);
	return;
Eof:
	*Status = -6;
	if (p != NULL) free(p);
	return;
Sys_err:
	*Status = -9;
	if (p != NULL) free(p);
	return;

/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
