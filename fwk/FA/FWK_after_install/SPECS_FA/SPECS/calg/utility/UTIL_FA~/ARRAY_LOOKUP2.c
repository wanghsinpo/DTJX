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

#define ARRAY_MAX       256
#define MAX_STR_LENG    256

void STRING_LOOKUP();
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : ARRAY_LOOKUP2
  Vers : 1
  Desc : Returns the array indices for the specified data elements of a STRING 
       : array.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Src             S    256      Source strings                  
  2 Pat             S    256      Pattern strings                 

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Pos             I    256      Positions of each pattern string

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
ARRAY_LOOKUP2(STRING *Src,STRING *Pat,INTEGER *Pos)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	int  i, j, k;

	if (Pos == NULL) {
		return;
	}

	/* loop Pat Arrey */
	for (i = 0; i < ARRAY_MAX; i++) {
        	Pos[i] = 0;

	        /* loop Src Array */
        	for (j = 0; j < ARRAY_MAX; j++) {
			STRING_LOOKUP(Src[j], Pat[i], &k);
			if (k > 0) {
				Pos[i] = j + 1;
                		break;
            		}
        	}
    	}

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
