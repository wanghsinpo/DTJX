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
  Name : TELP12_RJLOT_S
  Vers : 1
  Desc : Unloads the present wafer and loads the next wafer from cassette
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

static int
SRQ_VF(int Stb, STRING *Status, STRING *Error);

extern void
PROBER_SRQ(INTEGER Timeout, INTEGER *Statusbyte);

/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
TELP12_RJLOT_S(STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

        INTEGER Stb;
        INTEGER Rtn;

        PROBER_SRQ(5, &Stb);
        if (SRQ_VF(Stb, Status, Error)<0) goto Error;
        return;

Error:
        return;


/*
	printf("TELP12_RJLOT_S\n");
	printf(" < Status\t=%s\n", *Status);
	printf(" < Error\t=%s\n", *Error);
	return;
*/



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/

static int
SRQ_VF(int Stb, STRING *Status, STRING *Error)
{
        INTEGER Rtn;    /* For factory automation */
        STRING  Err;

        switch(Stb){
        case -1:                        /* Timeout */
                strcpy(*Status, "ERROR");
                strcpy(*Error, "#TIMEOUT_SRQ");
                return -1;

        case -2:                        /* Timeout */
                strcpy(*Status, "ERROR");
                strcpy(*Error, "#TIMEOUT_SPOLL");
                return -1;

        case 72:                        /* Lot End (0x48) */
                strcpy(*Status, "END");
                strcpy(*Error, "");
                return 0;               /* No more check STB */

        case 74:                        /* Initial wafer (0x4a) */
                PROBER_SRQ(100, &Stb);  /* Wait for next SRQ */
                switch (Stb){
                case -1:
                        strcpy(*Status, "ERROR");
                        strcpy(*Error, "#TIMEOUT_SRQ");
                        return -1;

                case -2:
                        strcpy(*Status, "ERROR");
                        strcpy(*Error, "#TIMEOUT_SPOLL");
                        return -1;

                case 80:                /* Prober error */
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

        case 76:
                strcpy(*Status, "ERROR");
                strcpy(*Error, "#ALIGN_REJECT");
                return -2;

        case 78:
                strcpy(*Status, "ERROR");
                strcpy(*Error, "#ALIGN_ASSIST");
                return -2;

        case 80:        /* Prober error */
                PROBER_IOUTPUT("s", &Rtn);
                if (Rtn<0) goto Timout;
                PROBER_IENTER(20, Err, &Rtn);
                if (Rtn<0) goto Timout;
                strcpy(*Status, "ERROR");
                sprintf(*Error, "#ERROR %s", Err);
                return -2;

        case 96:        /* Unload complete for next "l"(non-pipelining mode) */
                strcpy(*Status, "OK");
                strcpy(*Error, "#SLOAD_READY");
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

