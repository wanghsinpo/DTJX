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
  Name : PROBER_SRQ
  Vers : 1
  Desc : [UPDATE] Waits until SRQ is asserted
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Timeout         I    -        Timeout in seconds              

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Statusbyte      I    -        Status byte                     

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/

static int
FA_SPOLL(INTEGER Timeout);

/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
PROBER_SRQ(INTEGER Timeout,INTEGER *Statusbyte)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	if (HP_PRBDVR->Prb_address==2500) {
		*Statusbyte=FA_SPOLL(Timeout);
		if (*Statusbyte==-1) goto Timeout;
	} else { 
		if (Timeout>0){
			if (PROBER_WAITSRQ(Timeout)<0) goto Timeout;
		}
		*Statusbyte=PROBER_SPOLL();
	}
	if (*Statusbyte<0) goto Noresp;

	return;

Noresp:
	*Statusbyte=-2;		/* #TIMEOUT_SPOLL */
	return;

Timeout:
	*Statusbyte=-1;		/* #TIMEOUT_SRQ */
	return;

/*
	printf("PROBER_SRQ\n");
	printf(" > Timeout\t=%d\n", Timeout);
	printf(" < Statusbyte\t=%d\n", *Statusbyte);
	return;
*/



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/

static int
FA_SPOLL(INTEGER Timeout)
{
	FILE	*fgpib;
	int	i=0;
	int	waits=0;
	STRING	num, message;
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
			fclose(fgpib);
			break;
		}
		if (waittime < 1) {
			usleep((unsigned int)(waittime * _USEC));
		}
		else {
			sleep((unsigned int)waittime);
		}
		if (waits > Timeout) {
			return -1;
		}
		waits++;
	}

	num[0]='\0';
	while (1) {
		fgpib=fopen("/tmp/fapt/prober-tester","r");
		fscanf(fgpib, "%s", num);                 /* Read SRQ in GPIB */
		fclose(fgpib);

		/* Confirm to get the number from the file */
		if (('0'<=num[0])&&(num[0]<='9')) {
			break;
		}

		if (i==60) {  /* To prevent from hung up */
			return -1;
		}
		if (waittime < 1) {
			usleep((unsigned int)(waittime * _USEC));
		}
		else {
			sleep((unsigned int)waittime);
		}
		i++;
	}

	sprintf(message, "STB   = %d", atoi(num));
	PROBER_LOGWR(message, &status, &errmsg);

	system("rm -f /tmp/fapt/prober-tester");      /* Delete prober file */
	return atoi(num);
}

