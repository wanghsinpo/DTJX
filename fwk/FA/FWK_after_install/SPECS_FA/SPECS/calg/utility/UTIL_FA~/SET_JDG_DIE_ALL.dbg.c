#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_SET_JDG_DIE_ALL(void *_alg)
{
}

void
__SET_JDG_DIE_ALL(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;

	/* Local input/output variable definition */
	INTEGER	Judge;
	INTEGER	Offsetx;
	INTEGER	Offsety;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Judge, _TYPEI, 0, 0);
	TPLINITMEM(&Offsetx, _TYPEI, 0, 0);
	TPLINITMEM(&Offsety, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Judge);
	TPLGETDEBUGINVAR(_in, 1, &Offsetx);
	TPLGETDEBUGINVAR(_in, 2, &Offsety);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	SET_JDG_DIE_ALL(Judge,Offsetx,Offsety);

	/* Algorithm output variable setting */
}
