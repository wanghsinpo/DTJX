#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_G_CV(void *_alg)
{
}

void
__G_CV(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_trm;

	/* Local input/output variable definition */
	REAL	Vstart;
	REAL	Vstop;
	REAL	Vstep;
	REAL	Delay;
	REAL	Hold;
	INTEGER	pins[2];

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_trm = TPLDEBUGTRM(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Vstart, _TYPER, 0, 0);
	TPLINITMEM(&Vstop, _TYPER, 0, 0);
	TPLINITMEM(&Vstep, _TYPER, 0, 0);
	TPLINITMEM(&Delay, _TYPER, 0, 0);
	TPLINITMEM(&Hold, _TYPER, 0, 0);
	TPLINITMEM(&pins, _TYPEI, 2, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Vstart);
	TPLGETDEBUGINVAR(_in, 1, &Vstop);
	TPLGETDEBUGINVAR(_in, 2, &Vstep);
	TPLGETDEBUGINVAR(_in, 3, &Delay);
	TPLGETDEBUGINVAR(_in, 4, &Hold);
	TPLGETDEBUGTRMVAR(_trm, 0, &pins[0]);
	TPLGETDEBUGTRMVAR(_trm, 1, &pins[1]);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	G_CV(Vstart,Vstop,Vstep,Delay,Hold,pins);

	/* Algorithm output variable setting */
}
