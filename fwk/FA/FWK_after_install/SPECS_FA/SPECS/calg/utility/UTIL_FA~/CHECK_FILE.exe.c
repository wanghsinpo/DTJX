#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_CHECK_FILE(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Testplan;
	STRING	Limit;
	INTEGER	Result;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Testplan, _TYPES, 0, 0);
	TPLINITMEM(&Limit, _TYPES, 0, 0);
	TPLINITMEM(&Result, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Testplan);
	TPLGETEXECINVAR(_in, 1, &Limit);
	TPLPUTLASTINVAR(__in, 0, &Testplan);
	TPLPUTLASTINVAR(__in, 1, &Limit);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Result);
	TPLPUTLASTOUTVAR(__out, 0, &Result);

	/* Algorithm invocation */
	CHECK_FILE(Testplan,Limit,&Result);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Result);
	TPLPUTLASTOUTVAR(__out, 0, &Result);
}

void
__CHECK_FILE(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Testplan;
	STRING	Limit;
	INTEGER	Result;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Testplan, _TYPES, 0, 0);
	TPLINITMEM(&Limit, _TYPES, 0, 0);
	TPLINITMEM(&Result, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Testplan);
	TPLGETLASTINVAR(__in, 1, &Limit);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Result);

	/* Algorithm invocation */
	CHECK_FILE(Testplan,Limit,&Result);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Result);
}
