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
#include <string.h>

#define MAX_BUF_LENG 1024
extern  FILE *popen(const char*, const char*);
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : CHECK_PROFILE
  Vers : 1
  Desc : Description for this Algorithm spec.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Result          I    -        0:OK 1:TPL: 2:FWK: 3:MLIB: 4:TLI

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
CHECK_PROFILE(INTEGER *Result)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	STRING	name, vers, type;
	int	revcont, nums, libc, i, j;
	char	buffer[MAX_BUF_LENG];
	FILE	*fp;

	*Result = 0;
	TPLGETREVCONT(&revcont);

	TPLFILETPL(&name, &vers, &nums);
	if (strlen(name) > 0 && strcmp(vers, "1") == 0) {
                if (nums == 0) *Result = 1;
                else{
                  for (j = 0; j < nums; j++) {
			TPLFILESPCTPL(j, &name, &type, &vers);
			if (strcmp(vers, "1") == 0) {
				*Result = 1;
				break;
			}
                  }
                }
		if (*Result != 0) {
			return;
		}
	}

	TPLFILEFWK(&name, &vers, &nums);
	if (strlen(name) > 0 && strcmp(vers, "1") == 0) {
                if (nums == 0) *Result = 2;
                else{
                  for (j = 0; j < nums; j++) {
			TPLFILESPCFWK(j, &name, &type, &vers);
			if (strcmp(vers, "1") == 0) {
				*Result = 2;
				break;
			}
                  }
                }
		if (*Result != 0) {
			return;
		}
	}

        TPLFILENUMMLIB(&libc);
        for ( i = 0 ; i < libc ; i++ ) {
	    TPLFILEMLIBM(i, &name, &vers, &nums);
	    if (strlen(name) > 0 && strcmp(vers, "1") == 0) {
                if (nums == 0) *Result = 3;
                else{
                  for (j = 0; j < nums; j++) {
			TPLFILESPCMLIBM(i, j, &name, &vers);
			if (strcmp(vers, "1") == 0) {
				*Result = 3;
				break;
			}
                  }
                }
		if (*Result != 0) {
			return;
		}
            }
	}

	TPLFILETLIB(&name, &vers, &nums);
	if (strlen(name) > 0 && strcmp(vers, "1") == 0) {
                if (nums == 0) *Result = 4;
                else{
                  for (j = 0; j < nums; j++) {
			TPLFILESPCTLIB(j, &name, &vers);
			if (strcmp(vers, "1") == 0) {
				*Result = 4;
				break;
			}
                  }
                }
		if (*Result != 0) {
			return;
		}
	}

	TPLFILEPLIB(&name, &vers, &nums);
	if (strlen(name) > 0 && strcmp(vers, "1") == 0) {
                if (nums == 0) *Result = 5;
                else{
                  for (j = 0; j < nums; j++) {
			TPLFILESPCPLIB(j, &name, &vers);
			if (strcmp(vers, "1") == 0) {
				*Result = 5;
				break;
			}
                  }
                }
		if (*Result != 0) {
			return;
		}
	}

	TPLFILEULIB(&name, &vers, &nums);
	if (strlen(name) > 0 && strcmp(vers, "1") == 0) {
                if (nums == 0) *Result = 6;
                else{
                  for (j = 0; j < nums; j++) {
			TPLFILESPCULIB(j, &name, &vers);
			if (strcmp(vers, "1") == 0) {
				*Result = 6;
				break;
			}
                  }
                }
		if (*Result != 0) {
			return;
		}
	}

        TPLFILELIM2(&name, &vers, &nums);
        if((strlen(name) > 0) &&
           (strcmp(vers, "1") == 0 || strcmp(vers, "") == 0)){
          if(nums == 0) *Result = 7;
          else{
            for(j = 0; j < nums; j++){
              TPLFILESPCLIM(j, &name, &vers);
              if(strcmp(vers, "") == 0){
                *Result = 7;
                break;
              }
            }
          }
          if(*Result != 0) return;
        }

        TPLFILENUMTCO(&nums);
        for(j = 0; j < nums; j++){
          TPLFILETCO(j, &name, &vers);
          if(strcmp(vers, "1") == 0){
            *Result = 8;
            break;
          }
        }
        if(*Result != 0) return;

	TPLFILEDLIB(&name, &vers, &nums);
	if (strlen(name) > 0 && strcmp(vers, "1") == 0) {
                if (nums == 0) *Result = 9;
                else{
                  for (j = 0; j < nums; j++) {
			TPLFILESPCDLIB(j, &name, &vers);
			if (strcmp(vers, "1") == 0) {
				*Result = 9;
				break;
			}
                  }
                }
		if (*Result != 0) {
			return;
		}
	}

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
