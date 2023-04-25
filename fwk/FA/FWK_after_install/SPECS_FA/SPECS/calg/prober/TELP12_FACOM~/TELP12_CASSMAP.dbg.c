#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_TELP12_CASSMAP(void *_alg)
{
}

void
__TELP12_CASSMAP(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Cassmap[50];
	STRING	Status;
	STRING	Error;

	/* Data pointer initialization */
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Cassmap, _TYPEI, 50, 0);
	TPLINITMEM(&Status, _TYPES, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Cassmap);
	TPLGETDEBUGOUTVAR(_out, 1, &Status);
	TPLGETDEBUGOUTVAR(_out, 2, &Error);

	/* Algorithm invocation */
	TELP12_CASSMAP(&Cassmap,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Cassmap);
	TPLPUTDEBUGOUTVAR(_out, 1, &Status);
	TPLPUTDEBUGOUTVAR(_out, 2, &Error);
}
