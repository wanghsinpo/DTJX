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
  Name : FA_BLDSCR_LIM
  Vers : 1
  Desc : This algorithm alters Limit File according to conditions specified by 
       : external file.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Masscr          S    -        Master script file to read      
  2 Fmtscr          S    -        Script file for limformat to wri

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -        Command status                  
  2 Error           S    -        Error message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_BLDSCR_LIM(STRING Masscr,STRING Fmtscr,INTEGER *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	FILE *mfp, *dfp;
	char *lnp;
	char ln[256];
	char buf[256];
	char index[256], name[256];
	char speclo[256], spechi[256];
	char prodlo[256], prodhi[256], flg[256];
	char yield[10];
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

	fprintf(dfp, "rep\tflgd\t\n");
	fprintf(dfp, "rep\tflgl\t\n");

	while(fgets(ln, sizeof ln, mfp)!=NULL) {
	    if (ln[0]=='#') continue;  /* This line is comment */
	    if (strlen(ln)<68) break;
	    for(i=22;i<strlen(ln);i++)   /* The number with e from 22th char */
	        if (ln[i]=='e') ln[i]='E';
 	    lnp=&ln[0]; strncpy(buf,lnp,5); 
		strcpy(index,(s = strtok(buf," "))?s:"");
 	    lnp=&ln[6]; strncpy(buf,lnp,14); 
	   	strcpy(name,(s = strtok(buf," "))?s:"");
 	    lnp=&ln[21]; strncpy(buf,lnp,11); 
		strcpy(speclo,(s = strtok(buf, " "))?s:"");
 	    lnp=&ln[33]; strncpy(buf,lnp,11); 
		strcpy(spechi,(s = strtok(buf, " "))?s:"");
 	    lnp=&ln[45]; strncpy(buf,lnp,11); 
		strcpy(prodlo,(s = strtok(buf, " "))?s:"");
 	    lnp=&ln[57]; strncpy(buf,lnp,11); 
		strcpy(prodhi,(s = strtok(buf, " "))?s:"");
 	    lnp=&ln[69]; strncpy(buf,lnp,3); 
		strcpy(yield,(s = strtok(buf, " "))?s:"");
 	    lnp=&ln[73]; strncpy(buf,lnp,2); 
		strcpy(flg,(s = strtok(buf," "))?s:"");

	    if (atoi(prodlo)>atoi(speclo)) {
		printf("Index %s in LIMIT file,\n", index);
		printf("WARNING, ValidLo=%s\tSpecLo=%s\n", prodlo, speclo);
		sprintf(speclo, "%4.3f", atof(prodlo)*1.1);
		printf(" changed to ValidLo=%s\tSpecLo=%s\n",prodlo, speclo);
	    }
	    if (atoi(spechi)>atoi(prodhi)) {
		printf("Index %s in LIMIT file,\n", index);
		printf("WARNING, ValidHi=%s\tSpecHi=%s\n", prodhi, spechi);
		sprintf(spechi, "%4.3f", atof(prodhi)*0.9);
		printf(" changed to ValidHi=%s\tSpecHi=%s\n",prodhi, spechi);
	    }

	    fprintf(dfp, "var\t%s\t", name);
	    fprintf(dfp, "rep\tflgd\t%c\t", flg[0]); 
	    fprintf(dfp, "rep\tflgl\t%c\t", flg[1]);

	    fprintf(dfp, "rep\tlimmin\t1\t");
	    fprintf(dfp, "rep\tlim1\t%s\t",prodlo);
	    fprintf(dfp, "rep\tlim2\t%s\t",speclo);
	    fprintf(dfp, "rep\tlim3\t%s\t",spechi);
	    fprintf(dfp, "rep\tlim4\t%s\t",prodhi);
	    fprintf(dfp, "rep\tlimmax\t1\t");
	    fprintf(dfp, "rep\tbin1\t2\t3\t");
	    fprintf(dfp, "rep\tbin2\t1\t4\t");
	    fprintf(dfp, "rep\tbin3\t-\t+\t");
	    fprintf(dfp, "rep\tjdg\t1\t3\t");
	    fprintf(dfp, "rep\tyld\t%s",yield);
	    fprintf(dfp, "\n");

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
