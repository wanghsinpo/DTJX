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
#include <ALGUTIL.h>
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : DATALOG_DIEEND
  Vers : 1
  Desc : Logs datas on the specified file. This uses user bin.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Filename        S    -        Filename.                       
  2 Mode            I    -        All(0), Failed only(1)          

  Output Variables:

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
DATALOG_DIEEND(STRING Filename,INTEGER Mode)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/


/*
  This algoritm logs:
    1. Wafer ID
    2. Die X position
    3. Die Y position
    4. Module label
    5. Device label
    6. Output variable name
    7. Output value
    8. Lower limit
    9. Upper limit
   10. Pass/Fail status
*/



        INTEGER diepos;         /*  Current die position (index)        */
        INTEGER diex, diey;     /*  Current die position (xy axis)      */
        INTEGER windex;         /*  Wafer system variable index         */
        INTEGER mini, maxi;     /*  Outout index range                  */
        INTEGER type;           /*  Variable type                       */
        INTEGER dim, s1, s2;    /*  Variable dimension                  */
        INTEGER binttl;         /*  Total bin #                         */
        INTEGER judge;          /*  Pass(1) or Fail(0)                  */
        INTEGER binc;           /*  # of valid user bin                 */
        INTEGER usrbin[6];      /*  User bin #                          */
        INTEGER num;            /*  User bin index used as "numerator"  */
        INTEGER den;            /*  User bin index used as "denominator"*/
        INTEGER ival;           /*  INTEGER type output value           */
        REAL    lolim[6];       /*  Lower limit of user bin             */
        REAL    uplim[6];       /*  Upper limit of user bin             */
        REAL    rval;           /*  REAL type output value              */
        STRING  wafid;          /*  Wafer ID                            */
        STRING  outname;        /*  Output variable name                */
        STRING  modlabel;       /*  Module label                        */
        STRING  devlabel;       /*  Device label                        */
        FILE*   fp;
        int     i;

	/*  Get current die posision		                        */
	TPLDIEPOS(&diepos);
	TPLDIEINFO(diepos, &diex, &diey);

        /*  Remove old data file if new wafer is loaded                 */
	if (diepos == 0) {
            unlink(Filename);
	}
        if ((fp = fopen(Filename, "a")) == (FILE*) NULL) {
                printf("DATALOG_DIEEND: fopen() failed.\n");
                return;
	} 
        if (diepos == 0) {
		chmod(Filename, 0666);
	}

	/*  Get current wafer ID		                        */
	TPLTAGINDEX("WAFER", "SYS_WAFERID", &windex);
	TPLGETSTAG("WAFER", windex, diepos, &wafid);

	/*  Get output variable index range	                        */
	TPLGETRANGEDIE(diepos, &mini, &maxi);
        if (mini < 0 || maxi < 0) {
            fclose(fp);
            return;
        }

	/*  Main loop				                        */
	for (i = mini; i <= maxi; i++) { 
		TPLOUTINFO(i, &outname, &type, &dim, &s1, &s2);
                if ((type != 0 && type != 1) || dim != 0) {
                    continue;
                }

                TPLOUTJUDGE(i, diepos, &judge);
		if (Mode == 1 && judge == 1) {
			continue;
		}

		TPLMODULELABEL(i, &modlabel);
		TPLDEVICELABEL(i, &devlabel);
                TPLGETWAFUBIN(i, &binc, lolim, uplim, usrbin, &num, &den);

                fprintf(fp, "%s\t%d\t%d\t%s\t%s\t%s\t", 
                        wafid, diex, diey, modlabel, devlabel, outname);
		switch (type) {
                /*  REAL type                                           */
		case 0:
			TPLGETROUT(i, diepos, &rval);
                        fprintf(fp, "%1.3e\t", rval);
			break;
                /*  INTEGER type                                        */
		case 1:
			TPLGETIOUT(i, diepos, &ival);
                        fprintf(fp, "%d\t", ival);
			break;
		}
                fprintf(fp, "%1.3e\t%1.3e\t", lolim[num], uplim[num]);
                switch (judge) {
                case 0:
                        fprintf(fp, "FAIL!!\n");
                        break;
                case 1:
                        fprintf(fp, "PASS\n");
                        break;
                case 2:
                        fprintf(fp, "INVALID\n");
                        break;
                }
	}

	fclose(fp);



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
