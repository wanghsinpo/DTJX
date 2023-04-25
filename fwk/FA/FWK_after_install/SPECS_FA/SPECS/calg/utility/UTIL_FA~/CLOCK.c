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
#include <time.h>
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : CLOCK
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
  1 Year            I    -        Year:   YY or YYYY              
  2 Month           I    -        Month:  MM                      
  3 Day             I    -        Day:    DD                      
  4 Hour            I    -        Hour:   HH                      
  5 Minute          I    -        Minute: MM                      
  6 Second          I    -        Second: SS                      
  7 Value           R    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
CLOCK(INTEGER Digit,INTEGER *Year,INTEGER *Month,INTEGER *Day,INTEGER *Hour,INTEGER *Minute,INTEGER *Second,REAL *Value)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	time_t    l; 
	struct tm  *ptr;


	if (Year == NULL  || 
	    Month == NULL || 
	    Day == NULL   ||
            Hour==NULL    || 
	    Minute==NULL  || 
	    Second==NULL  || 
	    Value==NULL) {
		return;
	}

	l = time((time_t *) 0);
	ptr = localtime(&l);
	if(Digit == 4)
            *Year = ptr->tm_year + 1900;
        else
            *Year = ptr->tm_year % 100;
	*Month = ptr->tm_mon+1;
	*Day = ptr->tm_mday;
	*Hour = ptr->tm_hour;
	*Minute = ptr->tm_min;
	*Second = ptr->tm_sec;
	*Value = (double)l;

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
