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

#include <TOOLCTRL.h>

/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : QUERY_GRAPH
  Vers : 1
  Desc : Let Quick Query open Graph. Must be executed after QUERY_FILE.
       :   SPECS2.5: Initial revision.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Filter          I    -        Filter item.                    
  2 Type            I    -        0:XY, 1:Hist, 2:WaferMap        
  3 Unit            I    -        0:Lot, 1:Wafer, 2:Die           
  4 Variable        S    -        Output variable name.           
  5 Update          I    -        0:New, 1:Update                 

  Output Variables:

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
QUERY_GRAPH(INTEGER Filter,INTEGER Type,INTEGER Unit,STRING Variable,INTEGER Update)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	if(!Update){
		QQ_GRAPH_START(Filter, Type, Unit, Variable);
	}else{
		QQ_GRAPH_UPDATE(Filter, Type, Unit, Variable);
	}



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
