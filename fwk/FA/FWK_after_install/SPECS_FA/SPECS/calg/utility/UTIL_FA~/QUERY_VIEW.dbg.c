#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_QUERY_VIEW(void *_alg)
{
}

void
__QUERY_VIEW(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;

	/* Local input/output variable definition */
	STRING	Variable;
	INTEGER	Update;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Variable, _TYPES, 0, 0);
	TPLINITMEM(&Update, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Variable);
	TPLGETDEBUGINVAR(_in, 1, &Update);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	QUERY_VIEW(Variable,Update);

	/* Algorithm output variable setting */
}
