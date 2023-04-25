#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_RCP_DIETST(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Die[256];
	STRING	Tst[256];
	STRING	Rule;
	STRING	Die_tst[256];
	INTEGER	Status;
	STRING	Errmsg;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Die, _TYPES, 256, 0);
	TPLINITMEM(&Tst, _TYPES, 256, 0);
	TPLINITMEM(&Rule, _TYPES, 0, 0);
	TPLINITMEM(&Die_tst, _TYPES, 256, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Errmsg, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Die);
	TPLGETEXECINVAR(_in, 1, &Tst);
	TPLGETEXECINVAR(_in, 2, &Rule);
	TPLPUTLASTINVAR(__in, 0, &Die);
	TPLPUTLASTINVAR(__in, 1, &Tst);
	TPLPUTLASTINVAR(__in, 2, &Rule);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Die_tst);
	TPLGETEXECOUTVAR(_out, 1, &Status);
	TPLGETEXECOUTVAR(_out, 2, &Errmsg);
	TPLPUTLASTOUTVAR(__out, 0, &Die_tst);
	TPLPUTLASTOUTVAR(__out, 1, &Status);
	TPLPUTLASTOUTVAR(__out, 2, &Errmsg);

	/* Algorithm invocation */
	RCP_DIETST(Die,Tst,Rule,&Die_tst,&Status,&Errmsg);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Die_tst);
	TPLPUTEXECOUTVAR(_out, 1, &Status);
	TPLPUTEXECOUTVAR(_out, 2, &Errmsg);
	TPLPUTLASTOUTVAR(__out, 0, &Die_tst);
	TPLPUTLASTOUTVAR(__out, 1, &Status);
	TPLPUTLASTOUTVAR(__out, 2, &Errmsg);
}

void
__RCP_DIETST(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Die[256];
	STRING	Tst[256];
	STRING	Rule;
	STRING	Die_tst[256];
	INTEGER	Status;
	STRING	Errmsg;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Die, _TYPES, 256, 0);
	TPLINITMEM(&Tst, _TYPES, 256, 0);
	TPLINITMEM(&Rule, _TYPES, 0, 0);
	TPLINITMEM(&Die_tst, _TYPES, 256, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Errmsg, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Die);
	TPLGETLASTINVAR(__in, 1, &Tst);
	TPLGETLASTINVAR(__in, 2, &Rule);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Die_tst);
	TPLGETLASTOUTVAR(__out, 1, &Status);
	TPLGETLASTOUTVAR(__out, 2, &Errmsg);

	/* Algorithm invocation */
	RCP_DIETST(Die,Tst,Rule,&Die_tst,&Status,&Errmsg);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Die_tst);
	TPLPUTLASTOUTVAR(__out, 1, &Status);
	TPLPUTLASTOUTVAR(__out, 2, &Errmsg);
}
