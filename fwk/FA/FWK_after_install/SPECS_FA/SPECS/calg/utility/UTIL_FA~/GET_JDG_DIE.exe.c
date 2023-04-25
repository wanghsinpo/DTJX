#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_GET_JDG_DIE(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Typeindex;
	INTEGER	Dieindex;
	INTEGER	Judge;
	INTEGER	Offsetx;
	INTEGER	Offsety;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Typeindex, _TYPEI, 0, 0);
	TPLINITMEM(&Dieindex, _TYPEI, 0, 0);
	TPLINITMEM(&Judge, _TYPEI, 0, 0);
	TPLINITMEM(&Offsetx, _TYPEI, 0, 0);
	TPLINITMEM(&Offsety, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Typeindex);
	TPLGETEXECINVAR(_in, 1, &Dieindex);
	TPLPUTLASTINVAR(__in, 0, &Typeindex);
	TPLPUTLASTINVAR(__in, 1, &Dieindex);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Judge);
	TPLGETEXECOUTVAR(_out, 1, &Offsetx);
	TPLGETEXECOUTVAR(_out, 2, &Offsety);
	TPLPUTLASTOUTVAR(__out, 0, &Judge);
	TPLPUTLASTOUTVAR(__out, 1, &Offsetx);
	TPLPUTLASTOUTVAR(__out, 2, &Offsety);

	/* Algorithm invocation */
	GET_JDG_DIE(Typeindex,Dieindex,&Judge,&Offsetx,&Offsety);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Judge);
	TPLPUTEXECOUTVAR(_out, 1, &Offsetx);
	TPLPUTEXECOUTVAR(_out, 2, &Offsety);
	TPLPUTLASTOUTVAR(__out, 0, &Judge);
	TPLPUTLASTOUTVAR(__out, 1, &Offsetx);
	TPLPUTLASTOUTVAR(__out, 2, &Offsety);
}

void
__GET_JDG_DIE(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Typeindex;
	INTEGER	Dieindex;
	INTEGER	Judge;
	INTEGER	Offsetx;
	INTEGER	Offsety;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Typeindex, _TYPEI, 0, 0);
	TPLINITMEM(&Dieindex, _TYPEI, 0, 0);
	TPLINITMEM(&Judge, _TYPEI, 0, 0);
	TPLINITMEM(&Offsetx, _TYPEI, 0, 0);
	TPLINITMEM(&Offsety, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Typeindex);
	TPLGETLASTINVAR(__in, 1, &Dieindex);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Judge);
	TPLGETLASTOUTVAR(__out, 1, &Offsetx);
	TPLGETLASTOUTVAR(__out, 2, &Offsety);

	/* Algorithm invocation */
	GET_JDG_DIE(Typeindex,Dieindex,&Judge,&Offsetx,&Offsety);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Judge);
	TPLPUTLASTOUTVAR(__out, 1, &Offsetx);
	TPLPUTLASTOUTVAR(__out, 2, &Offsety);
}
