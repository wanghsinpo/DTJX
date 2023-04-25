#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_QUERY_GRAPH(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;

	/* Local input/output variable definition */
	INTEGER	Filter;
	INTEGER	Type;
	INTEGER	Unit;
	STRING	Variable;
	INTEGER	Update;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Filter, _TYPEI, 0, 0);
	TPLINITMEM(&Type, _TYPEI, 0, 0);
	TPLINITMEM(&Unit, _TYPEI, 0, 0);
	TPLINITMEM(&Variable, _TYPES, 0, 0);
	TPLINITMEM(&Update, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Filter);
	TPLGETEXECINVAR(_in, 1, &Type);
	TPLGETEXECINVAR(_in, 2, &Unit);
	TPLGETEXECINVAR(_in, 3, &Variable);
	TPLGETEXECINVAR(_in, 4, &Update);
	TPLPUTLASTINVAR(__in, 0, &Filter);
	TPLPUTLASTINVAR(__in, 1, &Type);
	TPLPUTLASTINVAR(__in, 2, &Unit);
	TPLPUTLASTINVAR(__in, 3, &Variable);
	TPLPUTLASTINVAR(__in, 4, &Update);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	QUERY_GRAPH(Filter,Type,Unit,Variable,Update);

	/* Algorithm output variable setting */
}

void
__QUERY_GRAPH(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;

	/* Local input/output variable definition */
	INTEGER	Filter;
	INTEGER	Type;
	INTEGER	Unit;
	STRING	Variable;
	INTEGER	Update;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Filter, _TYPEI, 0, 0);
	TPLINITMEM(&Type, _TYPEI, 0, 0);
	TPLINITMEM(&Unit, _TYPEI, 0, 0);
	TPLINITMEM(&Variable, _TYPES, 0, 0);
	TPLINITMEM(&Update, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Filter);
	TPLGETLASTINVAR(__in, 1, &Type);
	TPLGETLASTINVAR(__in, 2, &Unit);
	TPLGETLASTINVAR(__in, 3, &Variable);
	TPLGETLASTINVAR(__in, 4, &Update);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	QUERY_GRAPH(Filter,Type,Unit,Variable,Update);

	/* Algorithm output variable setting */
}
