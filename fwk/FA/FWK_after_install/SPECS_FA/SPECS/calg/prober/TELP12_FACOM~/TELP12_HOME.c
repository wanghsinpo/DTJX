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
  Name : TELP12_HOME
  Vers : 1
  Desc : Moves the wafer chuck (stage) to the initial position
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
TELP12_MOVE(REAL DieX,REAL DieY,REAL ModX,REAL ModY,STRING *Status,STRING *Error);

static int
SRQ_B(int Stb, STRING *Status, STRING *Error);

extern void
PROBER_SRQ(INTEGER Timeout, INTEGER *Statusbyte);

/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
TELP12_HOME(STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	INTEGER Rtn;
	INTEGER Stb;

	/*
	printf("Moving back to reference die... (Assuming ref.die=init.die) \n");
	*/

	PROBER_TIMEOUT(DEFAULT_TIMEOUT);

	PROBER_IOUTPUT("B", &Rtn);
	if (Rtn<0) goto Timout;
	PROBER_SRQ(10, &Stb);
	if (SRQ_B(Stb, Status, Error)<0) goto Error;

	HP_PRBDVR->Prb_curr_dx=HP_PRBDVR->Prb_init_dx;
	HP_PRBDVR->Prb_curr_dy=HP_PRBDVR->Prb_init_dy;
	HP_PRBDVR->Prb_curr_mx=HP_PRBDVR->Prb_init_mx;
	HP_PRBDVR->Prb_curr_my=HP_PRBDVR->Prb_init_my;

	HP_PRBDVR->Prb_curr_x=HP_PRBDVR->Prb_init_dx+HP_PRBDVR->Prb_init_mx;
	HP_PRBDVR->Prb_curr_y=HP_PRBDVR->Prb_init_dy+HP_PRBDVR->Prb_init_my;
	return;

Error:
	return;

Timout:
	strcpy(*Status, "ERROR");
	strcpy(*Error, "#TIMEOUT_IO");
	return;
/*
	printf("TELP12_HOME\n");
	printf(" < Status\t=%s\n", *Status);
	printf(" < Error\t=%s\n", *Error);
	return;
*/

/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/


static int
SRQ_B(int Stb, STRING *Status, STRING *Error)
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

	case 70:	/* Going home complete */
		strcpy(*Status, "OK");
		strcpy(*Error, "#INIT_CHIP");
		return 0;

	case 75:
		strcpy(*Status, "OK");
		strcpy(*Error, "#WAF_END");
		return 0;

	case 89:
		PROBER_SRQ(10, &Stb);
		strcpy(*Status, "OK");
		strcpy(*Error, "#INIT_CHIP");
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
