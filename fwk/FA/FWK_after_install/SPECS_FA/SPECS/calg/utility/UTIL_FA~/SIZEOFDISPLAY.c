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
#define MAX_BUF_LENG 1024
extern  FILE *popen(const char*, const char*);
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : SIZEOFDISPLAY
  Vers : 1
  Desc : Description for this Algorithm spec.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Width           I    -                                        
  2 Height          I    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
SIZEOFDISPLAY(INTEGER *Width,INTEGER *Height)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	char	buf[MAX_BUF_LENG];
	FILE	*fp;

	if ((fp = popen("/opt/SPECS/sys/bin/xrootsize", "r")) == NULL) {
		printf("SIZEOFDISPLAY: popen failed\n");
		return;
	}

	if (! fgets(buf, MAX_BUF_LENG, fp)) {
		printf("SIZEOFDISPLAY: fgets failed\n");
		return;
	}
	sscanf(buf, "%d", Width);

	if (! fgets(buf, MAX_BUF_LENG, fp)) {
		printf("SIZEOFDISPLAY: fgets failed\n");
		return;
	}
	sscanf(buf, "%d", Height);

	pclose(fp);

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
