#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_RCP_CHECK_KEY(void *_alg)
{
}

void
__RCP_CHECK_KEY(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Filename;
	INTEGER	Status;
	STRING	Errmsg;
	STRING	Dupkey;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Errmsg, _TYPES, 0, 0);
	TPLINITMEM(&Dupkey, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Filename);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);
	TPLGETDEBUGOUTVAR(_out, 1, &Errmsg);
	TPLGETDEBUGOUTVAR(_out, 2, &Dupkey);

	/* Algorithm invocation */
	RCP_CHECK_KEY(Filename,&Status,&Errmsg,&Dupkey);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
	TPLPUTDEBUGOUTVAR(_out, 1, &Errmsg);
	TPLPUTDEBUGOUTVAR(_out, 2, &Dupkey);
}
