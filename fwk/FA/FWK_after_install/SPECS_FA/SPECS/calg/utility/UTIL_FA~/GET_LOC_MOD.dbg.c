#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_GET_LOC_MOD(void *_alg)
{
}

void
__GET_LOC_MOD(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Typeindex;
	STRING	Modname;
	REAL	X;
	REAL	Y;
	INTEGER	Stat;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Typeindex, _TYPEI, 0, 0);
	TPLINITMEM(&Modname, _TYPES, 0, 0);
	TPLINITMEM(&X, _TYPER, 0, 0);
	TPLINITMEM(&Y, _TYPER, 0, 0);
	TPLINITMEM(&Stat, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Typeindex);
	TPLGETDEBUGINVAR(_in, 1, &Modname);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &X);
	TPLGETDEBUGOUTVAR(_out, 1, &Y);
	TPLGETDEBUGOUTVAR(_out, 2, &Stat);

	/* Algorithm invocation */
	GET_LOC_MOD(Typeindex,Modname,&X,&Y,&Stat);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &X);
	TPLPUTDEBUGOUTVAR(_out, 1, &Y);
	TPLPUTDEBUGOUTVAR(_out, 2, &Stat);
}
