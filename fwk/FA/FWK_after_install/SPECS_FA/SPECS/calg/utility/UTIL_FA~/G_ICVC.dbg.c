#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_G_ICVC(void *_alg)
{
}

void
__G_ICVC(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_trm;

	/* Local input/output variable definition */
	REAL	Vcestart;
	REAL	Vcestop;
	REAL	Vcestep;
	REAL	Ibstart;
	REAL	Ibstop;
	REAL	Ibstep;
	INTEGER	pins[3];

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_trm = TPLDEBUGTRM(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Vcestart, _TYPER, 0, 0);
	TPLINITMEM(&Vcestop, _TYPER, 0, 0);
	TPLINITMEM(&Vcestep, _TYPER, 0, 0);
	TPLINITMEM(&Ibstart, _TYPER, 0, 0);
	TPLINITMEM(&Ibstop, _TYPER, 0, 0);
	TPLINITMEM(&Ibstep, _TYPER, 0, 0);
	TPLINITMEM(&pins, _TYPEI, 3, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Vcestart);
	TPLGETDEBUGINVAR(_in, 1, &Vcestop);
	TPLGETDEBUGINVAR(_in, 2, &Vcestep);
	TPLGETDEBUGINVAR(_in, 3, &Ibstart);
	TPLGETDEBUGINVAR(_in, 4, &Ibstop);
	TPLGETDEBUGINVAR(_in, 5, &Ibstep);
	TPLGETDEBUGTRMVAR(_trm, 0, &pins[0]);
	TPLGETDEBUGTRMVAR(_trm, 1, &pins[1]);
	TPLGETDEBUGTRMVAR(_trm, 2, &pins[2]);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	G_ICVC(Vcestart,Vcestop,Vcestep,Ibstart,Ibstop,Ibstep,pins);

	/* Algorithm output variable setting */
}
