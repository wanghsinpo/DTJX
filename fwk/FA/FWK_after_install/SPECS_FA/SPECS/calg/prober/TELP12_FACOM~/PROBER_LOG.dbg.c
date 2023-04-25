#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_PROBER_LOG(void *_alg)
{
}

void
__PROBER_LOG(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Logmode;

	/* Data pointer initialization */
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Logmode, _TYPEI, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Logmode);

	/* Algorithm invocation */
	PROBER_LOG(&Logmode);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Logmode);
}
