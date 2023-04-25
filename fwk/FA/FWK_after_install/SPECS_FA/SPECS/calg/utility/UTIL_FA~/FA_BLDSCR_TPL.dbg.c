#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FA_BLDSCR_TPL(void *_alg)
{
}

void
__FA_BLDSCR_TPL(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Masscr;
	STRING	Fmtscr;
	INTEGER	Status;
	STRING	Error;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Masscr, _TYPES, 0, 0);
	TPLINITMEM(&Fmtscr, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Masscr);
	TPLGETDEBUGINVAR(_in, 1, &Fmtscr);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);
	TPLGETDEBUGOUTVAR(_out, 1, &Error);

	/* Algorithm invocation */
	FA_BLDSCR_TPL(Masscr,Fmtscr,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
	TPLPUTDEBUGOUTVAR(_out, 1, &Error);
}
