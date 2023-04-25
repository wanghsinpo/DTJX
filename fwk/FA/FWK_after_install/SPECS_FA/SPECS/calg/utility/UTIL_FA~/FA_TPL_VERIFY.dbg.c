#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FA_TPL_VERIFY(void *_alg)
{
}

void
__FA_TPL_VERIFY(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Revcont;
	INTEGER	Revmode;
	STRING	Lib[256];
	INTEGER	Libnum;
	STRING	Tco[256];
	INTEGER	Tconum;
	STRING	Tpl;
	STRING	Delimiter;
	INTEGER	Status;
	STRING	Error;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Revcont, _TYPEI, 0, 0);
	TPLINITMEM(&Revmode, _TYPEI, 0, 0);
	TPLINITMEM(&Lib, _TYPES, 256, 0);
	TPLINITMEM(&Libnum, _TYPEI, 0, 0);
	TPLINITMEM(&Tco, _TYPES, 256, 0);
	TPLINITMEM(&Tconum, _TYPEI, 0, 0);
	TPLINITMEM(&Tpl, _TYPES, 0, 0);
	TPLINITMEM(&Delimiter, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Revcont);
	TPLGETDEBUGINVAR(_in, 1, &Revmode);
	TPLGETDEBUGINVAR(_in, 2, &Lib);
	TPLGETDEBUGINVAR(_in, 3, &Libnum);
	TPLGETDEBUGINVAR(_in, 4, &Tco);
	TPLGETDEBUGINVAR(_in, 5, &Tconum);
	TPLGETDEBUGINVAR(_in, 6, &Tpl);
	TPLGETDEBUGINVAR(_in, 7, &Delimiter);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);
	TPLGETDEBUGOUTVAR(_out, 1, &Error);

	/* Algorithm invocation */
	FA_TPL_VERIFY(Revcont,Revmode,Lib,Libnum,Tco,Tconum,Tpl,Delimiter,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
	TPLPUTDEBUGOUTVAR(_out, 1, &Error);
}
