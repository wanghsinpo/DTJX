#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FA_LIMFMT(void *_alg)
{
}

void
__FA_LIMFMT(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Rev_flag;
	STRING	Brk_chr;
	STRING	Src_lim_dir;
	STRING	Script_dir;
	STRING	Dst_lim_dir;
	STRING	Src_lim;
	STRING	Script;
	STRING	Dst_lim;
	INTEGER	Status;
	STRING	Error;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Rev_flag, _TYPEI, 0, 0);
	TPLINITMEM(&Brk_chr, _TYPES, 0, 0);
	TPLINITMEM(&Src_lim_dir, _TYPES, 0, 0);
	TPLINITMEM(&Script_dir, _TYPES, 0, 0);
	TPLINITMEM(&Dst_lim_dir, _TYPES, 0, 0);
	TPLINITMEM(&Src_lim, _TYPES, 0, 0);
	TPLINITMEM(&Script, _TYPES, 0, 0);
	TPLINITMEM(&Dst_lim, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Rev_flag);
	TPLGETDEBUGINVAR(_in, 1, &Brk_chr);
	TPLGETDEBUGINVAR(_in, 2, &Src_lim_dir);
	TPLGETDEBUGINVAR(_in, 3, &Script_dir);
	TPLGETDEBUGINVAR(_in, 4, &Dst_lim_dir);
	TPLGETDEBUGINVAR(_in, 5, &Src_lim);
	TPLGETDEBUGINVAR(_in, 6, &Script);
	TPLGETDEBUGINVAR(_in, 7, &Dst_lim);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);
	TPLGETDEBUGOUTVAR(_out, 1, &Error);

	/* Algorithm invocation */
	FA_LIMFMT(Rev_flag,Brk_chr,Src_lim_dir,Script_dir,Dst_lim_dir,Src_lim,Script,Dst_lim,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
	TPLPUTDEBUGOUTVAR(_out, 1, &Error);
}
