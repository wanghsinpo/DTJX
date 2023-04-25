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
  Name : PROBER_IOUTPUT
  Vers : 1
  Desc : [NEW] Call PROBER_OUTPUT or FA_OUTPUT when OFFLINE case.
       : Date:  ['01/06/20] Initial revision
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Cmd             S    -                                        

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/

static int
FA_OUTPUT(STRING Cmd);

/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
PROBER_IOUTPUT(STRING Cmd,INTEGER *Status)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	if (HP_PRBDVR->Prb_address==2500) 
		*Status=FA_OUTPUT(Cmd);
	else 
		*Status=PROBER_OUTPUT(Cmd);

	return;

/*
	printf("PROBER_IOUTPUT\n");
	printf(" > Cmd\t=%s\n", Cmd);
	printf(" < Status\t=%d\n", *Status);
	return;
*/



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/

static int
FA_OUTPUT(STRING Cmd)
{
	FILE	*fgpib;
	int	i=0;
	STRING	message;
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

	fgpib=fopen("/tmp/fapt/tester-prober", "w");
	fprintf(fgpib, "%s", Cmd);                /* Write GPIB */
	fclose(fgpib);

	sprintf(message, "OUTPUT>%s", Cmd);
	PROBER_LOGWR(message, &status, &errmsg);

	while (1) {
		/* Wait until gpib file is erased */
		if ((fgpib=fopen("/tmp/fapt/tester-prober","r"))==0) {
			break;
		}
		fclose(fgpib);

		if (i==60) break; /* To prevent from hungup */

		if (waittime < 1) {
			usleep((unsigned int)(waittime * _USEC));
		}
		else {
			sleep((unsigned int)waittime);
		}
		i++;
	}
	return 0;
}
