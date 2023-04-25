#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_GET_SLOT_NO(void *_alg)
{
}

void
__GET_SLOT_NO(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Lotid;
	STRING	Waferid;
	INTEGER	Slotno;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Lotid, _TYPES, 0, 0);
	TPLINITMEM(&Waferid, _TYPES, 0, 0);
	TPLINITMEM(&Slotno, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Lotid);
	TPLGETDEBUGINVAR(_in, 1, &Waferid);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Slotno);

	/* Algorithm invocation */
	GET_SLOT_NO(Lotid,Waferid,&Slotno);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Slotno);
}
