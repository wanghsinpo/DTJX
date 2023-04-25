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
  Name : TELP12_GETCMAP
  Vers : 1
  Desc : [NEW] Get cassette map by using GPIB command "?CS" to the prober
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Cassno          S    -                                        

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Cassmap         I    50       Cassette map to be set. (0:SKIP,
  2 Status          S    -        "OK" or "ERROR"                 
  3 Error           S    -        Error message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/

#define	DEFAULT_TIMEOUT	5

/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
TELP12_GETCMAP(STRING Cassno,INTEGER *Cassmap,STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	INTEGER i;
	INTEGER Rtn; /* For factory automation */
	STRING	Stat;
	STRING  Cmd;

	sprintf(Cmd, "?CS,%s", Cassno);
	Cmd[5]='\0';

	PROBER_IOUTPUT(Cmd, &Rtn);
	if (Rtn<0) goto Timout;
	PROBER_IENTER(60, Stat, &Rtn);
	if (Rtn<0) goto Timout;

	for (i=0; i<25; i++){	
		if (Stat[i]=='0'){
			Cassmap[i]=0;
		}else{
			Cassmap[i]=1;
		}
	}

	strcpy(*Status, "OK");
	strcpy(*Error, "");
	return;

Timout:
	strcpy(*Status, "ERROR");
	strcpy(*Error, "#TIMEOUT_IO");
	return;


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
