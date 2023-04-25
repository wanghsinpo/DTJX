#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_SET_BRK_MOD(void *_alg)
{
}

void
__SET_BRK_MOD(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;

	/* Local input/output variable definition */
	INTEGER	Typeindex;
	INTEGER	Dieindex;
	INTEGER	Modindex;
	INTEGER	Break;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Typeindex, _TYPEI, 0, 0);
	TPLINITMEM(&Dieindex, _TYPEI, 0, 0);
	TPLINITMEM(&Modindex, _TYPEI, 0, 0);
	TPLINITMEM(&Break, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Typeindex);
	TPLGETDEBUGINVAR(_in, 1, &Dieindex);
	TPLGETDEBUGINVAR(_in, 2, &Modindex);
	TPLGETDEBUGINVAR(_in, 3, &Break);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	SET_BRK_MOD(Typeindex,Dieindex,Modindex,Break);

	/* Algorithm output variable setting */
}
