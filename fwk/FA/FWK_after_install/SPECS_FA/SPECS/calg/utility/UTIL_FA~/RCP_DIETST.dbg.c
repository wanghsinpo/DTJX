#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_RCP_DIETST(void *_alg)
{
}

void
__RCP_DIETST(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Die[256];
	STRING	Tst[256];
	STRING	Rule;
	STRING	Die_tst[256];
	INTEGER	Status;
	STRING	Errmsg;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Die, _TYPES, 256, 0);
	TPLINITMEM(&Tst, _TYPES, 256, 0);
	TPLINITMEM(&Rule, _TYPES, 0, 0);
	TPLINITMEM(&Die_tst, _TYPES, 256, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Errmsg, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Die);
	TPLGETDEBUGINVAR(_in, 1, &Tst);
	TPLGETDEBUGINVAR(_in, 2, &Rule);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Die_tst);
	TPLGETDEBUGOUTVAR(_out, 1, &Status);
	TPLGETDEBUGOUTVAR(_out, 2, &Errmsg);

	/* Algorithm invocation */
	RCP_DIETST(Die,Tst,Rule,&Die_tst,&Status,&Errmsg);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Die_tst);
	TPLPUTDEBUGOUTVAR(_out, 1, &Status);
	TPLPUTDEBUGOUTVAR(_out, 2, &Errmsg);
}
