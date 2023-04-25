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
  Name : FA_CHK_LIBPATH
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
  1 Orig            S    -        Direcory of file                

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -        0:OK -1:ERR                     
  2 Pathflug        I    -        0:relativity 1:absolute         
  3 Path            S    -                                        
  4 Filename        S    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_CHK_LIBPATH(STRING Orig,INTEGER *Status,INTEGER *Pathflug,STRING *Path,STRING *Filename)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	INTEGER	cmpResult = 0, i;
	char	*pot = NULL;

	*Status = 0;
	if (Orig[0] == '/') {
		*Pathflug = 1;
	}
	else {
		*Pathflug = 0;
	}
	for (i = strlen((char*) Orig) - 1; i > 0; i--) {
		if (Orig[i] == '/') {
			break;
		}
	}
	if (i <= 0) { /* Add 2005/09/15 and Modify 2006/11/02 */
		*Status = 1;
		strcpy(*Path, "");
		strcpy((char*) Filename, Orig);
		return;
	}
	strncpy(*Path, Orig, i);
	(*Path)[i] = '\0';
	pot = strrchr((char*) Orig, '/');
	if (pot == NULL) {
		strcpy((char*) Filename, Orig);
	}
	else {
		strcpy((char*) Filename, pot + 1);
	}

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
