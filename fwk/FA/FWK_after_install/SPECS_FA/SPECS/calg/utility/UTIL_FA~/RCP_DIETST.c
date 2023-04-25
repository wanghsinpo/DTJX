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

#define DIE_TST_SIZE    256
#define DIE_SIZE        256
#define TST_SIZE        256

/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : RCP_DIETST
  Vers : 1
  Desc : The Algorithm makes a Die Spec-Test Spec list for tplbuild command.
       :   SPECS3.0: Initial revision.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Die             S    256                                      
  2 Tst             S    256                                      
  3 Rule            S    -                                        

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Die_tst         S    256                                      
  2 Status          I    -        0: Ok                           
  3 Errmsg          S    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
RCP_DIETST(STRING *Die,STRING *Tst,STRING Rule,STRING *Die_tst,INTEGER *Status,STRING *Errmsg)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/
    int i;
    int sz;

    int die_sz, tst_sz;

    for (i = 0; i < DIE_TST_SIZE; i++) {
        strcpy(Die_tst[i], "");
    }
    *Status = 0;
    strcpy(*Errmsg, "");

    die_sz = DIE_SIZE;
    for (i = 0; i < DIE_SIZE; i++) {
        if (Die[i][0] == '\0') {
            die_sz = i + 1;
            break;
        }
    }
    tst_sz = TST_SIZE;
    for (i = 0; i < TST_SIZE; i++) {
        if (Tst[i][0] == '\0') {
            tst_sz = i + 1;
            break;
        }
    }
    if (die_sz < tst_sz) {
        *Status = 1;
        strcpy(*Errmsg,
               "Not enough number of die spec files to make die-test pairs.");
    }
    if (die_sz > tst_sz) {
        strcpy(*Errmsg,
               "Test spec files that cannot make die-test pairs are skipped.");
    }
    
    sz = (DIE_SIZE < TST_SIZE) ? DIE_SIZE : TST_SIZE;
    sz = (sz < DIE_TST_SIZE) ? sz : DIE_TST_SIZE;

    for (i = 0; i < sz; i++) {
        if (Die[i][0] == '\0' || Tst[i][0] == '\0') {
            break;
        }
        sprintf(Die_tst[i], "%s %s", Die[i], Tst[i]);
    }


    /*
	printf("RCP_DIETST\n");
	printf(" > Die\t=\n");
	printf(" > Tst\t=\n");
	printf(" > Rule\t=%s\n", Rule);
	printf(" < Die_tst\t=\n");
	printf(" < Status\t=%d\n", *Status);
	printf(" < Errmsg\t=%s\n", *Errmsg);
	return;
    */
/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
