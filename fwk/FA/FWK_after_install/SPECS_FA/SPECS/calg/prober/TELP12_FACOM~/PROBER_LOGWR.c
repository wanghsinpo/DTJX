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
#include <time.h>
#include <sys/time.h>

#define MAX_BUF_LENG 1024
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : PROBER_LOGWR
  Vers : 1
  Desc : Write Message in /var/opt/SPECS/log/prober.log
  Date : 11/15/2006
  Time : 03:20:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Message         S    -                                        

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          S    -        "OK" or "ERROR"                 
  2 Error           S    -        Error message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
PROBER_LOGWR(STRING Message,STRING *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	char	buffer[MAX_BUF_LENG];
	INTEGER	proberlog_time = 1;

	FILE	*flog;
	INTEGER	logmode = 0;

	struct timeval	now;
	struct timezone	tz;
	struct tm	*tmptr;

        gettimeofday(&now, &tz);
        tmptr = localtime(&now.tv_sec);

	strcpy(*Status, "OK");
	strcpy(*Error, "");

	flog = fopen("/opt/SPECS/sys/config/sysconf", "r");
	if (flog != NULL) {
		while (fgets(buffer, MAX_BUF_LENG, flog)) {
			if (strncmp(buffer, "PROBERLOG_TIME=", strlen("PROBERLOG_TIME=")) == 0) {
				if (strcmp(buffer + strlen("PROBERLOG_TIME="), "SEC\n") == 0) {
					proberlog_time = 1;
				}
				else if (strcmp(buffer + strlen("PROBERLOG_TIME="), "USEC\n") == 0) {
					proberlog_time = 2;
				}
				break;
			}
		}
		fclose(flog);
	}

	PROBER_LOG(&logmode);
	if(logmode == 1){
		flog = fopen("/var/opt/SPECS/log/prober.log","a");
		if (flog != NULL) {
			if(proberlog_time == 1){
				strftime(buffer, 256, "%Y-%m-%d %H:%M:%S", tmptr);
				fprintf(flog, "%s %s\n", buffer, Message);
			}
			else if(proberlog_time == 2){
				strftime(buffer, 256, "%Y-%m-%d %H:%M:%S", tmptr);
				fprintf(flog, "%s.%06d %s\n", buffer, now.tv_usec, Message);
			}
			fclose(flog);
		}
	}

/*
	printf("PROBER_LOGWR\n");
	printf(" > Message\t=%s\n", Message);
	printf(" < Status\t=%s\n", *Status);
	printf(" < Error\t=%s\n", *Error);
	return;
*/



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
