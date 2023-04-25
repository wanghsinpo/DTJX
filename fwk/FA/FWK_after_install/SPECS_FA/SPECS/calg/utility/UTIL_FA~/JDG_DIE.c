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
#include <ALGUTIL.h>
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : JDG_DIE
  Vers : 1
  Desc : Judge current die by parameter yield.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Tgt_yld         I    -        target parameter yield to be pas
  2 Last            I    -        all test are finished or not    
  3 Critical        I    -        user flag index as "critical" pa
  4 Ignore          I    -        user flag index as "ignored" par

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Jdg             I    -        0:fail/1:pass/2:unknown         
  2 Yld             R    -        parameter yield                 
  3 Pass_cnt        I    -        pass count of parameter         
  4 Fail_cnt        I    -        fail count of parameter         
  5 Total_cnt       I    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
JDG_DIE(INTEGER Tgt_yld,INTEGER Last,INTEGER Critical,INTEGER Ignore,INTEGER *Jdg,REAL *Yld,INTEGER *Pass_cnt,INTEGER *Fail_cnt,INTEGER *Total_cnt)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	INTEGER	Current_pos;

	TPLDIEPOS(&Current_pos);

	JDG_DIE_AT_POS2(Current_pos, Tgt_yld, Last, Critical, Ignore, Jdg, Yld, Pass_cnt, Fail_cnt, Total_cnt);

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
