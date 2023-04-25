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
  Name : TELP12_CASSINFO
  Vers : 1
  Desc : Returns cassette information
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Slotno          I    -        Wafer slot position             
  2 Cassno          I    -        Cassette number of wafer origine
  3 Wafcount        I    -        Remaining number of wafers in cu
  4 Casscount       I    -        Remaining number of cassettes   
  5 Status          S    -        "OK" or "ERROR"                 
  6 Error           S    -        Error message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/

#define DEFAULT_TIMEOUT 5

static int
VAL(STRING string, INTEGER width);

/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
TELP12_CASSINFO(INTEGER *Slotno,INTEGER *Cassno,INTEGER *Wafcount,INTEGER *Casscount,STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	STRING	Stat;
	INTEGER Rtn;
	int	i;


	*Slotno=0;
	*Cassno=0;
	*Wafcount=0;
	*Casscount=0;

	PROBER_TIMEOUT(DEFAULT_TIMEOUT);

	PROBER_IOUTPUT("S", &Rtn);
	if (Rtn<0) goto Timout;
	PROBER_IENTER(60, Stat, &Rtn);
	if (Rtn<0) goto Timout;

	if (strncmp(Stat+2,"FF",2)==0){ /* if Stat[2,3]="FF", not yet mapped */
		strcpy(*Status, "ERROR");
		strcpy(*Error, "#NOT_READY");
		return;
	}else{
		if ((Stat[4]=='0') && (Stat[5]=='0')){
			strcpy(*Status, "ERROR");
			strcpy(*Error, "#NO_CASSETTE");
			return;
		}
		if (VAL(Stat, 6)<0 || (VAL(Stat, 6)>252544)){
		/* possible return value: 000000...252544 */
		/* if some invalid char is included, it may excess the value */
			strcpy(*Status, "ERROR");
			sprintf(*Error, "#INVALID %s", Stat);
			return;
		}
		*Slotno=VAL(Stat, 2);
		*Wafcount=VAL(Stat+2, 2);
		for (i=4; i<=5; i++){
			if (Stat[i]=='1'){
				*Casscount=*Casscount+1;
			}
			if (Stat[i]=='2'){
				*Cassno=i-3;
			}
		}
		strcpy(*Status, "OK");
		strcpy(*Error, "#READY");
		return;
	}

Timout:
	strcpy(*Status, "ERROR");
	strcpy(*Error, "#TIMEOUT_IO");
	return;

/*
	printf("TELP12_CASSINFO\n");
	printf(" < Slotno\t=%d\n", *Slotno);
	printf(" < Wafcount\t=%d\n", *Wafcount);
	printf(" < Casscount\t=%d\n", *Casscount);
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
