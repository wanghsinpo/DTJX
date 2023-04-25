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
  Name : RCP_SYSCONF
  Vers : 1
  Desc : Read a parameter written in sysconf file.
       :   SPECS3.0: Initial revision.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Name            S    -        Parameter name for Recipe Manage

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Value           S    -        Parameter value read from syscon
  2 Status          I    -        0: Ok, -1: Not found, -2: Exec f

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
RCP_SYSCONF(STRING Name,STRING *Value,INTEGER *Status)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/
    char cmd[1024];
    FILE *fp;
    int l;

    *Status = 0;
    strcpy(*Value, "");

    sprintf(cmd,
            "/usr/bin/grep -Ee '^[ \t]*%s[ \t]*=' /opt/SPECS/sys/config/sysconf"
            "| /usr/bin/awk -F '=' "
            "'{val=$2;gsub(\"^[ \t]*\",\"\",val);"
            "gsub(\"[ \t]*$\",\"\",val); print val;}'",
            Name);

    if ((fp = popen(cmd, "r")) == NULL) {
        goto No_exec;
    }

    if (fgets(*Value, sizeof(STRING), fp) == NULL) {
        pclose(fp);
        *Status = -1;
        return;
    }

    l = strlen(*Value);
    if (l && (*Value)[l-1] == '\n') (*Value)[l-1] = '\0';

    pclose(fp);
    return;

  No_exec:
    *Status = -2;
    return;

    /*
	printf("RCP_SYSCONF\n");
	printf(" > Name\t=%s\n", Name);
	printf(" < Value\t=%s\n", *Value);
	printf(" < Status\t=%d\n", *Status);
	return;
    */

/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
