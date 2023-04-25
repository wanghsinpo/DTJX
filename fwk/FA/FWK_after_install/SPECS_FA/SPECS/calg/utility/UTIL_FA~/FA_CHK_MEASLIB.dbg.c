#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FA_CHK_MEASLIB(void *_alg)
{
}

void
__FA_CHK_MEASLIB(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Revcont;
	STRING	Lib[256];
	INTEGER	Libnum;
	STRING	Delimiter;
	INTEGER	Status;
	STRING	Error;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Revcont, _TYPEI, 0, 0);
	TPLINITMEM(&Lib, _TYPES, 256, 0);
	TPLINITMEM(&Libnum, _TYPEI, 0, 0);
	TPLINITMEM(&Delimiter, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Revcont);
	TPLGETDEBUGINVAR(_in, 1, &Lib);
	TPLGETDEBUGINVAR(_in, 2, &Libnum);
	TPLGETDEBUGINVAR(_in, 3, &Delimiter);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);
	TPLGETDEBUGOUTVAR(_out, 1, &Error);

	/* Algorithm invocation */
	FA_CHK_MEASLIB(Revcont,Lib,Libnum,Delimiter,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
	TPLPUTDEBUGOUTVAR(_out, 1, &Error);
}
