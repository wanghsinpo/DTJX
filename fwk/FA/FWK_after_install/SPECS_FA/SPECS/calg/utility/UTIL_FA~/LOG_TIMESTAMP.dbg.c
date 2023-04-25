#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_LOG_TIMESTAMP(void *_alg)
{
}

void
__LOG_TIMESTAMP(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_out;

	/* Local input/output variable definition */
	STRING	Timestamp;

	/* Data pointer initialization */
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Timestamp, _TYPES, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Timestamp);

	/* Algorithm invocation */
	LOG_TIMESTAMP(&Timestamp);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Timestamp);
}
