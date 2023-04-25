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
  Name : JDG_DIE_AT_POS2
  Vers : 1
  Desc : Judge specified die by parameter yield.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Die_pos         I    -        index of die                    
  2 Tgt_yld         I    -        target parameter yield to be pas
  3 Last            I    -        all test are finished or not    
  4 Critical        I    -        user flag index as "critical" pa
  5 Ignore          I    -        user flag index as "ignored" par

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Jdg             I    -        0:fail/1:pass/2:unknown         
  2 Yld             R    -        parameter yield                 
  3 Pass_cnt        I    -        pass count of parameter         
  4 Fail_cnt        I    -        fail count of parameter         
  5 Total_cnt       I    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
JDG_DIE_AT_POS2(INTEGER Die_pos,INTEGER Tgt_yld,INTEGER Last,INTEGER Critical,INTEGER Ignore,INTEGER *Jdg,REAL *Yld,INTEGER *Pass_cnt,INTEGER *Fail_cnt,INTEGER *Total_cnt)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	INTEGER	total_var, curr_jdg, selected;
        INTEGER type, dim, size1, size2;
	INTEGER	j;
	INTEGER force_fail, usrflag;
        STRING  name;
	static int debug = 0;

	*Jdg = 2;
	*Yld = 0;
	*Pass_cnt = 0;
	*Fail_cnt = 0;
	*Total_cnt = 0;
	force_fail = 0;

	TPLOUTCOUNT(&total_var);
	for (j = 0; j < total_var; j++) {
		if (Ignore != 0) {
			TPLGETUSRFLAG(j, Ignore - 1, &usrflag);
			if (usrflag != 0) {
				continue;
			}
		}
		TPLOUTSTAT(j, Die_pos, &selected);
		if (selected != 0) {
			TPLOUTINFO(j, &name, &type, &dim, &size1, &size2);
			if (dim == 0 && type < 2) {
				TPLOUTJUDGE(j, Die_pos, &curr_jdg);
				if (curr_jdg != 2) {
					(*Total_cnt)++;
				}
				switch (curr_jdg) {
				case 0:
					(*Fail_cnt)++;
					if (Critical != 0) {
						TPLGETUSRFLAG(j, Critical - 1, &usrflag);
						if (usrflag != 0) {
							force_fail = 1;
						}
					}
					break;
				case 1:
					(*Pass_cnt)++;
					break;
				case 2: case 3:
					break;
				}
			}
		}
	}

	if (*Pass_cnt + *Fail_cnt > 0) {
		if (Last) {
			*Yld = (REAL) *Pass_cnt / (REAL) (*Pass_cnt + *Fail_cnt) * 100.;
			if (*Yld >= Tgt_yld) {
				*Jdg = 1;
			}
			else {
				*Jdg = 0;
			}
		}
		else {
			*Yld = 100. - (REAL) *Fail_cnt / (REAL) *Total_cnt * 100.;
			if (*Yld < Tgt_yld) {
				*Jdg = 0;
			}
			*Yld = (REAL) *Pass_cnt / (REAL) *Total_cnt * 100.;
			if (*Jdg != 0 && *Yld >= Tgt_yld) {
				*Jdg = 1;
			}
		}
	}
	else {
		*Yld = 0.;
        }

	if (force_fail == 1) {
		*Jdg = 0;
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
