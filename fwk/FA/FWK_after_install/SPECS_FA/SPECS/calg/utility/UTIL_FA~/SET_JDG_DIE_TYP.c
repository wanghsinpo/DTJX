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
  Name : SET_JDG_DIE_TYP
  Vers : 1
  Desc : Set judgement flag of specified die type.
       :   SPECS2.5: Initial revision.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Typeindex       I    -        Die type index (DIE.TYPENUMBER) 
  2 Judge           I    -        Judgement value.                
  3 Offsetx         I    -        Die X position offset.          
  4 Offsety         I    -        Die Y position offset.          

  Output Variables:

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
SET_JDG_DIE_TYP(INTEGER Typeindex,INTEGER Judge,INTEGER Offsetx,INTEGER Offsety)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	int typei;
	int diei;
	int diepos;
	int total;

	if(Typeindex <= 0){
		return;
	}

	TPLDIETOTAL(&total);
	if(total <= 0){
		return;
	}

	diepos = -1;
	do{
		diepos++;
		if(diepos >= total){
			return;
		}
		TPLDIEPOS2TYPE(diepos, &typei, &diei);
	}while(typei != Typeindex - 1);

	for(; diepos < total; diepos++){
		TPLDIEPOS2TYPE(diepos, &typei, &diei);
		if(typei != Typeindex - 1){
			return;
		}
		TPLSETJDGDIE(diepos, Judge, Offsetx, Offsety);
	}



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
