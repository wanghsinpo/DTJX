#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_LOG_WAFER_END(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;

	/* Local input/output variable definition */
	STRING	Session;
	STRING	State;
	INTEGER	Result;
	STRING	Time;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&State, _TYPES, 0, 0);
	TPLINITMEM(&Result, _TYPEI, 0, 0);
	TPLINITMEM(&Time, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Session);
	TPLGETEXECINVAR(_in, 1, &State);
	TPLGETEXECINVAR(_in, 2, &Result);
	TPLGETEXECINVAR(_in, 3, &Time);
	TPLPUTLASTINVAR(__in, 0, &Session);
	TPLPUTLASTINVAR(__in, 1, &State);
	TPLPUTLASTINVAR(__in, 2, &Result);
	TPLPUTLASTINVAR(__in, 3, &Time);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	LOG_WAFER_END(Session,State,Result,Time);

	/* Algorithm output variable setting */
}

void
__LOG_WAFER_END(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;

	/* Local input/output variable definition */
	STRING	Session;
	STRING	State;
	INTEGER	Result;
	STRING	Time;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&State, _TYPES, 0, 0);
	TPLINITMEM(&Result, _TYPEI, 0, 0);
	TPLINITMEM(&Time, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Session);
	TPLGETLASTINVAR(__in, 1, &State);
	TPLGETLASTINVAR(__in, 2, &Result);
	TPLGETLASTINVAR(__in, 3, &Time);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	LOG_WAFER_END(Session,State,Result,Time);

	/* Algorithm output variable setting */
}
