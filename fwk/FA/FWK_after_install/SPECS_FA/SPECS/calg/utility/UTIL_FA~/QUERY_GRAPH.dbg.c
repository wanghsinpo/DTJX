#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_QUERY_GRAPH(void *_alg)
{
}

void
__QUERY_GRAPH(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;

	/* Local input/output variable definition */
	INTEGER	Filter;
	INTEGER	Type;
	INTEGER	Unit;
	STRING	Variable;
	INTEGER	Update;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Filter, _TYPEI, 0, 0);
	TPLINITMEM(&Type, _TYPEI, 0, 0);
	TPLINITMEM(&Unit, _TYPEI, 0, 0);
	TPLINITMEM(&Variable, _TYPES, 0, 0);
	TPLINITMEM(&Update, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Filter);
	TPLGETDEBUGINVAR(_in, 1, &Type);
	TPLGETDEBUGINVAR(_in, 2, &Unit);
	TPLGETDEBUGINVAR(_in, 3, &Variable);
	TPLGETDEBUGINVAR(_in, 4, &Update);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	QUERY_GRAPH(Filter,Type,Unit,Variable,Update);

	/* Algorithm output variable setting */
}
