#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FA_LMP_CLEARLN(void *_alg)
{
}

void
__FA_LMP_CLEARLN(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	INTEGER	LineNth;
	INTEGER	EraseMode;
	INTEGER	Status;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&LineNth, _TYPEI, 0, 0);
	TPLINITMEM(&EraseMode, _TYPEI, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &LineNth);
	TPLGETDEBUGINVAR(_in, 1, &EraseMode);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);

	/* Algorithm invocation */
	FA_LMP_CLEARLN(LineNth,EraseMode,&Status);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
}
