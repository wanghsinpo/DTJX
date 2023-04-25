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
  Name : FA_UPDATE_CARD
  Vers : 1
  Desc : FA: Update probecard touchdown counts
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 CardPath        S    -        Card File Directory             
  2 CardName        S    -        Card File Name                  
  3 TotalCount      R    -        Total Touchdown Count           

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -        0:OK -1:Error                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_UPDATE_CARD(STRING CardPath,STRING CardName,REAL TotalCount,INTEGER *Status)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	char Cardfile[255];
	char A[255];
	char Revision[255], Date[255];
	char cmd[255];
	char lc[32];
	REAL LimitCount;
	FILE *fp;

	sprintf(Cardfile, "%s/%s", CardPath, CardName);
	
	if((fp=fopen(Cardfile, "r"))==0) {
	    *Status=-1;
	    return;
	}

	fscanf(fp, "%s", Revision);
	fscanf(fp, "%s", A);
	fscanf(fp, "%s", lc);
	if((lc[strlen(lc)-4]=='E')||((lc[strlen(lc)-4]=='e')))
	    LimitCount=(REAL)atof(lc);
	else
	    LimitCount=(REAL)atoi(lc);
	fscanf(fp, "%s", Date);
	fclose(fp);

	if((fp=fopen(Cardfile, "w"))==0) {
	    *Status=-1;
	    return;
	}

	fprintf(fp, "%s\n", Revision);
	fprintf(fp, "%G\n", TotalCount);
	fprintf(fp, "%G\n", LimitCount);
	fprintf(fp, "%s", Date);
	fclose(fp);

	Status=0;
	return;

/*
	printf("FA_UPDATE_CARD\n");
	printf(" > CardPath\t=%s\n", CardPath);
	printf(" > CardName\t=%s\n", CardName);
	printf(" > TotalCount\t=%G\n", TotalCount);
	printf(" < Status\t=%d\n", *Status);
	return;
*/


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
