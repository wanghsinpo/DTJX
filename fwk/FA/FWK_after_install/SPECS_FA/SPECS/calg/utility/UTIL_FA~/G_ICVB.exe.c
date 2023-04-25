#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_G_ICVB(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_trm, *__trm;

	/* Local input/output variable definition */
	REAL	Vbestart;
	REAL	Vbestop;
	REAL	Vbestep;
	INTEGER	pins[3];

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_trm = TPLEXECTRM(_alg);
	__trm = TPLLASTTRM(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Vbestart, _TYPER, 0, 0);
	TPLINITMEM(&Vbestop, _TYPER, 0, 0);
	TPLINITMEM(&Vbestep, _TYPER, 0, 0);
	TPLINITMEM(&pins, _TYPEI, 3, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Vbestart);
	TPLGETEXECINVAR(_in, 1, &Vbestop);
	TPLGETEXECINVAR(_in, 2, &Vbestep);
	TPLPUTLASTINVAR(__in, 0, &Vbestart);
	TPLPUTLASTINVAR(__in, 1, &Vbestop);
	TPLPUTLASTINVAR(__in, 2, &Vbestep);
	TPLGETEXECTRMVAR(_trm, 0, &pins[0]);
	TPLGETEXECTRMVAR(_trm, 1, &pins[1]);
	TPLGETEXECTRMVAR(_trm, 2, &pins[2]);
	TPLPUTLASTTRMVAR(__trm, 0, &pins[0]);
	TPLPUTLASTTRMVAR(__trm, 1, &pins[1]);
	TPLPUTLASTTRMVAR(__trm, 2, &pins[2]);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	G_ICVB(Vbestart,Vbestop,Vbestep,pins);

	/* Algorithm output variable setting */
}

void
__G_ICVB(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__trm;

	/* Local input/output variable definition */
	REAL	Vbestart;
	REAL	Vbestop;
	REAL	Vbestep;
	INTEGER	pins[3];

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__trm = TPLLASTTRM(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Vbestart, _TYPER, 0, 0);
	TPLINITMEM(&Vbestop, _TYPER, 0, 0);
	TPLINITMEM(&Vbestep, _TYPER, 0, 0);
	TPLINITMEM(&pins, _TYPEI, 3, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Vbestart);
	TPLGETLASTINVAR(__in, 1, &Vbestop);
	TPLGETLASTINVAR(__in, 2, &Vbestep);
	TPLGETLASTTRMVAR(__trm, 0, &pins[0]);
	TPLGETLASTTRMVAR(__trm, 1, &pins[1]);
	TPLGETLASTTRMVAR(__trm, 2, &pins[2]);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	G_ICVB(Vbestart,Vbestop,Vbestep,pins);

	/* Algorithm output variable setting */
}
