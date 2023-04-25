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
  Name : JDG_WAF_BY_PARA
  Vers : 1
  Desc : Judge current wafer by parameter yield.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Tgt_yld         I    -        target parameter yield to be pas
  2 Last            I    -        all test are finished or not    
  3 Critical        I    -        user flag index as "critical" pa
  4 Ignore          I    -        user flag index as "ignored" par

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
JDG_WAF_BY_PARA(INTEGER Tgt_yld,INTEGER Last,INTEGER Critical,INTEGER Ignore,INTEGER *Jdg,REAL *Yld,INTEGER *Pass_cnt,INTEGER *Fail_cnt,INTEGER *Total_cnt)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	INTEGER	selected_var;
	INTEGER	total_out, total_die, selected_die;
	INTEGER type, dim, size1, size2;
	INTEGER	curr_jdg, j, k;
        INTEGER pass_waf, fail_waf, total_waf;
        INTEGER tgt_item_yld, item_yld;
	INTEGER force_fail, usrflag;
        REAL out_yld;
        STRING name;
	static int debug = 0;

	*Jdg = 2;
	*Yld = 0;
	*Pass_cnt = 0;
	*Fail_cnt = 0;
	*Total_cnt = 0;
	force_fail = 0;

	TPLOUTCOUNT(&total_out);
	TPLDIETOTAL(&total_die);

	if (Last) {
		for (j = 0; j < total_out; j++) {
			if (Ignore != 0) {
				TPLGETUSRFLAG(j, Ignore - 1, &usrflag);
				if (usrflag != 0) {
					continue;
				}
			}

			TPLOUTINFO(j, &name, &type, &dim, &size1, &size2);
			if (dim == 0 && type < 2) {
				TPLGETWAFJUDGE(j, &tgt_item_yld, &item_yld, &curr_jdg);
				(*Total_cnt)++;
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
				}
			}
		}
		if (*Pass_cnt + *Fail_cnt > 0) {
			*Yld = (REAL) *Pass_cnt / (REAL) (*Pass_cnt + *Fail_cnt) * 100.;
			if (*Yld >= Tgt_yld) {
				*Jdg = 1;
			}
			else {
				*Jdg = 0;
			}
		}
	}
        else {
                for (j = 0; j < total_out; j++) {
                        pass_waf = 0;
                        fail_waf = 0;
                        total_waf = 0;
                        if (Ignore != 0) {
                                TPLGETUSRFLAG(j, Ignore - 1, &usrflag);
                                if (usrflag != 0) {
                                        continue;
                                }
                        }

                        for (k = 0; k < total_die; k++) {
                                TPLDIESTAT(k, &selected_die);
                                if (selected_die != 0) {
                                        TPLOUTSTAT(j, k, &selected_var);
                                        if (selected_var != 0) {
                                                TPLOUTINFO(j, &name, &type, &dim, &size1, &size2);
                                                if (dim == 0 && type < 2) {
                                                        TPLOUTJUDGE(j, k, &curr_jdg);
                                                        if (curr_jdg != 2) {
                                                                total_waf++;
                                                        }
                                                        switch (curr_jdg) {
                                                        case 0:
                                                                fail_waf++;
                                                                if (Critical != 0) {
                                                                        TPLGETUSRFLAG(j, Critical - 1, &usrflag);
                                                                        if (usrflag != 0) {
									        force_fail = 1;
                                                                        }
                                                                }
                                                                break;
                                                        case 1:
                                                                pass_waf++;
                                                                break;
                                                        case 2: case 3:
                                                                break;
                                                        }
                                                }
                                        }
                                }
                        }
                        if (total_waf > 0) {
                                (*Total_cnt)++;
                        }
                        if (pass_waf > 0 || fail_waf > 0) {
                                TPLGETWAFJUDGE(j, &tgt_item_yld, &item_yld, &curr_jdg);
                                out_yld = (REAL) pass_waf / (REAL) total_waf * 100.;
                                if (out_yld >= tgt_item_yld) {
                                        (*Pass_cnt)++;
                                }
                                else {
                                        out_yld = 100. - (REAL) fail_waf / (REAL) total_waf * 100.;
                                        if (out_yld < tgt_item_yld) {
                                                (*Fail_cnt)++;
                                        }
                                }
                        }
                }

                if (*Pass_cnt + *Fail_cnt > 0) {
                        *Yld = 100. - (REAL) *Fail_cnt / (REAL) *Total_cnt * 100.;
                        if (*Yld < Tgt_yld) {
                                *Jdg = 0;
                        }
                        *Yld = (REAL) *Pass_cnt / (REAL) *Total_cnt * 100.;
                        if (*Jdg != 0 && *Yld >= Tgt_yld) {
                                *Jdg = 1;
                        }
                }
                else {
                        *Yld = 0;
                }
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
