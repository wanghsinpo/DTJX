#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_G_IDVD(void *_alg)
{
}

void
__G_IDVD(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_trm;

	/* Local input/output variable definition */
	REAL	Vdstart;
	REAL	Vdstop;
	REAL	Vdstep;
	REAL	Vgstart;
	REAL	Vgstop;
	REAL	Vgstep;
	INTEGER	pins[4];

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_trm = TPLDEBUGTRM(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Vdstart, _TYPER, 0, 0);
	TPLINITMEM(&Vdstop, _TYPER, 0, 0);
	TPLINITMEM(&Vdstep, _TYPER, 0, 0);
	TPLINITMEM(&Vgstart, _TYPER, 0, 0);
	TPLINITMEM(&Vgstop, _TYPER, 0, 0);
	TPLINITMEM(&Vgstep, _TYPER, 0, 0);
	TPLINITMEM(&pins, _TYPEI, 4, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Vdstart);
	TPLGETDEBUGINVAR(_in, 1, &Vdstop);
	TPLGETDEBUGINVAR(_in, 2, &Vdstep);
	TPLGETDEBUGINVAR(_in, 3, &Vgstart);
	TPLGETDEBUGINVAR(_in, 4, &Vgstop);
	TPLGETDEBUGINVAR(_in, 5, &Vgstep);
	TPLGETDEBUGTRMVAR(_trm, 0, &pins[0]);
	TPLGETDEBUGTRMVAR(_trm, 1, &pins[1]);
	TPLGETDEBUGTRMVAR(_trm, 2, &pins[2]);
	TPLGETDEBUGTRMVAR(_trm, 3, &pins[3]);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	G_IDVD(Vdstart,Vdstop,Vdstep,Vgstart,Vgstop,Vgstep,pins);

	/* Algorithm output variable setting */
}
