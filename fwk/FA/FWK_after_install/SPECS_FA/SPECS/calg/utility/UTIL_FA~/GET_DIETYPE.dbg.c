#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_GET_DIETYPE(void *_alg)
{
}

void
__GET_DIETYPE(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_out;

	/* Local input/output variable definition */
	STRING	Type;

	/* Data pointer initialization */
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Type, _TYPES, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Type);

	/* Algorithm invocation */
	GET_DIETYPE(&Type);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Type);
}
