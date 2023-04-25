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
#include <string.h>
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : LOG_WAFER_END
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
  1 Session         S    -                                        
  2 State           S    -                                        
  3 Result          I    -                                        
  4 Time            S    -                                        

  Output Variables:

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
LOG_WAFER_END(STRING Session,STRING State,INTEGER Result,STRING Time)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	STRING	file, judge;
	FILE	*fptr;

	if (Result == 0) {
		strcpy(judge, "Fail");
	}
	else if (Result == 1) {
		strcpy(judge, "Pass");
	}
	else {
		strcpy(judge, "");
	}

	sprintf(file, "/var/opt/SPECS/log/testlog.%s", Session); /* AVPATH_ */

	if ((fptr = fopen(file, "a+")) == 0) {
		return;
	}

	fprintf(fptr, "          End:      %s\n", Time);
	fprintf(fptr, "          State:    %s\n", State);
	fprintf(fptr, "          Result:   %s\n", judge);
	fprintf(fptr, "\n");

	fclose(fptr);

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
