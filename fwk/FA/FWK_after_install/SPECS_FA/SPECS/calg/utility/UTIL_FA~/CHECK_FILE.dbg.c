#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_CHECK_FILE(void *_alg)
{
}

void
__CHECK_FILE(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Testplan;
	STRING	Limit;
	INTEGER	Result;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Testplan, _TYPES, 0, 0);
	TPLINITMEM(&Limit, _TYPES, 0, 0);
	TPLINITMEM(&Result, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Testplan);
	TPLGETDEBUGINVAR(_in, 1, &Limit);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Result);

	/* Algorithm invocation */
	CHECK_FILE(Testplan,Limit,&Result);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Result);
}
