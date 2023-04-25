#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FA_CHKRUN_FWK(void *_alg)
{
}

void
__FA_CHKRUN_FWK(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Name;
	STRING	Status;
	INTEGER	numFile;
	INTEGER	numRunning;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Name, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPES, 0, 0);
	TPLINITMEM(&numFile, _TYPEI, 0, 0);
	TPLINITMEM(&numRunning, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Name);
	TPLGETDEBUGINVAR(_in, 1, &Status);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &numFile);
	TPLGETDEBUGOUTVAR(_out, 1, &numRunning);

	/* Algorithm invocation */
	FA_CHKRUN_FWK(Name,Status,&numFile,&numRunning);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &numFile);
	TPLPUTDEBUGOUTVAR(_out, 1, &numRunning);
}
