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

#define DIE_TST_SIZE    256
#define DIE_SIZE        256
#define MOD_SIZE        256
#define TST_SIZE        256
#define MLIB_SIZE	6

#define INT16_MAX      32767
#define CMD_BUF_SIZE   40000

/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : RCP_TPLBLD
  Vers : 1
  Desc : This algorithm generates Test Plan dynamically.
       :   SPECS3.1: Initial revision.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Waf_dir         S    -                                        
  2 Prb_dir         S    -                                        
  3 Die_dir         S    -                                        
  4 Mod_dir         S    -                                        
  5 Tst_dir         S    -                                        
  6 Tpl_dir         S    -                                        
  7 Waf             S    -                                        
  8 Prb             S    -                                        
  9 Die             S    256                                      
 10 Mod             S    256                                      
 11 Tst             S    256                                      
 12 Mlib            S    6                                        
 13 Tpl             S    -                                        

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
RCP_TPLBLD(STRING Waf_dir,STRING Prb_dir,STRING Die_dir,STRING Mod_dir,STRING Tst_dir,STRING Tpl_dir,STRING Waf,STRING Prb,STRING *Die,STRING *Mod,STRING *Tst,STRING *Mlib,STRING Tpl,INTEGER *Status,STRING *Errmsg,INTEGER *Ndetail,STRING *Detail)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/
    STRING err, t, die_tst[DIE_TST_SIZE];
    char tmp_str[CMD_BUF_SIZE];
    INTEGER cmd_ret;
    char cmd[CMD_BUF_SIZE];

    int i;
    int j, die_dup;

    if (strcmp(Tpl, "") == 0) {
        *Status = -2;
        strcpy(*Errmsg, "No test plan name is specified.");
        return;
    }

    RCP_DIETST(Die, Tst, "", die_tst, Status, Errmsg);
    if (*Status) {
        return;
    }

    RCP_MK_FILENAME(Tpl_dir, Tpl, ".tpl", &t);

    strcpy(cmd, "/opt/SPECS/sys/bin/tplbuild");
    if (strcmp(Waf, "")) {
        strcat(cmd, " -waf ");
        strcat(cmd, Waf);
        if (INT16_MAX < strlen(cmd)) {
            goto String_overflow;
        }
    }
    if (strcmp(Prb, "")) {
        strcat(cmd, " -prb ");
        strcat(cmd, Prb);
        if (INT16_MAX < strlen(cmd)) {
            goto String_overflow;
        }
    }
    for (i = 0; i < DIE_SIZE; i++) {
        if (strcmp(Die[i], "") == 0) {
            break;
        }
        die_dup = 0;
        for (j = 0; j < i; j++) {
            if (strcmp(Die[i], Die[j]) == 0) {
                die_dup++;
                break;
            }
        }
        if (die_dup) {
            continue;
        }
        strcat(cmd, " -die ");
        strcat(cmd, Die[i]);
        if (INT16_MAX < strlen(cmd)) {
            goto String_overflow;
        }
    }
    for (i = 0; i < MOD_SIZE; i++) {
        if (strcmp(Mod[i], "") == 0) {
            break;
        }
        strcat(cmd, " -mod ");
        strcat(cmd, Mod[i]);
        if (INT16_MAX < strlen(cmd)) {
            goto String_overflow;
        }
    }
    for (i = 0; i < TST_SIZE; i++) {
        if (strcmp(die_tst[i], "") == 0) {
            break;
        }
        strcat(cmd, " -tst ");
        strcat(cmd, die_tst[i]);
        if (INT16_MAX < strlen(cmd)) {
            goto String_overflow;
        }
    }
    tmp_str[0] = '\0';
    for (i = 0; i < MLIB_SIZE; i++) {
        if (strcmp(Mlib[i], "") == 0) {
            break;
        }
        if(i != 0)
            strcat(tmp_str, ",");
        strcat(tmp_str, Mlib[i]);
        if (INT16_MAX < strlen(cmd)) {
            goto String_overflow;
        }
    }
    if(0 != strlen(tmp_str)){
        strcat(cmd, " -m ");
        strcat(cmd, tmp_str);
    }

    if (strcmp(Waf_dir, "")) {
        strcat(cmd, " -wafpath ");
        strcat(cmd, Waf_dir);
        if (INT16_MAX < strlen(cmd)) {
            goto String_overflow;
        }
    }
    if (strcmp(Prb_dir, "")) {
        strcat(cmd, " -prbpath ");
        strcat(cmd, Prb_dir);
        if (INT16_MAX < strlen(cmd)) {
            goto String_overflow;
        }
    }
    if (strcmp(Die_dir, "")) {
        strcat(cmd, " -diepath ");
        strcat(cmd, Die_dir);
        if (INT16_MAX < strlen(cmd)) {
            goto String_overflow;
        }
    }
    if (strcmp(Mod_dir, "")) {
        strcat(cmd, " -modpath ");
        strcat(cmd, Mod_dir);
        if (INT16_MAX < strlen(cmd)) {
            goto String_overflow;
        }
    }
    if (strcmp(Tst_dir, "")) {
        strcat(cmd, " -tstpath ");
        strcat(cmd, Tst_dir);
        if (INT16_MAX < strlen(cmd)) {
            goto String_overflow;
        }
    }

    RCP_EXEC_CMD(cmd, t, Status, Errmsg, Ndetail, Detail, &cmd_ret);

    if (*Status < 0) {
        unlink(t);
    }
    return;

  String_overflow:
    *Status = -1;
    sprintf(*Errmsg, "Internal string buffer overflow.");
    return;
    /*
	printf("RCP_TPLBLD\n");
	printf(" > Waf_dir\t=%s\n", Waf_dir);
	printf(" > Prb_dir\t=%s\n", Prb_dir);
	printf(" > Die_dir\t=%s\n", Die_dir);
	printf(" > Mod_dir\t=%s\n", Mod_dir);
	printf(" > Tst_dir\t=%s\n", Tst_dir);
	printf(" > Tpl_dir\t=%s\n", Tpl_dir);
	printf(" > Waf\t=%s\n", Waf);
	printf(" > Prb\t=%s\n", Prb);
	printf(" > Die\t=\n");
	printf(" > Mod\t=\n");
	printf(" > Tst\t=\n");
	printf(" > Tpl\t=%s\n", Tpl);
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
