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
  Name : FA_MK_DATANAME
  Vers : 1
  Desc : This algorithm generates file name to dump data for a current wafer.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Dir             S    -        Data Directory                  
  2 File            S    -        File Directory                  
  3 Slot            I    -        SlotNumber                      
  4 Adtfmt          S    -        Adt Format                      
  5 Session         S    -        SessionID                       

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Datadir         S    -        Data Directory Path             
  2 Dataname        S    -        Data File Name                  
  3 Status          I    -        0:OK -1:Error                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_MK_DATANAME(STRING Dir,STRING File,INTEGER Slot,STRING Adtfmt,STRING Session,STRING *Datadir,STRING *Dataname,INTEGER *Status)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	char Outputdir[255];
	char Outputfile[255];
	char Err[255];
	char cmd[255];
	int  Exist, R, W, E;
	int  Adt;
	int  I;

	strcpy(Err, "/tmp/tplbld.err");
	*Status=0;

	/* Check the adt format */

	Adt=0;
	if ((strcmp(Adtfmt, "adt"))==0) Adt=2;
	if ((strcmp(Adtfmt, "ad2"))==0) Adt=3;
	if ((strcmp(Adtfmt, "ad3"))==0) Adt=4;
	if ((strcmp(Adtfmt, "ad5"))==0) Adt=5;
	if ((strcmp(Adtfmt, "1"))==0) {
		Adt=1;
		strcpy(Adtfmt, "adt");
	}
	if ((strcmp(Adtfmt, "2"))==0) {
		Adt=2;
		strcpy(Adtfmt, "adt");
	}
	if ((strcmp(Adtfmt, "3"))==0) {
		Adt=3;
		strcpy(Adtfmt, "ad2");
	}
	if ((strcmp(Adtfmt, "4"))==0) {
		Adt=4;
		strcpy(Adtfmt, "ad3");
	}
	if ((strcmp(Adtfmt, "5"))==0) {
		Adt=4;
		strcpy(Adtfmt, "ad5");
	}
	if (Adt==0) {
		*Status=-1;
		return;
	}

	/* Verify Directory */

	VERIFY_FILE(Dir, "Directory", &Exist, &R, &W, &E);   /* Add 2005/09/15 */
	if (Exist==0) {
		*Status=-1;
		return;
	}                                                    /* Add 2005/09/15 */

	sprintf(Outputdir, "%s/%s", Dir, File);
	strcpy(*Datadir, Outputdir);
	VERIFY_FILE(Outputdir, "Directory", &Exist, &R, &W, &E);
	if (Exist==0) {
		sprintf(cmd, "mkdir %s 2> %s", Outputdir, Err);
		system(cmd);
	} else {
		if ((W!=1)&&(E!=1)) {
			*Status=-1;  /* 2005/09/15 */
			return;
		}
	}

	/* Verify File */

	I=1;
	while (I<100) {
		if (I==1) {
			sprintf(Outputfile, "%s/%d.%s", Outputdir, Slot, Adtfmt);
			sprintf(*Dataname, "%d", Slot);
		} else {
			sprintf(Outputfile, "%s/%d#%d.%s", Outputdir, Slot, I, Adtfmt);
			sprintf(*Dataname, "%d#%d", Slot, I);
		}

		VERIFY_FILE(Outputfile, "Normal", &Exist, &R, &W, &E);

		if (Exist<1) {
			*Status=0;
			break;
		} else {
			*Status=-1;
			I++;
		}
	}

	return;

/*
	printf("FA_MK_DATANAME\n");
	printf(" > Dir\t=%s\n", Dir);
	printf(" > File\t=%s\n", File);
	printf(" > Slot\t=%d\n", Slot);
	printf(" > adtfmt\t=%s\n", adtfmt);
	printf(" < Datadir\t=%s\n", *Datadir);
	printf(" < Dataname\t=%s\n", *Dataname);
	printf(" < Status\t=%d\n", *Status);
	return;
*/



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
