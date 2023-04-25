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

#define SUBSTRING_MAX   128
#define MAX_STR_LENG    256
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : STRING_SPLIT
  Vers : 1
  Desc : Returns data (without separators) from a STRING variable, which contai
       : ns data separated by data separators
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Src             S    -        Source string                   
  2 Del             S    -        Delimiter                       

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Elem            S    128      Substrings                      
  2 Count           I    -        Number of substrings            

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
STRING_SPLIT(STRING Src,STRING Del,STRING *Elem,INTEGER *Count)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	char  *s_ptr;
	char  *d_ptr;
	unsigned int    nn;


	if (Count == NULL || Elem == NULL) {
		return;
	}

	*Count = 0;
	memset((void *) *Elem, '\0', SUBSTRING_MAX*MAX_STR_LENG);
	if(strlen(Src) == 0) {
		return;
	}
	s_ptr = Src;

	while(1){
        	if ((d_ptr = strstr(s_ptr, Del)) != NULL && strlen(Del) > 0) {
			nn = (unsigned int)(d_ptr - s_ptr);
			if (nn > 0) {
				if (nn > MAX_STR_LENG - 1) {
					nn = MAX_STR_LENG - 1;
				}
				if (SUBSTRING_MAX > *Count) {
					strncpy(Elem[*Count], s_ptr, nn);
				}
                		*Count += 1;
       	     		}
			s_ptr = d_ptr + strlen(Del);
		} else {
			if ((nn = strlen(s_ptr)) == 0) {
				break;
			}
			if (nn > MAX_STR_LENG - 1) {
				nn = MAX_STR_LENG - 1;
			}
			if (SUBSTRING_MAX > *Count) {
				strncpy(Elem[*Count], s_ptr, nn);
			}
			*Count += 1;
            		break;
        	}
    	}

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
