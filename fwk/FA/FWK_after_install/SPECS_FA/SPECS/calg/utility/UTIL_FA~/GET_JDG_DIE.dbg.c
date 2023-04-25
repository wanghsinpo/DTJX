#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_GET_JDG_DIE(void *_alg)
{
}

void
__GET_JDG_DIE(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Typeindex;
	INTEGER	Dieindex;
	INTEGER	Judge;
	INTEGER	Offsetx;
	INTEGER	Offsety;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Typeindex, _TYPEI, 0, 0);
	TPLINITMEM(&Dieindex, _TYPEI, 0, 0);
	TPLINITMEM(&Judge, _TYPEI, 0, 0);
	TPLINITMEM(&Offsetx, _TYPEI, 0, 0);
	TPLINITMEM(&Offsety, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Typeindex);
	TPLGETDEBUGINVAR(_in, 1, &Dieindex);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Judge);
	TPLGETDEBUGOUTVAR(_out, 1, &Offsetx);
	TPLGETDEBUGOUTVAR(_out, 2, &Offsety);

	/* Algorithm invocation */
	GET_JDG_DIE(Typeindex,Dieindex,&Judge,&Offsetx,&Offsety);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Judge);
	TPLPUTDEBUGOUTVAR(_out, 1, &Offsetx);
	TPLPUTDEBUGOUTVAR(_out, 2, &Offsety);
}
