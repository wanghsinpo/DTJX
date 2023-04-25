#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_GET_NEXT_MOD(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Typeindex_c;
	INTEGER	Diex_c;
	INTEGER	Diey_c;
	STRING	Modname_c;
	INTEGER	Typeindex;
	INTEGER	Diex;
	INTEGER	Diey;
	STRING	Modname;
	INTEGER	Stat;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Typeindex_c, _TYPEI, 0, 0);
	TPLINITMEM(&Diex_c, _TYPEI, 0, 0);
	TPLINITMEM(&Diey_c, _TYPEI, 0, 0);
	TPLINITMEM(&Modname_c, _TYPES, 0, 0);
	TPLINITMEM(&Typeindex, _TYPEI, 0, 0);
	TPLINITMEM(&Diex, _TYPEI, 0, 0);
	TPLINITMEM(&Diey, _TYPEI, 0, 0);
	TPLINITMEM(&Modname, _TYPES, 0, 0);
	TPLINITMEM(&Stat, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Typeindex_c);
	TPLGETEXECINVAR(_in, 1, &Diex_c);
	TPLGETEXECINVAR(_in, 2, &Diey_c);
	TPLGETEXECINVAR(_in, 3, &Modname_c);
	TPLPUTLASTINVAR(__in, 0, &Typeindex_c);
	TPLPUTLASTINVAR(__in, 1, &Diex_c);
	TPLPUTLASTINVAR(__in, 2, &Diey_c);
	TPLPUTLASTINVAR(__in, 3, &Modname_c);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Typeindex);
	TPLGETEXECOUTVAR(_out, 1, &Diex);
	TPLGETEXECOUTVAR(_out, 2, &Diey);
	TPLGETEXECOUTVAR(_out, 3, &Modname);
	TPLGETEXECOUTVAR(_out, 4, &Stat);
	TPLPUTLASTOUTVAR(__out, 0, &Typeindex);
	TPLPUTLASTOUTVAR(__out, 1, &Diex);
	TPLPUTLASTOUTVAR(__out, 2, &Diey);
	TPLPUTLASTOUTVAR(__out, 3, &Modname);
	TPLPUTLASTOUTVAR(__out, 4, &Stat);

	/* Algorithm invocation */
	GET_NEXT_MOD(Typeindex_c,Diex_c,Diey_c,Modname_c,&Typeindex,&Diex,&Diey,&Modname,&Stat);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Typeindex);
	TPLPUTEXECOUTVAR(_out, 1, &Diex);
	TPLPUTEXECOUTVAR(_out, 2, &Diey);
	TPLPUTEXECOUTVAR(_out, 3, &Modname);
	TPLPUTEXECOUTVAR(_out, 4, &Stat);
	TPLPUTLASTOUTVAR(__out, 0, &Typeindex);
	TPLPUTLASTOUTVAR(__out, 1, &Diex);
	TPLPUTLASTOUTVAR(__out, 2, &Diey);
	TPLPUTLASTOUTVAR(__out, 3, &Modname);
	TPLPUTLASTOUTVAR(__out, 4, &Stat);
}

void
__GET_NEXT_MOD(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Typeindex_c;
	INTEGER	Diex_c;
	INTEGER	Diey_c;
	STRING	Modname_c;
	INTEGER	Typeindex;
	INTEGER	Diex;
	INTEGER	Diey;
	STRING	Modname;
	INTEGER	Stat;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Typeindex_c, _TYPEI, 0, 0);
	TPLINITMEM(&Diex_c, _TYPEI, 0, 0);
	TPLINITMEM(&Diey_c, _TYPEI, 0, 0);
	TPLINITMEM(&Modname_c, _TYPES, 0, 0);
	TPLINITMEM(&Typeindex, _TYPEI, 0, 0);
	TPLINITMEM(&Diex, _TYPEI, 0, 0);
	TPLINITMEM(&Diey, _TYPEI, 0, 0);
	TPLINITMEM(&Modname, _TYPES, 0, 0);
	TPLINITMEM(&Stat, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Typeindex_c);
	TPLGETLASTINVAR(__in, 1, &Diex_c);
	TPLGETLASTINVAR(__in, 2, &Diey_c);
	TPLGETLASTINVAR(__in, 3, &Modname_c);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Typeindex);
	TPLGETLASTOUTVAR(__out, 1, &Diex);
	TPLGETLASTOUTVAR(__out, 2, &Diey);
	TPLGETLASTOUTVAR(__out, 3, &Modname);
	TPLGETLASTOUTVAR(__out, 4, &Stat);

	/* Algorithm invocation */
	GET_NEXT_MOD(Typeindex_c,Diex_c,Diey_c,Modname_c,&Typeindex,&Diex,&Diey,&Modname,&Stat);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Typeindex);
	TPLPUTLASTOUTVAR(__out, 1, &Diex);
	TPLPUTLASTOUTVAR(__out, 2, &Diey);
	TPLPUTLASTOUTVAR(__out, 3, &Modname);
	TPLPUTLASTOUTVAR(__out, 4, &Stat);
}
