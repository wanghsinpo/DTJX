#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_PROBER_FLATCOMP(void *_alg)
{
}

void
__PROBER_FLATCOMP(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Tpl_OriFla;
	INTEGER	Prb_OriFla;
	STRING	Status;
	STRING	Error;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Tpl_OriFla, _TYPEI, 0, 0);
	TPLINITMEM(&Prb_OriFla, _TYPEI, 0, 0);
	TPLINITMEM(&Status, _TYPES, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Tpl_OriFla);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Prb_OriFla);
	TPLGETDEBUGOUTVAR(_out, 1, &Status);
	TPLGETDEBUGOUTVAR(_out, 2, &Error);

	/* Algorithm invocation */
	PROBER_FLATCOMP(Tpl_OriFla,&Prb_OriFla,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Prb_OriFla);
	TPLPUTDEBUGOUTVAR(_out, 1, &Status);
	TPLPUTDEBUGOUTVAR(_out, 2, &Error);
}
