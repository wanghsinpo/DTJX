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

#define INT16_MAX      32767
#define CMD_BUF_SIZE   40000

/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : RCP_EXEC_CMD
  Vers : 1
  Desc : Execute command file and get result file.
       :   SPECS3.0: Initial revision.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Cmd             S    -                                        
  2 Result          S    -                                        

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -        0: OK, -1: Exec Err, -2: No File
  2 Errmsg          S    -                                        
  3 Ndetail         I    -        # of lines of detail error messa
  4 Detail          S    10       Detailed error message          
  5 Cmd_ret         I    -        Return value from Command       

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
RCP_EXEC_CMD(STRING Cmd,STRING Result,INTEGER *Status,STRING *Errmsg,INTEGER *Ndetail,STRING *Detail,INTEGER *Cmd_ret)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/
    STRING err;

    int st, i, l;
    char buf[CMD_BUF_SIZE];
    FILE *fp;

    *Ndetail = 0;
    for (i = 0; i < 10; i++) {
        strcpy(Detail[i], "");
    }
    *Cmd_ret = 0;

    if (strcmp(Cmd, "") == 0) {
        *Status = -2;
        strcpy(*Errmsg, "No command is specified.");
        return;
    }

    sprintf(buf, "/usr/bin/touch %s", Result);
    st = system(buf);
    if (st) {
        *Status = -2;
        sprintf(*Errmsg, "Cannot store the result. \"%s\"", Result);
        return;
    }

    sprintf(err, "/var/tmp/rcp_exec_cmd.%d", getpid());
    *Status = 0;
    strcpy(*Errmsg, "");

    sprintf(buf, "%s > %s 2> %s", Cmd, Result, err);
    l = strlen(buf);
    if ((INT16_MAX < l) || (sysconf(_SC_ARG_MAX) <= l)) {
        *Status = -1;
        sprintf(*Errmsg, "Internal string buffer overflow.");
        unlink(err);
        return;
    }
    st = system(buf);

    *Cmd_ret = (st >> 8) % 256;
    if (*Cmd_ret >= 128) {
        *Cmd_ret -= 256;
    }

    if (st) {
        *Status = -1;
        if ((fp = fopen(err, "r")) == NULL) {
            goto No_errfl;
        }
        for (i = 0; i < 10; i++) {
            if (fgets(buf, sizeof(buf), fp) == NULL) {
                break;
            }
            l = strlen(buf);
            if (l && buf[l-1] == '\n') {
                buf[l-1] = '\0';
            }
            strcpy(Detail[i], buf);
            *Ndetail = i + 1;
        }
        fclose(fp);

        if (*Ndetail > 0) {
            strcpy(*Errmsg, Detail[0]);
        }
        else {
            sprintf(*Errmsg, "Error found while executing: %s", Cmd);
        }
    }
    unlink(err);
    return;

No_errfl:
    *Status = -1;
    sprintf(*Errmsg, "Cannot execute command: %s", Cmd);
    unlink(err);
    return;
    
    /*
	printf("RCP_EXEC_CMD\n");
	printf(" > Cmd\t=%s\n", Cmd);
	printf(" > Result\t=%s\n", Result);
	printf(" < Status\t=%d\n", *Status);
	printf(" < Errmsg\t=%s\n", *Errmsg);
	printf(" < Ndetail\t=%d\n", *Ndetail);
	printf(" < Detail\t=\n");
	printf(" < Cmd_ret\t=%d\n", *Cmd_ret);
	return;
    */


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
