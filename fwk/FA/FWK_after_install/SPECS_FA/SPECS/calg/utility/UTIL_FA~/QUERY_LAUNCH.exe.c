#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_QUERY_LAUNCH(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;

	/* Local input/output variable definition */
	STRING	Session;
	STRING	Port;
	STRING	Project;
	STRING	Hostname;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Port, _TYPES, 0, 0);
	TPLINITMEM(&Project, _TYPES, 0, 0);
	TPLINITMEM(&Hostname, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Session);
	TPLGETEXECINVAR(_in, 1, &Port);
	TPLGETEXECINVAR(_in, 2, &Project);
	TPLGETEXECINVAR(_in, 3, &Hostname);
	TPLPUTLASTINVAR(__in, 0, &Session);
	TPLPUTLASTINVAR(__in, 1, &Port);
	TPLPUTLASTINVAR(__in, 2, &Project);
	TPLPUTLASTINVAR(__in, 3, &Hostname);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	QUERY_LAUNCH(Session,Port,Project,Hostname);

	/* Algorithm output variable setting */
}

void
__QUERY_LAUNCH(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;

	/* Local input/output variable definition */
	STRING	Session;
	STRING	Port;
	STRING	Project;
	STRING	Hostname;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Port, _TYPES, 0, 0);
	TPLINITMEM(&Project, _TYPES, 0, 0);
	TPLINITMEM(&Hostname, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Session);
	TPLGETLASTINVAR(__in, 1, &Port);
	TPLGETLASTINVAR(__in, 2, &Project);
	TPLGETLASTINVAR(__in, 3, &Hostname);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	QUERY_LAUNCH(Session,Port,Project,Hostname);

	/* Algorithm output variable setting */
}
