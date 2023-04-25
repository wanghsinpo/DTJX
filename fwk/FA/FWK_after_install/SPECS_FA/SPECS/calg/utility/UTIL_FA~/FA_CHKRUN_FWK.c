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
  Name : FA_CHKRUN_FWK
  Vers : 1
  Desc : Description for this Algorithm spec.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Name            S    -        Key word of grep                
  2 Status          S    -        SPECS Status                    

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 numFile         I    -        The number of process regarding 
  2 numRunning      I    -        The number of running process re

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_CHKRUN_FWK(STRING Name,STRING Status,INTEGER *numFile,INTEGER *numRunning)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	char cmd[255];
	FILE *fp;

#if __hpux
	sprintf(cmd, "tplstat 2>/dev/null | awk '{print $8}' | grep %s | wc | cut -c -1 > /tmp/numfile", Name);
#else
	sprintf(cmd, "tplstat 2>/dev/null | awk '{print $8}' | grep %s | wc | awk '{print $1}' > /tmp/numfile", Name);
#endif

	system(cmd);

	fp=fopen("/tmp/numfile", "r");
	if (fp==0) {
	    printf("PROCESS CHECK ERROR: %s or %s is not accessible.",
					Name,Status);
	    return;
	}
	fscanf(fp, "%d", numFile);
	fclose(fp);
	
#if __hpux
	sprintf(cmd, "tplstat 2>/dev/null | awk '{print $2 $8}' | grep %s | grep %s | wc | cut -c -1 > /tmp/numfile", Name, Status);
#else
	sprintf(cmd, "tplstat 2>/dev/null | awk '{print $2 $8}' | grep %s | grep %s | wc | awk '{print $1}' > /tmp/numfile", Name, Status);
#endif

	system(cmd);

	fp=fopen("/tmp/numfile", "r");
	if (fp==0) {
	    printf("PROCESS CHECK ERROR: %s or %s is not accessible.",
					Name,Status);
	    return;
	}
	fscanf(fp, "%d", numRunning);
	fclose(fp);

/*
	printf("FA_CHKRUN_FWK\n");
	printf(" > Name\t=%s\n", Name);
	printf(" > Status\t=%s\n", Status);
	printf(" < numFile\t=%d\n", *numFile);
	printf(" < numRunning\t=%d\n", *numRunning);
	return;
*/


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
