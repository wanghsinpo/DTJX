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
  Name : JDG_WAF_BY_DIE
  Vers : 1
  Desc : Judge current wafer by die yield.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Tgt_wafyld      I    -        target parameter yield to be pas
  2 Tgt_dieyld      I    -                                        
  3 Last            I    -        all test are finished or not    

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Jdg             I    -        0:fail/1:pass/2:unknown         
  2 Yld             R    -        die yield                       
  3 Pass_cnt        I    -        pass count of die               
  4 Fail_cnt        I    -        fail count of die               
  5 Total_cnt       I    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
JDG_WAF_BY_DIE(INTEGER Tgt_wafyld,INTEGER Tgt_dieyld,INTEGER Last,INTEGER *Jdg,REAL *Yld,INTEGER *Pass_cnt,INTEGER *Fail_cnt,INTEGER *Total_cnt)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	REAL	curr_yld;
	INTEGER	total_die, selected;
	INTEGER	curr_jdg, curr_pcnt, curr_fcnt, curr_tcnt;
	INTEGER	j;
	static int debug = 0;

	*Jdg = 2;
	*Yld = 0;
	*Pass_cnt = 0;
	*Fail_cnt = 0;
	*Total_cnt = 0;

	TPLDIETOTAL(&total_die);
	for (j = 0; j < total_die; j++) {
		TPLDIESTAT(j, &selected);
		if (selected != 0) {
			(*Total_cnt)++;
			JDG_DIE_AT_POS(j, Tgt_dieyld, Last,
				&curr_jdg, &curr_yld, &curr_pcnt, &curr_fcnt, &curr_tcnt);
			switch (curr_jdg) {
			case 0:
				(*Fail_cnt)++;
				break;
			case 1:
				(*Pass_cnt)++;
				break;
			case 2: case 3:
				break;
			}
		}
	}

	if (*Pass_cnt + *Fail_cnt > 0) {
		if (Last) {
			*Yld = (REAL) *Pass_cnt / (REAL) (*Pass_cnt + *Fail_cnt) * 100.;
			if (*Yld >= Tgt_wafyld) {
				*Jdg = 1;
			}
			else {
				*Jdg = 0;
			}
		}
		else {
			*Yld = 100. - (REAL) *Fail_cnt / (REAL) *Total_cnt * 100.;
			if (*Yld < Tgt_wafyld) {
				*Jdg = 0;
			}
			*Yld = (REAL) *Pass_cnt / (REAL) *Total_cnt * 100.;
			if (*Jdg != 0 && *Yld >= Tgt_wafyld) {
				*Jdg = 1;
			}
		}
	}
	else {
		*Yld = 0.;
	}

	if (debug) {
                printf(" Last: %d\n", Last);
                printf("Total: %d\n", *Total_cnt);
                printf(" Pass: %d\n", *Pass_cnt);
                printf(" Fail: %d\n", *Fail_cnt);
                printf("Yield: %f\n", *Yld);
                printf("Judge: %d\n", *Jdg);
	}

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
