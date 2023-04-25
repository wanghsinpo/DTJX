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
  Name : TELP12_INITIAL
  Vers : 1
  Desc : Defines the initial die/module location
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 DieX            R    -        Initial Die X position from wafe
  2 DieY            R    -        Initial Die Y position from wafe
  3 ModX            R    -        Initial Module X position from d
  4 ModY            R    -        Initial Module Y position from d
  5 StepX           R    -        X index size in um              
  6 StepY           R    -        Y index size in um              
  7 Coord           I    -        XY Coordinate System (1..4)     

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          S    -        "OK" or "ERROR"                 
  2 Error           S    -        Error message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/

#define DEFAULT_TIMEOUT  5

static int
VAL(STRING string, INTEGER width);

/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
TELP12_INITIAL(REAL DieX,REAL DieY,REAL ModX,REAL ModY,REAL StepX,REAL StepY,INTEGER Coord,STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	INTEGER Rtn;
	STRING	P_para;

	HP_PRBDVR->Prb_init_dx=DieX;
	HP_PRBDVR->Prb_init_dy=DieY;
	HP_PRBDVR->Prb_init_mx=ModX;
	HP_PRBDVR->Prb_init_my=ModY;

	HP_PRBDVR->Prb_curr_dx=DieX;
	HP_PRBDVR->Prb_curr_dy=DieY;
	HP_PRBDVR->Prb_curr_mx=ModX;
	HP_PRBDVR->Prb_curr_my=ModY;

	HP_PRBDVR->Prb_curr_x=DieX+ModX;
	HP_PRBDVR->Prb_curr_y=DieY+ModY;

	strcpy(*Status, "OK");
	strcpy(*Error, "");

	PROBER_TIMEOUT(DEFAULT_TIMEOUT);
	PROBER_IOUTPUT("G", &Rtn);
	if (Rtn<0) goto Timout;
	PROBER_IENTER(255, P_para, &Rtn);
	if (Rtn<0) goto Timout;
	
	if (StepX==0.0){
		if ((HP_PRBDVR->Prb_flat==0)||(HP_PRBDVR->Prb_flat==180)||(HP_PRBDVR->Prb_flat==-180)){
			HP_PRBDVR->Prb_stepx=(double)VAL(P_para+22, 5);
		}else{
			HP_PRBDVR->Prb_stepx=(double)VAL(P_para+27, 5);
		}
	}else{
		HP_PRBDVR->Prb_stepx=StepX;
		if (StepX!=(double)VAL(P_para+22, 5)){
			strcpy(*Status, "ERROR");
			sprintf(*Error, "#STEPX");
			return;
		}
	}

	if (StepY==0.0){
		if ((HP_PRBDVR->Prb_flat==0)||(HP_PRBDVR->Prb_flat==180)||(HP_PRBDVR->Prb_flat==-180)){
			HP_PRBDVR->Prb_stepy=(double)VAL(P_para+27, 5);
		}else{
			HP_PRBDVR->Prb_stepy=(double)VAL(P_para+22, 5);
		}
	}else{
		HP_PRBDVR->Prb_stepy=StepY;
		if (StepY!=(double)VAL(P_para+27, 5)){
			strcpy(*Status, "ERROR");
			sprintf(*Error, "#STEPY");
			return;
		}
	}

	if ((Coord==1)||(Coord==2)||(Coord==3)||(Coord==4)){
		HP_PRBDVR->Prb_coord=Coord;
	}else{
		strcpy(*Status, "ERROR");
		sprintf(*Error, "#COORD");
		return;
	}

	return;

Timout:
	strcpy(*Status, "ERROR");
	strcpy(*Error, "#TIMEOUT_IO");
	return;
/*
	printf("TELP12_INITIAL\n");
	printf(" > DieX\t=%G\n", DieX);
	printf(" > DieY\t=%G\n", DieY);
	printf(" > ModX\t=%G\n", ModX);
	printf(" > ModY\t=%G\n", ModY);
	printf(" < Status\t=%s\n", *Status);
	printf(" < Error\t=%s\n", *Error);
	return;
*/


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/


static int
VAL(STRING string, INTEGER width)
{
	STRING  buf;
	INTEGER int_val;

	strncpy(buf, string, width);
	buf[width]='\0';
	int_val=atoi(buf);

	return int_val;
}
