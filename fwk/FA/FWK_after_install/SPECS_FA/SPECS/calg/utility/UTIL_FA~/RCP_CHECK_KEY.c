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

#define FILE_NAME_LEN  (32)

static void remove_file(STRING dst, STRING keylst, STRING diff, STRING nullkey)
{
    unlink(dst);
    unlink(keylst);
    unlink(diff);
    unlink(nullkey);
}

/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : RCP_CHECK_KEY
  Vers : 1
  Desc : Check if recipe file has duplicate key fields.
       :   SPECS3.0: Initial revision.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Filename        S    -                                        

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -        0: OK, -1: Err, -2: No File     
  2 Errmsg          S    -                                        
  3 Dupkey          S    -        Duplicated key                  

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
RCP_CHECK_KEY(STRING Filename,INTEGER *Status,STRING *Errmsg,STRING *Dupkey)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/
    STRING dst, keylst, diff, nullkey, detail[10], key, key2;
    INTEGER cmd_ret, ndetail, line_no;
    char cmd[8192];
    char *p_ret;

    int pid, l, i;
    FILE *fp;

    STRING file_nm[3], pat[3], rep[3], rep_fl[3];
    INTEGER pos, rep_fl_len;
    char * name[3];
    STRING * fl_p;
    char   ** key_p;

    pid = getpid();
    sprintf(dst,     "/var/tmp/rcp_key.%d",     pid);
    sprintf(keylst,  "/var/tmp/rcp_keylst.%d",  pid);
    sprintf(diff,    "/var/tmp/rcp_keydif.%d",  pid);
    sprintf(nullkey, "/var/tmp/rcp_nullkey.%d", pid);
    strcpy(*Dupkey,   "");
    *Status = 0;

    if ((fp = fopen(Filename, "r")) == NULL) {
        *Status = -2;
        strcpy(*Errmsg, "Recipe file is not found.");
        return;
    }
    fclose(fp);

    sprintf(cmd,
            "/usr/bin/grep -Ee '^[^#][^\t ]*' %s | /usr/bin/cut -f 1 | "
            "/usr/bin/grep -Ee '^[^\t]' | /usr/bin/sort",
            Filename);
    RCP_EXEC_CMD(cmd, dst, Status, Errmsg, &ndetail, detail, &cmd_ret);
    if (*Status) {
        remove_file(dst, keylst, diff, nullkey);
        return;
    }

    sprintf(cmd,
            "/usr/bin/awk "
            "'/^.+$/{if (!match($0,\"^[A-Za-z0-9_]+$\")){print $0;exit}}' "
            "%s",
            dst);
    fp = popen(cmd, "r");
    if (fp != NULL) {
        p_ret = fgets(key, sizeof(key), fp);
        pclose(fp);
        if (p_ret) {
            l = strlen(key);
            if (l && key[l-1] == '\n') key[l-1] = '\0';
            *Status=-1;
            sprintf(*Errmsg,
                    "Recipe key must consist of A-Z,a-z,0-9 and '_': \"%s\"", key);
            remove_file(dst, keylst, diff, nullkey);
            return;
        }
    }

    sprintf(cmd, "/usr/bin/uniq %s", dst);
    RCP_EXEC_CMD(cmd, keylst, Status, Errmsg, &ndetail, detail, &cmd_ret);
    if (*Status) {
        remove_file(dst, keylst, diff, nullkey);
        return;
    }

    sprintf(cmd, "/usr/bin/diff %s %s", dst, keylst);
    RCP_EXEC_CMD(cmd, diff, Status, Errmsg, &ndetail, detail, &cmd_ret);
    if (*Status) {
        if (cmd_ret == 1) {
            sprintf(cmd,
                    "/usr/bin/awk '{if (match($1,\"^[<>]+\")){print $2;}}' %s",
                    diff);
            if ((fp = popen(cmd, "r")) == NULL) {
                remove_file(dst, keylst, diff, nullkey);
                return;
            }
            if (fgets(key, sizeof(key), fp)) {
                l = strlen(key);
                if (l && key[l-1] == '\n') key[l-1] = '\0';
                sprintf(*Errmsg, "Duplicate key is found, \"%s\".", key);
                strcpy(*Dupkey, key);
            }
            pclose(fp);
        }
        remove_file(dst, keylst, diff, nullkey);
        return;
    }

    sprintf(cmd, "/usr/bin/sed -e 's/\t[^\t][^\t]*/\tX/g' %s "
                 " | /usr/bin/awk -F'\t' 'BEGIN{ln=0;}"
                    "/^[^#]/{ln=ln+1;"
                           "if ((!match($0,\"^[ \t]*$\"))&&match($1,\"^[ ]*$\"))"
                              "{print ln;exit 0;}}"
                    "END{print 0;}'", Filename);
    RCP_EXEC_CMD(cmd, nullkey, Status, Errmsg, &ndetail, detail, &cmd_ret);
    if (*Status) {
        remove_file(dst, keylst, diff, nullkey);
        return;
    }
    if ((fp = fopen(nullkey, "r")) == NULL) {
        *Status = -1;
        sprintf(*Errmsg, "Error on accessing internal file, %s", nullkey);
        remove_file(dst, keylst, diff, nullkey);
        return;
    }
    if ((fscanf(fp, "%d", &line_no) == 1) && 
        (line_no > 0)) {
        *Status = -1;
        sprintf(*Errmsg, "Null key is found at line %d.", line_no);
    }
    fclose(fp);


    name[0] = "RCP_TPL";   strcpy(file_nm[0], "");
    name[1] = "RCP_LIM";   strcpy(file_nm[1], "");
    name[2] = NULL;        strcpy(file_nm[2], "");

    for (fl_p = file_nm, key_p = name;
         *key_p != NULL;
         fl_p++, key_p++) {

        RCP_SYSCONF(*key_p, fl_p, Status);
        if (*Status != 0) {
            sprintf(*Errmsg, "\"%s\" is not found in sysconf.", *key_p);
            return;
        }
    }

    strcpy(pat[0], "$(RCP)");   strcpy(rep[0], "");
    strcpy(pat[1], "$(SI)");    strcpy(rep[1], "0");
    strcpy(pat[2], "");         strcpy(rep[2], "");

    for (i = 0; i < 2; i++) {
        pos = 0;
        strcpy(rep_fl[i], "");
        STRING_LOOKUP(file_nm[i], pat[0], &pos);
        if (pos <= 0) {
            continue;
        }
        RCP_REPLACE_WD(file_nm[i], pat, rep, rep_fl[i]);
    }

    if ((fp = fopen(keylst, "r")) == NULL) {
        *Status = -1;
        sprintf(*Errmsg, "Error on accessing internal file, %s", nullkey);
        remove_file(dst, keylst, diff, nullkey);
        return;
    }
    while (fgets(key, sizeof(key), fp)) {
        l = strlen(key);
        if (l && key[l-1] == '\n') key[l-1] = '\0';

        for (i = 0; i < 2; i++) {
            rep_fl_len = strlen(rep_fl[i]);
            if (rep_fl_len <= 0) {
                continue;
            }
            if (rep_fl_len + strlen(key)> FILE_NAME_LEN) {
                *Status = -1;
                fclose(fp);
                strncpy(key2, key, FILE_NAME_LEN); key2[FILE_NAME_LEN]='\0';
                sprintf(*Errmsg,
                        "Recipe key is too long. (0 < key length <= %d)\nIt is used as a part of test plan or limit file name. (%s)",
                        FILE_NAME_LEN - rep_fl_len, key2);
                remove_file(dst, keylst, diff, nullkey);
                return;
            }
        }
    }
    fclose(fp);


    remove_file(dst, keylst, diff, nullkey);
    return;

    /*
	printf("RCP_CHECK_KEY\n");
	printf(" > Filename\t=%s\n", Filename);
	printf(" < Status\t=%d\n", *Status);
	printf(" < Errmsg\t=%s\n", *Errmsg);
	printf(" < Dupkey\t=%s\n", *Dupkey);
	return;
    */

/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
