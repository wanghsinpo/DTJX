#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_SET_BRK_MOD(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;

	/* Local input/output variable definition */
	INTEGER	Typeindex;
	INTEGER	Dieindex;
	INTEGER	Modindex;
	INTEGER	Break;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Typeindex, _TYPEI, 0, 0);
	TPLINITMEM(&Dieindex, _TYPEI, 0, 0);
	TPLINITMEM(&Modindex, _TYPEI, 0, 0);
	TPLINITMEM(&Break, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Typeindex);
	TPLGETEXECINVAR(_in, 1, &Dieindex);
	TPLGETEXECINVAR(_in, 2, &Modindex);
	TPLGETEXECINVAR(_in, 3, &Break);
	TPLPUTLASTINVAR(__in, 0, &Typeindex);
	TPLPUTLASTINVAR(__in, 1, &Dieindex);
	TPLPUTLASTINVAR(__in, 2, &Modindex);
	TPLPUTLASTINVAR(__in, 3, &Break);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	SET_BRK_MOD(Typeindex,Dieindex,Modindex,Break);

	/* Algorithm output variable setting */
}

void
__SET_BRK_MOD(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;

	/* Local input/output variable definition */
	INTEGER	Typeindex;
	INTEGER	Dieindex;
	INTEGER	Modindex;
	INTEGER	Break;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Typeindex, _TYPEI, 0, 0);
	TPLINITMEM(&Dieindex, _TYPEI, 0, 0);
	TPLINITMEM(&Modindex, _TYPEI, 0, 0);
	TPLINITMEM(&Break, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Typeindex);
	TPLGETLASTINVAR(__in, 1, &Dieindex);
	TPLGETLASTINVAR(__in, 2, &Modindex);
	TPLGETLASTINVAR(__in, 3, &Break);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	SET_BRK_MOD(Typeindex,Dieindex,Modindex,Break);

	/* Algorithm output variable setting */
}
