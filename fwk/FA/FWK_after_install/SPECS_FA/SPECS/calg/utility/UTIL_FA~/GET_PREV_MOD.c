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
  Name : GET_PREV_MOD
  Vers : 1
  Desc : Search failed module.
       :   SPECS2.5: Initial revision.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Typeindex_c     I    -        Current type index.             
  2 Diex_c          I    -        Current die x.                  
  3 Diey_c          I    -        Current die y.                  
  4 Modname_c       S    -        Current module name.            

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Typeindex       I    -        Prev die type w/ failed module. 
  2 Diex            I    -        Prev die x w/ failed module.    
  3 Diey            I    -        Prev die y w/ failed module.    
  4 Modname         S    -        Prev failed module name.        
  5 Stat            I    -        0:ok/-1:error                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
GET_PREV_MOD(INTEGER Typeindex_c,INTEGER Diex_c,INTEGER Diey_c,STRING Modname_c,INTEGER *Typeindex,INTEGER *Diex,INTEGER *Diey,STRING *Modname,INTEGER *Stat)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	int    diepos;
	int    modindex;
	int    modtotal;
	int    judge;
	int    pass;
	int    fail;
	int    total;
	int    min_in_mod;
	int    max_in_mod;
	int    min_in_die;
	int    max_in_die;
	int    dieindex;
	int    duplicated;
	int    diebegin;
	int    modbegin;
	int    stat;
	int    outindex;
	STRING diename;
	STRING tmpname;

	*Stat = -1;
        Typeindex_c -= 1;                                                       /* let 0 based                  */

	if(Typeindex_c >= 0){
                TPLDIEXY2POS(Typeindex_c, Diex_c, Diey_c, &diebegin);
	}else{
                TPLDIETOTAL(&diebegin);
                diebegin -= 1;
        }
	if(diebegin < 0){
		return;
	}

	for(diepos = diebegin; diepos >= 0; diepos--){				/* search whole current wafer	*/
		TPLDIEPOS2TYPE(diepos, Typeindex, &dieindex);
		TPLDIEPOS2XY(diepos, Typeindex, Diex, Diey);
		TPLMODULETOTAL(diepos, &modtotal);

                modbegin = modtotal - 1;
                TPLGETRANGEMOD(diepos, modbegin, &min_in_mod, &max_in_mod);
                TPLMODULELABEL(min_in_mod, Modname);
		if(*Typeindex == Typeindex_c &&
                   *Diex      == Diex_c &&
                   *Diey      == Diey_c){
			for(modindex = modtotal - 1; modindex >= 0; modindex--){
				TPLGETRANGEMOD(diepos, modindex, &min_in_mod, &max_in_mod);
				TPLMODULELABEL(min_in_mod, Modname);
				if(strcmp(*Modname, Modname_c) == 0){
					modbegin = modindex - 1;
					break;
				}
			}
		}

		for(modindex = modbegin; modindex >= 0; modindex--){		/* search inside specified die	*/
			JDG_MOD_AT_POS(diepos, modindex, 0, &judge, &pass, &fail, &total); 
			if(judge == 0){						/* found failed module		*/
				TPLGETRANGEMOD(diepos, modindex, &min_in_mod, &max_in_mod);
				TPLMODULELABEL(min_in_mod, Modname);

                                if(*Typeindex != Typeindex_c ||
                                   *Diex      != Diex_c ||
                                   *Diey      != Diey_c){			/* type changed	(not duplicated	*/
					*Stat = 0;
                                        *Typeindex += 1;                        /* let 1 based                  */
                                        return;
				}

				if(strcmp(*Modname, Modname_c) == 0){		/* duplicate module		*/
					continue;
				}

				TPLGETRANGEDIE(diepos, &min_in_die, &max_in_die);
				duplicated = 0;
				for(outindex = max_in_die; outindex > max_in_mod; outindex--){
					TPLMODULELABEL(outindex, &tmpname);
					if(strcmp(tmpname, *Modname) == 0){	/* already probed		*/
						duplicated = 1;
						break;
					}
				}
				if(!duplicated){
                                    *Stat = 0; 
                                    *Typeindex += 1;                            /* let 1 based                  */
                                    return;
				}
			}
		}
	}



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
