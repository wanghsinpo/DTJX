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

#define DIE_SIZE 256
#define TST_SIZE 256
#define MOD_SIZE 256
#define LMS_SIZE 256
#define DIEL_SIZE 256
#define DIET_SIZE 256
#define MODL_SIZE 256

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
  Name : FA_QUERY_RECIP
  Vers : 1
  Desc : Query recipe items in the recipe file from key recipe id.
       :   SPECS3.0: Initial revision.
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
  8 Tpl             S    -                                        
  9 Lim             S    -                                        
 10 Rcp             S    -                                        
 11 Lt_id           S    -                                        
 12 Pt_id           S    -                                        
 13 Ps_id           S    -                                        
 14 Item            S    32                                       
 15 Status          I    -        0: OK, -1: Exec Err, -2: No File
 16 Errmsg          S    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_QUERY_RECIP(STRING Key,STRING Filename,STRING *Waf,STRING *Die,STRING *Mod,STRING *Tst,STRING *Prb,STRING *Lms,STRING *Tco,STRING *Tpl,STRING *Lim,STRING *Rcp,STRING *Lt_id,STRING *Pt_id,STRING *Ps_id,STRING *Item,INTEGER *Status,STRING *Errmsg)
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

    strcpy(cmd, "/opt/SPECS/usr/recipe/fa_recipe_q.sh");
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
    for (i = 0; i < TCO_SIZE; i++) {
        *(Tco[i]) = '\0';
    }
    *(*Tpl) = '\0';
    *(*Lim) = '\0';
    *(*Rcp) = '\0';
    *(*Lt_id) = '\0';
    *(*Pt_id) = '\0';
    *(*Ps_id) = '\0';
    sprintf(line, "%s %s %s", cmd, Filename, Key);
    FA_RCP_EXEC_CMD(line, spc, Status, Errmsg, &ndetail, detail, &cmd_ret);

    if (cmd_ret == 1) {
        *Status = 1;
    }
    if (*Status == 0 || *Status == 1) {
        if ((fp = fopen(spc, "r")) == NULL) {
            goto No_recipe;
        }

        for (i = 0; i < item_sz; i++) {
            get_line(fp, line, sizeof(line));
            strncpy(Item[i], line, STRING_SZ);
            Item[i][STRING_SZ] = '\0';
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
                else if (strcmp(spc_nm, "TPL") == 0) {
                    strcpy(*Tpl, line);
                }
                else if (strcmp(spc_nm, "Limit File") == 0) {
                    strcpy(*Lim, line);
                }
                else if (strcmp(spc_nm, "Prober RCP") == 0) {
                    strcpy(*Rcp, line);
                }
                else if (strcmp(spc_nm, "STEP") == 0) {
                    strcpy(*Lt_id, line);
                }
                else if (strcmp(spc_nm, "PRODUCT") == 0) {
                    strcpy(*Pt_id, line);
                }
                else if (strcmp(spc_nm, "PROCESS") == 0) {
                    strcpy(*Ps_id, line);
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
    unlink(spc);
    return;

  Array_overflow:
    *Status = -4;
    sprintf(*Errmsg, "Subscript of spec name array is out of range.");
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
