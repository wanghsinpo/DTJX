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
#include <string.h>
#include <errno.h>
#if __hpux
extern char *sys_errlist[];
#endif
extern int errno;
STRING SysParam[] = {
	"SMODE",
	"OP_LANG",
	"ADTFORMAT",
	"CLEARONRETEST",
	"CLEARONREJECT",
	"IPCPORT",
	"PROJECT",
	"HOSTNAME",
	"ADTLOGGING"
};
INTEGER numSysParam = sizeof(SysParam) / sizeof(STRING);
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : CHECK_SYSCONF
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
  1 ERRNO           I    -                                        
  2 ERRMSG          S    -                                        
  3 SMODE           S    -                                        
  4 OP_LANG         S    -                                        
  5 ADTFORMAT       S    -                                        
  6 CLEARONRETEST   S    -                                        
  7 CLEARONREJECT   S    -                                        
  8 PORTID          S    -                                        
  9 PROJID          S    -                                        
 10 HOSTNAME        S    -                                        
 11 ADTLOGGING      S    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
CHECK_SYSCONF(INTEGER *ERRNO,STRING *ERRMSG,STRING *SMODE,STRING *OP_LANG,STRING *ADTFORMAT,STRING *CLEARONRETEST,STRING *CLEARONREJECT,STRING *PORTID,STRING *PROJID,STRING *HOSTNAME,STRING *ADTLOGGING)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	INTEGER j;
	STRING	file = "/opt/SPECS/sys/config/sysconf"; /* AVPATH_ */
	STRING	symbol, value[9], buffer;
	FILE	*fptr;
        char    *s;

	*ERRNO = 0;
	strcpy(*ERRMSG,        "");
	strcpy(*SMODE,         "");
	strcpy(*OP_LANG,       "");
	strcpy(*ADTFORMAT,     "");
	strcpy(*CLEARONRETEST, "");
	strcpy(*CLEARONREJECT, "");
	strcpy(*PORTID,        "");
	strcpy(*PROJID,        "");
	strcpy(*HOSTNAME,      "");
	strcpy(*ADTLOGGING,    "");

	for (j = 0; j < numSysParam; j++) {
		strcpy(value[j], "");
	}

	if ((fptr = fopen(file, "r")) == 0) {
		*ERRNO = errno;
		sprintf( *ERRMSG, "%s", sys_errlist[errno] );
		return;
	}

	while (fscanf(fptr, "%s", buffer) == 1) {
		strcpy(symbol, (s = strtok(buffer, "="))?s:"");
		for (j = 0; j < numSysParam; j++) {
			if (strcmp(symbol, SysParam[j]) == 0) {
				strcpy(value[j], (s = strtok(0, "="))?s:"");
				break;
			}
		}
	}

	fclose(fptr);

	for (j = 0; j < numSysParam; j++) {
		if (strcmp(value[j], "") == 0) {
			*ERRNO = -1;
			sprintf(*ERRMSG, "No %s found in %s", SysParam[j], file);
			break;
		}
	}

	strcpy(*SMODE,         value[0]);
	strcpy(*OP_LANG,       value[1]);
	strcpy(*ADTFORMAT,     value[2]);
	strcpy(*CLEARONRETEST, value[3]);
	strcpy(*CLEARONREJECT, value[4]);
	strcpy(*PORTID,        value[5]);
	strcpy(*PROJID,        value[6]);
	strcpy(*HOSTNAME,      value[7]);
	strcpy(*ADTLOGGING,    value[8]);

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
