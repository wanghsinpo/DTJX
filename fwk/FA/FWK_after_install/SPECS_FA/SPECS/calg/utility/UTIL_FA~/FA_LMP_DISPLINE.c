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
  Name : FA_LMP_DISPLINE
  Vers : 1
  Desc : FA Algorithm: Display a combination of Label + Value in LMP User Value
       :  Displayment area.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 LineNth         I    -        Line number where to display    
  2 DispLabel       S    -        Label String (Max 18 Chars)     
  3 DispStr         S    -        Value String (Max 30 Chars)     
  4 DispFgc         S    -        Foreground Color of the Value St
  5 DispBgc         S    -        Background Color of the Value St

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -        GEM Reply                       

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_LMP_DISPLINE(INTEGER LineNth,STRING DispLabel,STRING DispStr,STRING DispFgc,STRING DispBgc,INTEGER *Status)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/
        int     i;
        int     stat;
        int     len;
        STRING  line_nth;
        STRING  disp_label;
        STRING  disp_str;
        STRING  fgc;
        STRING  bgc;

        /* Check Line_Nth 1,2,3,4,5,6,7,8 */
        if(LineNth < 1 || LineNth > 8) {
          *Status = -1;
          return;
        }
        sprintf(line_nth,"%d\0",LineNth);

        len = strlen(DispLabel);
        /* Check DispLabel */
        if(len == 0 || DispLabel == "") {
          *Status = -1;
          return;
        }

        /* Display only first 18 chars */
        if(len > 18) {
          strncpy(disp_label, DispLabel,18);
          disp_label[18]='\0';
        }
        else {
          strcpy(disp_label,DispLabel);
        }

        /* Check DispStr */
        len = strlen(DispStr);
        if(len == 0 || DispStr == "") {
          *Status = -1;
          return;
        }

        /* Display only first 30 chars */
        if(len > 30) {
          strncpy(disp_str, DispStr,30);
          disp_str[30]='\0';
        }
        else {
          strcpy(disp_str,DispStr);
        }

        /* Check Fgc */
        len = strlen(DispFgc);
        if(len == 0 || DispFgc == "") {
          sprintf(fgc,"default\0");
        }
        else {
          strcpy(fgc,DispFgc);
        }

        /* Check Bgc */
        len = strlen(DispBgc);
        if(len == 0 || DispBgc == "") {
          sprintf(bgc,"default\0");
        }
        else {
          strcpy(bgc,DispBgc);
        }

        gemLmpDisp("DISPLINE", line_nth, DispLabel, DispStr, fgc, bgc, &stat);
        *Status = stat;

        
/*
	printf("FA_LMP_DISPLINE\n");
	printf(" > LineNth\t=%d\n", LineNth);
	printf(" > DispLabel\t=%s\n", DispLabel);
	printf(" > DispStr\t=%s\n", DispStr);
	printf(" > DispFgc\t=%s\n", DispFgc);
	printf(" > DispBgc\t=%s\n", DispBgc);
*/

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
