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
  Name : PROBER_CONFIG
  Vers : 1
  Desc : Defines the prober model and GPIB address
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Model           S    -        Prober Model Name               
  2 Address         I    -        Prober GPIB Address             

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          S    -        "OK" or "ERROR"                 
  2 Error           S    -        Error message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
PROBER_CONFIG(STRING Model,INTEGER Address,STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	int	Logmode, flag;
	STRING	Logfile, Cmd;

	strcpy(HP_PRBDVR->Prb_model, Model);

	if ((Address==0)||(((Address/100)>=7)&&((Address/100)<=31))){
		if (((Address%100)>=0)&&((Address%100)<=31)){
			HP_PRBDVR->Prb_address=Address;
		}else{
			strcpy(*Status, "ERROR");
			sprintf(*Error, "#ADDRESS");
			return;
		}
	}else{
		strcpy(*Status, "ERROR");
		sprintf(*Error, "#ADDRESS");
		return;
	}

	HP_PRBDVR->Prb_init_dx=0;
	HP_PRBDVR->Prb_init_dy=0;
	HP_PRBDVR->Prb_init_mx=0;
	HP_PRBDVR->Prb_init_my=0;
	HP_PRBDVR->Prb_curr_dx=0;
	HP_PRBDVR->Prb_curr_dy=0;
	HP_PRBDVR->Prb_curr_mx=0;
	HP_PRBDVR->Prb_curr_my=0;
	HP_PRBDVR->Prb_curr_x=0;
	HP_PRBDVR->Prb_curr_y=0;

	HP_PRBDVR->Prb_coord=1;
	HP_PRBDVR->Prb_flat=0;

        strcpy(Logfile, "/var/opt/SPECS/log/prober.log");
        if (access(Logfile, 0)==0) {
                PROBER_LOG_MODE=1;
                printf("GPIB I/O Logging ON: Logfile= %s\n",Logfile);
                system("chmod 666 /var/opt/SPECS/log/prober.log 2> /dev/null");
        } else {
                PROBER_LOG_MODE=0;
        }

	strcpy(*Status, "OK");
	strcpy(*Error, "");
	return;

Sys_error:
	strcpy(*Status, "ERROR");
	strcpy(*Error, "#LOGGING");
	return;

/*
	printf("PROBER_CONFIG\n");
	printf(" > Model\t=%s\n", Model);
	printf(" > Address\t=%d\n", Address);
	printf(" < Status\t=%s\n", *Status);
	printf(" < Error\t=%s\n", *Error);
	return;
*/


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
