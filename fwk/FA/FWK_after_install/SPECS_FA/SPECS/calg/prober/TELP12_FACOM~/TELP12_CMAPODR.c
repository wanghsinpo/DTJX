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
  Name : TELP12_CMAPODR
  Vers : 1
  Desc : [UPDATE] Set cassette map of the current cassette.
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Cassno          S    -                                        
  2 Slotstat        I    50       Cassette map to be set. (0:SKIP,

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          S    -        "OK" or "ERROR"                 
  2 Error           S    -        Error message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/

#define	DEFAULT_TIMEOUT	5

static int
SRQ_RL(int Stb, STRING *Status, STRING *Error);

extern void
PROBER_SRQ(INTEGER Timeout, INTEGER *Statusbyte);

/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
TELP12_CMAPODR(STRING Cassno,INTEGER *Slotstat,STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	INTEGER	Rtn;
	INTEGER	i, Stb;
	STRING	Stat;
	char	buf[3];

	sprintf(Stat, "RL,%s,", Cassno);

	for (i=0; i<25; i++){
		strcpy(buf,"");
		if ((1<=Slotstat[i])&&(Slotstat[i]<=9)){
			sprintf(buf,"0%d",Slotstat[i]);
		}else if((10<=Slotstat[i])&&(Slotstat[i]<=25)){
			sprintf(buf,"%d",Slotstat[i]);
		}else{
			strcpy(buf,"  ");
		}
		strcat(Stat,buf);
	}

	PROBER_TIMEOUT(DEFAULT_TIMEOUT);

	PROBER_IOUTPUT(Stat, &Rtn);
	if (Rtn<0) goto Timout;
	PROBER_SRQ(300, &Stb);
	if (SRQ_RL(Stb, Status, Error)<0) goto Error; 

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
SRQ_RL(int Stb, STRING *Status, STRING *Error)
{
	STRING	Err;
	INTEGER	Rtn;

        switch(Stb){
	case -1:        /* Timeout */
		strcpy(*Status, "ERROR");
		strcpy(*Error, "#TIMEOUT_SRQ");
		return -1;

	case -2:
		strcpy(*Status, "ERROR");
		strcpy(*Error, "#TIMEOUT_SPOLL");
		return -1;

	case 80:        /* Prober error */
		PROBER_IOUTPUT("s", &Rtn);
		if (Rtn<0) goto Timout;
		PROBER_IENTER(20, Err, &Rtn);
		if (Rtn<0) goto Timout;
		strcpy(*Status, "ERROR");
		sprintf(*Error, "#ERROR %s", Err);
		return -2;

	case 254:       /* Prober error */
		PROBER_IOUTPUT("s", &Rtn);
		if (Rtn<0) goto Timout;
		PROBER_IENTER(20, Err, &Rtn);
		if (Rtn<0) goto Timout;
		strcpy(*Status, "ERROR");
		sprintf(*Error, "#ERROR %s", Err);
		return -2;

	case 89:
		strcpy(*Status, "OK");
		strcpy(*Error, "");
		return 0;

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
