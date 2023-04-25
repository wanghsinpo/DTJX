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
  Name : G_ICVB
  Vers : 1
  Desc : Measures the bipolar transistor Collector Current-Base Voltage charact
       : eristics (Ic-Vb characteristics), and displays the measurement results
       :  on a graph
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Vbestart        R    -        Base start voltage              
  2 Vbestop         R    -        Base stop voltage               
  3 Vbestep         R    -        Base step voltage               

    Device Terminals:
  1 E               I    -                                        
  2 B               I    -                                        
  3 C               I    -                                        

  Output Variables:

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
G_ICVB(REAL Vbestart,REAL Vbestop,REAL Vbestep,INTEGER pins[])
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	INTEGER	Emitter;
	INTEGER	Base;
	INTEGER	Collector;
	INTEGER	Ports[2];
	REAL	*I;
	REAL	*V;
	REAL	**Ydata;
	REAL	Ranges[2];

	int	N1;
	int	N2;
	int	i;

	Emitter   = pins[0];
	Base      = pins[1];
	Collector = pins[2];
	N1    = _ABS((Vbestop - Vbestart) / Vbestep) + 1;
	I     = (REAL*) malloc(sizeof(REAL) * N1 * 2);
	Ydata = (REAL**) malloc(sizeof(REAL*) * 2);

	CONNECT_PIN(fnsmu(1), Emitter);
	CONNECT_PIN(fnsmu(2), Base);
	CONNECT_PIN(fnsmu(3), Collector);
	Ports[0] = Base;
	Ports[1] = Collector;
	Ranges[0] = 0;
	Ranges[1] = 0;
	FORCE_V(Collector, 0, 20, .1);
	FORCE_V(Base, 0, 20, .1);
	SET_IV(Emitter,
	       1,
	       _ABS(_MAX(Vbestart, Vbestop)),
	       -Vbestart,
	       -Vbestop,
	       N1,
	       0,
	       0,
	       .1,
	       0.0,
	       COMP_CONT);
	SWEEP_MIV(2, Ports, Ranges, I, (REAL*) NULL, (REAL*) NULL);
	DISABLE_PORT(Base);
	DISABLE_PORT(Collector);
	DISABLE_PORT(Emitter);
	CONNECT_PIN(fnsmu(1), 0);
	CONNECT_PIN(fnsmu(2), 0);
	CONNECT_PIN(fnsmu(3), 0);

	for (i = 0; i < 2 * N1; i++) {
		if (I[i] == 0) {
			I[i] = 1e-15;
		}
		I[i] = _ABS(I[i]);
	}
	Ydata[0] = I;
	Ydata[1] = I + N1;

	graphDisp_Y(Vbestart, 
		    Vbestop, 
		    Vbestep, 
		    Ydata, 
		    2,
		    "Vb [V]",
		    "ABS(Ic)/ABS(Ib) [A]",
		    LOG,
		    "Sweep", 
		    "Vb - Ic/Ib");

	free(I);
	free(Ydata);

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
