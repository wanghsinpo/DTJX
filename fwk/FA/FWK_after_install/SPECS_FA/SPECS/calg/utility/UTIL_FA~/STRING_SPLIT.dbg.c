#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_STRING_SPLIT(void *_alg)
{
}

void
__STRING_SPLIT(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Src;
	STRING	Del;
	STRING	Elem[128];
	INTEGER	Count;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Src, _TYPES, 0, 0);
	TPLINITMEM(&Del, _TYPES, 0, 0);
	TPLINITMEM(&Elem, _TYPES, 128, 0);
	TPLINITMEM(&Count, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Src);
	TPLGETDEBUGINVAR(_in, 1, &Del);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Elem);
	TPLGETDEBUGOUTVAR(_out, 1, &Count);

	/* Algorithm invocation */
	STRING_SPLIT(Src,Del,&Elem,&Count);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Elem);
	TPLPUTDEBUGOUTVAR(_out, 1, &Count);
}
