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
WRITE_SCALAR_TAG(INTEGER index, INTEGER type, STRING value);
static void
WRITE_ARRAY1_TAG(INTEGER index, INTEGER type, INTEGER size1, char* value);
static void
WRITE_ARRAY2_TAG(INTEGER index, INTEGER type, INTEGER size1, INTEGER size2, char* value);
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : APPLY_FWKCONF
  Vers : 1
  Desc : Read configuration parameter and apply them.
       :   SPECS2.5: Added special parameters.
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
APPLY_FWKCONF(STRING File,INTEGER Type,INTEGER *Errno,STRING *Errmsg)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



        INTEGER index, type, dim, size1, size2;
        STRING  name,value2;
        char    *src,buffer[LINE_MAX],line[LINE_MAX],value[LINE_MAX];
        char    modified[LINE_MAX], symbol[LINE_MAX];
        FILE    *fp;
        char    *s;

        *Errno = 0;
        strcpy(*Errmsg, "");

        if ((fp = fopen(File, "r")) == 0) {
                *Errno = errno;
                sprintf(*Errmsg, "%s", sys_errlist[errno]);
                return;
        }

        while (fgets(buffer, LINE_MAX, fp)) {
                strcpy(line, buffer);
                strcpy(symbol, "");
                strcpy(value, "");
                strtok(line, "!");
                strcpy(symbol, (s = strtok(line, ":"))?s:"");
                strcpy(value, (s = strtok(0, "!"))?s:"");
/*
                DEL_HEAD_SPACE(symbol, &modified); strcpy(symbol, modified);
                DEL_TAIL_SPACE(symbol, &modified); strcpy(symbol, modified);
                DEL_HEAD_SPACE(value,  &modified); strcpy(value, modified);
                DEL_TAIL_SPACE(value,  &modified); strcpy(value, modified);
*/

                if (symbol[strlen(symbol)-1] == '\n'){
                        symbol[strlen(symbol)-1] = '\0';
                }
                if (value[strlen(value)-1] == '\n'){
                        value[strlen(value)-1] = '\0';
                }
                if (symbol[0] != '!' && strcmp(symbol, "") != 0 && strcmp(value, "") != 0) {
                        if (symbol[0] == '*') {
                                if (Type == 1) {
                                        continue;
                                }
                                src = ((char*) symbol) + 1;
                        }
                        else {
                                if (Type == 2) {
                                        continue;
                                }
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
                                strncpy(value2,value,255);
                                value2[255]='\0';
                                WRITE_SCALAR_TAG(index, type, value2);
                                break;
                        case 1:
                                WRITE_ARRAY1_TAG(index, type, size1, value);
                                break;
                        case 2:
                                WRITE_ARRAY2_TAG(index, type, size1, size2, value);
                                break;
                        }
                }
        }

        fclose(fp);

        return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/

static void
WRITE_SCALAR_TAG(INTEGER index, INTEGER type, STRING value)
{
        switch (type) {
        case 0:
                TPLPUTRTAG("SYSTEM", index, 0, atof(value));
                break;
        case 1:
                TPLPUTITAG("SYSTEM", index, 0, atoi(value));
                break;
        case 2:
                if (strlen(value) > 0) {
                        TPLPUTCTAG("SYSTEM", index, 0, value[0]);
                }
                break;
        case 3:
                TPLPUTSTAG("SYSTEM", index, 0, value);
                break;
        }

        return;
}

static int 
GET_TOKEN(INTEGER init_flag, char *src, char *token)
{

   static int i;
   static int ni;
   static int ri;
   static int input_len;
   int  len;
   char buf[LINE_MAX];


   if(init_flag == 1) {
     input_len = strlen(src);
     ni=ri=0;
     i=0;
   }
   bzero(buf,LINE_MAX);
   for(; i<input_len; i++) {
     if(src[i]== ',') {
       if(ni == 0) {
         token[0] = '\0';
         i++;
         return 0;
       }
       else {
         buf[ri]='\0';
         ni = 0;
         ri = 0;
         strcpy(token,buf);
         len = strlen(buf);
         i++;
         return len;
       }
     }
     else if(src[i] == '\\') {
       if(src[i+1] == ',') {
         ni++;
         buf[ri++]=',';
         i++;
       }
       else if (src[i+1]=='\\') {
         ni++;
         buf[ri++]='\\';
         i++;
       }
       else if (src[i+1]=='t') {
         ni++;
         buf[ri++]='\t';
         i++;
       }
       else if (src[i+1]=='n') {
         ni++;
         buf[ri++]='\n';
         i++;
       }
       else {
         ni++;
         buf[ri++]='\\';
       }
     }
     else {
       ni++;
       buf[ri++]=src[i];
     }
   }
   if(ni == 0) {
     token[0] = '\0';
     i++;
     return 0;
   }
   else {
     strcpy(token,buf);
     token[ni]='\0';
     len = strlen(buf);
     i++;
     return len;
   }
   return -1;
}

static void
WRITE_ARRAY1_TAG(INTEGER index, INTEGER type, INTEGER size1, char* value)
{
        REAL    *rval;
        INTEGER *ival;
        CHARACTER *cval;
        STRING  *sval;
        INTEGER j,rtn;
        STRING  token;

        rtn = GET_TOKEN(1, value, token);
        
        switch (type) {
        case 0:
                rval = (REAL*) malloc(sizeof(REAL) * size1);
                for (j = 0; j < size1 && token != NULL; j++) {
                        rval[j] = atof(token);
                        rtn = GET_TOKEN(0, value, token);
                }
                TPLPUTRATAG("SYSTEM", index, 0, rval);
                free(rval);
                break;
        case 1:
                ival = (INTEGER*) malloc(sizeof(INTEGER) * size1);
                for (j = 0; j < size1 && token != NULL; j++) {
                        ival[j] = atoi(token);
                        rtn = GET_TOKEN(0, value, token);
                }
                TPLPUTIATAG("SYSTEM", index, 0, ival);
                free(ival);
                break;
        case 2:
                cval = (CHARACTER*) malloc(sizeof(CHARACTER) * size1);
                for (j = 0; j < size1 && token != NULL; j++) {
                        cval[j] = token[0];
                        rtn = GET_TOKEN(0, value, token);
                }
                TPLPUTCATAG("SYSTEM", index, 0, cval);
                free(cval);
                break;
        case 3:
                sval = (STRING*) malloc(sizeof(STRING) * size1);
                for (j = 0; j < size1 && token != NULL; j++) {
                        strcpy(sval[j], token);
                        rtn = GET_TOKEN(0, value, token);
                }
                TPLPUTSATAG("SYSTEM", index, 0, sval);
                free(sval);
                break;
        }

        return;
}

static void
WRITE_ARRAY2_TAG(INTEGER index, INTEGER type, INTEGER size1, INTEGER size2, char* value)
{
        REAL    *rval;
        INTEGER *ival;
        CHARACTER *cval;
        STRING  *sval;
        INTEGER j, k, rtn;
        STRING  token;


        printf("INDEX = %d\n",index);
        printf("TYPE = %d\n",type);
        printf("SIZE1 & SIZE2 = %d & %d\n",size1,size2);
        printf("VALUE = %s\n",value);

        rtn = GET_TOKEN(1, value, token);
        switch (type) {
        case 0:
                rval = (REAL*) malloc(sizeof(REAL) * size1 * size2);
                for (j = 0; j < size2; j++) {
                        for (k = 0; k < size1; k++) {
                                rval[size1 * j + k] = atof(token);
                                rtn = GET_TOKEN(0, value, token);
                        }
                }
                TPLPUTRATAG("SYSTEM", index, 0, rval);
                free(rval);
                break;
        case 1:
                ival = (INTEGER*) malloc(sizeof(INTEGER) * size1 * size2);
                for (j = 0; j < size2; j++) {
                        for (k = 0; k < size1; k++) {
                                ival[size1 * j + k] = atoi(token);
                                rtn = GET_TOKEN(0, value, token);
                        }
                }
                TPLPUTIATAG("SYSTEM", index, 0, ival);
                free(ival);
                break;
        case 2:
                cval = (CHARACTER*) malloc(sizeof(CHARACTER) * size1 * size2);
                for (j = 0; j < size2; j++) {
                        for (k = 0; k < size1; k++) {
                                cval[size1 * j + k] = token[0];
                                rtn = GET_TOKEN(0, value, token);
                        }
                }
                TPLPUTCATAG("SYSTEM", index, 0, cval);
                free(cval);
                break;
        case 3:
                sval = (STRING*) malloc(sizeof(STRING) * size1 * size2);
                for (j = 0; j < size2; j++) {
                        for (k = 0; k < size1; k++) {
                                strcpy(sval[size1 * j + k], token);
                                printf("Token=%s & %s\n",sval[size1*j+k],token);
                                rtn = GET_TOKEN(0, value, token);
                        }
                }
                TPLPUTSATAG("SYSTEM", index, 0, sval);
                free(sval);
                break;
        }

        return;
}
