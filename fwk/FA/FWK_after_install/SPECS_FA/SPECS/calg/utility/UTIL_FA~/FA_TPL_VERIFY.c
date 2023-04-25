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
static void
MakeFilename(INTEGER Revcont,STRING Root,STRING Name,STRING Delimiter,STRING *File,STRING *Revition);
static INTEGER
OpenRevision(INTEGER Revmode,STRING Type,STRING File,STRING Revision);
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : FA_TPL_VERIFY
  Vers : 1
  Desc : Validate test plan with multi-measurement libraries and test plan cons
       : tants.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Revcont         I    -        Revision Control Mode           
  2 Revmode         I    -        Revision Name/Number Option     
  3 Lib             S    256      Measurement Library File (with R
  4 Libnum          I    -        Number of Measurement Library   
  5 Tco             S    256      Test Plan Constant File (with Re
  6 Tconum          I    -        Number of Test Plan Constant    
  7 Tpl             S    -        Test Plan File (with Revision)  
  8 Delimiter       S    -        Delimiter between File and Revis

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -        Error Code                      
  2 Error           S    -        Error Message                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_TPL_VERIFY(INTEGER Revcont,INTEGER Revmode,STRING *Lib,INTEGER Libnum,STRING *Tco,INTEGER Tconum,STRING Tpl,STRING Delimiter,INTEGER *Status,STRING *Error)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	STRING	Problib, Testlib, Utillib, Devlib, Fwknam;
	STRING	Probrev, Testrev, Utilrev, Devrev, Fwkrev;
	INTEGER	Probnum, Testnum, Utilnum, Devnum, Fwknum;
	STRING	Measlib, Tconam, Tplnam;
	STRING	Measrev, Tcorev, Tplrev;
	INTEGER	Measnum;
	STRING	Buf;
	INTEGER	Cnt, Num;
	char	Tplverify[65536];
	FILE	*Pipe;

	const INTEGER	SIZEOF_ARRAY = 256;
	const STRING	CALGDIR = "/opt/SPECS/usr/calg/";
	const STRING	TCODIR = "/opt/SPECS/usr/tco/";
	const STRING	TPLDIR = "/opt/SPECS/usr/tpl/";

	const STRING	ERRMESG_REVOPEN_LIBFAIL = "Fail to open measurement library as revision : %s, %s";
	const STRING	ERRMESG_REVOPEN_TCOFAIL = "Fail to open test plan constant as revition : %s, %s";
	const STRING	ERRMESG_REVOPEN_TPLFAIL = "Fail to open test plan as revision : %s, %s";
	const STRING	ERRMESG_CANNOT_OPENPIPE = "Fail to open pipe";
	const STRING	ERRMESG_TPL_NOT_SPECIFIED = "Test plan is not specified";

	*Status = 0;
	strcpy(*Error, "");
	strcpy(Tplverify, "/opt/SPECS/sys/bin/tplverify");

	Probnum = 0;
	Testnum = 0;
	Utilnum = 0;
	Devnum = 0;
	Fwknum = 0;

	TPLFILEPLIB(&Problib, &Probrev, &Probnum);
	if (Probnum != 0)
		sprintf(Tplverify, "%s -p %s", Tplverify, Problib);
	TPLFILETLIB(&Testlib, &Testrev, &Testnum);
	if (Testnum != 0)
		sprintf(Tplverify, "%s -t %s", Tplverify, Testlib);
	TPLFILEULIB(&Utillib, &Utilrev, &Utilnum);
	if (Utilnum != 0)
		sprintf(Tplverify, "%s -u %s", Tplverify, Utillib);
	TPLFILEDLIB(&Devlib, &Devrev, &Devnum);
	if (Devnum != 0)
		sprintf(Tplverify, "%s -dvl %s", Tplverify, Devlib);
	TPLFILEFWK(&Fwknam, &Fwkrev, &Fwknum);
	if (Fwknum != 0)
		sprintf(Tplverify, "%s -fwk %s", Tplverify, Fwknam);

	for (Cnt = 0; Cnt < Libnum && Cnt < SIZEOF_ARRAY; Cnt++) {
		if (strlen(Lib[Cnt]) != 0) {
			MakeFilename(Revcont, (char *)CALGDIR, Lib[Cnt], Delimiter, &Measlib, &Measrev);
			sprintf(Tplverify, (Cnt == 0) ? "%s -m %s" : "%s,%s", Tplverify, Measlib);

			if (OpenRevision(Revmode, "lib", Measlib, Measrev) != 0) {
				*Status = -2;
				sprintf(*Error, ERRMESG_REVOPEN_LIBFAIL, Measlib, Measrev);
				return;
			}
		}
	}
	if (Libnum == 0) {
		Num = 0;
		TPLFILENUMMLIB(&Num);
		for (Cnt = 0; Cnt < Num; Cnt++) {
			TPLFILEMLIBM(Cnt, &Measlib, &Measrev, &Measnum);
			sprintf(Tplverify, (Cnt == 0) ? "%s -m %s" : "%s,%s", Tplverify, Measlib);
		}
	}

	for (Cnt = 0; Cnt < Tconum && Cnt < SIZEOF_ARRAY; Cnt++) {
		if (strlen(Tco[Cnt]) != 0) {
			MakeFilename(Revcont, (char *)TCODIR, Tco[Cnt], Delimiter, &Tconam, &Tcorev);
			sprintf(Tplverify, "%s -tco %s", Tplverify, Tconam);

			if (OpenRevision(Revmode, "tco", Tconam, Tcorev) != 0) {
				*Status = -3;
				sprintf(*Error, ERRMESG_REVOPEN_TCOFAIL, Tconam, Tcorev);
				return;
			}
		}
	}
	if (Tconum == 0) {
		Num = 0;
		TPLFILENUMTCO(&Num);
		for (Cnt = 0; Cnt < Num; Cnt++) {
			TPLFILETCO(Cnt, &Tconam, &Tcorev);
			sprintf(Tplverify, "%s -tco %s", Tplverify, Tconam);
		}
	}

	if (strlen(Tpl) != 0) {
		MakeFilename(Revcont, (char *)TPLDIR, Tpl, Delimiter, &Tplnam, &Tplrev);
		sprintf(Tplverify, "%s %s", Tplverify, Tpl);

		if (OpenRevision(Revmode, "tpl", Tplnam, Tplrev) != 0) {
			*Status = -4;
			sprintf(*Error, ERRMESG_REVOPEN_TPLFAIL, Tplnam, Tplrev);
			return;
		}
	}
	else {
		*Status = -5;
		strcpy(*Error, ERRMESG_TPL_NOT_SPECIFIED);
		return;
	}

	Pipe = popen(Tplverify, "r");
	if (Pipe == NULL) {
		*Status = -5;
		strcpy(*Error, ERRMESG_CANNOT_OPENPIPE);
		return;
	}
	while (fgets(Buf, SIZEOF_ARRAY, Pipe)) {
		if (strlen(*Error) + strlen(Buf) >= SIZEOF_ARRAY) {
			break;
		}
		strcat(*Error, Buf);
		break;
	}
	pclose(Pipe);

	if (strlen(*Error) != 0) {
		*Status = -1;
	}

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
static void
MakeFilename(INTEGER Revcont,STRING Root,STRING Name,STRING Delimiter,STRING *File,STRING *Revision)
{
	STRING	Buf;
	char	*Ptr;

	strcpy(*File, Name);
	strcpy(*Revision, "");

	if (Revcont != 0) {
		Ptr = strtok(*File, Delimiter);
		if (Ptr == NULL) {
			strcpy(*File, Name);
		}
		else {
			strcpy(*Revision, Ptr);
		}
	}

	if ((*File)[0] != '/') {
		sprintf(Buf, "%s%s", Root, *File);
		strcpy(*File, Buf);
	}
}

static INTEGER
OpenRevision(INTEGER Revmode,STRING Type,STRING File,STRING Revision)
{
	char	Revopen[65536];

	if (strlen(Revision) == 0) {
		return(0);
	}

	if (Revmode != 0) {
		sprintf(Revopen, "/opt/SPECS/sys/bin/revopen -t %s -n %s %s", Type, Revision, File);
	}
	else {
		sprintf(Revopen, "/opt/SPECS/sys/bin/revopen -t %s -a %s %s", Type, Revision, File);
	}

	if (system(Revopen) != 0) {
		return(-1);
	}
	return(0);
}
