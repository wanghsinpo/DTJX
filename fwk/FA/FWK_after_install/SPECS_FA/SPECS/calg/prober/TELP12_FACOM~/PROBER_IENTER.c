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
  Name : PROBER_IENTER
  Vers : 1
  Desc : [NEW] Call PROBER_ENTER or FA_ENTER when OFFLINE case.
       : Date:    ['01/06/20] Initial revision
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Timeout         I    -                                        

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Dt              S    -                                        
  2 Status          I    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/

static int
FA_ENTER(STRING *Dt, INTEGER Timeout);

/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
PROBER_IENTER(INTEGER Timeout,STRING *Dt,INTEGER *Status)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	char	buf[32];
	char	data[256];
	int	i=0;

	if (HP_PRBDVR->Prb_address==2500)
		*Status=FA_ENTER(Dt, Timeout);
	else {
		*Status=PROBER_ENTER(*Dt, Timeout);
	}

	return;

/*
	printf("PROBER_IENTER\n");
	printf(" < Data\t=%s\n", *Dt);
	printf(" < Timeout\t=%d\n", Timeout);
	printf(" < Status\t=%d\n", *Status);
	return;
*/



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/

static int
FA_ENTER(STRING *Dt, INTEGER Timeout)
{
	FILE	*fgpib;
	int	i=0;
	STRING	ent_val, message;
	STRING	status, errmsg;

	const INTEGER	_USEC = 1e+6;
	char	*gain = getenv("PRBSIM_WAITTIME_GAIN");
	char	*offset = getenv("PRBSIM_WAITTIME_OFFSET");
	double	waittime = 1.0;

	if (gain != NULL) {
		waittime *= atof(gain);
	}
	if (offset != NULL) {
		waittime += atof(offset);
	}

	if (waittime < 1) {
		usleep((unsigned int)(waittime * _USEC));
	}
	else {
		sleep((unsigned int)waittime);
	}
	while (1) {
		/* Wait until gpib file can be read */
		if((fgpib=fopen("/tmp/fapt/prober-tester","r"))!=0) {
			break;
		}

		if (i==60) {
			strcpy(*Dt, "None");
			return -1; /* To prevent from hungup */
		}
		if (waittime < 1) {
			usleep((unsigned int)(waittime * _USEC));
		}
		else {
			sleep((unsigned int)waittime);
		}
		i++;
	}

	fgets(ent_val, sizeof ent_val, fgpib);        /* Read GPIB */
	fclose(fgpib);

	strcpy(*Dt, ent_val);
	sprintf(message, "ENTER < %s", ent_val);
	PROBER_LOGWR(message, &status, &errmsg);

	system("rm -f /tmp/fapt/prober-tester");     /* Delete prober file */
	return 0;
}
