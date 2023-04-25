#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_IS_CALG(void *_alg)
{
}

void
__IS_CALG(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Lang;

	/* Data pointer initialization */
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Lang, _TYPEI, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Lang);

	/* Algorithm invocation */
	IS_CALG(&Lang);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Lang);
}
