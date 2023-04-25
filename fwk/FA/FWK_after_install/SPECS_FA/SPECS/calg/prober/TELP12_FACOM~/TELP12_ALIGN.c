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
  Name : TELP12_ALIGN
  Vers : 1
  Desc : Aligns wafer and move chuck to the initial position
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          S    -        "OK" or "ERROR"                 
  2 Error           S    -        Error message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/

#define	DEFAULT_TIMEOUT	5

static int
VAL(STRING string, INTEGER width);

extern void
TELP12_SLOAD(INTEGER Cassno, INTEGER Slotno, STRING *Status, STRING *Error);


/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
TELP12_ALIGN(STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	int	Cassno, Slotno;
	STRING	Cass_stat;
	INTEGER Rtn;

	PROBER_TIMEOUT(DEFAULT_TIMEOUT);
	PROBER_IOUTPUT("S", &Rtn);
	if (Rtn<0) goto Timout;
	PROBER_IENTER(10, Cass_stat, &Rtn);
	if (Rtn<0) goto Timout;

	Slotno=VAL(Cass_stat, 2);
	if (Slotno==0){
		strcpy(*Status, "ERROR");
		strcpy(*Error, "#NOWAFER");
		return;
	}

	Cassno=0;
	if (Cass_stat[4]=='2'){
		Cassno=1;
	}
	if (Cass_stat[5]=='2'){
		Cassno=2;
	}
	if (Cassno==0){
		strcpy(*Status, "ERROR");
		strcpy(*Error, "#NOT_READY");
		return;
	}

	/*
		The fllowing function will once unload the current wafer
		and re-load the same wafer to align it again.
		It may take for as much as 2 minutes.
		It's available only when P-12 is set non-pipeline mode.
	*/

	TELP12_SLOAD(Cassno, Slotno, Status, Error);
	return;

Timout:
	strcpy(*Status, "ERROR");
	strcpy(*Error, "#TIMEOUT_IO");
	return;
	
/*
	printf("TELP12_ALIGN\n");
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
