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
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : FA_GETKEY_ITEMS
  Vers : 1
  Desc : Desc: Get many items in the file from key recipe id. 
       : Date: '00/Nov/28 Initial revision
       : Date: '01/Mar/09 Released  K.N
       : Date: '01/Jul/19 Change to Lynx1 by M.N
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Key             S    -        Key ID (PPExecName)             
  2 Filename        S    -        File Name                       

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Waf             S    -        Wafer spec name                 
  2 Die             S    -        Die spec name                   
  3 Tst             S    -        Test spec name                  
  4 Prb             S    -        Probe card spec name            
  5 Tpl             S    -        Test plan file name             
  6 Lim             S    -        Limit file name                 
  7 Rcp             S    -        Prober recipe file name         
  8 Lot_id          S    -        Lot ID                          
  9 Product_id      S    -        Product ID                      
 10 Process_id      S    -        Process ID                      
 11 Status          I    -        0:OK -1:Eof -2:No Data -3:No Fil

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_GETKEY_ITEMS(STRING Key,STRING Filename,STRING *Waf,STRING *Die,STRING *Tst,STRING *Prb,STRING *Tpl,STRING *Lim,STRING *Rcp,STRING *Lot_id,STRING *Product_id,STRING *Process_id,INTEGER *Status)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	int	i;
	int	e,r,w,x;
	STRING	Field;
	STRING	Command;
	FILE	*pp;
	
	strcpy(*Waf, "");
	strcpy(*Die, "");
	strcpy(*Tst, "");
	strcpy(*Prb, "");
	strcpy(*Tpl, "");
	strcpy(*Lim, "");
	strcpy(*Rcp, "");
	strcpy(*Lot_id, "");
	strcpy(*Product_id, "");
	strcpy(*Process_id, "");
	*Status = 0;
	
	VERIFY_FILE(Filename, "Normal", &e, &r, &w, &x);	/* File Check */
	if (r==0) goto NoFile;
	
	for (i=1; i<=10; i++){
		sprintf(Command, "grep -v '^#' %s | awk -F : '{ if($1 == \"%s\"){ if(%d<=NF){ print $%d; } else { print \":\"; }}}'", Filename, Key, i+1, i+1);
		if ((pp = popen(Command, "r")) == NULL) goto NoFile;
		if (fgets(Field, sizeof(Field), pp) == NULL) goto Eof;
		if (Field[strlen(Field)-1] == '\n') Field[strlen(Field)-1] = '\0';

printf("**%s**%d\n",Field, strcmp(Field, ":"));
		if (strcmp(Field, ":") == 0) goto OverFlow;
		switch (i){
		case 1:
			strcpy(*Lot_id, Field);
			break;
		case 2:
			strcpy(*Product_id, Field);
			break;
		case 3:
			strcpy(*Process_id, Field);
			break;
		case 4:
			strcpy(*Waf, Field);
			break;
		case 5:
			strcpy(*Die, Field);
			break;
		case 6:
			strcpy(*Tst, Field);
			break;
		case 7:
			strcpy(*Prb, Field);
			break;
		case 8:
			strcpy(*Tpl, Field);
			break;
		case 9:
			strcpy(*Lim, Field);
			break;
		case 10:
			strcpy(*Rcp, Field);
			break;
		}
		pclose(pp);
	}

	printf("FA_GETKEY_ITEMS\n");
	printf(" > Key\t=%s\n", Key);
	printf(" > Filename\t=%s\n", Filename);
	printf(" < Waf_name\t=%s\n", *Waf);
	printf(" < Die_name\t=%s\n", *Die);
	printf(" < Tst_name\t=%s\n", *Tst);
	printf(" < Prb_name\t=%s\n", *Prb);
	printf(" < Tpl_name\t=%s\n", *Tpl);
	printf(" < Lim_name\t=%s\n", *Lim);
	printf(" < Rcp_name\t=%s\n", *Rcp);
	printf(" < Status\t=%d\n", *Status);
	return;

NoFile:
	*Status=-3;
	return;
OverFlow:
	if (pp != NULL) pclose(pp);
	*Status=-2;
	return;
Eof:
	if (pp != NULL) pclose(pp);
	*Status=-1;
	return;
	


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
