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
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : WAIT
  Vers : 1
  Desc : Waits for the speicifed duration
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Wait            R    -                                        

  Output Variables:

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
WAIT(REAL Wait)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/


	int  _CPORT = 0;
	long usec;
	unsigned long sec;
	struct timeval timeout;


	if (Wait < 0.0) {
	        if (_CPORT != 0) {
	            	printf("Wait=%lf error\n",  Wait);
       		}
        	return;
    	} 

	sec = (unsigned long) Wait;
	usec = Wait * 1000000 - (double)((long)Wait) * 1000000;
	if (_CPORT != 0) {
		printf("Wait=%lf, sec=%lu, usec=%ld\n", Wait, sec, usec);
    	}

	timeout.tv_sec = sec;
	timeout.tv_usec = usec;
	if (select(0, (fd_set *)NULL, (fd_set *)NULL, (fd_set *)NULL, &timeout) != 0) {
		if (_CPORT != 0) {
			printf("select timed out NG\n");
        	}
	} else {
		if(_CPORT != 0 ){
			printf("select timed out OK\n");
        	}
    	} 

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
