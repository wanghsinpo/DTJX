#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_G_HFE(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_trm, *__trm;

	/* Local input/output variable definition */
	REAL	Ibestart;
	REAL	Ibestop;
	INTEGER	Ibestep;
	REAL	Vce;
	INTEGER	pins[3];

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_trm = TPLEXECTRM(_alg);
	__trm = TPLLASTTRM(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Ibestart, _TYPER, 0, 0);
	TPLINITMEM(&Ibestop, _TYPER, 0, 0);
	TPLINITMEM(&Ibestep, _TYPEI, 0, 0);
	TPLINITMEM(&Vce, _TYPER, 0, 0);
	TPLINITMEM(&pins, _TYPEI, 3, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Ibestart);
	TPLGETEXECINVAR(_in, 1, &Ibestop);
	TPLGETEXECINVAR(_in, 2, &Ibestep);
	TPLGETEXECINVAR(_in, 3, &Vce);
	TPLPUTLASTINVAR(__in, 0, &Ibestart);
	TPLPUTLASTINVAR(__in, 1, &Ibestop);
	TPLPUTLASTINVAR(__in, 2, &Ibestep);
	TPLPUTLASTINVAR(__in, 3, &Vce);
	TPLGETEXECTRMVAR(_trm, 0, &pins[0]);
	TPLGETEXECTRMVAR(_trm, 1, &pins[1]);
	TPLGETEXECTRMVAR(_trm, 2, &pins[2]);
	TPLPUTLASTTRMVAR(__trm, 0, &pins[0]);
	TPLPUTLASTTRMVAR(__trm, 1, &pins[1]);
	TPLPUTLASTTRMVAR(__trm, 2, &pins[2]);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	G_HFE(Ibestart,Ibestop,Ibestep,Vce,pins);

	/* Algorithm output variable setting */
}

void
__G_HFE(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__trm;

	/* Local input/output variable definition */
	REAL	Ibestart;
	REAL	Ibestop;
	INTEGER	Ibestep;
	REAL	Vce;
	INTEGER	pins[3];

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__trm = TPLLASTTRM(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Ibestart, _TYPER, 0, 0);
	TPLINITMEM(&Ibestop, _TYPER, 0, 0);
	TPLINITMEM(&Ibestep, _TYPEI, 0, 0);
	TPLINITMEM(&Vce, _TYPER, 0, 0);
	TPLINITMEM(&pins, _TYPEI, 3, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Ibestart);
	TPLGETLASTINVAR(__in, 1, &Ibestop);
	TPLGETLASTINVAR(__in, 2, &Ibestep);
	TPLGETLASTINVAR(__in, 3, &Vce);
	TPLGETLASTTRMVAR(__trm, 0, &pins[0]);
	TPLGETLASTTRMVAR(__trm, 1, &pins[1]);
	TPLGETLASTTRMVAR(__trm, 2, &pins[2]);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	G_HFE(Ibestart,Ibestop,Ibestep,Vce,pins);

	/* Algorithm output variable setting */
}
