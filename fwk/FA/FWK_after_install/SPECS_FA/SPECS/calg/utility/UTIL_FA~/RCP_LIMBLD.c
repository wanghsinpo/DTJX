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
#include <unistd.h>

#define LMS_SIZE 256

#define INT16_MAX      32767
#define CMD_BUF_SIZE   40000

/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : RCP_LIMBLD
  Vers : 1
  Desc : This algorithm generates Limit File dynamically.
       :   SPECS3.0: Initial revision.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Tpl_dir         S    -                                        
  2 Lms_dir         S    -                                        
  3 Lim_dir         S    -                                        
  4 Tpl             S    -                                        
  5 Lms             S    256                                      
  6 Lim             S    -                                        

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -        0: OK, -1: Exec Err, -2: No File
  2 Errmsg          S    -                                        
  3 Ndetail         I    -        # of lines of detail error messa
  4 Detail          S    10       Detailed error message          

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
RCP_LIMBLD(STRING Tpl_dir,STRING Lms_dir,STRING Lim_dir,STRING Tpl,STRING *Lms,STRING Lim,INTEGER *Status,STRING *Errmsg,INTEGER *Ndetail,STRING *Detail)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/
    STRING err, t, l;
    INTEGER cmd_ret;
    char cmd[CMD_BUF_SIZE];
    int i;

    if (strcmp(Tpl, "") == 0) {
        *Status = -2;
        strcpy(*Errmsg, "No test plan name is specified.");
        return;
    }
    if (strcmp(Lim, "") == 0) {
        *Status = -2;
        strcpy(*Errmsg, "No limit file name is specified.");
        return;
    }

    RCP_MK_FILENAME(Tpl_dir, Tpl, "", &t);
    RCP_MK_FILENAME(Lim_dir, Lim, ".lim", &l);

    strcpy(cmd, "/opt/SPECS/sys/bin/limbuild");

    for (i = 0; i < LMS_SIZE; i++) {
        if (strcmp(Lms[i], "") == 0) {
            break;
        }
        strcat(cmd, " -lms ");
        strcat(cmd, Lms[i]);
        if (INT16_MAX < strlen(cmd)) {
            goto String_overflow;
        }
    }
    if (strcmp(Lms_dir, "")) {
        strcat(cmd, " -lmspath ");
        strcat(cmd, Lms_dir);
        if (INT16_MAX < strlen(cmd)) {
            goto String_overflow;
        }
    }
    strcat(cmd, " ");
    strcat(cmd, t);
    if (INT16_MAX < strlen(cmd)) {
        goto String_overflow;
    }

    RCP_EXEC_CMD(cmd, l, Status, Errmsg, Ndetail, Detail, &cmd_ret);

    if (*Status < 0) {
        unlink(l);
    }
    return;

  String_overflow:
    *Status = -1;
    sprintf(*Errmsg, "Internal string buffer overflow.");
    return;
    /*
	printf("RCP_LIMBLD\n");
	printf(" > Tpl_dir\t=%s\n", Tpl_dir);
	printf(" > Lms_dir\t=%s\n", Lms_dir);
	printf(" > Lim_dir\t=%s\n", Lim_dir);
	printf(" > Tpl\t=%s\n", Tpl);
	printf(" > Lms\t=\n");
	printf(" > Lim\t=%s\n", Lim);
	printf(" < Status\t=%d\n", *Status);
	printf(" < Errmsg\t=%s\n", *Errmsg);
	printf(" < Ndetail\t=%d\n", *Ndetail);
	printf(" < Detail\t=\n");
	return;
    */
/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
