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
  Name : FA_BLDSCR_TPL
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
  1 Masscr          S    -        Master script file to read      
  2 Fmtscr          S    -        Script file for tplformat to wri

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -        Command status                  
  2 Error           S    -        Error message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_BLDSCR_TPL(STRING Masscr,STRING Fmtscr,INTEGER *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	FILE *mfp, *dfp;
	char *lnp;
	char ln[256];
	char buf[256];
	char index[256];
	char dname[256], outname[256];
	int i;
        char *s;

	memset(buf,'\0', 256);

	*Status=0;
	
	mfp=fopen(Masscr, "r");
	if (mfp==0) {
	    *Status=-1;
	    strcpy(*Error, "Master file not found.");
	    return;
	}
	dfp=fopen(Fmtscr, "w");
	if (dfp==0) {
	    *Status=-1;
	    strcpy(*Error, "Formatted file not found.");
	    return;
	}

	while(fgets(ln, sizeof ln, mfp)!=NULL) {
	    if (ln[0]=='#') continue;  /* This line is comment */
	    if (strlen(ln)<26) break;
 	    lnp=&ln[0]; strncpy(buf,lnp,5); 
		strcpy(index,(s = strtok(buf," "))?s:"");
 	    lnp=&ln[6]; strncpy(buf,lnp,18); 
	   	strcpy(dname,(s = strtok(buf," "))?s:"");
 	    lnp=&ln[19];strncpy(buf,lnp,18); 
		strcpy(outname,(s = strtok(buf, " "))?s:"");

	    fprintf(dfp, "rep\t");
	    fprintf(dfp, "var\t%s\t", dname);
	    fprintf(dfp, "%s\n",outname);
	}

	fclose(mfp);
	fclose(dfp);
	
	*Status=0;
	strcpy(*Error, "");

	return;

/*
	printf("FA_BLDSCR_LIM\n");
	printf(" > Masscr\t=%s\n", Masscr);
	printf(" > Fmtscr\t=%s\n", Fmtscr);
	printf(" < Status\t=%d\n", *Status);
	printf(" < Error\t=%s\n", *Error);
	return;
*/


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
