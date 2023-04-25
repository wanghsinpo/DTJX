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
  Name : SETUSRBIN_LPBGN
  Vers : 1
  Desc : Initializes "user bin" condition.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Waftgt          I    -        Wafer-level yield target.       
  2 Lottgt          I    -        Lot-level yield target.         

  Output Variables:

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
SETUSRBIN_LPBGN(INTEGER Waftgt,INTEGER Lottgt)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



/*
  This algorithm sets user-bins as follow:

  * Even # of limits are defined.

       Lim(N-1)    Lim(N)          lim(N+1)    Lim(N+2)
    ...---+----------+----------------+-----------+---...
                     <- user bin (0) ->
          <------------ user bin (1) ------------->
                           ...

  * Odd # of limits are defined.

       Lim(N-2)   Lim(N-1)   lim(N)    Lim(N+1)    Lim(N+2)
    ...---+----------+---------+----------+-----------+---...
                     <--- user bin (0) --->
          <-------------- user bin (1) --------------->
                             ...
*/


	REAL	lim[10];	/*  Limit value			        */
	INTEGER outcount;	/*  # of output variables	        */
	INTEGER	lolim[5];       /*  Lower limit of user bin             */
        INTEGER uplim[5];       /*  Upper limit of user bin		*/
	INTEGER	binc;		/*  Bin # total				*/
	INTEGER limc;		/*  # of limit   		        */
	INTEGER bin[11];	/*  Binning			        */
        INTEGER type;           /*  Variable type                       */
        INTEGER dim, s1, s2;    /*  Dimension                           */
        STRING  name;           /*  Output variable name                */
	int	i, j;

	TPLOUTCOUNT(&outcount);

	for (i = 0; i < outcount; i++) {
                /*  Binning is valid for scalar-type REAL/INTEGER       */
                TPLOUTINFO(i, &name, &type, &dim, &s1, &s2);
                if (type < 0 || 1 < type || dim != 0) {
                        continue;
                }

                TPLGETWAFBIN(i, &binc, lim, bin, &limc);
                if (limc % 2 == 0) {
                        for (j = 0; j < limc / 2; j++) {
                                lolim[j] = limc / 2 - j - 1;
                                uplim[j] = limc / 2 + j;
                        }
                } else {
                        for (j = 0; j < limc / 2; j++) {
                                lolim[j] = limc / 2 - j - 1;
                                uplim[j] = limc / 2 + j + 1;
                        }
                }
                TPLSETUSRBIN(i, 
                             limc / 2,          /* UsrBin total         */
                             lolim, uplim,      /* Limit index array    */
                             0,                 /* "Numerator" bin      */
                             limc / 2,          /* "Denomnator" bin     */
                             Waftgt,		/* Wafer level target   */
                             Lottgt);		/* Lot level target     */
	}


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
