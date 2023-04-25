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
  Name : WRITE_WAFER_SUM
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
  1 Slot            I    -                                        
  2 Lot             S    -                                        
  3 Wafer           S    -                                        
  4 Yld_item        R    -                                        
  5 Yld_die         R    -                                        
  6 Judge           I    -                                        

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Summary         S    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
WRITE_WAFER_SUM(INTEGER Slot,STRING Lot,STRING Wafer,REAL Yld_item,REAL Yld_die,INTEGER Judge,STRING *Summary)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/


    
	STRING buffer;

	memset(*Summary, ' ', 73);
	(*Summary)[73] = 0;

	sprintf(buffer, "%d", Slot);
	strncpy(*Summary + 1, buffer, strlen(buffer));

	if (strlen(Lot) > 24) {
		strncpy(buffer, Lot, 24);
		buffer[24] = '\0';
	}
	else {
		strcpy(buffer, Lot);
	}
	strncpy(*Summary + 10, buffer, strlen(buffer));

	if (strlen(Wafer) > 10) {
		strncpy(buffer, Wafer, 10);
		buffer[10] = '\0';
	}
	else {
		strcpy(buffer, Wafer);
	}
	strncpy(*Summary + 35, buffer, strlen(buffer));

	if (Judge < 0) {
		return;
	}

	sprintf(buffer, "%5.2f", Yld_item);
	strncpy(*Summary + 46, buffer, strlen(buffer));
    
	sprintf(buffer, "%5.2f", Yld_die);
	strncpy(*Summary + 57, buffer, strlen(buffer));

	switch (Judge) {
	case 0:
		strcpy(buffer, "Fail");
		break;
	case 1:
		strcpy(buffer, "Pass");
		break;
	}
	strncpy(*Summary + 68, buffer, strlen(buffer));



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
