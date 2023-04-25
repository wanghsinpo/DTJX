#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_WAIT(void *_alg)
{
}

void
__WAIT(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;

	/* Local input/output variable definition */
	REAL	Wait;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Wait, _TYPER, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Wait);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	WAIT(Wait);

	/* Algorithm output variable setting */
}
