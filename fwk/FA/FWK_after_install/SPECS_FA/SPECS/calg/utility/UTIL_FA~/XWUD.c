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

#define MAX_BUF_LENG    1024
#define MAX_STR_LENG    256
#define PATH            "/usr/bin/X11/xwud"
extern  FILE *popen(const char*, const char*);
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : XWUD
  Vers : 1
  Desc : Executes the xwud(1) command to display a window image, which is store
       : d in the specified dump file
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 File            S    -        xwd dump file (see xwd(1))      
  2 Xpos            I    -        X position                      
  3 Ypos            I    -        Y position                      
  4 Noclick         I    -        1 to ignore mouse click         

  Output Variables:

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
XWUD(STRING File,INTEGER Xpos,INTEGER Ypos,INTEGER Noclick)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/


	int   _CPORT = 0;
	char  buf[MAX_STR_LENG];
	char  op[MAX_BUF_LENG];   
	FILE  *fp1;


	strcpy(op, PATH);
	strcat(op, " -in ");
	strcat(op, File);
	strcat(op, " -geometry ");
	sprintf(buf, "+%d+%d", Xpos, Ypos);
	strcat(op, buf);
	if (Noclick == 1) {
		strcat(op, " -noclick");
	}
	strcat(op, " &");
	if (_CPORT != 0) {
        	printf("op=%s\n",op);
    	}

	if ((fp1 = popen(op, "r")) == NULL) {
		if (_CPORT != 0) {
            		printf("xwud error\n");
        	}
    	}
    	pclose(fp1);

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
