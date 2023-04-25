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
  Name : LOG_LOT_BEGIN
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
  2 Lotid           S    -                                        
  3 Testplan        S    -                                        
  4 Algorithm       S    -                                        
  5 Limitfile       S    -                                        
  6 Operator        S    -                                        
  7 Date            S    -                                        
  8 Time            S    -                                        

  Output Variables:

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
LOG_LOT_BEGIN(STRING Session,STRING Lotid,STRING Testplan,STRING Algorithm,STRING Limitfile,STRING Operator,STRING Date,STRING Time)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	STRING	file, text;
	FILE	*fptr;

	sprintf(file, "/var/opt/SPECS/log/testlog.%s", Session); /* AVPATH_ */

	if ((fptr = fopen(file, "a+")) == 0) {
		return;
	}

	sprintf(text, "================================");
	fprintf(fptr, "%s LOT TEST START %s\n", text, text);
	fprintf(fptr, "\n");
	fprintf(fptr, "     Lot ID:     %s\n", Lotid);
	fprintf(fptr, "     Test Plan:  %s\n", Testplan);
	fprintf(fptr, "     Algorithm:  %s\n", Algorithm);
	fprintf(fptr, "     Limit File: %s\n", Limitfile);
	fprintf(fptr, "     Operator:   %s\n", Operator);
	fprintf(fptr, "     Date:       %s\n", Date);
	fprintf(fptr, "     Start:      %s\n", Time);
	fprintf(fptr, "\n");

	fclose(fptr);

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
