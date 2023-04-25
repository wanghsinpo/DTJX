#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FA_LMP_DISPLINE(void *_alg)
{
}

void
__FA_LMP_DISPLINE(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	INTEGER	LineNth;
	STRING	DispLabel;
	STRING	DispStr;
	STRING	DispFgc;
	STRING	DispBgc;
	INTEGER	Status;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&LineNth, _TYPEI, 0, 0);
	TPLINITMEM(&DispLabel, _TYPES, 0, 0);
	TPLINITMEM(&DispStr, _TYPES, 0, 0);
	TPLINITMEM(&DispFgc, _TYPES, 0, 0);
	TPLINITMEM(&DispBgc, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &LineNth);
	TPLGETDEBUGINVAR(_in, 1, &DispLabel);
	TPLGETDEBUGINVAR(_in, 2, &DispStr);
	TPLGETDEBUGINVAR(_in, 3, &DispFgc);
	TPLGETDEBUGINVAR(_in, 4, &DispBgc);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);

	/* Algorithm invocation */
	FA_LMP_DISPLINE(LineNth,DispLabel,DispStr,DispFgc,DispBgc,&Status);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
}
