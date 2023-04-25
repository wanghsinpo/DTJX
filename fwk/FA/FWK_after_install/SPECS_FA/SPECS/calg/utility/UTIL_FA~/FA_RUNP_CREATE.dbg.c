#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FA_RUNP_CREATE(void *_alg)
{
}

void
__FA_RUNP_CREATE(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Meas_dir;
	STRING	Fwk_dir;
	STRING	Meas;
	STRING	Fwk;
	INTEGER	Status;
	STRING	Error;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Meas_dir, _TYPES, 0, 0);
	TPLINITMEM(&Fwk_dir, _TYPES, 0, 0);
	TPLINITMEM(&Meas, _TYPES, 0, 0);
	TPLINITMEM(&Fwk, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Meas_dir);
	TPLGETDEBUGINVAR(_in, 1, &Fwk_dir);
	TPLGETDEBUGINVAR(_in, 2, &Meas);
	TPLGETDEBUGINVAR(_in, 3, &Fwk);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);
	TPLGETDEBUGOUTVAR(_out, 1, &Error);

	/* Algorithm invocation */
	FA_RUNP_CREATE(Meas_dir,Fwk_dir,Meas,Fwk,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
	TPLPUTDEBUGOUTVAR(_out, 1, &Error);
}
