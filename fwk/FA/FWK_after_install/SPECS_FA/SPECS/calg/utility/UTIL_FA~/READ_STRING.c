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

#define MAX_STR_LENG    256
#define MAX_BUF_LENG    1024
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : READ_STRING
  Vers : 1
  Desc : Reads string data from a STRING variable, and returns it to another ST
       : RING variable
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
  1 Value           S    -        Read value                      
  2 Stat            I    -        1(ok), 0(no data), -1(EOF)      

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
READ_STRING(STRING Format,STRING String,STRING *Value,INTEGER *Stat)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/


	char  wkbuf[MAX_BUF_LENG];


	if (Value == NULL || Stat == NULL) {
		return;
	}

	memset((void *) *Value, '\0', MAX_STR_LENG);
	memset((void *)  wkbuf, '\0', MAX_BUF_LENG);

	*Stat = sscanf(String, Format, wkbuf);
	wkbuf[MAX_STR_LENG - 1] = '\0';
	strcpy(*Value, wkbuf);

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
