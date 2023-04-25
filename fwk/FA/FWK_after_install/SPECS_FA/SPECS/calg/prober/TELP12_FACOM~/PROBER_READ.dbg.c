#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_PROBER_READ(void *_alg)
{
}

void
__PROBER_READ(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_out;

	/* Local input/output variable definition */
	STRING	Ent_val;
	STRING	Status;
	STRING	Error;

	/* Data pointer initialization */
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Ent_val, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPES, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Ent_val);
	TPLGETDEBUGOUTVAR(_out, 1, &Status);
	TPLGETDEBUGOUTVAR(_out, 2, &Error);

	/* Algorithm invocation */
	PROBER_READ(&Ent_val,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Ent_val);
	TPLPUTDEBUGOUTVAR(_out, 1, &Status);
	TPLPUTDEBUGOUTVAR(_out, 2, &Error);
}
