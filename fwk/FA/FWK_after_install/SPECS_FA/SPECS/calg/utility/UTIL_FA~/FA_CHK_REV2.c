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
  Name : FA_CHK_REV2
  Vers : 1
  Desc : Get TPL file information.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Session         S    -        Session Number                  
  2 Kinds           S    -        Type of Library                 
  3 Count           I    -        Index of Multi-Measurement Libra

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -        Error Code                      
  2 Filename        S    -        File Name                       
  3 Rev             S    -        Revision                        
  4 Path            S    -        File Name with Directory        
  5 BasicPath       S    -        Directory                       

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_CHK_REV2(STRING Session,STRING Kinds,INTEGER Count,INTEGER *Status,STRING *Filename,STRING *Rev,STRING *Path,STRING *BasicPath)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	INTEGER	Num;
	char *Ptr;

	*Status = 0;
	strcpy(*Filename, "");
	strcpy(*Rev, "");
	strcpy(*Path, "");
	strcpy(*BasicPath, "");

	if (strcmp(Kinds, "MEAS") == 0) {
		Num = 0;
		TPLFILENUMMLIB(&Num);
		if (Count < Num) {
			TPLFILEMLIBM(Count, Path, Rev, &Num);
		}
		else {
			*Status = -2;
		}
	}
	else if (strcmp(Kinds, "PRB") == 0) {
		Num = 0;
		TPLFILEPLIB(Path, Rev, &Num);
	}
	else if (strcmp(Kinds, "TST") == 0) {
		Num = 0;
		TPLFILETLIB(Path, Rev, &Num);
	}
	else if (strcmp(Kinds, "UTL") == 0) {
		Num = 0;
		TPLFILEULIB(Path, Rev, &Num);
	}
	else if (strcmp(Kinds, "DEV") == 0) {
		Num = 0;
		TPLFILEDLIB(Path, Rev, &Num);
	}
	else {
		*Status = -1;
	}

	if (Num != 0 && *Status == 0) {
		strcpy(*Filename, *Path);
		strcpy(*BasicPath, *Path);
		Ptr = strrchr(*Path, '/');

		if (Ptr != NULL) {
			strcpy(*Filename, Ptr + 1);
			(*BasicPath)[strlen(*BasicPath) - strlen(Ptr) + 1] = '\0';
		}
		else {
			strcpy(*BasicPath, "/");
		}
	}

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
