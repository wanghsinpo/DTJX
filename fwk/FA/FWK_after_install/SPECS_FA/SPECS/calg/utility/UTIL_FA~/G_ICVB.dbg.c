#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_G_ICVB(void *_alg)
{
}

void
__G_ICVB(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_trm;

	/* Local input/output variable definition */
	REAL	Vbestart;
	REAL	Vbestop;
	REAL	Vbestep;
	INTEGER	pins[3];

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_trm = TPLDEBUGTRM(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Vbestart, _TYPER, 0, 0);
	TPLINITMEM(&Vbestop, _TYPER, 0, 0);
	TPLINITMEM(&Vbestep, _TYPER, 0, 0);
	TPLINITMEM(&pins, _TYPEI, 3, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Vbestart);
	TPLGETDEBUGINVAR(_in, 1, &Vbestop);
	TPLGETDEBUGINVAR(_in, 2, &Vbestep);
	TPLGETDEBUGTRMVAR(_trm, 0, &pins[0]);
	TPLGETDEBUGTRMVAR(_trm, 1, &pins[1]);
	TPLGETDEBUGTRMVAR(_trm, 2, &pins[2]);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	G_ICVB(Vbestart,Vbestop,Vbestep,pins);

	/* Algorithm output variable setting */
}
