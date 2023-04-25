/****** <BEGIN> INCLUDE FILES *********** DON'T EDIT FROM <BEGIN> TO <END> ***/
#include <stdio.h>
#include <stdlib.h>
#include <tis.h>
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
  Name : G_HFE
  Vers : 1
  Desc : Measures the bipolar transistor Collector Current-hFE characteristics 
       : (Ic-hFE characteristics), and displays the measurement results on a gr
       : aph
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Ibestart        R    -        Base start current              
  2 Ibestop         R    -        Base stop current               
  3 Ibestep         I    -        Base number of steps            
  4 Vce             R    -        Collector voltage               

    Device Terminals:
  1 E               I    -                                        
  2 B               I    -                                        
  3 C               I    -                                        

  Output Variables:

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
G_HFE(REAL Ibestart,REAL Ibestop,INTEGER Ibestep,REAL Vce,INTEGER pins[])
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	INTEGER	Emitter;
	INTEGER	Base;
	INTEGER	Collector;
	INTEGER	N1;
	INTEGER	N2;
	REAL	*Ib;
	REAL	*Ic;
	REAL	*V;
	REAL	**Hfe;
	REAL	**Absic;

	int	i;
	int	pnum[1];


	Emitter   = pins[0];
	Base      = pins[1];
	Collector = pins[2];
	N1        = Ibestep;
	pnum[0]   = N1;
	Ib    = (REAL*) malloc(sizeof(REAL) * N1);
	Ic    = (REAL*) malloc(sizeof(REAL) * N1);
	V     = (REAL*) malloc(sizeof(REAL) * N1);
	Hfe   = (REAL**) malloc(sizeof(REAL*) * 1);
	Absic = (REAL**) malloc(sizeof(REAL*) * 1);
	Hfe[0]   = (REAL*) malloc(sizeof(REAL) * N1);
	Absic[0] = (REAL*) malloc(sizeof(REAL) * N1);

	CONNECT_PIN(fngnd(),  Emitter);
	CONNECT_PIN(fnsmu(1), Base);
	CONNECT_PIN(fnsmu(2), Collector);
	FORCE_V(Collector, Vce, 20, 0.1);
	SET_IV(Base, 
	       -2, 
	       _ABS(_MAX(Ibestart, Ibestop)),
	       Ibestart,
	       Ibestop,
	       N1,
	       0,
	       0,
	       20,
	       0.0,
	       COMP_CONT);
	SWEEP_IV(Collector, 2, 0, Ic, Ib, (double*) NULL);
	DISABLE_PORT(Collector);
	DISABLE_PORT(Base);
	CONNECT_PIN(fngnd(),  0);
	CONNECT_PIN(fnsmu(1), 0);
	CONNECT_PIN(fnsmu(2), 0);

	for (i = 0; i < N1; i++) {
		if (Ib[i] == 0) {
			Ib[i] = 1e-15;
		}
		if (Ic[i] == 0) {
			Ic[i] = 1e-15;
		}
		Absic[0][i] = _ABS(Ic[i]);
		Hfe[0][i]   = _ABS(Ic[i]) / _ABS(Ib[i]);
	}

	graphDisp_XY(Absic, 
		     Hfe, 
		     pnum,
		     1,
		     "ABS(Ic) [A]",
		     "hfe",
		     LOG,
		     LOG,
		     "Sweep", 
		     "hFE");

	free(Ib);
	free(Ic);
	free(V);
	free(Hfe[0]);
	free(Hfe);
	free(Absic[0]);
	free(Absic);

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
