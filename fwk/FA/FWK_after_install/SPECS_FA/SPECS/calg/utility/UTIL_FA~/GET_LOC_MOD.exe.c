#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_GET_LOC_MOD(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Typeindex;
	STRING	Modname;
	REAL	X;
	REAL	Y;
	INTEGER	Stat;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Typeindex, _TYPEI, 0, 0);
	TPLINITMEM(&Modname, _TYPES, 0, 0);
	TPLINITMEM(&X, _TYPER, 0, 0);
	TPLINITMEM(&Y, _TYPER, 0, 0);
	TPLINITMEM(&Stat, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Typeindex);
	TPLGETEXECINVAR(_in, 1, &Modname);
	TPLPUTLASTINVAR(__in, 0, &Typeindex);
	TPLPUTLASTINVAR(__in, 1, &Modname);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &X);
	TPLGETEXECOUTVAR(_out, 1, &Y);
	TPLGETEXECOUTVAR(_out, 2, &Stat);
	TPLPUTLASTOUTVAR(__out, 0, &X);
	TPLPUTLASTOUTVAR(__out, 1, &Y);
	TPLPUTLASTOUTVAR(__out, 2, &Stat);

	/* Algorithm invocation */
	GET_LOC_MOD(Typeindex,Modname,&X,&Y,&Stat);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &X);
	TPLPUTEXECOUTVAR(_out, 1, &Y);
	TPLPUTEXECOUTVAR(_out, 2, &Stat);
	TPLPUTLASTOUTVAR(__out, 0, &X);
	TPLPUTLASTOUTVAR(__out, 1, &Y);
	TPLPUTLASTOUTVAR(__out, 2, &Stat);
}

void
__GET_LOC_MOD(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Typeindex;
	STRING	Modname;
	REAL	X;
	REAL	Y;
	INTEGER	Stat;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Typeindex, _TYPEI, 0, 0);
	TPLINITMEM(&Modname, _TYPES, 0, 0);
	TPLINITMEM(&X, _TYPER, 0, 0);
	TPLINITMEM(&Y, _TYPER, 0, 0);
	TPLINITMEM(&Stat, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Typeindex);
	TPLGETLASTINVAR(__in, 1, &Modname);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &X);
	TPLGETLASTOUTVAR(__out, 1, &Y);
	TPLGETLASTOUTVAR(__out, 2, &Stat);

	/* Algorithm invocation */
	GET_LOC_MOD(Typeindex,Modname,&X,&Y,&Stat);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &X);
	TPLPUTLASTOUTVAR(__out, 1, &Y);
	TPLPUTLASTOUTVAR(__out, 2, &Stat);
}
