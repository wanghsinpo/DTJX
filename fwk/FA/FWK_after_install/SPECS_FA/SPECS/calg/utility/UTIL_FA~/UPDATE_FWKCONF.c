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
#include <errno.h>
#include <ALGUTIL.h>
#if __hpux
extern char *sys_errlist[];
#endif
extern int errno;

static void
WRITE_SCALAR_TAG(INTEGER index, INTEGER type, char *value);
static void
WRITE_ARRAY1_TAG(INTEGER index, INTEGER type, INTEGER size1, char *value);
static void
WRITE_ARRAY2_TAG(INTEGER index, INTEGER type, INTEGER size1, INTEGER size2, char *value);
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : UPDATE_FWKCONF
  Vers : 1
  Desc : Store current configuration parameters.
       :   SPECS2.5: Added type parameter.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 File            S    -                                        
  2 Type            I    -        0:All vars, 1:Normal vars only, 

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Errno           I    -                                        
  2 Errmsg          S    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
#define LINE_MAX 8196
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
UPDATE_FWKCONF(STRING File,INTEGER Type,INTEGER *Errno,STRING *Errmsg)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



        INTEGER index, type, dim, size1, size2;
        char  modified[LINE_MAX], symbol[LINE_MAX];
        STRING  bckFile,name;
        char*   src, buffer[LINE_MAX], line[LINE_MAX], value[LINE_MAX];
        FILE    *fptr, *bfptr;
        char    *s;

        *Errno = 0;
        strcpy(*Errmsg, "");

        sprintf(bckFile, "%s~", File);
        if (rename(File, bckFile) != 0) {
                *Errno = errno;
                sprintf(*Errmsg, "%s", sys_errlist[errno]);
                return;
        }

        if ((fptr = fopen(File, "w")) == 0) {
                *Errno = errno;
                sprintf(*Errmsg, "%s", sys_errlist[errno]);
                return;
        }

        if ((bfptr = fopen(bckFile, "r")) == 0) {
                *Errno = errno;
                sprintf(*Errmsg, "%s", sys_errlist[errno]);
                return;
        }

        while (fgets(buffer, LINE_MAX, bfptr) != NULL) {
                strcpy(line, buffer);
                strcpy(symbol, "");
                strcpy(value, "");
                strtok(line, "!");
                strcpy(symbol, (s = strtok(line, ":"))?s:"");
                strcpy(value, (s = strtok(NULL, "!"))?s:"");

/*
                DEL_HEAD_SPACE(symbol, &modified); strcpy(symbol, modified);
                DEL_TAIL_SPACE(symbol, &modified); strcpy(symbol, modified);
                DEL_HEAD_SPACE(value,  &modified); strcpy(value,  modified);
                DEL_TAIL_SPACE(value,  &modified); strcpy(value,  modified);
*/
                if(symbol[strlen(symbol)-1]=='\n'){
                        symbol[strlen(symbol)-1]='\0';
                }
                if(value[strlen(value)-1]=='\n'){
                        value[strlen(value)-1]='\0';
                }

                if (symbol[0] != '!' && strcmp(symbol, "") != 0) {
                        if ((Type == 1 && symbol[0] == '*') ||
                            (Type == 2 && symbol[0] != '*')) {
                                sprintf(symbol, "%s", buffer);
                        }
                        else {
                                if (symbol[0] == '*') {
                                        src = ((char*) symbol) + 1;
                                }
                                else {
                                        src = (char*) symbol;
                                }

                                TPLTAGINDEX("SYSTEM", src, &index);
                                if (index == -1) {
                                        *Errno = 1;
                                        sprintf(*Errmsg, "%s is not defined as TAG variable", src);
                                        break;
                                }
                                TPLTAGINFO("SYSTEM", index, &name, &type, &dim, &size1, &size2);
                                switch (dim) {
                                case 0:
                                        WRITE_SCALAR_TAG(index, type, value);
                                        break;
                                case 1:
                                        WRITE_ARRAY1_TAG(index, type, size1, value);
                                        break;
                                case 2:
                                        WRITE_ARRAY2_TAG(index, type, size1, size2, value);
                                        break;
                                }
                                if(value[strlen(value)-1]=='\n'){
                                        value[strlen(value)-1]='\0';
                                }

                                sprintf(symbol, "%s:%s\n", symbol, value);
                        }
                }
                else {
                        sprintf(symbol, "%s", buffer);
                } 
                fprintf(fptr, "%s", symbol);
        }

        fclose(fptr);
        fclose(bfptr);

        return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/

static void
WRITE_SCALAR_TAG(INTEGER index, INTEGER type, char *value)
{
        REAL    rval;
        INTEGER ival;
        CHARACTER cval;

        switch (type) {
        case 0:
                TPLGETRTAG("SYSTEM", index, 0, &rval);
                sprintf(value, "%le", rval);
                break;
        case 1:
                TPLGETITAG("SYSTEM", index, 0, &ival);
                sprintf(value, "%d", ival);
                break;
        case 2:
                if (strlen(value) > 0) {
                        TPLGETCTAG("SYSTEM", index, 0, &cval);
                        sprintf(value, "%c", cval);
                }
                break;
        case 3:
                TPLGETSTAG("SYSTEM", index, 0, (STRING *)value);
                break;
        }

        return;
}

static void
WRITE_ARRAY1_TAG(INTEGER index, INTEGER type, INTEGER size1, char *value)
{
        REAL    *rval;
        INTEGER *ival;
        CHARACTER *cval;
        STRING  *sval;
        INTEGER j;
        char  token[LINE_MAX];

        strcpy(value, "");
        switch (type) {
        case 0:
                rval = (REAL*) malloc(sizeof(REAL) * size1);
                TPLGETRATAG("SYSTEM", index, 0, rval);
                for (j = 0; j < size1; j++) {
                        sprintf(token, "%le,", rval[j]);
                        strcat(value, token);
                }
                free(rval);
                break;
        case 1:
                ival = (INTEGER*) malloc(sizeof(INTEGER) * size1);
                TPLGETIATAG("SYSTEM", index, 0, ival);
                for (j = 0; j < size1; j++) {
                        sprintf(token, "%d,", ival[j]);
                        strcat(value, token);
                }
                free(ival);
                break;
        case 2:
                cval = (CHARACTER*) malloc(sizeof(CHARACTER) * size1);
                TPLGETCATAG("SYSTEM", index, 0, cval);
                for (j = 0; j < size1; j++) {
                        sprintf(token, "%c,", cval[j]);
                        strcat(value, token);
                }
                free(cval);
                break;
        case 3:
                sval = (STRING*) malloc(sizeof(STRING) * size1);
                TPLGETSATAG("SYSTEM", index, 0, sval);
                for (j = 0; j < size1; j++) {
                        sprintf(token, "%s,", sval[j]);
                        strcat(value, token);
                }
                free(sval);
                break;
        }

        value[strlen(value) - 1] = '\0';    /* Erace ',' at the tail. */

        return;
}

static void
WRITE_ARRAY2_TAG(INTEGER index, INTEGER type, INTEGER size1, INTEGER size2, char *value)
{
        REAL    *rval;
        INTEGER *ival;
        CHARACTER *cval;
        STRING  *sval;
        INTEGER j, k;
        char  token[LINE_MAX];

        strcpy(value, "");
        switch (type) {
        case 0:
                rval = (REAL*) malloc(sizeof(REAL) * size1 * size2);
                TPLGETRATAG("SYSTEM", index, 0, rval);
                for (j = 0; j < size2; j++) {
                        for (k = 0; k < size1; k++) {
                                sprintf(token, "%le,", rval[size1 * j + k]);
                                strcat(value, token);
                        }
                }
                free(rval);
                break;
        case 1:
                ival = (INTEGER*) malloc(sizeof(INTEGER) * size1 * size2);
                TPLGETIATAG("SYSTEM", index, 0, ival);
                for (j = 0; j < size2; j++) {
                        for (k = 0; k < size1; k++) {
                                sprintf(token, "%d,", ival[size1 * j + k]);
                                strcat(value, token);
                        }
                }
                free(ival);
                break;
        case 2:
                cval = (CHARACTER*) malloc(sizeof(CHARACTER) * size1 * size2);
                TPLGETCATAG("SYSTEM", index, 0, cval);
                for (j = 0; j < size2; j++) {
                        for (k = 0; k < size1; k++) {
                                sprintf(token, "%c,", cval[size1 * j + k]);
                                strcat(value, token);
                        }
                }
                free(cval);
                break;
        case 3:
                sval = (STRING*) malloc(sizeof(STRING) * size1 * size2);
                TPLGETSATAG("SYSTEM", index, 0, sval);
                for (j = 0; j < size2; j++) {
                        for (k = 0; k < size1; k++) {
                                sprintf(token, "%s,", sval[size1 * j + k]);
                                strcat(value, token);
                        }
                }
                free(sval);
                break;
        }

        value[strlen(value) - 1] = '\0';    /* Erace ',' at the tail. */

        return;
}
