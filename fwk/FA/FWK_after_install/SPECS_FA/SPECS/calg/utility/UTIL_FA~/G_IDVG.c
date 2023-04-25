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
  Name : G_IDVG
  Vers : 1
  Desc : Measures the MOSFET Drain Current-Gate Voltage characteristics (Id-Vg 
       : characteristics), and displays the measurement results on a graph
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Vgstart         R    -        Gate start voltage              
  2 Vgstop          R    -        Gate stop voltage               
  3 Vgstep          R    -        Gate step voltage               
  4 Vsubstart       R    -        Substrate start voltage         
  5 Vsubstop        R    -        Substrate stop voltage          
  6 Vsubstep        R    -        Substrate step voltage          
  7 Vd              R    -        Drain voltage                   

    Device Terminals:
  1 S               I    -                                        
  2 G               I    -        Gate terminal                   
  3 D               I    -        Drain terminal                  
  4 Sub             I    -        Substrate terminal              

  Output Variables:

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
G_IDVG(REAL Vgstart,REAL Vgstop,REAL Vgstep,REAL Vsubstart,REAL Vsubstop,REAL Vsubstep,REAL Vd,INTEGER pins[])
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	INTEGER	Source;
	INTEGER	Gate;
	INTEGER	Drain;
	INTEGER	Substrate;
	INTEGER N1;
	INTEGER	N2;
	REAL	**Id;
	REAL	*Im;
	REAL	*V;
	REAL	V2;

	int	i, j;


	Source    = pins[0];
	Gate      = pins[1];
	Drain     = pins[2];
	Substrate = pins[3];
	N1 = _ABS((Vgstop   - Vgstart)   / Vgstep)   + 1;
	N2 = _ABS((Vsubstop - Vsubstart) / Vsubstep) + 1;
	Im = (REAL*) malloc(sizeof(REAL) * N1);
	V  = (REAL*) malloc(sizeof(REAL) * N1);
	Id = (REAL**) malloc(sizeof(REAL*) * N2);

	CONNECT_PIN(fnsmu(1), Drain);
	CONNECT_PIN(fngnd(),  Source);
	CONNECT_PIN(fnsmu(3), Gate);
	CONNECT_PIN(fnsmu(4), Substrate);
	FORCE_V(Drain, Vd, Vd, .1);
	FORCE_V(Gate, 0, 20, .1);
	for (i = 0; i < N2; i++) {
		Id[i] = (REAL*) malloc(sizeof(REAL) * N1);
		V2 = Vsubstart + Vsubstep * i;
		if (Substrate) {
			FORCE_V(Substrate, V2, V2, .1);
		}
		SET_IV(Gate,
		       1,
		       _ABS(_MAX(Vgstart, Vgstop)),
		       Vgstart,
		       Vgstop,
		       N1,
		       0,
		       0,
		       0.1,
		       0.0,
		       COMP_CONT);
		SWEEP_IV(Drain, 2, 0, Im, V, (REAL*) NULL);
		for (j = 0; j < N1; j++) {
			Id[i][j] = Im[j];
		}
	}
	DISABLE_PORT(Drain);
	DISABLE_PORT(Gate);
	if (Substrate) {
		DISABLE_PORT(Substrate);
	}
	CONNECT_PIN(fnsmu(1), 0);
	CONNECT_PIN(fngnd(),  0);
	CONNECT_PIN(fnsmu(3), 0);
	CONNECT_PIN(fnsmu(4), 0);

	graphDisp_Y(Vgstart, 
		    Vgstop, 
		    Vgstep, 
		    Id,
		    N2,
  	  	    "Vg [V]",
		    "Id [A]",
		    LINEAR,
		    "Sweep",
		    "Vg - Id");
	
	for (i = 0; i < N2; i++) {
		free(Id[i]);
	}
	free(Id);
	free(Im);
	free(V);

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
