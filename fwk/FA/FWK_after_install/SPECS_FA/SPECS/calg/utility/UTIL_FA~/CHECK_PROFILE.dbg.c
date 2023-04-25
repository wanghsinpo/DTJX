#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_CHECK_PROFILE(void *_alg)
{
}

void
__CHECK_PROFILE(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Result;

	/* Data pointer initialization */
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Result, _TYPEI, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Result);

	/* Algorithm invocation */
	CHECK_PROFILE(&Result);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Result);
}
