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
  Name : TELP12_CLEAN
  Vers : 1
  Desc : Executes probe cleaning with cleaning plate
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          S    -        "OK" or "ERROR"                 
  2 Error           S    -        Error message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/

#define DEFAULT_TIMEOUT 5

extern void
PROBER_SRQ(INTEGER Timeout, INTEGER *Statusbyte);

static int
SRQ_p(int Stb, STRING *Status, STRING *Error);

/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
TELP12_CLEAN(STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

        INTEGER Stb;
	INTEGER	Rtn;

        PROBER_TIMEOUT(DEFAULT_TIMEOUT);

	PROBER_IOUTPUT("p", &Rtn);/* Probe Tip Cleaning */
	if (Rtn<0) goto Timout;

        PROBER_SRQ(100, &Stb);
        if (SRQ_p(Stb, Status, Error)<0) goto Error;

        return;

Error:
        return;

Timout:
        strcpy(*Status, "ERROR");
        strcpy(*Error, "#TIMEOUT_IO");
        return;


/*
	printf("TELP12_CLEAN\n");
	printf(" < Status\t=%s\n", *Status);
	printf(" < Error\t=%s\n", *Error);
	return;
*/


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/

static int
SRQ_p(int Stb, STRING *Status, STRING *Error)
{
	STRING  Err;
	INTEGER	Rtn;

	switch(Stb){
	case -1:	/* Timeout */
		strcpy(*Status, "ERROR");
		strcpy(*Error, "#TIMEOUT_SRQ");
		return -1;

	case -2:	/* Timeout */
		strcpy(*Status, "ERROR");
		strcpy(*Error, "#TIMEOUT_SPOLL");
		return -1;

	case 89:	/* Cleaning complete */
		strcpy(*Status, "OK");
		strcpy(*Error, "");
		return 0;

	case 80:	/* Prober error */
		PROBER_IOUTPUT("s", &Rtn);
		if (Rtn<0) goto Timout;
		PROBER_IENTER(20, Err, &Rtn);
		if (Rtn<0) goto Timout;
		strcpy(*Status, "ERROR");
		sprintf(*Error, "#ERROR %s", Err);
		return -2;

	default:
		strcpy(*Status, "ERROR");
		sprintf(*Error, "#SRQ %d", Stb);
		return -2;
	}

Timout:
        strcpy(*Status, "ERROR");
        strcpy(*Error, "#TIMEOUT_IO");
        return -1;
}
