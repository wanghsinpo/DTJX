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
  Name : TELP12_WAFID
  Vers : 1
  Desc : Returns wafer ID on the chuck
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Wafid           S    -        ID of wafer on the chuck        
  2 Status          S    -        "OK" or "ERROR"                 
  3 Error           S    -        Error message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/

#define DEFAULT_TIMEOUT	5

/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
TELP12_WAFID(STRING *Wafid,STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	INTEGER Rtn;
	STRING	Waf_id;
        int	i;

	PROBER_TIMEOUT(DEFAULT_TIMEOUT);

	PROBER_IOUTPUT("n", &Rtn);
	if (Rtn<0) goto Timout;
	PROBER_IENTER(30, Waf_id, &Rtn);
	if (Rtn<0) goto Timout;

	strcpy(*Wafid, "");
	strncat(*Wafid, Waf_id, 21);

	strcpy(*Status, "OK");
	strcpy(*Error, "");
	return;

Timout:
	strcpy(*Status, "ERROR");
	strcpy(*Error, "#TIMEOUT_IO");
	return;

/*
	printf("TELP12_WAFID\n");
	printf(" < Wafid\t=%s\n", *Wafid);
	printf(" < Status\t=%s\n", *Status);
	printf(" < Error\t=%s\n", *Error);
	return;
*/


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
