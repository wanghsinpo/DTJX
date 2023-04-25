#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_G_ICVC(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_trm, *__trm;

	/* Local input/output variable definition */
	REAL	Vcestart;
	REAL	Vcestop;
	REAL	Vcestep;
	REAL	Ibstart;
	REAL	Ibstop;
	REAL	Ibstep;
	INTEGER	pins[3];

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_trm = TPLEXECTRM(_alg);
	__trm = TPLLASTTRM(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Vcestart, _TYPER, 0, 0);
	TPLINITMEM(&Vcestop, _TYPER, 0, 0);
	TPLINITMEM(&Vcestep, _TYPER, 0, 0);
	TPLINITMEM(&Ibstart, _TYPER, 0, 0);
	TPLINITMEM(&Ibstop, _TYPER, 0, 0);
	TPLINITMEM(&Ibstep, _TYPER, 0, 0);
	TPLINITMEM(&pins, _TYPEI, 3, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Vcestart);
	TPLGETEXECINVAR(_in, 1, &Vcestop);
	TPLGETEXECINVAR(_in, 2, &Vcestep);
	TPLGETEXECINVAR(_in, 3, &Ibstart);
	TPLGETEXECINVAR(_in, 4, &Ibstop);
	TPLGETEXECINVAR(_in, 5, &Ibstep);
	TPLPUTLASTINVAR(__in, 0, &Vcestart);
	TPLPUTLASTINVAR(__in, 1, &Vcestop);
	TPLPUTLASTINVAR(__in, 2, &Vcestep);
	TPLPUTLASTINVAR(__in, 3, &Ibstart);
	TPLPUTLASTINVAR(__in, 4, &Ibstop);
	TPLPUTLASTINVAR(__in, 5, &Ibstep);
	TPLGETEXECTRMVAR(_trm, 0, &pins[0]);
	TPLGETEXECTRMVAR(_trm, 1, &pins[1]);
	TPLGETEXECTRMVAR(_trm, 2, &pins[2]);
	TPLPUTLASTTRMVAR(__trm, 0, &pins[0]);
	TPLPUTLASTTRMVAR(__trm, 1, &pins[1]);
	TPLPUTLASTTRMVAR(__trm, 2, &pins[2]);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	G_ICVC(Vcestart,Vcestop,Vcestep,Ibstart,Ibstop,Ibstep,pins);

	/* Algorithm output variable setting */
}

void
__G_ICVC(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__trm;

	/* Local input/output variable definition */
	REAL	Vcestart;
	REAL	Vcestop;
	REAL	Vcestep;
	REAL	Ibstart;
	REAL	Ibstop;
	REAL	Ibstep;
	INTEGER	pins[3];

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__trm = TPLLASTTRM(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Vcestart, _TYPER, 0, 0);
	TPLINITMEM(&Vcestop, _TYPER, 0, 0);
	TPLINITMEM(&Vcestep, _TYPER, 0, 0);
	TPLINITMEM(&Ibstart, _TYPER, 0, 0);
	TPLINITMEM(&Ibstop, _TYPER, 0, 0);
	TPLINITMEM(&Ibstep, _TYPER, 0, 0);
	TPLINITMEM(&pins, _TYPEI, 3, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Vcestart);
	TPLGETLASTINVAR(__in, 1, &Vcestop);
	TPLGETLASTINVAR(__in, 2, &Vcestep);
	TPLGETLASTINVAR(__in, 3, &Ibstart);
	TPLGETLASTINVAR(__in, 4, &Ibstop);
	TPLGETLASTINVAR(__in, 5, &Ibstep);
	TPLGETLASTTRMVAR(__trm, 0, &pins[0]);
	TPLGETLASTTRMVAR(__trm, 1, &pins[1]);
	TPLGETLASTTRMVAR(__trm, 2, &pins[2]);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	G_ICVC(Vcestart,Vcestop,Vcestep,Ibstart,Ibstop,Ibstep,pins);

	/* Algorithm output variable setting */
}
