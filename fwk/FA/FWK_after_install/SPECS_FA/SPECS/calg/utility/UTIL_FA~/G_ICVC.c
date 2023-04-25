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
  Name : G_ICVC
  Vers : 1
  Desc : Measures the bipolar transistor Collector Current-Collector Voltage ch
       : aracteristics (Ic-Vc characteristics), and displays the measurement re
       : sults on a graph
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Vcestart        R    -        Collector start voltage         
  2 Vcestop         R    -        Collector stop voltage          
  3 Vcestep         R    -        Collector step voltage          
  4 Ibstart         R    -        Base start current              
  5 Ibstop          R    -        Base stop current               
  6 Ibstep          R    -        Base step current               

    Device Terminals:
  1 E               I    -                                        
  2 B               I    -                                        
  3 C               I    -                                        

  Output Variables:

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
G_ICVC(REAL Vcestart,REAL Vcestop,REAL Vcestep,REAL Ibstart,REAL Ibstop,REAL Ibstep,INTEGER pins[])
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	INTEGER	Emitter;
	INTEGER	Base;
	INTEGER	Collector;
	REAL	V2;
	REAL	**Ic;
	REAL	*Im;
	REAL	*V;

	int	N1;
	int	N2;
	int	i, j;


	Emitter   = pins[0];
	Base      = pins[1];
	Collector = pins[2];
	N1 = _ABS((Vcestop - Vcestart) / Vcestep) + 1;
	N2 = _ABS((Ibstop  - Ibstart)  / Ibstep)  + 1;
	Im = (REAL*) malloc(sizeof(REAL) * N1);
	V  = (REAL*) malloc(sizeof(REAL) * N1);
	Ic = (REAL**) malloc(sizeof(REAL*) * N2);

	CONNECT_PIN(fnsmu(1), Emitter);
	CONNECT_PIN(fnsmu(2), Base);
	CONNECT_PIN(fnsmu(3), Collector);
	FORCE_V(Emitter, 0, 20, .1);
	for (i = 0; i < N2; i++) {
		Ic[i] = (REAL*) malloc(sizeof(REAL) * N1);
		V2 = Ibstart + Ibstep * i;
		FORCE_I(Base, V2, V2, 20);
		SET_IV(Collector,
		       1,
		       _ABS(_MAX(Vcestart, Vcestop)),
		       Vcestart,
		       Vcestop,
		       N1,
		       0,
		       0,
		       .1,
		       0.0,
		       COMP_CONT);
		SWEEP_IV(Collector, 2, 0, Im, V, (double*) NULL);
		for(j = 0; j < N1; j++) {
			Ic[i][j] = Im[j];
		}
	}
	DISABLE_PORT(Collector);
	DISABLE_PORT(Base);
	CONNECT_PIN(fnsmu(1), 0);
	CONNECT_PIN(fnsmu(2), 0);
	CONNECT_PIN(fnsmu(3), 0);

	graphDisp_Y(Vcestart,
		    Vcestop,
		    Vcestep,
		    Ic,
		    N2,
		    "Vc [V]",
		    "Ic [A]",
		    LINEAR,
		    "Sweep",
		    "Vc - Ic");

	for (i = 0; i < N2; i++) {
		free(Ic[i]);
	}
	free(Ic);
	free(Im);
	free(V);

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
