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
  Name : READ_REAL
  Vers : 1
  Desc : Reads a value from a STRING variable, and returns it to a REAL variabl
       : e
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Format          S    -        Format string                   
  2 String          S    -        String to read from             

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Value           R    -        Read value                      
  2 Stat            I    -        1(ok), 0(no data), -1(EOF)      

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
READ_REAL(STRING Format,STRING String,REAL *Value,INTEGER *Stat)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	float	f;

	if (Value == NULL || Stat == NULL) {
		return;
	}

	f = 0.0;
	*Stat = sscanf(String, Format, &f);
	*Value = f;

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
