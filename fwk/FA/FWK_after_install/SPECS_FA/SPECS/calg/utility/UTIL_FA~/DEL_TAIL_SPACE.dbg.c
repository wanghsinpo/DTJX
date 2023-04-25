#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_DEL_TAIL_SPACE(void *_alg)
{
}

void
__DEL_TAIL_SPACE(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Original;
	STRING	Modified;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Original, _TYPES, 0, 0);
	TPLINITMEM(&Modified, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Original);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Modified);

	/* Algorithm invocation */
	DEL_TAIL_SPACE(Original,&Modified);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Modified);
}
