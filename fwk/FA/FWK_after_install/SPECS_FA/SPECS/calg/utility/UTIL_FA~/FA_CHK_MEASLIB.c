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
#include <unistd.h>
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : FA_CHK_MEASLIB
  Vers : 1
  Desc : Check multi-measurement libraris.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Revcont         I    -        Revision Control Mode           
  2 Lib             S    256      Measurement Library File (with R
  3 Libnum          I    -        Number of Measurement Library   
  4 Delimiter       S    -        Delimiter between File and Revis

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -        Error Code                      
  2 Error           S    -        Error Message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_CHK_MEASLIB(INTEGER Revcont,STRING *Lib,INTEGER Libnum,STRING Delimiter,INTEGER *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	STRING	Problib, Testlib, Utillib;
	STRING	Probrev, Testrev, Utilrev;
	INTEGER	Probnum, Testnum, Utilnum;
	STRING	Measlib, Libname, Shlname;
	STRING	Buf;
	INTEGER	Cnt;
        char	*Ptr;

	const INTEGER	SIZEOF_ARRAY = 256;
	const STRING	CALGDIR = "/opt/SPECS/usr/calg/";

	const STRING	ERRMESG_ILLEGAL_NAME = "Illegal measurement library is specified : %s";
	const STRING	ERRMESG_CANNOT_ACCESS = "Cannot access the specified file : %s";

	*Status = 0;
	strcpy(*Error, "");

	Probnum=0;
	Testnum=0;
	Utilnum=0;

	TPLFILEPLIB(&Problib, &Probrev, &Probnum);
	TPLFILETLIB(&Testlib, &Testrev, &Testnum);
	TPLFILEULIB(&Utillib, &Utilrev, &Utilnum);

	for (Cnt = 0; Cnt < Libnum && Cnt < SIZEOF_ARRAY; Cnt++) {
		if (strlen(Lib[Cnt]) != 0) {
			strcpy(Measlib, Lib[Cnt]);
			if (Revcont != 0) {
				Ptr = strtok(Measlib, Delimiter);
				if (Ptr == NULL) {
					strcpy(Measlib, Lib[Cnt]);
				}
			}
			if (Measlib[0] != '/') {
				sprintf(Buf, "%s%s", CALGDIR, Measlib);
				strcpy(Measlib, Buf);
			}

			if (Probnum != 0 && strcmp(Measlib, Problib) == 0) {
				*Status = - 1;
				sprintf(*Error, ERRMESG_ILLEGAL_NAME, Problib);
				break;
			}
			if (Testnum != 0 && strcmp(Measlib, Testlib) == 0) {
				*Status = - 2;
				sprintf(*Error, ERRMESG_ILLEGAL_NAME, Testlib);
				break;
			}
			if (Utilnum != 0 && strcmp(Measlib, Utillib) == 0) {
				*Status = - 3;
				sprintf(*Error, ERRMESG_ILLEGAL_NAME, Utillib);
				break;
			}

			sprintf(Libname, "%s.lib", Measlib);
#ifdef __hpux
			sprintf(Shlname, "%s.sl", Measlib);
#elif __linux
			sprintf(Shlname, "%s.so", Measlib);
#endif

			if (access(Libname, R_OK) != 0) {
				*Status = - 4;
				sprintf(*Error, ERRMESG_CANNOT_ACCESS, Libname);
				break;
			}
			if (access(Shlname, R_OK) != 0) {
				*Status = - 5;
				sprintf(*Error, ERRMESG_CANNOT_ACCESS, Shlname);
				break;
			}
		}
	}

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
