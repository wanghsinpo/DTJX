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
  Name : TELP12_CHKMOVE
  Vers : 1
  Desc : Moves the chuck by X/Ydist[um] relatively
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Xdist           R    -        X(R-L) Movement distance in [um]
  2 Ydist           R    -        Y(F-B) Movement distance in [um]

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          S    -        "OK" or "ERROR"                 
  2 Error           S    -        Error message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/

#define DEFAULT_TIMEOUT  5

#define ABS(x)  (((x)>0)?(x):-(x))

extern void
PROBER_SRQ(INTEGER Timeout, INTEGER *Statusbyte);

static int
SRQ_XY(int Stb, STRING *Status, STRING *Error);

static int
SRQ_IJ(int Stb, STRING *Status, STRING *Error);

extern void
TELP12_UP(STRING *Status, STRING *Error);

/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
TELP12_CHKMOVE(REAL Xdist,REAL Ydist,STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	INTEGER	Stb;
	REAL	Maxindex;
	STRING	Cmd, Stat, Err;
	INTEGER Rtn;

	strcpy(*Status, "OK");
	strcpy(*Error, "#XY_MOVE");

	PROBER_TIMEOUT(DEFAULT_TIMEOUT);

	TELP12_DOWN(&Stat, &Err);
	if (strcmp(Stat, "OK")!=0){
		strcpy(*Status, Stat);
		strcpy(*Error, Err);
		return;
	}

	if ((ABS(Xdist)>99999)){
		strcpy(*Status, "ERROR");
		sprintf(*Error, "#XMTRAVEL");
		return;
	}

	if ((ABS(Ydist)>99999)){
		strcpy(*Status, "ERROR");
		sprintf(*Error, "#YMTRAVEL");
		return;
	}

	if(ABS(Xdist)>=1.0){
		sprintf(Cmd, "I%+06d%02d", (int)(Xdist), 1);	
		PROBER_IOUTPUT(Cmd, &Rtn);
		if (Rtn<0) goto Timout;
		PROBER_SRQ(10, &Stb);
		if(SRQ_IJ(Stb, Status, Error) < 0) goto Error;
	}

	if(ABS(Ydist)>=1.0){
		sprintf(Cmd, "J%+06d%02d", -1*(int)(Ydist), 1);	
		PROBER_IOUTPUT(Cmd, &Rtn);
		if (Rtn<0) goto Timout;
		PROBER_SRQ(10, &Stb);
		if(SRQ_IJ(Stb, Status, Error) < 0) goto Error;
	}

	return;

Error:
	return;

Timout:
	strcpy(*Status, "ERROR");
	strcpy(*Error, "#TIMEOUT_IO");
	return;


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/


static int	  
SRQ_XY(int Stb, STRING *Status, STRING *Error)
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
	case 66:
		strcpy(*Status, "OK");
		strcpy(*Error, "#XY_MOVE");
		return 0;

	case 75:
		strcpy(*Status, "OK");
		strcpy(*Error, "#WAF_END");
		return -2;

	case 79:
		/*
		   P-8 returns STB=79 when probing point moves out of
		   the probe area.
		   However, it happens even when probing the dies on the
		   edge of wafer and micro-moving more than half of the 
		   die pitch.
		   It will be fixed in the future version of P-8 S/W,
		   but until then, #PROBEAREA error should be masked.
		*/

		strcpy(*Status, "OK");
		strcpy(*Error, "#XY_MOVE");
		return 0;
		/*
		strcpy(*Status, "ERROR");
		strcpy(*Error, "#PROBEAREA");
		return -2;
		*/
		/* for XY command, STB=79 is also expected spolled twice! */

	case 80:	/* Prober error */
		PROBER_SRQ(1,&Stb);	/* Clear SRQ if any */
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

static int	  
SRQ_IJ(int Stb, STRING *Status, STRING *Error)
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
	case 66:
		strcpy(*Status, "OK");
		strcpy(*Error, "#XY_MOVE");
		return 0;

	case 75:
		strcpy(*Status, "OK");
		strcpy(*Error, "#WAF_END");
		return -2;

	case 79:
		/*
		   P-8 returns STB=79 when probing point moves out of
		   the probe area.
		   However, it happens even when probing the dies on the
		   edge of wafer and micro-moving more than half of the 
		   die pitch.
		   It will be fixed in the future version of P-8 S/W,
		   but until then, #PROBEAREA error should be masked.
		*/

		strcpy(*Status, "OK");
		strcpy(*Error, "#XY_MOVE");
		return 0;
		/*
		strcpy(*Status, "ERROR");
		strcpy(*Error, "#PROBEAREA");
		return -2;
		*/

	case 80:	/* Prober error */
		PROBER_SRQ(1,&Stb);	/* Clear SRQ if any */
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
