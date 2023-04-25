#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_G_CV(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_trm, *__trm;

	/* Local input/output variable definition */
	REAL	Vstart;
	REAL	Vstop;
	REAL	Vstep;
	REAL	Delay;
	REAL	Hold;
	INTEGER	pins[2];

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_trm = TPLEXECTRM(_alg);
	__trm = TPLLASTTRM(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Vstart, _TYPER, 0, 0);
	TPLINITMEM(&Vstop, _TYPER, 0, 0);
	TPLINITMEM(&Vstep, _TYPER, 0, 0);
	TPLINITMEM(&Delay, _TYPER, 0, 0);
	TPLINITMEM(&Hold, _TYPER, 0, 0);
	TPLINITMEM(&pins, _TYPEI, 2, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Vstart);
	TPLGETEXECINVAR(_in, 1, &Vstop);
	TPLGETEXECINVAR(_in, 2, &Vstep);
	TPLGETEXECINVAR(_in, 3, &Delay);
	TPLGETEXECINVAR(_in, 4, &Hold);
	TPLPUTLASTINVAR(__in, 0, &Vstart);
	TPLPUTLASTINVAR(__in, 1, &Vstop);
	TPLPUTLASTINVAR(__in, 2, &Vstep);
	TPLPUTLASTINVAR(__in, 3, &Delay);
	TPLPUTLASTINVAR(__in, 4, &Hold);
	TPLGETEXECTRMVAR(_trm, 0, &pins[0]);
	TPLGETEXECTRMVAR(_trm, 1, &pins[1]);
	TPLPUTLASTTRMVAR(__trm, 0, &pins[0]);
	TPLPUTLASTTRMVAR(__trm, 1, &pins[1]);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	G_CV(Vstart,Vstop,Vstep,Delay,Hold,pins);

	/* Algorithm output variable setting */
}

void
__G_CV(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__trm;

	/* Local input/output variable definition */
	REAL	Vstart;
	REAL	Vstop;
	REAL	Vstep;
	REAL	Delay;
	REAL	Hold;
	INTEGER	pins[2];

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__trm = TPLLASTTRM(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Vstart, _TYPER, 0, 0);
	TPLINITMEM(&Vstop, _TYPER, 0, 0);
	TPLINITMEM(&Vstep, _TYPER, 0, 0);
	TPLINITMEM(&Delay, _TYPER, 0, 0);
	TPLINITMEM(&Hold, _TYPER, 0, 0);
	TPLINITMEM(&pins, _TYPEI, 2, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Vstart);
	TPLGETLASTINVAR(__in, 1, &Vstop);
	TPLGETLASTINVAR(__in, 2, &Vstep);
	TPLGETLASTINVAR(__in, 3, &Delay);
	TPLGETLASTINVAR(__in, 4, &Hold);
	TPLGETLASTTRMVAR(__trm, 0, &pins[0]);
	TPLGETLASTTRMVAR(__trm, 1, &pins[1]);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	G_CV(Vstart,Vstop,Vstep,Delay,Hold,pins);

	/* Algorithm output variable setting */
}
