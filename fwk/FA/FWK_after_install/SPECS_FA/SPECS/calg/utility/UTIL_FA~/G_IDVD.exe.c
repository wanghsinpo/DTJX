#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_G_IDVD(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_trm, *__trm;

	/* Local input/output variable definition */
	REAL	Vdstart;
	REAL	Vdstop;
	REAL	Vdstep;
	REAL	Vgstart;
	REAL	Vgstop;
	REAL	Vgstep;
	INTEGER	pins[4];

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_trm = TPLEXECTRM(_alg);
	__trm = TPLLASTTRM(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Vdstart, _TYPER, 0, 0);
	TPLINITMEM(&Vdstop, _TYPER, 0, 0);
	TPLINITMEM(&Vdstep, _TYPER, 0, 0);
	TPLINITMEM(&Vgstart, _TYPER, 0, 0);
	TPLINITMEM(&Vgstop, _TYPER, 0, 0);
	TPLINITMEM(&Vgstep, _TYPER, 0, 0);
	TPLINITMEM(&pins, _TYPEI, 4, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Vdstart);
	TPLGETEXECINVAR(_in, 1, &Vdstop);
	TPLGETEXECINVAR(_in, 2, &Vdstep);
	TPLGETEXECINVAR(_in, 3, &Vgstart);
	TPLGETEXECINVAR(_in, 4, &Vgstop);
	TPLGETEXECINVAR(_in, 5, &Vgstep);
	TPLPUTLASTINVAR(__in, 0, &Vdstart);
	TPLPUTLASTINVAR(__in, 1, &Vdstop);
	TPLPUTLASTINVAR(__in, 2, &Vdstep);
	TPLPUTLASTINVAR(__in, 3, &Vgstart);
	TPLPUTLASTINVAR(__in, 4, &Vgstop);
	TPLPUTLASTINVAR(__in, 5, &Vgstep);
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
	G_IDVD(Vdstart,Vdstop,Vdstep,Vgstart,Vgstop,Vgstep,pins);

	/* Algorithm output variable setting */
}

void
__G_IDVD(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__trm;

	/* Local input/output variable definition */
	REAL	Vdstart;
	REAL	Vdstop;
	REAL	Vdstep;
	REAL	Vgstart;
	REAL	Vgstop;
	REAL	Vgstep;
	INTEGER	pins[4];

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__trm = TPLLASTTRM(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Vdstart, _TYPER, 0, 0);
	TPLINITMEM(&Vdstop, _TYPER, 0, 0);
	TPLINITMEM(&Vdstep, _TYPER, 0, 0);
	TPLINITMEM(&Vgstart, _TYPER, 0, 0);
	TPLINITMEM(&Vgstop, _TYPER, 0, 0);
	TPLINITMEM(&Vgstep, _TYPER, 0, 0);
	TPLINITMEM(&pins, _TYPEI, 4, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Vdstart);
	TPLGETLASTINVAR(__in, 1, &Vdstop);
	TPLGETLASTINVAR(__in, 2, &Vdstep);
	TPLGETLASTINVAR(__in, 3, &Vgstart);
	TPLGETLASTINVAR(__in, 4, &Vgstop);
	TPLGETLASTINVAR(__in, 5, &Vgstep);
	TPLGETLASTTRMVAR(__trm, 0, &pins[0]);
	TPLGETLASTTRMVAR(__trm, 1, &pins[1]);
	TPLGETLASTTRMVAR(__trm, 2, &pins[2]);
	TPLGETLASTTRMVAR(__trm, 3, &pins[3]);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	G_IDVD(Vdstart,Vdstop,Vdstep,Vgstart,Vgstop,Vgstep,pins);

	/* Algorithm output variable setting */
}
