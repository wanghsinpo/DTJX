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
  Name : FA_UPD_VGEMVAR
  Vers : 1
  Desc : Description for this Algorithm spec.
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
  3 VarData         S    -        New Data                        

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -        GEM Reply                       

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
FA_UPD_VGEMVAR(INTEGER SendCEID,STRING VarName,STRING VarData,INTEGER *Status)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/
    
        int  stat;
        int  len;

        char Ceid[256];
	/* Check CEID */
        if (SendCEID < 0) {
          *Status=-1;
          return;
        }
        sprintf(Ceid,"%d\0",SendCEID);

        /* Check Variable Name */
        len=strlen(VarName);
        if (len == 0 || VarName=="") {
          *Status=-1;
          return;
        }

        /* Check Variable Data */
        len=strlen(VarData);
        if (len == 0 || VarData=="") {
          *Status=-1;
          return;
        }

        gemUpdVar(Ceid,VarName,VarData,&stat);
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
