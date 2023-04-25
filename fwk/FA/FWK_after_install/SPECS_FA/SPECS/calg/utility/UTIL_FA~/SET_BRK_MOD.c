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
  Name : SET_BRK_MOD
  Vers : 1
  Desc : Set judgement flag of specified module.
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
  2 Dieindex        I    -        Die index in die type (DIE.NUMBE
  3 Modindex        I    -        Module index (MODULE.NUMBER)    
  4 Break           I    -        Breakpoint flag.                

  Output Variables:

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
SET_BRK_MOD(INTEGER Typeindex,INTEGER Dieindex,INTEGER Modindex,INTEGER Break)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	int diepos;

	TPLDIETYPE2POS(Typeindex - 1, Dieindex - 1, &diepos);
	TPLSETBRKMOD(diepos, Modindex - 1, Break);



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
