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

#define BUF_SIZE   40000

#define WAF_SIZE 1
#define PRB_SIZE 1
#define DIE_SIZE 256
#define TST_SIZE 256
#define MOD_SIZE 256
#define LMS_SIZE 256
#define MLIB_SIZE 6

#define TCO_SIZE 16

#define STRING_SZ (sizeof(STRING)-1)

static int get_line(FILE *fp, char *buf, int sz)
{
    int l;
    char *c_ret;

    c_ret = fgets(buf, sz, fp);
    l = strlen(buf);

    if (l && buf[l-1] == '\n') {
        buf[l-1] = '\0';
    }
    return c_ret ? -1 : 0;
}

/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : RCP_QUERY_RECIP
  Vers : 1
  Desc : Query recipe items in the recipe file from key recipe id.
       :   SPECS3.1: Initial revision.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Key             S    -                                        
  2 Filename        S    -                                        

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Waf             S    -                                        
  2 Die             S    256                                      
  3 Mod             S    256                                      
  4 Tst             S    256                                      
  5 Prb             S    -                                        
  6 Lms             S    256                                      
  7 Tco             S    16                                       
  8 Mlib            S    6                                        
  9 Item            S    32                                       
 10 Status          I    -        0: OK, -1: Exec Err, -2: No File
 11 Errmsg          S    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
RCP_QUERY_RECIP(STRING Key,STRING Filename,STRING *Waf,STRING *Die,STRING *Mod,STRING *Tst,STRING *Prb,STRING *Lms,STRING *Tco,STRING *Mlib,STRING *Item,INTEGER *Status,STRING *Errmsg)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/
    STRING cmd, spc, detail[10], spc_nm;
    INTEGER n_item, ndetail, cmd_ret;
    char line[BUF_SIZE];
    int i;
    FILE *fp;

    const int item_sz = 32;
    const char del[] = "\t";

    strcpy(cmd, "/opt/SPECS/usr/recipe/recipe_q.sh");
    sprintf(spc, "/var/tmp/spc.%d", getpid());

    for (i = 0; i < item_sz; i++) {
        *(Item[i]) = '\0';
    }

    *(*Waf) = '\0';
    for (i = 0; i < DIE_SIZE; i++) {
        *(Die[i]) = '\0';
    }
    for (i = 0; i < MOD_SIZE; i++) {
        *(Mod[i]) = '\0';
    }
    for (i = 0; i < TST_SIZE; i++) {
        *(Tst[i]) = '\0';
    }
    *(*Prb) = '\0';
    for (i = 0; i < LMS_SIZE; i++) {
        *(Lms[i]) = '\0';
    }

    sprintf(line, "%s %s %s", cmd, Filename, Key);
    RCP_EXEC_CMD(line, spc, Status, Errmsg, &ndetail, detail, &cmd_ret);

    if (cmd_ret == 1) {
        *Status = 1;
    }
    if (*Status == 0 || *Status == 1) {
        if ((fp = fopen(spc, "r")) == NULL) {
            goto No_recipe;
        }

        spc_nm[0] = '\0';
        n_item = 0;
        get_line(fp, line, sizeof(line));
        while (strcmp(line, "# EOD") != 0) {
            if (strncmp(line, "# ", 2) == 0) {
                strcpy(spc_nm, &line[2]);
                n_item = 0;
            }
            else {
                if (strcmp(spc_nm, "WAF") == 0) {
                    if (n_item >= WAF_SIZE) {
                        goto Array_overflow;
                    }
                    strcpy(*Waf, line);
                }
                else if (strcmp(spc_nm, "DIE") == 0) {
                    if (n_item >= DIE_SIZE) {
                        goto Array_overflow;
                    }
                    strcpy(Die[n_item], line);
                }
                else if (strcmp(spc_nm, "MOD") == 0) {
                    if (n_item >= MOD_SIZE) {
                        goto Array_overflow;
                    }
                    strcpy(Mod[n_item], line);
                }
                else if (strcmp(spc_nm, "TST") == 0) {
                    if (n_item >= TST_SIZE) {
                        goto Array_overflow;
                    }
                    strcpy(Tst[n_item], line);
                }
                else if (strcmp(spc_nm, "PRB") == 0) {
                    if (n_item >= PRB_SIZE) {
                        goto Array_overflow;
                    }
                    strcpy(*Prb, line);
                }
                else if (strcmp(spc_nm, "LMS") == 0) {
                    if (n_item >= LMS_SIZE) {
                        goto Array_overflow;
                    }
                    strcpy(Lms[n_item], line);
                }
                else if (strcmp(spc_nm, "TCO") == 0) {
                    if (n_item >= TCO_SIZE) {
                        goto Array_overflow;
                    }
                    strcpy(Tco[n_item], line);
                }
                else if (strcmp(spc_nm, "MLIB") == 0) {
                    if (n_item >= MLIB_SIZE) {
                        goto Array_overflow;
                    }
                    strcpy(Mlib[n_item], line);
                }
                else if (strcmp(spc_nm, "ITEM") == 0) {
                    if (n_item >= item_sz) {
                        goto Column_overflow;
                    }
                    strncpy(Item[n_item], line, STRING_SZ);
                    Item[n_item][STRING_SZ] = '\0';
                }
                else {
                    goto No_recipe;
                }
                n_item++;
            }

            get_line(fp, line, sizeof(line));
        }

        fclose(fp);
    }
    unlink(spc);
    return;

  No_recipe:
    *Status = -3;
    sprintf(*Errmsg, "Cannot find a recipe by the key, \"%s\".", Key);
    if(fp != NULL){ fclose(fp); }
    unlink(spc);
    return;

  Array_overflow:
    *Status = -4;
    sprintf(*Errmsg, "Too many file names at the column, \"%s\".", spc_nm);
    fclose(fp);
    unlink(spc);
    return;

  Column_overflow:
    *Status = -4;
    sprintf(*Errmsg, "Too many columns in the recipe file.");
    fclose(fp);
    unlink(spc);
    return;

    /*
	printf("RCP_QUERY_RECIP\n");
	printf(" > Key\t=%s\n", Key);
	printf(" > Filename\t=%s\n", Filename);
	printf(" < Waf\t=%s\n", *Waf);
	printf(" < Die\t=\n");
	printf(" < Mod\t=\n");
	printf(" < Tst\t=\n");
	printf(" < Prb\t=%s\n", *Prb);
	printf(" < Lms\t=\n");
	printf(" < Item\t=\n");
	printf(" < Status\t=%d\n", *Status);
	printf(" < Errmsg\t=%s\n", *Errmsg);
	return;
    */
/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
