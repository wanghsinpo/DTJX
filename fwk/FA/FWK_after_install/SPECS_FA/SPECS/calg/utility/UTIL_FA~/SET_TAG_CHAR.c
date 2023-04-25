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
#include <ALGUTIL.h>
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : SET_TAG_CHAR
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
  1 Name            S    -                                        
  2 Value           C    -                                        

  Output Variables:

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
SET_TAG_CHAR(STRING Name,CHARACTER Value)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	CHARACTER *array;
	INTEGER	index, type, dim, size1, size2;
	INTEGER	j, k;
	STRING	name;

	TPLTAGINDEX("SYSTEM", Name, &index);
	if (index == -1) {
		return;
	}

	TPLTAGINFO("SYSTEM", index, &name, &type, &dim, &size1, &size2);
	if (type != 2) {
		return;
	}

	switch (dim) {
	case 0:
		TPLPUTCTAG("SYSTEM", index, 0, Value);
		break;
	case 1:
		array = (CHARACTER*) malloc(sizeof(CHARACTER) * size1);
		for (j = 0; j < size1; j++) {
			array[j] = Value;
		}
		TPLPUTCATAG("SYSTEM", index, 0, array);
		free(array);
		break;
	case 2:
		array = (CHARACTER*) malloc(sizeof(CHARACTER) * size1 * size2);
		for (j = 0; j < size2; j++) {
			for (k = 0; k < size1; k++) {
				array[size1 * j + k] = Value;
			}
		}
		TPLPUTCATAG("SYSTEM", index, 0, array);
		free(array);
		break;
	}

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
