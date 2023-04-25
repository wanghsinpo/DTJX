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
  Name : RCP_REPLACE_WD
  Vers : 1
  Desc : Replace keyword in Format String.
       :   SPECS3.0: Initial revision.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Format          S    -                                        
  2 Find_wd         S    5                                        
  3 Replace_wd      S    5                                        

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 String          S    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
RCP_REPLACE_WD(STRING Format,STRING *Find_wd,STRING *Replace_wd,STRING *String)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

    char cmd[4096];
    STRING line;

    FILE *fp;
    int l;
    int i;

    strcpy(*String, "");

    if (strlen(Find_wd[0]) <= 0) {
        strcpy(*String, Format);
        return;
    }

    sprintf(cmd, "/usr/bin/echo '%s' | /usr/bin/sed ", Format);
    for (i = 0; i < 5; i++) {
        if (strlen(Find_wd[i]) <= 0) {
            break;
        }
        sprintf(&cmd[strlen(cmd)], "-e 's/%s/%s/' ", Find_wd[i], Replace_wd[i]);
    }

    if ((fp = popen(cmd, "r")) == NULL) {
        return;
    }

    if (fgets(line, sizeof(STRING), fp) == NULL) {
        pclose(fp);
        return;
    }

    pclose(fp);

    l = strlen(line);
    if (l && line[l-1] == '\n') line[l-1] = '\0';

    strcpy(*String, line);
    return;


/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
