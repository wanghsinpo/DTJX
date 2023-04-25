#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_RCP_SYSCONF(void *_alg)
{
}

void
__RCP_SYSCONF(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Name;
	STRING	Value;
	INTEGER	Status;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Name, _TYPES, 0, 0);
	TPLINITMEM(&Value, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Name);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Value);
	TPLGETDEBUGOUTVAR(_out, 1, &Status);

	/* Algorithm invocation */
	RCP_SYSCONF(Name,&Value,&Status);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Value);
	TPLPUTDEBUGOUTVAR(_out, 1, &Status);
}
