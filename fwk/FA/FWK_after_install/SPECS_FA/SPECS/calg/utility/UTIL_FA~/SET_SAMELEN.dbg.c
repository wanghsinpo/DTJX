#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_SET_SAMELEN(void *_alg)
{
}

void
__SET_SAMELEN(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Original;
	STRING	Reference;
	STRING	Modified;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Original, _TYPES, 0, 0);
	TPLINITMEM(&Reference, _TYPES, 0, 0);
	TPLINITMEM(&Modified, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Original);
	TPLGETDEBUGINVAR(_in, 1, &Reference);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Modified);

	/* Algorithm invocation */
	SET_SAMELEN(Original,Reference,&Modified);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Modified);
}
