#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_STRING_LOOKUP(void *_alg)
{
}

void
__STRING_LOOKUP(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Src;
	STRING	Pat;
	INTEGER	Pos;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Src, _TYPES, 0, 0);
	TPLINITMEM(&Pat, _TYPES, 0, 0);
	TPLINITMEM(&Pos, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Src);
	TPLGETDEBUGINVAR(_in, 1, &Pat);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Pos);

	/* Algorithm invocation */
	STRING_LOOKUP(Src,Pat,&Pos);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Pos);
}
