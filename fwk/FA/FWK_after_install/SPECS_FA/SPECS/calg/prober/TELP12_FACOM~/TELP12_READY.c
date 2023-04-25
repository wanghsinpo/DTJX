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
  Name : TELP12_READY
  Vers : 1
  Desc : Waits for prober ready SRQ
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Timeout         I    -        Wait time for SRQ               

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          S    -        "OK" or "ERROR"                 
  2 Error           S    -        Error message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/

#define DEFAULT_TIMEOUT 5

static int
SRQ(int Stb, STRING *Status, STRING *Error);

extern void
PROBER_SRQ(INTEGER Timeout, INTEGER *Statusbyte);

/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
TELP12_READY(INTEGER Timeout,STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	INTEGER	Stb;
	INTEGER	Rtn;

	PROBER_TIMEOUT(DEFAULT_TIMEOUT);

	PROBER_SRQ(Timeout, &Stb);
	if (SRQ(Stb, Status, Error)<0) goto Error;

	return;

Error:
	return;

/*
	printf("TELP12_READY\n");
	printf(" < Status\t=%s\n", *Status);
	printf(" < Error\t=%s\n", *Error);
	return;
*/


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/

static int
SRQ(int Stb, STRING *Status, STRING *Error)
{
	STRING  Err;
	INTEGER	Rtn;

	switch(Stb){
        case -1:
                strcpy(*Status, "ERROR");
                strcpy(*Error, "#TIMEOUT_SRQ");
                return -1;

        case -2:
                strcpy(*Status, "ERROR");
                strcpy(*Error, "#TIMEOUT_SPOLL");
                return -1;

        case 65:
        case 67:
        case 79:
                strcpy(*Status, "OK");
                strcpy(*Error, "#XY_MOVE");
		PROBER_SRQ(5, &Stb);	/* To clear 2nd SRQ, if any */
                return 0;

        case 66:
                strcpy(*Status, "OK");
                strcpy(*Error, "#XY_MOVE");
                return 0;

        case 70:
                strcpy(*Status, "OK");
                strcpy(*Error, "#INIT_CHIP");
                return 0;

	case 72:
                strcpy(*Status, "END");
                sprintf(*Error, "");
		return 0;

        case 74:
                PROBER_SRQ(300, &Stb);  /* Wait for next SRQ */
                switch (Stb){
                case -1:
                        strcpy(*Status, "ERROR");
                        strcpy(*Error, "#TIMEOUT_SRQ");
                        return -1;

                case -2:
                        strcpy(*Status, "ERROR");
                        strcpy(*Error, "#TIMEOUT_SPOLL");
                        return -1;

                case 70:                /* Initial Chip */
                        strcpy(*Status, "OK");
                        strcpy(*Error, "#INIT_WAFER");
                        return 0;

		case 80:		/* Prober error */
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

	case 75:
		strcpy(*Status, "OK");
		strcpy(*Error, "#WAF_END");
		return -2;

	case 76:
		strcpy(*Status, "ERROR");
		strcpy(*Error, "#ALIGN_REJECT");
		return -2;

	case 78:
		strcpy(*Status, "ERROR");
		strcpy(*Error, "#ALIGN_ASSIST");
		return -2;

	case 80:	/* Prober error */
		PROBER_IOUTPUT("s", &Rtn);
		if (Rtn<0) goto Timout;
		PROBER_IENTER(20, Err, &Rtn);
		if (Rtn<0) goto Timout;
		strcpy(*Status, "ERROR");
		sprintf(*Error, "#ERROR %s", Err);
		return -2;

	case 82:        /* Ready to accept product file name(if anabled) */
		strcpy(*Status, "OK");
		strcpy(*Error, "#SETUP_READY");
		return 0;

	case 89:        /* Ready to accept product file name(if anabled) */
		strcpy(*Status, "OK");
		strcpy(*Error, "#CONTINUE");
		return 0;

	case 96:        /* Unload complete for next "l"(non-pipelining mode) */
		strcpy(*Status, "OK");
		strcpy(*Error, "#SLOAD_READY");
		return 0;

	case 112:	/* Cass.mapping done (If enabled) */
		strcpy(*Status, "OK");
		strcpy(*Error, "#CASSMAP_READY");
		return 0;

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
