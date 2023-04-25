#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_ARRAY_LOOKUP2(void *_alg)
{
}

void
__ARRAY_LOOKUP2(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Src[256];
	STRING	Pat[256];
	INTEGER	Pos[256];

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Src, _TYPES, 256, 0);
	TPLINITMEM(&Pat, _TYPES, 256, 0);
	TPLINITMEM(&Pos, _TYPEI, 256, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Src);
	TPLGETDEBUGINVAR(_in, 1, &Pat);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Pos);

	/* Algorithm invocation */
	ARRAY_LOOKUP2(Src,Pat,&Pos);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Pos);
}
