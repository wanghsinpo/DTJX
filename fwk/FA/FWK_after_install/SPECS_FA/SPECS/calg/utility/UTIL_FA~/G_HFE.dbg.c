#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_G_HFE(void *_alg)
{
}

void
__G_HFE(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_trm;

	/* Local input/output variable definition */
	REAL	Ibestart;
	REAL	Ibestop;
	INTEGER	Ibestep;
	REAL	Vce;
	INTEGER	pins[3];

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_trm = TPLDEBUGTRM(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Ibestart, _TYPER, 0, 0);
	TPLINITMEM(&Ibestop, _TYPER, 0, 0);
	TPLINITMEM(&Ibestep, _TYPEI, 0, 0);
	TPLINITMEM(&Vce, _TYPER, 0, 0);
	TPLINITMEM(&pins, _TYPEI, 3, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Ibestart);
	TPLGETDEBUGINVAR(_in, 1, &Ibestop);
	TPLGETDEBUGINVAR(_in, 2, &Ibestep);
	TPLGETDEBUGINVAR(_in, 3, &Vce);
	TPLGETDEBUGTRMVAR(_trm, 0, &pins[0]);
	TPLGETDEBUGTRMVAR(_trm, 1, &pins[1]);
	TPLGETDEBUGTRMVAR(_trm, 2, &pins[2]);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	G_HFE(Ibestart,Ibestop,Ibestep,Vce,pins);

	/* Algorithm output variable setting */
}
