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
  Name : FA_QUERY_COND
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
  2 Level           S    -                                        
  3 Filename        S    -                                        

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Tco             S    16                                       
  2 Limf            S    -                                        
  3 DieLabel        S    256                                      
  4 DieType         S    256                                      
  5 ModLabel        S    256                                      
  6 Item            S    32                                       
  7 Status          I    -        0: OK, -1: Exec Err, -2: No File
  8 Errmsg          S    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_QUERY_COND(STRING Key,STRING Level,STRING Filename,STRING *Tco,STRING *Limf,STRING *DieLabel,STRING *DieType,STRING *ModLabel,STRING *Item,INTEGER *Status,STRING *Errmsg)
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

    strcpy(cmd, "/opt/SPECS/usr/recipe/fa_cond_q.sh");
    sprintf(spc, "/var/tmp/spc.%d", getpid());

    for (i = 0; i < item_sz; i++) {
        *(Item[i]) = '\0';
    }

    for (i = 0; i < TCO_SIZE; i++) {
        *(Tco[i]) = '\0';
    }
    *(*Limf) = '\0';
    for (i = 0; i < DIEL_SIZE; i++) {
        *(DieLabel[i]) = '\0';
    }
    for (i = 0; i < DIET_SIZE; i++) {
        *(DieType[i]) = '\0';
    }
    for (i = 0; i < MODL_SIZE; i++) {
        *(ModLabel[i]) = '\0';
    }
    sprintf(line, "%s %s %s %s", cmd, Filename, Key, Level);
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
                if (strncmp(spc_nm, "TCO", 3) == 0) {
                    if (n_item >= TCO_SIZE) {
                        goto Array_overflow;
                    }
                    strcpy(Tco[n_item], line);
                }
                else if (strncmp(spc_nm, "Limit File",10) == 0) {
                    strcpy(*Limf, line);
                }
                else if (strncmp(spc_nm, "DIE Label",9) == 0) {
                    if (n_item >= DIEL_SIZE) {
                        goto Array_overflow;
                    }
                    strcpy(DieLabel[n_item], line);
                }
                else if (strncmp(spc_nm, "DIE Type", 8) == 0) {
                    if (n_item >= DIET_SIZE) {
                        goto Array_overflow;
                    }
                    strcpy(DieType[n_item], line);
                }
                else if (strncmp(spc_nm, "MOD Label", 9) == 0) {
                    if (n_item >= MODL_SIZE) {
                        goto Array_overflow;
                    }
                    strcpy(ModLabel[n_item], line);
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
    sprintf(*Errmsg, "Cannot find a recipe by the key, \"%s\",\"%s\".", Key,Level);
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
