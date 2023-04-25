#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_LOG_PROBER(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;

	/* Local input/output variable definition */
	STRING	Session;
	STRING	Message;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Message, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Session);
	TPLGETEXECINVAR(_in, 1, &Message);
	TPLPUTLASTINVAR(__in, 0, &Session);
	TPLPUTLASTINVAR(__in, 1, &Message);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	LOG_PROBER(Session,Message);

	/* Algorithm output variable setting */
}

void
__LOG_PROBER(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;

	/* Local input/output variable definition */
	STRING	Session;
	STRING	Message;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Message, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Session);
	TPLGETLASTINVAR(__in, 1, &Message);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	LOG_PROBER(Session,Message);

	/* Algorithm output variable setting */
}
