#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_G_IDVG(void *_alg)
{
}

void
__G_IDVG(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_trm;

	/* Local input/output variable definition */
	REAL	Vgstart;
	REAL	Vgstop;
	REAL	Vgstep;
	REAL	Vsubstart;
	REAL	Vsubstop;
	REAL	Vsubstep;
	REAL	Vd;
	INTEGER	pins[4];

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_trm = TPLDEBUGTRM(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Vgstart, _TYPER, 0, 0);
	TPLINITMEM(&Vgstop, _TYPER, 0, 0);
	TPLINITMEM(&Vgstep, _TYPER, 0, 0);
	TPLINITMEM(&Vsubstart, _TYPER, 0, 0);
	TPLINITMEM(&Vsubstop, _TYPER, 0, 0);
	TPLINITMEM(&Vsubstep, _TYPER, 0, 0);
	TPLINITMEM(&Vd, _TYPER, 0, 0);
	TPLINITMEM(&pins, _TYPEI, 4, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Vgstart);
	TPLGETDEBUGINVAR(_in, 1, &Vgstop);
	TPLGETDEBUGINVAR(_in, 2, &Vgstep);
	TPLGETDEBUGINVAR(_in, 3, &Vsubstart);
	TPLGETDEBUGINVAR(_in, 4, &Vsubstop);
	TPLGETDEBUGINVAR(_in, 5, &Vsubstep);
	TPLGETDEBUGINVAR(_in, 6, &Vd);
	TPLGETDEBUGTRMVAR(_trm, 0, &pins[0]);
	TPLGETDEBUGTRMVAR(_trm, 1, &pins[1]);
	TPLGETDEBUGTRMVAR(_trm, 2, &pins[2]);
	TPLGETDEBUGTRMVAR(_trm, 3, &pins[3]);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	G_IDVG(Vgstart,Vgstop,Vgstep,Vsubstart,Vsubstop,Vsubstep,Vd,pins);

	/* Algorithm output variable setting */
}
