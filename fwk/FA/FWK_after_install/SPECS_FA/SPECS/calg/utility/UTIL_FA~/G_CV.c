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
  Name : G_CV
  Vers : 1
  Desc : Measures the Capacitance-Voltage characteristics (C-V characteristics)
       : , and displays the measurement results on a graph
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Vstart          R    -        Inversion voltage               
  2 Vstop           R    -        Accumulation voltage            
  3 Vstep           R    -        Step voltage                    
  4 Delay           R    -        Step delay time                 
  5 Hold            R    -        Hold time                       

    Device Terminals:
  1 H               I    -                                        
  2 L               I    -                                        

  Output Variables:

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
G_CV(REAL Vstart,REAL Vstop,REAL Vstep,REAL Delay,REAL Hold,INTEGER pins[])
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	INTEGER	H;
	INTEGER	L;
	INTEGER	N;
	REAL	Freq;
	REAL	**C;
	REAL	*G;
	REAL	*V;


	H = pins[0];
	L = pins[1];
	N = _ABS((Vstop - Vstart) / Vstep) + 1;
	G = (REAL*) malloc(sizeof(REAL) * N);
	V = (REAL*) malloc(sizeof(REAL) * N);
	C = (REAL**) malloc(sizeof(REAL*) * 1);
	C[0] = (REAL*) malloc(sizeof(REAL) * N);
	
	CONNECT_PIN(fncmh(), H);
	CONNECT_PIN(fncml(), L);
	SET_CV84(Vstart, Vstop, N, Hold, Delay);	/* frq is default (1MHz) */
	SWEEP_CV84(0, C[0], G, V);
	CONNECT_PIN(fncmh(), 0);
	CONNECT_PIN(fncml(), 0);

	graphDisp_Y(Vstart, 
		    Vstop, 
		    Vstep, 
		    C, 
		    1,
		    "Bias [V]",
		    "Cap [F]",
		    LINEAR, 
		    "Sweep", 
		    "C_V");

	free(C[0]);
	free(C);
	free(G);
	free(V);

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
