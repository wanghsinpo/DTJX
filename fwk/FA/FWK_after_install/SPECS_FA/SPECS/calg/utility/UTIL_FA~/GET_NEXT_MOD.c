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
  Name : GET_NEXT_MOD
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
  1 Typeindex       I    -        Next die type w/ failed module. 
  2 Diex            I    -        Next die x w/ failed module.    
  3 Diey            I    -        Next die y w/ failed module.    
  4 Modname         S    -        Next failed module name.        
  5 Stat            I    -        0:ok/-1:error                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
GET_NEXT_MOD(INTEGER Typeindex_c,INTEGER Diex_c,INTEGER Diey_c,STRING Modname_c,INTEGER *Typeindex,INTEGER *Diex,INTEGER *Diey,STRING *Modname,INTEGER *Stat)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	int    diepos;
	int    dietotal;
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
	STRING tmpname;

	*Stat = -1;
	Typeindex_c-= 1;

	if(Typeindex_c < 0){
                diebegin = 0;
        }else{
                TPLDIEXY2POS(Typeindex_c, Diex_c, Diey_c, &diebegin);           /* search start position        */
                if(diebegin < 0){
                        return;
                }
        }

	TPLDIETOTAL(&dietotal);
	for(diepos = diebegin; diepos < dietotal; diepos++){			/* search whole current wafer	*/
		TPLDIEPOS2TYPE(diepos, Typeindex, &dieindex);
		TPLDIEPOS2XY(diepos, Typeindex, Diex, Diey);
		TPLMODULETOTAL(diepos, &modtotal);

                modbegin = 0;
                TPLGETRANGEMOD(diepos, modbegin, &min_in_mod, &max_in_mod);
                TPLMODULELABEL(min_in_mod, Modname);
		if(*Typeindex == Typeindex_c &&                                 /* search inside current die    */
                   *Diex      == Diex_c && 
                   *Diey      == Diey_c){
			for(modindex = 0; modindex < modtotal; modindex++){
				TPLGETRANGEMOD(diepos, modindex, &min_in_mod, &max_in_mod);
				TPLMODULELABEL(min_in_mod, Modname);
				if(strcmp(*Modname, Modname_c) == 0){           /* ignore current module        */
					modbegin = modindex + 1;
					break;
				}
			}
		}

		for(modindex = modbegin; modindex < modtotal; modindex++){	/* search inside specified die	*/
			JDG_MOD_AT_POS(diepos, modindex, 0, &judge, &pass, &fail, &total); 
			if(judge == 0){						/* found failed module		*/
				TPLGETRANGEMOD(diepos, modindex, &min_in_mod, &max_in_mod);
				TPLMODULELABEL(min_in_mod, Modname);

				if(*Typeindex != Typeindex_c ||                 /* not current die              */
                                   *Diex      != Diex_c ||
                                   *Diey      != Diey_c){
					*Stat = 0;
                                        *Typeindex += 1;                        /* let 1 based                  */
                                        return;
				}

				if(strcmp(*Modname, Modname_c) == 0){		/* same with current module	*/
					continue;
				}

				TPLGETRANGEDIE(diepos, &min_in_die, &max_in_die);
				duplicated = 0;
				for(outindex = min_in_die; outindex < min_in_mod; outindex++){
					TPLMODULELABEL(outindex, &tmpname);
					if(strcmp(tmpname, *Modname) == 0){	/* already probed		*/
						duplicated = 1;
						break;
					}
				}
				if(!duplicated){
					*Stat = 0;
                                        *Typeindex += 1;                        /* let 1 based                  */
                                        return;
				}
			}
		}
	}



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
