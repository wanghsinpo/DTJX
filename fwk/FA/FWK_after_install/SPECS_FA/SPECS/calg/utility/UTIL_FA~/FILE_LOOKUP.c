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

#define TEMP_FILE       "/var/tmp/dirlook."
#define LKUP_FILE_MAX   1024
#define MAX_STR_LENG    256
#define MAX_BUF_LENG    1024
extern  FILE *popen(const char*, const char*);
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : FILE_LOOKUP
  Vers : 1
  Desc : Searches for and returns all the file names (in all directories under 
       : a specified directory) that have a specified suffix
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Dir             S    -        Search directory name           
  2 Suffix          S    -        Suffix                          

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Files           S    1024     Found files                     
  2 Count           I    -        Number of found files           
  3 Depth           I    -        Max directory depth + 1         

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FILE_LOOKUP(STRING Dir,STRING Suffix,STRING *Files,INTEGER *Count,INTEGER *Depth)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	int   _CPORT = 0;
	int   N, i;
	char  Script[MAX_STR_LENG];
	char  buf[MAX_STR_LENG];
	char  op[MAX_BUF_LENG * 2];
	char  c;   
	FILE  *fps, *fp1;


	if (Files == NULL || Count == NULL || Depth == NULL) {
		return;
	}

	memset((void *) *Files, '\0', LKUP_FILE_MAX * MAX_STR_LENG);
	*Count = 0; 
	*Depth = 0;

	strcpy(Script, TEMP_FILE);
	sprintf(buf, "%d", getpid());
	strcat(Script, buf);
	if (_CPORT != 0) {
		printf("\n\n***** start FILE_LOOKUP *****\n");
		printf("Script=%s\n", Script);
	}
	remove(Script);
	if ((fps = fopen(Script, "w")) == NULL){
		remove(Script);
		return;
	}

	strcpy(op, "cd ");
	strcat(op, Dir);
	strcat(op, "; /usr/bin/find .");
	if(strlen(Suffix) > 0){
		strcat(op, " -name '*.");
		strcat(op, Suffix);
		strcat(op, "'");
    	}
	strcat(op, " | awk -F '/' '{ print NF - 1 }' | sort -n | uniq | tail -1\n");

	strcat(op, "cd ");
	strcat(op, Dir);
	strcat(op, "; /usr/bin/find .");
	if (strlen(Suffix) > 0){
		strcat(op, " -name '*.");
		strcat(op, Suffix);
		strcat(op, "'");
    	}
	strcat(op, " | sed -e 's=^./=='");
	if (strlen(Suffix) > 0){
		strcat(op, " -e 's/.");
		strcat(op, Suffix);
		strcat(op, "$//'");
    	}
	strcat(op, "\n");
	if (_CPORT != 0){
		printf("op=%s\n",op);
	}

	if (fwrite((void *) op, strlen(op), 1, fps) == NULL){
		fclose(fps);
		remove(Script);
		return;
	}
	fclose(fps);

	strcpy(op, "sh < ");
	strcat(op, Script);
	strcat(op, " 2> /dev/null");
	if (_CPORT != 0) {
		printf("op=%s\n",op);
	}
	if ((fp1 = popen(op, "r")) == NULL) {
		remove(Script);
		return;
	}

	N = -1;
    	while (1) {
        	i = 0;
        	memset((void *) buf, '\0', sizeof(buf));
        	while (1) {
            		c = getc(fp1);
            		if (c == EOF || c=='\n') {
				break;
			}
            		if (i < MAX_STR_LENG - 1){
                		buf[i]=c;
			}
			i++;
		}
		if (_CPORT != 0){
			printf("buf=%s\n", buf);
		}
		if (N < 0) {
			N++;
			if (strlen(buf) == 0) {
				break;
			}
			if (sscanf(buf, "%d", &i) != 1) {
				break;
			}
			*Depth = i; 
			if (_CPORT != 0) {
				printf("Depth=%d\n", *Depth);
			}
		}
		else {
			if (strlen(buf) > 0) {
				if (N < LKUP_FILE_MAX) {
					strcpy(Files[N], buf);
				}
				N++;
			}
		}
		if (c == EOF) {
			break;
		}
    	}

    	*Count = N;
    	pclose(fp1);
    	remove(Script);
    	if(_CPORT != 0){
		printf("***** stop FILE_LOOKUP *****\n\n");
	}

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
