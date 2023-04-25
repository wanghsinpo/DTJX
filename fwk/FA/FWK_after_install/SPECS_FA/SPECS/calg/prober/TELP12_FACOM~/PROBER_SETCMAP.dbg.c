#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_PROBER_SETCMAP(void *_alg)
{
}

void
__PROBER_SETCMAP(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Cassno;
	INTEGER	SlotStat[50];
	STRING	Status;
	STRING	Error;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Cassno, _TYPES, 0, 0);
	TPLINITMEM(&SlotStat, _TYPEI, 50, 0);
	TPLINITMEM(&Status, _TYPES, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Cassno);
	TPLGETDEBUGINVAR(_in, 1, &SlotStat);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);
	TPLGETDEBUGOUTVAR(_out, 1, &Error);

	/* Algorithm invocation */
	PROBER_SETCMAP(Cassno,SlotStat,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
	TPLPUTDEBUGOUTVAR(_out, 1, &Error);
}
