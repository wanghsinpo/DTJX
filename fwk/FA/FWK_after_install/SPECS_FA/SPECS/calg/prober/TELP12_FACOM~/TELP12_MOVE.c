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
  Name : TELP12_MOVE
  Vers : 1
  Desc : Moves the wafer chuck (stage) to the specified position
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 DieX            R    -        Die X position from wafer origin
  2 DieY            R    -        Die Y position from wafer origin
  3 ModX            R    -        Module X position from die origi
  4 ModY            R    -        Module Y position from die origi

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
TELP12_MOVE(REAL DieX,REAL DieY,REAL ModX,REAL ModY,STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	INTEGER	Stb;
	INTEGER Rtn;
	REAL	Xdist, Ydist, Ximove, Yimove, Xumove, Yumove, Xstep, Ystep;
	REAL	Maxindex;
	STRING	Cmd, Stat, Err;

	strcpy(*Status, "OK");
	strcpy(*Error, "#XY_MOVE");

	if ((HP_PRBDVR->Prb_stepx==0)){
		strcpy(*Status, "ERROR");
		sprintf(*Error, "#STEPX");
		return;
	}
	if ((HP_PRBDVR->Prb_stepy==0)){
		strcpy(*Status, "ERROR");
		sprintf(*Error, "#STEPY");
		return;
	}

	Xdist=DieX-HP_PRBDVR->Prb_curr_dx;
	Ydist=DieY-HP_PRBDVR->Prb_curr_dy;

	if ((ABS(Xdist/HP_PRBDVR->Prb_stepx)>99)){
		strcpy(*Status, "ERROR");
		sprintf(*Error, "#XDTRAVEL");
		return;
	}

	if ((ABS(Ydist/HP_PRBDVR->Prb_stepy)>99)){
		strcpy(*Status, "ERROR");
		sprintf(*Error, "#YDTRAVEL");
		return;
	}

	switch(HP_PRBDVR->Prb_coord){
	case 1:
		switch(HP_PRBDVR->Prb_flat){
		case 0:
			Ximove=Xdist;
			Yimove=Ydist;
			Xstep=HP_PRBDVR->Prb_stepx;
			Ystep=HP_PRBDVR->Prb_stepy;
			break;
		case 90:
		case -270:
			Ximove=Ydist;
			Yimove=-Xdist;
			Xstep=HP_PRBDVR->Prb_stepy;
			Ystep=HP_PRBDVR->Prb_stepx;
			break;
		case 180:
		case -180:
			Ximove=-Xdist;
			Yimove=-Ydist;
			Xstep=HP_PRBDVR->Prb_stepx;
			Ystep=HP_PRBDVR->Prb_stepy;
			break;
		case 270:
		case -90:
			Ximove=-Ydist;
			Yimove=Xdist;
			Xstep=HP_PRBDVR->Prb_stepy;
			Ystep=HP_PRBDVR->Prb_stepx;
			break;
		default:
			strcpy(*Status, "ERROR");
			sprintf(*Error, "#FLAT");
			break;
		}
		break;
	case 2:
		switch(HP_PRBDVR->Prb_flat){
		case 0:
			Ximove=-Xdist;
			Yimove=Ydist;
			Xstep=HP_PRBDVR->Prb_stepx;
			Ystep=HP_PRBDVR->Prb_stepy;
			break;
		case 90:
		case -270:
			Ximove=Ydist;
			Yimove=Xdist;
			Xstep=HP_PRBDVR->Prb_stepy;
			Ystep=HP_PRBDVR->Prb_stepx;
			break;
		case 180:
		case -180:
			Ximove=Xdist;
			Yimove=-Ydist;
			Xstep=HP_PRBDVR->Prb_stepx;
			Ystep=HP_PRBDVR->Prb_stepy;
			break;
		case 270:
		case -90:
			Ximove=-Ydist;
			Yimove=-Xdist;
			Xstep=HP_PRBDVR->Prb_stepy;
			Ystep=HP_PRBDVR->Prb_stepx;
			break;
		default:
			strcpy(*Status, "ERROR");
			sprintf(*Error, "#FLAT");
			break;
		}
		break;
	case 3:
		switch(HP_PRBDVR->Prb_flat){
		case 0:
			Ximove=-Xdist;
			Yimove=-Ydist;
			Xstep=HP_PRBDVR->Prb_stepx;
			Ystep=HP_PRBDVR->Prb_stepy;
			break;
		case 90:
		case -270:
			Ximove=-Ydist;
			Yimove=Xdist;
			Xstep=HP_PRBDVR->Prb_stepy;
			Ystep=HP_PRBDVR->Prb_stepx;
			break;
		case 180:
		case -180:
			Ximove=Xdist;
			Yimove=Ydist;
			Xstep=HP_PRBDVR->Prb_stepx;
			Ystep=HP_PRBDVR->Prb_stepy;
			break;
		case 270:
		case -90:
			Ximove=Ydist;
			Yimove=-Xdist;
			Xstep=HP_PRBDVR->Prb_stepy;
			Ystep=HP_PRBDVR->Prb_stepx;
			break;
		default:
			strcpy(*Status, "ERROR");
			sprintf(*Error, "#FLAT");
			break;
		}
		break;
	case 4:
		switch(HP_PRBDVR->Prb_flat){
		case 0:
			Ximove=Xdist;
			Yimove=-Ydist;
			Xstep=HP_PRBDVR->Prb_stepx;
			Ystep=HP_PRBDVR->Prb_stepy;
			break;
		case 90:
		case -270:
			Ximove=-Ydist;
			Yimove=-Xdist;
			Xstep=HP_PRBDVR->Prb_stepy;
			Ystep=HP_PRBDVR->Prb_stepx;
			break;
		case 180:
		case -180:
			Ximove=-Xdist;
			Yimove=Ydist;
			Xstep=HP_PRBDVR->Prb_stepx;
			Ystep=HP_PRBDVR->Prb_stepy;
			break;
		case 270:
		case -90:
			Ximove=Ydist;
			Yimove=Xdist;
			Xstep=HP_PRBDVR->Prb_stepy;
			Ystep=HP_PRBDVR->Prb_stepx;
			break;
		default:
			strcpy(*Status, "ERROR");
			sprintf(*Error, "#FLAT");
			break;
		}
		break;
	default:
		strcpy(*Status, "ERROR");
		sprintf(*Error, "#COORD");
		break;
	}

	PROBER_TIMEOUT(DEFAULT_TIMEOUT);

	if ((Xdist != 0)||(Ydist != 0)){
		sprintf(Cmd, "X%+03dY%+03d", (int)(Ximove/Xstep), -1*(int)(Yimove/Ystep));
		PROBER_IOUTPUT(Cmd, &Rtn);
		if(Rtn < 0) goto Timout; 

		PROBER_SRQ(10, &Stb);
		if (SRQ_XY(Stb, Status, Error)<0) goto Error;

		PROBER_SRQ(10, &Stb);
		if (SRQ_XY(Stb, Status, Error)<0) goto Error;

		HP_PRBDVR->Prb_curr_dx=DieX;
		HP_PRBDVR->Prb_curr_dy=DieY;
	}


	Xdist = ModX - HP_PRBDVR->Prb_curr_mx;
	Ydist = ModY - HP_PRBDVR->Prb_curr_my;

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

	switch(HP_PRBDVR->Prb_coord){
	case 1:
		switch(HP_PRBDVR->Prb_flat){
		case 0:
			Xumove=Xdist;
			Yumove=Ydist;
			break;
		case 90:
		case -270:
			Xumove=Ydist;
			Yumove=-Xdist;
			break;
		case 180:
		case -180:
			Xumove=-Xdist;
			Yumove=-Ydist;
			break;
		case 270:
		case -90:
			Xumove=-Ydist;
			Yumove=Xdist;
			break;
		default:
			strcpy(*Status, "ERROR");
			sprintf(*Error, "#FLAT");
			break;
		}
		break;
	case 2:
		switch(HP_PRBDVR->Prb_flat){
		case 0:
			Xumove=-Xdist;
			Yumove=Ydist;
			break;
		case 90:
		case -270:
			Xumove=Ydist;
			Yumove=Xdist;
			break;
		case 180:
		case -180:
			Xumove=Xdist;
			Yumove=-Ydist;
			break;
		case 270:
		case -90:
			Xumove=-Ydist;
			Yumove=-Xdist;
			break;
		default:
			strcpy(*Status, "ERROR");
			sprintf(*Error, "#FLAT");
			break;
		}
		break;
	case 3:
		switch(HP_PRBDVR->Prb_flat){
		case 0:
			Xumove=-Xdist;
			Yumove=-Ydist;
			break;
		case 90:
		case -270:
			Xumove=-Ydist;
			Yumove=Xdist;
			break;
		case 180:
		case -180:
			Xumove=Xdist;
			Yumove=Ydist;
			break;
		case 270:
		case -90:
			Xumove=Ydist;
			Yumove=-Xdist;
			break;
		default:
			strcpy(*Status, "ERROR");
			sprintf(*Error, "#FLAT");
			break;
		}
		break;
	case 4:
		switch(HP_PRBDVR->Prb_flat){
		case 0:
			Xumove=Xdist;
			Yumove=-Ydist;
			break;
		case 90:
		case -270:
			Xumove=-Ydist;
			Yumove=-Xdist;
			break;
		case 180:
		case -180:
			Xumove=-Xdist;
			Yumove=Ydist;
			break;
		case 270:
		case -90:
			Xumove=Ydist;
			Yumove=Xdist;
			break;
		default:
			strcpy(*Status, "ERROR");
			sprintf(*Error, "#FLAT");
			break;
		}
		break;
	default:
		strcpy(*Status, "ERROR");
		sprintf(*Error, "#COORD");
		break;
	}

	if(ABS(Xumove)>=1.0){
		sprintf(Cmd, "I%+06d%02d", (int)(Xumove), 1);	
		PROBER_IOUTPUT(Cmd, &Rtn);
		if(Rtn < 0) goto Timout; 
		PROBER_SRQ(10, &Stb);
		if(SRQ_IJ(Stb, Status, Error) < 0) goto Error;
	}

	if(ABS(Yumove)>=1.0){
		sprintf(Cmd, "J%+06d%02d", -1*(int)(Yumove), 1);	
		PROBER_IOUTPUT(Cmd, &Rtn);
		if(Rtn < 0) goto Timout; 
		PROBER_SRQ(10, &Stb);
		if(SRQ_IJ(Stb, Status, Error) < 0) goto Error;
	}

	HP_PRBDVR->Prb_curr_mx=HP_PRBDVR->Prb_curr_mx+(int)Xdist;
	HP_PRBDVR->Prb_curr_my=HP_PRBDVR->Prb_curr_my+(int)Ydist;
	HP_PRBDVR->Prb_curr_x=HP_PRBDVR->Prb_curr_dx+HP_PRBDVR->Prb_curr_mx;
	HP_PRBDVR->Prb_curr_y=HP_PRBDVR->Prb_curr_dy+HP_PRBDVR->Prb_curr_my;

	TELP12_UP(&Stat, &Err);
	if (strcmp(Stat, "OK")!=0){
		strcpy(*Status, Stat);
		strcpy(*Error, Err);
		return;
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
