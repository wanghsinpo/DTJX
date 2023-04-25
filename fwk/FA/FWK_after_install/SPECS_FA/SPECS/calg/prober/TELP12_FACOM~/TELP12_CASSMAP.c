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
  Name : TELP12_CASSMAP
  Vers : 1
  Desc : Returns cassette map
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Cassmap         I    50       Cassette map                    
  2 Status          S    -        "OK" or "ERROR"                 
  3 Error           S    -        Error message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/

#define	DEFAULT_TIMEOUT	5

/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
TELP12_CASSMAP(INTEGER *Cassmap,STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	STRING	Stat, Err;
	int	i, Stb;
	INTEGER Rtn;

	for (i=0; i<50; i++){
		Cassmap[i]=0;
	}

	PROBER_TIMEOUT(DEFAULT_TIMEOUT);

	PROBER_IOUTPUT("d", &Rtn);
	if (Rtn<0) goto Timout;
	PROBER_IENTER(60, Stat, &Rtn);
	if (Rtn<0) goto Timout;
				/* 1xxx..xx2yyy..yy total 52 byte */

	for (i=0; i<25; i++){		/* Cassette #1 */
		if (Stat[i+1]=='a'){
			Cassmap[i]=1;
		}else{
			Cassmap[i]=0;
		}
	}

	for (i=25; i<50; i++){		/* Cassette #2 */
		if (Stat[i+2]=='a'){
			Cassmap[i]=1;
		}else{
			Cassmap[i]=0;
		}
	}

	strcpy(*Status, "OK");
	strcpy(*Error, "");
	return;

Timout:
	strcpy(*Status, "ERROR");
	strcpy(*Error, "#TIMEOUT_IO");
	return;


/*
	printf("TELP12_CASSMAP\n");
	printf(" < Cassmap\t=\n");
	printf(" < Status\t=%s\n", *Status);
	printf(" < Error\t=%s\n", *Error);
	return;
*/


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
