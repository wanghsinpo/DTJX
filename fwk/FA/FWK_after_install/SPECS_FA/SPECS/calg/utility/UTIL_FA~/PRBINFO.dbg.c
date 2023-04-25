#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_PRBINFO(void *_alg)
{
}

void
__PRBINFO(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Index;
	INTEGER	Pad;
	INTEGER	Pin;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Index, _TYPEI, 0, 0);
	TPLINITMEM(&Pad, _TYPEI, 0, 0);
	TPLINITMEM(&Pin, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Index);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Pad);
	TPLGETDEBUGOUTVAR(_out, 1, &Pin);

	/* Algorithm invocation */
	PRBINFO(Index,&Pad,&Pin);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Pad);
	TPLPUTDEBUGOUTVAR(_out, 1, &Pin);
}
