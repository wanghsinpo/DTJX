#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_GET_BRK_MOD(void *_alg)
{
}

void
__GET_BRK_MOD(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Typeindex;
	INTEGER	Dieindex;
	INTEGER	Modindex;
	INTEGER	Break;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Typeindex, _TYPEI, 0, 0);
	TPLINITMEM(&Dieindex, _TYPEI, 0, 0);
	TPLINITMEM(&Modindex, _TYPEI, 0, 0);
	TPLINITMEM(&Break, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Typeindex);
	TPLGETDEBUGINVAR(_in, 1, &Dieindex);
	TPLGETDEBUGINVAR(_in, 2, &Modindex);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Break);

	/* Algorithm invocation */
	GET_BRK_MOD(Typeindex,Dieindex,Modindex,&Break);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Break);
}
