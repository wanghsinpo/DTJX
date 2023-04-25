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
#include <malloc.h>
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : G_IDVD
  Vers : 1
  Desc : Measures the MOSFET Drain Current-Drain Voltage characteristics (Id-Vd
       :  characteristics), and displays the measurement results on a graph
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Vdstart         R    -        Drain start voltage             
  2 Vdstop          R    -        Drain stop voltage              
  3 Vdstep          R    -        Drain step voltage              
  4 Vgstart         R    -        Gate start voltage              
  5 Vgstop          R    -        Gate stop voltage               
  6 Vgstep          R    -        Gate step voltage               

    Device Terminals:
  1 S               I    -                                        
  2 G               I    -        Gate terminal                   
  3 D               I    -        Drain terminal                  
  4 Sub             I    -        Substrate terminal              

  Output Variables:

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
G_IDVD(REAL Vdstart,REAL Vdstop,REAL Vdstep,REAL Vgstart,REAL Vgstop,REAL Vgstep,INTEGER pins[])
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	INTEGER	Source;
        INTEGER	Gate;
        INTEGER	Drain;
        INTEGER	Substrate;
        INTEGER	N1;
        INTEGER	N2;
	REAL	**Id;
	REAL	*Im;
	REAL	*V;
	REAL	V2;

	int	i, j;


        Source     = pins[0];
        Gate       = pins[1];
        Drain      = pins[2];
        Substrate  = pins[3];
        N1 = _ABS((Vdstop - Vdstart) / Vdstep) + 1;
        N2 = _ABS((Vgstop - Vgstart) / Vgstep) + 1;
	Im = (REAL*) malloc(sizeof(REAL) * N1);
	V  = (REAL*) malloc(sizeof(REAL) * N1);
        Id = (REAL**) malloc(sizeof(REAL*) * N2);

	CONNECT_PIN(fnsmu(1), Drain);
	CONNECT_PIN(fngnd(),  Source);
	CONNECT_PIN(fnsmu(3), Gate);
	CONNECT_PIN(fnsmu(4), Substrate);

	if (Substrate) {
		FORCE_V(Substrate, 0, 0, .1);
	}
	for(i = 0; i < N2; i ++) {
		Id[i] = (REAL*) malloc(sizeof(REAL) * N1);
		V2 = Vgstart + Vgstep * i;
		FORCE_V(Gate, V2, V2, .1);
		SET_IV(Drain, 
		       1, 
		       _ABS(_MAX(Vdstart, Vdstop)),
		       Vdstart,
		       Vdstop,
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
	CONNECT_PIN(fnsmu(1), 0);
	CONNECT_PIN(fngnd(),  0);
	CONNECT_PIN(fnsmu(3), 0);
	CONNECT_PIN(fnsmu(4), 0);

	graphDisp_Y(Vdstart, 
		    Vdstop, 
  		    Vdstep, 
		    Id, 
	  	    N2,
		    "Vd [V]",
		    "Id [A]",
		    LINEAR,
		    "Sweep", 
		    "Vd - Id");

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
