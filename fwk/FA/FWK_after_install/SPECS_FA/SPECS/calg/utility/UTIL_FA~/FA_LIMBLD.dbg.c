#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FA_LIMBLD(void *_alg)
{
}

void
__FA_LIMBLD(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Rev_flag;
	STRING	Brk_chr;
	STRING	Tpl_dir;
	STRING	Lim_dir;
	STRING	Tpl;
	STRING	Lim;
	INTEGER	Status;
	STRING	Error;
	INTEGER	Ndetail;
	STRING	Detail[10];

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Rev_flag, _TYPEI, 0, 0);
	TPLINITMEM(&Brk_chr, _TYPES, 0, 0);
	TPLINITMEM(&Tpl_dir, _TYPES, 0, 0);
	TPLINITMEM(&Lim_dir, _TYPES, 0, 0);
	TPLINITMEM(&Tpl, _TYPES, 0, 0);
	TPLINITMEM(&Lim, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);
	TPLINITMEM(&Ndetail, _TYPEI, 0, 0);
	TPLINITMEM(&Detail, _TYPES, 10, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Rev_flag);
	TPLGETDEBUGINVAR(_in, 1, &Brk_chr);
	TPLGETDEBUGINVAR(_in, 2, &Tpl_dir);
	TPLGETDEBUGINVAR(_in, 3, &Lim_dir);
	TPLGETDEBUGINVAR(_in, 4, &Tpl);
	TPLGETDEBUGINVAR(_in, 5, &Lim);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);
	TPLGETDEBUGOUTVAR(_out, 1, &Error);
	TPLGETDEBUGOUTVAR(_out, 2, &Ndetail);
	TPLGETDEBUGOUTVAR(_out, 3, &Detail);

	/* Algorithm invocation */
	FA_LIMBLD(Rev_flag,Brk_chr,Tpl_dir,Lim_dir,Tpl,Lim,&Status,&Error,&Ndetail,&Detail);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
	TPLPUTDEBUGOUTVAR(_out, 1, &Error);
	TPLPUTDEBUGOUTVAR(_out, 2, &Ndetail);
	TPLPUTDEBUGOUTVAR(_out, 3, &Detail);
}
