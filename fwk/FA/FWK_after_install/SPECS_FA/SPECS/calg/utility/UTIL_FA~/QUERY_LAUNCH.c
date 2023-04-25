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

#include <TOOLCTRL.h>

/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : QUERY_LAUNCH
  Vers : 1
  Desc : Start Quick Query.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Session         S    -        Session ID                      
  2 Port            S    -        Port ID                         
  3 Project         S    -        Project ID                      
  4 Hostname        S    -        Hostname                        

  Output Variables:

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
QUERY_LAUNCH(STRING Session,STRING Port,STRING Project,STRING Hostname)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



        STRING  opt[32];        /* enough size */
        STRING  _Session;
        STRING  _Port;
        STRING  _Hostname;
        INTEGER nopt;

        /* Never insert a space character between an option and a parameter. */

        sprintf(_Port,     "-c%s", Port    );
        sprintf(_Session,  "-g%s", Session );
        sprintf(_Hostname, "-h%s", Hostname);

        nopt = 0;
        strcpy(opt[nopt], _Port    );   nopt++;
        strcpy(opt[nopt], _Session );   nopt++;
        strcpy(opt[nopt], _Hostname);   nopt++;

	QQ_INIT(opt, nopt);



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
