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
  Name : RCP_MK_FILENAME
  Vers : 1
  Desc : Make file name from directory name and file name.
       :   SPECS3.0: Initial revision.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Dirname         S    -                                        
  2 Filename        S    -                                        
  3 Suffix          S    -                                        

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Fullfile        S    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
RCP_MK_FILENAME(STRING Dirname,STRING Filename,STRING Suffix,STRING *Fullfile)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/
    STRING dir, fil;
    int sl, fl, dl;

    if (Dirname[0] == '\0' || Filename[0] == '/') {
        strcpy(*Fullfile, Filename);
    }
    else {
        strcpy(dir, Dirname);
        dl = strlen(dir);
        if (dir[dl-1] != '/') {
            strcat(dir, "/");
        }
        sprintf(*Fullfile, "%s%s", dir, Filename);
    }

    sl = strlen(Suffix);
    fl = strlen(*Fullfile);
    if (sl) {
        if (fl < sl) {
            strcat(*Fullfile, Suffix);
        }
        else {
            if (strcmp(&(*Fullfile)[fl-sl], Suffix)) {
                strcat(*Fullfile, Suffix);
            }
        }
    }
    /*
	printf("RCP_MK_FILENAME\n");
	printf(" > Dirname\t=%s\n", Dirname);
	printf(" > Filename\t=%s\n", Filename);
	printf(" > Suffix\t=%s\n", Suffix);
	printf(" < Fullfile\t=%s\n", *Fullfile);
	return;
    */
/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
