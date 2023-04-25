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
  Name : GEM_SENDEVENT
  Vers : 1
  Desc : Send all of event for using this command.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Event           S    -        Event name                      
  2 Parms           S    500                                      

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -        GEM Reply                       

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
GEM_SENDEVENT(STRING Event,STRING *Parms,INTEGER *Status)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/
	int	i;
	int	stat;
	char	*ptr[500];
        FILE    *fptr;

	for (i=0;i<500;i++)
		ptr[i] = Parms[i];
	
	gemSendEvent(Event, ptr, &stat); 
	*Status = stat;
/*
        fptr =fopen("/usr/tmp/gemmsgspecs.log","a");
        printf("EVENT = %s\n",Event);
        fprintf(fptr,"EVENT = %s\n",Event);
	for (i=0;i<500;i++){
                if (strcmp(Parms[i],"")!=0){
                        printf("Parms[%3d]:\"%s\"\n",i+1,Parms[i]);
                        fprintf(fptr,"Parms[%3d]:\"%s\"\n",i+1,Parms[i]);
                }
        }
        fclose(fptr);
*/
/*
	printf(" < Status\t=%d\n", *Status);
*/	
	return;


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
