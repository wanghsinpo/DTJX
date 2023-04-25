#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_GET_MODLABEL(void *_alg)
{
}

void
__GET_MODLABEL(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_out;

	/* Local input/output variable definition */
	STRING	Label;

	/* Data pointer initialization */
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Label, _TYPES, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Label);

	/* Algorithm invocation */
	GET_MODLABEL(&Label);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Label);
}
