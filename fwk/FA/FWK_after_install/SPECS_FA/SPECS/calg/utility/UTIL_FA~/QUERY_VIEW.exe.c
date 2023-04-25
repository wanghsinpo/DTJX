#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_QUERY_VIEW(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;

	/* Local input/output variable definition */
	STRING	Variable;
	INTEGER	Update;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Variable, _TYPES, 0, 0);
	TPLINITMEM(&Update, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Variable);
	TPLGETEXECINVAR(_in, 1, &Update);
	TPLPUTLASTINVAR(__in, 0, &Variable);
	TPLPUTLASTINVAR(__in, 1, &Update);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	QUERY_VIEW(Variable,Update);

	/* Algorithm output variable setting */
}

void
__QUERY_VIEW(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;

	/* Local input/output variable definition */
	STRING	Variable;
	INTEGER	Update;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Variable, _TYPES, 0, 0);
	TPLINITMEM(&Update, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Variable);
	TPLGETLASTINVAR(__in, 1, &Update);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	QUERY_VIEW(Variable,Update);

	/* Algorithm output variable setting */
}
