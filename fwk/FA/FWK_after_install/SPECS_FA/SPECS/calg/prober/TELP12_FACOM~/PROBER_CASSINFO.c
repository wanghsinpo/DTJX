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
  Name : PROBER_CASSINFO
  Vers : 1
  Desc : Returns cassette information
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Slotno          I    -        Wafer slot position             
  2 Cassno          I    -        Cassette number of wafer origine
  3 Wafcount        I    -        Remaining number of wafers in cu
  4 Casscount       I    -        Remaining number of cassettes   
  5 Status          S    -        "OK" or "ERROR"                 
  6 Error           S    -        Error message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/

extern void
TELP12_CASSINFO(INTEGER *Slotno, INTEGER *Cassno, INTEGER *Wafcount, INTEGER *Casscount,
	STRING *Status, STRING *Error);

/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
PROBER_CASSINFO(INTEGER *Slotno,INTEGER *Cassno,INTEGER *Wafcount,INTEGER *Casscount,STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	TELP12_CASSINFO(Slotno, Cassno, Wafcount, Casscount, Status, Error);
	return;

/*
	printf("PROBER_CASSINFO\n");
	printf(" < Slotno\t=%d\n", *Slotno);
	printf(" < Wafcount\t=%d\n", *Wafcount);
	printf(" < Casscount\t=%d\n", *Casscount);
	printf(" < Status\t=%s\n", *Status);
	printf(" < Error\t=%s\n", *Error);
	return;
*/



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
