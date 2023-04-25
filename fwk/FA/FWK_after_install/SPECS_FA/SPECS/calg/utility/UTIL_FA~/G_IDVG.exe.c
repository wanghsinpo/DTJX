#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_G_IDVG(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_trm, *__trm;

	/* Local input/output variable definition */
	REAL	Vgstart;
	REAL	Vgstop;
	REAL	Vgstep;
	REAL	Vsubstart;
	REAL	Vsubstop;
	REAL	Vsubstep;
	REAL	Vd;
	INTEGER	pins[4];

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_trm = TPLEXECTRM(_alg);
	__trm = TPLLASTTRM(__alg);

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
	TPLGETEXECINVAR(_in, 0, &Vgstart);
	TPLGETEXECINVAR(_in, 1, &Vgstop);
	TPLGETEXECINVAR(_in, 2, &Vgstep);
	TPLGETEXECINVAR(_in, 3, &Vsubstart);
	TPLGETEXECINVAR(_in, 4, &Vsubstop);
	TPLGETEXECINVAR(_in, 5, &Vsubstep);
	TPLGETEXECINVAR(_in, 6, &Vd);
	TPLPUTLASTINVAR(__in, 0, &Vgstart);
	TPLPUTLASTINVAR(__in, 1, &Vgstop);
	TPLPUTLASTINVAR(__in, 2, &Vgstep);
	TPLPUTLASTINVAR(__in, 3, &Vsubstart);
	TPLPUTLASTINVAR(__in, 4, &Vsubstop);
	TPLPUTLASTINVAR(__in, 5, &Vsubstep);
	TPLPUTLASTINVAR(__in, 6, &Vd);
	TPLGETEXECTRMVAR(_trm, 0, &pins[0]);
	TPLGETEXECTRMVAR(_trm, 1, &pins[1]);
	TPLGETEXECTRMVAR(_trm, 2, &pins[2]);
	TPLGETEXECTRMVAR(_trm, 3, &pins[3]);
	TPLPUTLASTTRMVAR(__trm, 0, &pins[0]);
	TPLPUTLASTTRMVAR(__trm, 1, &pins[1]);
	TPLPUTLASTTRMVAR(__trm, 2, &pins[2]);
	TPLPUTLASTTRMVAR(__trm, 3, &pins[3]);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	G_IDVG(Vgstart,Vgstop,Vgstep,Vsubstart,Vsubstop,Vsubstep,Vd,pins);

	/* Algorithm output variable setting */
}

void
__G_IDVG(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__trm;

	/* Local input/output variable definition */
	REAL	Vgstart;
	REAL	Vgstop;
	REAL	Vgstep;
	REAL	Vsubstart;
	REAL	Vsubstop;
	REAL	Vsubstep;
	REAL	Vd;
	INTEGER	pins[4];

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__trm = TPLLASTTRM(__alg);

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
	TPLGETLASTINVAR(__in, 0, &Vgstart);
	TPLGETLASTINVAR(__in, 1, &Vgstop);
	TPLGETLASTINVAR(__in, 2, &Vgstep);
	TPLGETLASTINVAR(__in, 3, &Vsubstart);
	TPLGETLASTINVAR(__in, 4, &Vsubstop);
	TPLGETLASTINVAR(__in, 5, &Vsubstep);
	TPLGETLASTINVAR(__in, 6, &Vd);
	TPLGETLASTTRMVAR(__trm, 0, &pins[0]);
	TPLGETLASTTRMVAR(__trm, 1, &pins[1]);
	TPLGETLASTTRMVAR(__trm, 2, &pins[2]);
	TPLGETLASTTRMVAR(__trm, 3, &pins[3]);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	G_IDVG(Vgstart,Vgstop,Vgstep,Vsubstart,Vsubstop,Vsubstep,Vd,pins);

	/* Algorithm output variable setting */
}
