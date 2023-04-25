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
#include <facomcore.h>
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : FA_LMP_CLEARLN
  Vers : 1
  Desc : FA Algorithm: Clear a line of LMP User Value Displayment area.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 LineNth         I    -        Line number where to erase      
  2 EraseMode       I    -        1:ClearAll,2:ClearValue(Not chan

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -        GEM Reply                       

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_LMP_CLEARLN(INTEGER LineNth,INTEGER EraseMode,INTEGER *Status)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/
	int	i;
	int     stat;
	int     len;
	STRING  event;
	STRING  line_nth;
        STRING  d_label;
        STRING  d_str;
        STRING  d_fgc;
        STRING  d_bgc;

	/* Check Line_Nth 1,2,3,4,5,6,7,8 */
	if(LineNth < 1 || LineNth > 8) {
	  *Status = -1;
	  return;
	}
	sprintf(line_nth,"%d\0",LineNth);

	/* Check EraseMode 1,2 */
	if(EraseMode < 1 || EraseMode > 2) {
	  *Status = -1;
	  return;
	}
        d_label[0]='\0';
        d_str[0]='\0';
        sprintf(d_fgc,"default\0");
        sprintf(d_bgc,"default\0");
        switch (EraseMode) {
          case 1:
	         sprintf(event,"DISPLINE\0");
                 break;
          case 2:
	         sprintf(event,"CLEARLINE\0");
                 break;
	}
	gemLmpDisp(event,line_nth,d_label,d_str,d_fgc,d_bgc,&stat);

	*Status = stat;

/*
	printf("FA_LMP_CLEARLINE\n");
	printf(" > LineNth\t=%d\n", LineNth);
	printf(" > EraseMode\t=%d\n", EraseMode);
	printf(" < Status\t=%d\n", *Status);
*/
	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
