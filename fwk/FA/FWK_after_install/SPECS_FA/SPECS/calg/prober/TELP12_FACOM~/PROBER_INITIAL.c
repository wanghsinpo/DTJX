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
  Name : PROBER_INITIAL
  Vers : 1
  Desc : Defines the initial die/module location
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 DieX            R    -        Initial Die X position from wafe
  2 DieY            R    -        Initial Die Y position from wafe
  3 ModX            R    -        Initial Module X position from d
  4 ModY            R    -        Initial Module Y position from d
  5 StepX           R    -        X index size in um              
  6 StepY           R    -        Y index size in um              
  7 Coord           I    -        XY Coordinate System (1..4)     

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          S    -        "OK" or "ERROR"                 
  2 Error           S    -        Error message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/

extern void
TELP12_INITIAL(REAL DieX,REAL DieY,REAL ModX,REAL ModY,REAL StepX,REAL StepY,INTEGER Coord,STRING *Status,STRING *Error);

/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
PROBER_INITIAL(REAL DieX,REAL DieY,REAL ModX,REAL ModY,REAL StepX,REAL StepY,INTEGER Coord,STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	TELP12_INITIAL(DieX,DieY,ModX,ModY,StepX,StepY,Coord,Status,Error);
	return;

/*
	printf("PROBER_INITIAL\n");
	printf(" > DieX\t=%G\n", DieX);
	printf(" > DieY\t=%G\n", DieY);
	printf(" > ModX\t=%G\n", ModX);
	printf(" > ModY\t=%G\n", ModY);
	printf(" < Status\t=%s\n", *Status);
	printf(" < Error\t=%s\n", *Error);
	return;
*/


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
