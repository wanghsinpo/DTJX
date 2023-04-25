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
  Name : TELP12_SETUP
  Vers : 1
  Desc : Specifies product file name
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Drive           S    -        Setup filename                  
  2 Filename        S    -        Setup filename                  

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          S    -        "OK" or "ERROR"                 
  2 Error           S    -        Error message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/

#define DEFAULT_TIMEOUT 5

static int
SRQ_N(int Stb, STRING Filename, STRING *Status, STRING *Error);

extern void
PROBER_SRQ(INTEGER Timeout, INTEGER *Statusbyte);

/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
TELP12_SETUP(STRING Drive,STRING Filename,STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	STRING	Stat, Cmd, Err, Setfile;
	int	i, Stb;
	INTEGER	Rtn;

	strncpy(Setfile, Filename, 20);
	Setfile[20]='\0';

	PROBER_TIMEOUT(DEFAULT_TIMEOUT);
	sprintf(Cmd, "N%s", Setfile);
	PROBER_IOUTPUT(Cmd, &Rtn);
	if (Rtn<0) goto Timout;
					/* Set prod.file */
	PROBER_SRQ(60, &Stb);
	if (SRQ_N(Stb, Filename, Status, Error)<0) goto Error;

	return;

Error:
	return;

Timout:
	strcpy(*Status, "ERROR");
	strcpy(*Error, "#TIMEOUT_IO");
	return;


/*
	printf("TELP12_SETUP\n");
	printf(" > Drive\t=%s\n", Drive);
	printf(" > Filename\t=%s\n", Filename);
	printf(" < Status\t=%s\n", *Status);
	printf(" < Error\t=%s\n", *Error);
	return;
*/


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/


static int SRQ_N(int Stb, STRING Filename, STRING *Status, STRING *Error)
{
	STRING	Err;
	INTEGER	Rtn;

	switch(Stb){
	case -1:
		strcpy(*Status, "ERROR");
		strcpy(*Error, "#TIMEOUT_SRQ");
		return -1;
	case -2:
		strcpy(*Status, "ERROR");
		strcpy(*Error, "#TIMEOUT_SPOLL");
		return -1;
	case 78:
		strcpy(*Status, "ERROR");
		sprintf(*Error, "#NOFILE");
		return -2;
	case 80:
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
