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
  Name : FA_READ_CARD
  Vers : 1
  Desc : Desc: Read name, type, and count in probe card.
       : Date: '00/11/27 1st revision
       : Date: '01/10/07 Read file and return the parameters.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 CardPath        S    -                                        

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 CardType        S    -        Card Type                       
  2 CardName        S    -        Card Name                       
  3 TotalCount      R    -        Total Touchdown Count           
  4 LimitCount      R    -        Limit of Touchdonw Cound        
  5 Status          I    -        0:OK -1:Error                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_READ_CARD(STRING CardPath,STRING *CardType,STRING *CardName,REAL *TotalCount,REAL *LimitCount,INTEGER *Status)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	char Revision[255];
	char Date[255];
	char Filename[255];
	char Read_file[255];
	char tc[32], lc[32];
	int  Exist, W, R, E;
	FILE *fp;

	*Status=0;
	W=0;

	/*   Searching a cardname   */

	sprintf(Read_file, "%s/read_card",CardPath);
	if ((fp=fopen(Read_file, "r"))!=0) {
	    fscanf(fp, "%s", CardName);
	    fscanf(fp, "%s", CardType);
	    fclose(fp);
	}

	if (strcmp(*CardName, "")==0)
	    strcpy(*CardName, "cardfile");
	if (strcmp(*CardType, "")==0)
	    strcpy(*CardType, "CardType");

	/* Read parameters from found cardname */

	sprintf(Filename, "%s/%s", CardPath, CardName);
	if ((fp=fopen(Filename, "r"))!=0) {
	    fscanf(fp, "%s", Revision);
	    fscanf(fp, "%s", tc);
	    fscanf(fp, "%s", lc);
	    fscanf(fp, "%s", Date);
	    if((tc[strlen(tc)-4]=='E')||((tc[strlen(tc)-4]=='e')))
		*TotalCount=(REAL)atof(tc);
	    else
		*TotalCount=(REAL)atoi(tc);
	    if((lc[strlen(lc)-4]=='E')||((lc[strlen(lc)-4]=='e')))
		*LimitCount=(REAL)atof(lc);
	    else
		*LimitCount=(REAL)atoi(lc);
	    fclose(fp);
	} else {
	    strcpy(*CardType, "");
	    strcpy(*CardName, "");
	    *TotalCount=0;
	    *LimitCount=0;
	    strcpy(Date, "");
	    *Status=-1;
	}

	/* Check the permission */

	VERIFY_FILE(Filename, "Normal", &Exist, &R, &W, &E);
	if (W!=1) {
	    strcpy(*CardType, "");
	    strcpy(*CardName, "");
	    *TotalCount=0;
	    *LimitCount=0;
	    strcpy(Date, "");
	    *Status=-1;
	}    
	
/*
	printf("FA_READ_CARD\n");
	printf(" > CardPath\t=%s\n", CardPath);
	printf(" < CardType\t=%s\n", *CardType);
	printf(" < CardName\t=%s\n", *CardName);
	printf(" < TotalCount\t=%G\n", *TotalCount);
	printf(" < LimitCount\t=%G\n", *LimitCount);
	printf(" < Status\t=%d\n", *Status);
	return;
*/


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
