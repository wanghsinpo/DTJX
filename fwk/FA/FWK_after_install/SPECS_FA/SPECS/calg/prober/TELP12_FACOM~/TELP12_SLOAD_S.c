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
  Name : TELP12_SLOAD_S
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

extern void
PROBER_SRQ(INTEGER Timeout, INTEGER *Statusbyte);

static int
SRQ_l(int Cassno, int Slotno, int Stb, STRING *Status, STRING *Error);

/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
TELP12_SLOAD_S(INTEGER Cassno,INTEGER Slotno,STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	int	Stb, Slot, Cn, Waf, Cass;
	INTEGER Rtn;
	STRING	Cmd, Stat, Err;

	PROBER_SRQ(5, &Stb);
	if (SRQ_l(Cassno, Slotno, Stb, Status, Error)<0) goto Error;

	HP_PRBDVR->Prb_curr_dx = HP_PRBDVR->Prb_init_dx;
	HP_PRBDVR->Prb_curr_dy = HP_PRBDVR->Prb_init_dy;
	HP_PRBDVR->Prb_curr_mx = HP_PRBDVR->Prb_init_mx;
	HP_PRBDVR->Prb_curr_my = HP_PRBDVR->Prb_init_my;
	HP_PRBDVR->Prb_curr_x = HP_PRBDVR->Prb_init_dx+HP_PRBDVR->Prb_init_mx;
	HP_PRBDVR->Prb_curr_y = HP_PRBDVR->Prb_init_dy+HP_PRBDVR->Prb_init_my;

	return;

Error:
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


static int
SRQ_l(int Cassno, int Slotno, int Stb, STRING *Status, STRING *Error)
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

        case 70:
                strcpy(*Status, "OK");
                strcpy(*Error, "#INIT_CHIP");
                return 0;

	case 72:
		if ((Cassno==0)||(Slotno==0))
		{
			strcpy(*Status, "OK");	/* l000 for NOP */
			strcpy(*Error, "");
			return 0;
		}else{				/* for l999 to lot end */
                       	strcpy(*Status, "END");
                       	strcpy(*Error, "");
                       	return 0;		/* No more check STB */
		}

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

	case 101:
		strcpy(*Status, "ERROR");
		strcpy(*Error, "#NOWAFER");
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
