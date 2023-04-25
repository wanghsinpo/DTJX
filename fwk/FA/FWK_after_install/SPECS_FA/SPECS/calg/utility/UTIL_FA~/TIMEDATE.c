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
#include <time.h>
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : TIMEDATE
  Vers : 1
  Desc : Returns the present date and time
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Digit           I    -        # digits to represent a year    

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Date            S    -        mm/dd/yy or mm/dd/yyyy          
  2 Time            S    -        hh:mm:ss                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
TIMEDATE(INTEGER Digit,STRING *Date,STRING *Time)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	time_t l;
	struct tm  *ptr;


	if (Date == NULL || Time == NULL) {
		return;
	}

	l = time((time_t *) 0);
	ptr = localtime(&l);
        if(Digit == 4){
            sprintf(*Date, "%02d/%02d/%04d", ptr->tm_mon+1, 
                                             ptr->tm_mday, 
					     ptr->tm_year + 1900);
        }
        else {
            sprintf(*Date, "%02d/%02d/%02d", ptr->tm_mon+1, 
                                             ptr->tm_mday, 
					     ptr->tm_year % 100);
        }

	sprintf(*Time, "%02d:%02d:%02d", ptr->tm_hour, 
		 			 ptr->tm_min, 
					 ptr->tm_sec);

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
