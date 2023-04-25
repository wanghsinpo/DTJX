#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_SET_JDG_DIE_TYP(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;

	/* Local input/output variable definition */
	INTEGER	Typeindex;
	INTEGER	Judge;
	INTEGER	Offsetx;
	INTEGER	Offsety;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Typeindex, _TYPEI, 0, 0);
	TPLINITMEM(&Judge, _TYPEI, 0, 0);
	TPLINITMEM(&Offsetx, _TYPEI, 0, 0);
	TPLINITMEM(&Offsety, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Typeindex);
	TPLGETEXECINVAR(_in, 1, &Judge);
	TPLGETEXECINVAR(_in, 2, &Offsetx);
	TPLGETEXECINVAR(_in, 3, &Offsety);
	TPLPUTLASTINVAR(__in, 0, &Typeindex);
	TPLPUTLASTINVAR(__in, 1, &Judge);
	TPLPUTLASTINVAR(__in, 2, &Offsetx);
	TPLPUTLASTINVAR(__in, 3, &Offsety);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	SET_JDG_DIE_TYP(Typeindex,Judge,Offsetx,Offsety);

	/* Algorithm output variable setting */
}

void
__SET_JDG_DIE_TYP(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;

	/* Local input/output variable definition */
	INTEGER	Typeindex;
	INTEGER	Judge;
	INTEGER	Offsetx;
	INTEGER	Offsety;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Typeindex, _TYPEI, 0, 0);
	TPLINITMEM(&Judge, _TYPEI, 0, 0);
	TPLINITMEM(&Offsetx, _TYPEI, 0, 0);
	TPLINITMEM(&Offsety, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Typeindex);
	TPLGETLASTINVAR(__in, 1, &Judge);
	TPLGETLASTINVAR(__in, 2, &Offsetx);
	TPLGETLASTINVAR(__in, 3, &Offsety);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	SET_JDG_DIE_TYP(Typeindex,Judge,Offsetx,Offsety);

	/* Algorithm output variable setting */
}
