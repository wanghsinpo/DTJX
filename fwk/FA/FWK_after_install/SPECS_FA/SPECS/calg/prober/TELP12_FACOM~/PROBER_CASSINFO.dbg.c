#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_PROBER_CASSINFO(void *_alg)
{
}

void
__PROBER_CASSINFO(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Slotno;
	INTEGER	Cassno;
	INTEGER	Wafcount;
	INTEGER	Casscount;
	STRING	Status;
	STRING	Error;

	/* Data pointer initialization */
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Slotno, _TYPEI, 0, 0);
	TPLINITMEM(&Cassno, _TYPEI, 0, 0);
	TPLINITMEM(&Wafcount, _TYPEI, 0, 0);
	TPLINITMEM(&Casscount, _TYPEI, 0, 0);
	TPLINITMEM(&Status, _TYPES, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Slotno);
	TPLGETDEBUGOUTVAR(_out, 1, &Cassno);
	TPLGETDEBUGOUTVAR(_out, 2, &Wafcount);
	TPLGETDEBUGOUTVAR(_out, 3, &Casscount);
	TPLGETDEBUGOUTVAR(_out, 4, &Status);
	TPLGETDEBUGOUTVAR(_out, 5, &Error);

	/* Algorithm invocation */
	PROBER_CASSINFO(&Slotno,&Cassno,&Wafcount,&Casscount,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Slotno);
	TPLPUTDEBUGOUTVAR(_out, 1, &Cassno);
	TPLPUTDEBUGOUTVAR(_out, 2, &Wafcount);
	TPLPUTDEBUGOUTVAR(_out, 3, &Casscount);
	TPLPUTDEBUGOUTVAR(_out, 4, &Status);
	TPLPUTDEBUGOUTVAR(_out, 5, &Error);
}
