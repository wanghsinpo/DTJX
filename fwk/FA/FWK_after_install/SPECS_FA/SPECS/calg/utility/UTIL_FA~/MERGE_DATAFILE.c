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
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : MERGE_DATAFILE
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
  1 Original        S    -                                        
  2 New             S    -                                        
  3 Format          S    -                                        
  4 Numwaf          I    -                                        
  5 Waferid         S    50                                       

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Stat            I    -                                        
  2 Error           S    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
MERGE_DATAFILE(STRING Original,STRING New,STRING Format,INTEGER Numwaf,STRING *Waferid,INTEGER *Stat,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	STRING	merge, command, wafer, errrep;
        INTEGER i;
        FILE *fp;

	*Stat = 0;
	strcpy(*Error, "");
        strcpy(wafer, "");

	sprintf(merge, "%s.mrg", Original);
	sprintf(errrep, "%s.err", Original);
	sprintf(Original, "%s.%s", Original, Format);
	sprintf(New, "%s.%s", New, Format);
        for (i = 0; i < Numwaf; i++) {
		sprintf(wafer, "%s %s", wafer, Waferid+i);
        }

        if (unlink(errrep) != 0) {
		if (errno != ENOENT) {
			*Stat = -1;
			strcpy(*Error, sys_errlist[errno]);
			return;
		}
        }

	sprintf(command, "/opt/SPECS/sys/bin/datamerge -t base %s %s %s 1>%s 2>%s",
		Original, New, wafer, merge, errrep); /* AVPATH_ */

	if (system(command) < 0) {
		*Stat = -1;
		strcpy(*Error, sys_errlist[errno]);
		return;
	}

	if ((fp = fopen(errrep, "r")) == NULL) {
		*Stat = -1;
		strcpy(*Error, sys_errlist[errno]);
		return;
        }

	fscanf(fp, "%s", *Error);
	fclose(fp);
	unlink(errrep);

        if (strlen(*Error)) {
		*Stat = -1;
		unlink(merge);
		return;
        }

	if (rename(merge, Original) != 0) {
		*Stat = -1;
		strcpy(*Error, sys_errlist[errno]);
		return;
	}

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
