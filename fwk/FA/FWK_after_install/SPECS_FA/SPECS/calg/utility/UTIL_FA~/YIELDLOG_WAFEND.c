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
  Name : YIELDLOG_WAFEND
  Vers : 1
  Desc : Logs yield on the specified file. This uses user bin.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Filename        S    -        Filename.                       
  2 Dieyield        I    -        Die yield target value.         

  Output Variables:

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
YIELDLOG_WAFEND(STRING Filename,INTEGER Dieyield)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	INTEGER	wi;			/*  Wafer system tag index	*/
	INTEGER	dietotal;		/*  Total # of dice		*/
	INTEGER	itemtotal;		/*  Total # of output variables	*/
	INTEGER	diepass, diefail;	/*  Pass/Fail counter		*/
        INTEGER judge;                  /*  Pass (1) or Fail(0)         */
        INTEGER wafnum;                 /*  WAFER.NUMBER                */
	INTEGER	itemyield, yield;	/*  Minimum of item yield	*/
        INTEGER	target;                 /*  Yield target                */
	INTEGER	dieyldrslt;		/*  Die yield 			*/
        INTEGER mini, maxi;
	STRING	wafid;			/*  Wafer ID			*/

	int	die, item;		/*  Loop counter		*/
	FILE*	fp;                     /*                              */
	
        /*  Get current wafer ID                                        */
        TPLTAGINDEX("WAFER", "SYS_WAFERID", &wi);
        TPLGETSTAG("WAFER", wi, 0, &wafid);

	/*  Get # of dice and items	                                */
	TPLDIETOTAL(&dietotal);
	TPLOUTCOUNT(&itemtotal);

	/*  Calculate Item Yield	                                */
        itemyield = 100;
	for (item = 0; item < itemtotal; item++) {
                TPLGETWAFJUDGE(item, &target, &yield, &judge);
		if (yield < itemyield) {
			itemyield = yield;
		}
	}

	/*  Calculate Die Yield	                                        */
        diepass = 0;
        diefail = 0;
        dieyldrslt = 100;
	for (die = 0; die < dietotal; die++) {
                TPLGETRANGEDIE(die, &mini, &maxi);
		for (item = mini; item <= maxi; item++) {
                        TPLOUTJUDGE(item, die, &judge);
                        if (judge == 0) {
                                diefail += 1;
                                break;
                        }
		}
                diepass += 1;
	}
        if (diepass + diefail) {
            dieyldrslt = (diepass * 100 ) / (diepass + diefail);
        }

	/*  Log	                                                        */
        TPLSYSINDEX("WAFER", "NUMBER", &wi);
        TPLGETISYS("WAFER", wi, &wafnum);
        if (wafnum == 1) {
            unlink(Filename);
        }
	if ((fp = fopen(Filename, "a")) == (FILE*) NULL) {
		printf("YIELDLOG_WAFEND: fopen() failed.\n");
		return;
	}
        if (wafnum == 1) {
                chmod(Filename, 0666);
        }
	fprintf(fp, 
		"%s\t%d\t%d\t%s\n", 
		wafid, 
		itemyield, 
		dieyldrslt,
		(dieyldrslt >= Dieyield)? "PASS" : "FAIL!!");
	fclose(fp);



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
