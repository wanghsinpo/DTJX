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
  Name : GEM_GETCMD
  Vers : 1
  Desc : Get all of commands for using this algorirthm.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Cmd             S    -        Command                         
  2 Rply            S    -        Reply string                    
  3 Parms           S    500                                      

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
GEM_GETCMD(STRING *Cmd,STRING *Rply,STRING *Parms)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	INTEGER i;
	char	*ptr[500];
        FILE    *fptr;
	
	for (i=0; i<500;i++)
		ptr[i] = Parms[i];
	gemGetCmd(*Cmd, *Rply, ptr);

/*
        fptr =fopen("/usr/tmp/gemmsgspecs.log","a");
        if (strncmp(Cmd,"NULL",4)!=0){
          printf("CMD = %s\n",Cmd);
          fprintf(fptr,"CMD = %s\n",Cmd);
  	  for (i=0;i<500;i++){
		  if (strcmp(Parms[i],"")!=0){
	        	  printf("Parms[%3d]:\"%s\"\n", i+1, Parms[i]);
                          fprintf(fptr, "Parms[%3d]:\"%s\"\n", i+1, Parms[i]);
                  }
          }
        }
          fclose(fptr);
*/
/*
	printf("GEM_GETCMD\n");
	printf("Command=%s\n",Cmd);
	for (i=0;i<300;i++)
		if (strcmp(Parms[i],"")!=0)
			printf("%d:%s\n", i+1, Parms[i]);
	printf(" < Rply\t=%s\n", *Rply);
*/	
	return;


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
