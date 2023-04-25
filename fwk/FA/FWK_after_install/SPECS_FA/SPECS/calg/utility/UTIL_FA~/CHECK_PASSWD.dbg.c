#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_CHECK_PASSWD(void *_alg)
{
}

void
__CHECK_PASSWD(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Name;
	STRING	Command;
	INTEGER	Result;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Name, _TYPES, 0, 0);
	TPLINITMEM(&Command, _TYPES, 0, 0);
	TPLINITMEM(&Result, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Name);
	TPLGETDEBUGINVAR(_in, 1, &Command);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Result);

	/* Algorithm invocation */
	CHECK_PASSWD(Name,Command,&Result);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Result);
}
