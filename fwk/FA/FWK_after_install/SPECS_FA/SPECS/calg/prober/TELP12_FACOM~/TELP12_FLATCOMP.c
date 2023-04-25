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
  Name : TELP12_FLATCOMP
  Vers : 1
  Desc : Gets prober orientation flat angle and save delta from TPL
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Tpl_OriFla      I    -        Flat angle defined in TPL       

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Prb_OriFla      I    -        Flat angle defined in prober    
  2 Status          S    -        "OK" or "ERROR"                 
  3 Error           S    -        Error message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/

#define DEFAULT_TIMEOUT  5

/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
TELP12_FLATCOMP(INTEGER Tpl_OriFla,INTEGER *Prb_OriFla,STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	STRING  P_para;
	INTEGER	Rtn;

	*Prb_OriFla=-1;
	strcpy(*Status, "OK");
	strcpy(*Error, "");

	PROBER_TIMEOUT(DEFAULT_TIMEOUT);
	PROBER_IOUTPUT("G", &Rtn);
	if (Rtn<0) goto Timout;
	PROBER_IENTER(255, P_para, &Rtn);
	if (Rtn<0) goto Timout;

	switch(P_para[21]){
	case '0':
		*Prb_OriFla=0;
		break;
	case '3':
		*Prb_OriFla=90;
		break;
	case '5':
		*Prb_OriFla=180;
		break;
	case '7':
		*Prb_OriFla=270;
		break;
	default:
		strcpy(*Status, "ERROR");
		strcpy(*Error, "#PRB_FLAT");
		break;
	}

	if (Tpl_OriFla==-1){
		return;
	}else{
		switch(Tpl_OriFla){
		case 0:
		case 360:
		case -360:
			Tpl_OriFla=0;
			break;
		case 90:
		case -270:
			Tpl_OriFla=90;
			break;
		case 180:
		case -180:
			Tpl_OriFla=180;
			break;
		case 270:
		case -90:
			Tpl_OriFla=270;
			break;
		default:
			strcpy(*Status, "ERROR");
			strcpy(*Error, "#TPL_FLAT");
			break;
		}
	}

	HP_PRBDVR->Prb_flat=*Prb_OriFla-Tpl_OriFla;
	return;

Timout:
	strcpy(*Status, "ERROR");
	strcpy(*Error, "#TIMEOUT_IO");
	return;
/*
	printf("PROBER_FLATCOMP\n");
	printf(" > Tpl_OriFla\t=%d\n", Tpl_OriFla);
	printf(" < Prb_OriFla\t=%d\n", *Prb_OriFla);
	printf(" < Status\t=%s\n", *Status);
	printf(" < Error\t=%s\n", *Error);
	return;
*/


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
