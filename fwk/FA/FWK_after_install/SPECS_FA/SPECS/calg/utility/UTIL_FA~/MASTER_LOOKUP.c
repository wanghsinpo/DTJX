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

#define MAX_BUF_LENG    1024
#define MAX_STR_LENG    256 
#define ERR_EOF         -1 
#define ERR_OVERFLOW    -2 
#define ERR_NOFILE      -3 
extern  FILE *popen(const char*, const char*);
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : MASTER_LOOKUP
  Vers : 1
  Desc : Returns specified field of specified line in an ASCII data file
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 File            S    -        Master filename                 
  2 Key             S    -        Key string                      
  3 Fnum            I    -        Field number, 1 ~ 199           

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Field           S    -        Extracted field                 
  2 Stat            I    -        0(ok),-1(no key),-2(invalid),-3(

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
MASTER_LOOKUP(STRING File,STRING Key,INTEGER Fnum,STRING *Field,INTEGER *Stat)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	int   _CPORT = 0;
	int   i;
	char  op[MAX_BUF_LENG];
	char  cnv[MAX_STR_LENG];
	char  c;   
	FILE  *fpf, *fpi;


	if (Field == NULL || Stat == NULL) {
		return;
	}

	memset((void *) *Field, '\0', MAX_STR_LENG);
	*Stat=0;

	if(Fnum < 1 || Fnum > 199) {
        	*Stat = ERR_OVERFLOW;
        	return;
    	}
 
    	if ((fpf = fopen(File, "r")) == NULL) {
         	*Stat = ERR_NOFILE; 
        	return; 
    	}
    	fclose(fpf);

	strcpy(op, "grep -v '^#' ");
	strcat(op, File);
	strcat(op, " | ");
	strcat(op, "awk -F: '{if($1==\"");
	strcat(op, Key);
	strcat(op, "\"){if(");
	sprintf(cnv, "%d", Fnum);
	strcat(op, cnv); 
	strcat(op, "<=NF){print $");
	strcat(op, cnv); 
	strcat(op, ";} else {print \":\";}}}' "); 
	strcat(op, " 2> /dev/null");
	if(_CPORT != 0){
        	printf("%s\n", op);
    	}

	if ((fpi = popen(op,"r")) == NULL) {
	        *Stat = ERR_OVERFLOW;
        	return; 
    	}
    	i = 0;
    	while ((c = getc(fpi)) != EOF) {
	        if (c == '\n' || i >= MAX_STR_LENG - 1) {
			i++;
			break;
		}
        	*(*Field + i) = c;
        	i++;
    	}
    	pclose(fpi);

	if (i == 0) {
        	*Stat = ERR_EOF;
        	return;
    	}

    	if (_CPORT != 0) {
        	printf("Field=|%s|\n", *Field);
    	}
    	if(*(*Field) == ':') {
        	memset((void *) *Field, '\0', MAX_STR_LENG);
        	*Stat = ERR_OVERFLOW;
    	}

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
