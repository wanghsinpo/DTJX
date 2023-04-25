#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_LOG_LOT_BEGIN(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;

	/* Local input/output variable definition */
	STRING	Session;
	STRING	Lotid;
	STRING	Testplan;
	STRING	Algorithm;
	STRING	Limitfile;
	STRING	Operator;
	STRING	Date;
	STRING	Time;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Lotid, _TYPES, 0, 0);
	TPLINITMEM(&Testplan, _TYPES, 0, 0);
	TPLINITMEM(&Algorithm, _TYPES, 0, 0);
	TPLINITMEM(&Limitfile, _TYPES, 0, 0);
	TPLINITMEM(&Operator, _TYPES, 0, 0);
	TPLINITMEM(&Date, _TYPES, 0, 0);
	TPLINITMEM(&Time, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Session);
	TPLGETEXECINVAR(_in, 1, &Lotid);
	TPLGETEXECINVAR(_in, 2, &Testplan);
	TPLGETEXECINVAR(_in, 3, &Algorithm);
	TPLGETEXECINVAR(_in, 4, &Limitfile);
	TPLGETEXECINVAR(_in, 5, &Operator);
	TPLGETEXECINVAR(_in, 6, &Date);
	TPLGETEXECINVAR(_in, 7, &Time);
	TPLPUTLASTINVAR(__in, 0, &Session);
	TPLPUTLASTINVAR(__in, 1, &Lotid);
	TPLPUTLASTINVAR(__in, 2, &Testplan);
	TPLPUTLASTINVAR(__in, 3, &Algorithm);
	TPLPUTLASTINVAR(__in, 4, &Limitfile);
	TPLPUTLASTINVAR(__in, 5, &Operator);
	TPLPUTLASTINVAR(__in, 6, &Date);
	TPLPUTLASTINVAR(__in, 7, &Time);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	LOG_LOT_BEGIN(Session,Lotid,Testplan,Algorithm,Limitfile,Operator,Date,Time);

	/* Algorithm output variable setting */
}

void
__LOG_LOT_BEGIN(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;

	/* Local input/output variable definition */
	STRING	Session;
	STRING	Lotid;
	STRING	Testplan;
	STRING	Algorithm;
	STRING	Limitfile;
	STRING	Operator;
	STRING	Date;
	STRING	Time;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Lotid, _TYPES, 0, 0);
	TPLINITMEM(&Testplan, _TYPES, 0, 0);
	TPLINITMEM(&Algorithm, _TYPES, 0, 0);
	TPLINITMEM(&Limitfile, _TYPES, 0, 0);
	TPLINITMEM(&Operator, _TYPES, 0, 0);
	TPLINITMEM(&Date, _TYPES, 0, 0);
	TPLINITMEM(&Time, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Session);
	TPLGETLASTINVAR(__in, 1, &Lotid);
	TPLGETLASTINVAR(__in, 2, &Testplan);
	TPLGETLASTINVAR(__in, 3, &Algorithm);
	TPLGETLASTINVAR(__in, 4, &Limitfile);
	TPLGETLASTINVAR(__in, 5, &Operator);
	TPLGETLASTINVAR(__in, 6, &Date);
	TPLGETLASTINVAR(__in, 7, &Time);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	LOG_LOT_BEGIN(Session,Lotid,Testplan,Algorithm,Limitfile,Operator,Date,Time);

	/* Algorithm output variable setting */
}
