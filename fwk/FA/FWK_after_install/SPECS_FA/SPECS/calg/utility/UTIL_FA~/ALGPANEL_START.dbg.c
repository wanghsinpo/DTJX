#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_ALGPANEL_START(void *_alg)
{
}

void
__ALGPANEL_START(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;

	/* Local input/output variable definition */
	INTEGER	Mode;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Mode, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Mode);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	ALGPANEL_START(Mode);

	/* Algorithm output variable setting */
}
