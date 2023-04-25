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
#include <facomcore.h>
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : FA_UPD_VGEMLVAR
  Vers : 1
  Desc : Update VGEM list type variable
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 SendCEID        I    -        CEID to Host                    
  2 VarName         S    -        Variable Name to update         
  3 VarNum          I    -        Num of Data                     
  4 VarData         S    32       New Data List(MAX 32 elements)  

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -        GEM Reply                       

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_UPD_VGEMLVAR(INTEGER SendCEID,STRING VarName,INTEGER VarNum,STRING *VarData,INTEGER *Status)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/
    
        int  stat;
        int  len;
        int  i;

        char Ceid[256];
        char Num[256];
        char *ptr[32];

	/* Check CEID */
        if (SendCEID < 0) {
          *Status=-1;
          return;
        }
        sprintf(Ceid,"%d\0",SendCEID);

	/* Check VarNum */
        if (VarNum < 0 || VarNum > 32) {
          *Status=-1;
          return;
        }
        sprintf(Num,"%d\0",VarNum);

        /* Check Variable Name */
        len=strlen(VarName);
        if (len == 0 || VarName=="") {
          *Status=-1;
          return;
        }

        /* Check Variable Data */
        if (VarData==NULL) {
          *Status=-1;
          return;
        }
    
        /* Copy List Data */
        for (i=0; i<32; i++) {
           ptr[i] = NULL;
        }
        for (i=0; i<VarNum; i++) {
           ptr[i] = VarData[i];
        }

        gemUpdListVar(Ceid,VarName,Num,ptr,&stat);
        *Status=stat;

/*
	printf("FA_UPD_VGEMVAL\n");
	printf(" > SendCEID\t=%s\n", SendCEID);
	printf(" > VarName\t=%s\n", VarName);
	printf(" > VarData\t=%s\n", VarData);
	printf(" < Status\t=%d\n", *Status);
*/

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
