#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_CHECK_TIME(void *_alg)
{
}

void
__CHECK_TIME(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_out;

	/* Local input/output variable definition */
	REAL	Time;

	/* Data pointer initialization */
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Time, _TYPER, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Time);

	/* Algorithm invocation */
	CHECK_TIME(&Time);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Time);
}
