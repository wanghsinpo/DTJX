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
  Name : TELP12_SLOAD
  Vers : 1
  Desc : [NEW] Loads specified wafer from the specified cassette.
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Cassno          I    -        1 or 2                          
  2 Slotno          I    -        1 to 25                         

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          S    -        "OK" or "ERROR"                 
  2 Error           S    -        Error message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/

#define DEFAULT_TIMEOUT  5

/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
TELP12_SLOAD(INTEGER Cassno,INTEGER Slotno,STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	int	Stb, Slot, Cn, Waf, Cass;
	INTEGER Rtn;
	STRING	Cmd, Stat, Err;

	switch(Cassno){
	case 0:	/* Cassno=0 or Slotno=0 for unload only */
		TELP12_CASSINFO(&Slot, &Cn, &Waf, &Cass, Stat, Err);
		if (Slot!=0){
			TELP12_LOAD(Stat, Err);
			if (strcmp(Stat, "OK")==0)
			    TELP12_LOAD_S(Stat, Err);
		}
		strcpy(*Status, Stat);
		strcpy(*Error, Err);
		return;
		break;
	case 1:
	case 2:
		break;
	case 9:
		Slotno=99;
		break;
	default:
		strcpy(*Status, "ERROR");
		sprintf(*Error, "#CASSNO");
		return;
	}

	switch(Slotno){
	case 0:	/* Cassno=0 or Slotno=0 for unload only */
		TELP12_CASSINFO(&Slot, &Cn, &Waf, &Cass, Stat, Err);
		if (Slot!=0){
			TELP12_LOAD(Stat, Err);
			if (strcmp(Stat, "OK")==0)
			    TELP12_LOAD_S(Stat, Err);
		}
		strcpy(*Status, Stat);
		strcpy(*Error, Err);
		return;
		break;
	case 99:
		Cassno=9;
		break;
	default:
		if ((Slotno<1) || (Slotno>25)){
			strcpy(*Status, "ERROR");
			sprintf(*Error, "#SLOTNO");
			return;
		}
	}

	PROBER_TIMEOUT(DEFAULT_TIMEOUT);
	sprintf(Cmd, "l%1d%02d", Cassno, Slotno);
	PROBER_IOUTPUT(Cmd, &Rtn);
	if(Rtn < 0) goto Timout;

	strcpy(*Status, "OK");
	strcpy(*Error, "#TIMEOUT_SRQ");

	return;

Error:
	return;

Timout:
	strcpy(*Status, "ERROR");
	strcpy(*Error, "#TIMEOUT_IO");
	return;

/*
	printf("TELP12_SLOAD\n");
	printf(" > Cassno\t=%d\n", Cassno);
	printf(" > Slotno\t=%d\n", Slotno);
	printf(" < Status\t=%s\n", *Status);
	printf(" < Error\t=%s\n", *Error);
	return;
*/


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
