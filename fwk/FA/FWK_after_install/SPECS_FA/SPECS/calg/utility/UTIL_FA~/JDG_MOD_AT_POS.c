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
  Name : JDG_MOD_AT_POS
  Vers : 1
  Desc : Return if specified module has failed outputs.
       :   SPECS2.5: Initial revision.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Die_pos         I    -        index of die                    
  2 Mod_pos         I    -        Index of module                 
  3 Ignore          I    -        user flag index as "ignored" par

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Jdg             I    -        0:fail/1:pass/2:unknown         
  2 Pass_cnt        I    -        pass count of item              
  3 Fail_cnt        I    -        fail count of item              
  4 Total_cnt       I    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
JDG_MOD_AT_POS(INTEGER Die_pos,INTEGER Mod_pos,INTEGER Ignore,INTEGER *Jdg,INTEGER *Pass_cnt,INTEGER *Fail_cnt,INTEGER *Total_cnt)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	INTEGER	curr_jdg, selected;
        INTEGER type, dim, size1, size2;
	INTEGER	j;
	INTEGER min, max;
	INTEGER usrflag;
        STRING  name;
	static int debug = 0;

	*Jdg = 2;
	*Pass_cnt = 0;
	*Fail_cnt = 0;
	*Total_cnt = 0;

	TPLGETRANGEMOD(Die_pos, Mod_pos, &min, &max);
	for (j = min; j <= max; j++) {
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

	if (*Fail_cnt > 0) {
		*Jdg = 0;
	}
	else if (*Pass_cnt > 0) {
		*Jdg = 1;
        }

	if (debug) {
                printf("Total: %d\n", *Total_cnt);
                printf(" Pass: %d\n", *Pass_cnt);
                printf(" Fail: %d\n", *Fail_cnt);
                printf("  Jdg: %f\n", *Jdg);
	}

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
