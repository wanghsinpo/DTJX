#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_STRING_TIME(void *_alg)
{
}

void
__STRING_TIME(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	REAL	Time;
	STRING	Symbol;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Time, _TYPER, 0, 0);
	TPLINITMEM(&Symbol, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Time);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Symbol);

	/* Algorithm invocation */
	STRING_TIME(Time,&Symbol);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Symbol);
}
