#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FA_TPLBLD2(void *_alg)
{
}

void
__FA_TPLBLD2(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Rev_flag;
	STRING	Brk_chr;
	STRING	Waf_dir;
	STRING	Prb_dir;
	STRING	Die_dir;
	STRING	Tst_dir;
	STRING	Mod_dir;
	STRING	Tpl_dir;
	STRING	Waf;
	STRING	Prb;
	STRING	Die[128];
	STRING	Tst[128];
	STRING	Mod[128];
	STRING	Tpl;
	STRING	Meas;
	STRING	Tester;
	STRING	Prober;
	STRING	Utility;
	STRING	Device;
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
	TPLINITMEM(&Waf_dir, _TYPES, 0, 0);
	TPLINITMEM(&Prb_dir, _TYPES, 0, 0);
	TPLINITMEM(&Die_dir, _TYPES, 0, 0);
	TPLINITMEM(&Tst_dir, _TYPES, 0, 0);
	TPLINITMEM(&Mod_dir, _TYPES, 0, 0);
	TPLINITMEM(&Tpl_dir, _TYPES, 0, 0);
	TPLINITMEM(&Waf, _TYPES, 0, 0);
	TPLINITMEM(&Prb, _TYPES, 0, 0);
	TPLINITMEM(&Die, _TYPES, 128, 0);
	TPLINITMEM(&Tst, _TYPES, 128, 0);
	TPLINITMEM(&Mod, _TYPES, 128, 0);
	TPLINITMEM(&Tpl, _TYPES, 0, 0);
	TPLINITMEM(&Meas, _TYPES, 0, 0);
	TPLINITMEM(&Tester, _TYPES, 0, 0);
	TPLINITMEM(&Prober, _TYPES, 0, 0);
	TPLINITMEM(&Utility, _TYPES, 0, 0);
	TPLINITMEM(&Device, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);
	TPLINITMEM(&Ndetail, _TYPEI, 0, 0);
	TPLINITMEM(&Detail, _TYPES, 10, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Rev_flag);
	TPLGETDEBUGINVAR(_in, 1, &Brk_chr);
	TPLGETDEBUGINVAR(_in, 2, &Waf_dir);
	TPLGETDEBUGINVAR(_in, 3, &Prb_dir);
	TPLGETDEBUGINVAR(_in, 4, &Die_dir);
	TPLGETDEBUGINVAR(_in, 5, &Tst_dir);
	TPLGETDEBUGINVAR(_in, 6, &Mod_dir);
	TPLGETDEBUGINVAR(_in, 7, &Tpl_dir);
	TPLGETDEBUGINVAR(_in, 8, &Waf);
	TPLGETDEBUGINVAR(_in, 9, &Prb);
	TPLGETDEBUGINVAR(_in, 10, &Die);
	TPLGETDEBUGINVAR(_in, 11, &Tst);
	TPLGETDEBUGINVAR(_in, 12, &Mod);
	TPLGETDEBUGINVAR(_in, 13, &Tpl);
	TPLGETDEBUGINVAR(_in, 14, &Meas);
	TPLGETDEBUGINVAR(_in, 15, &Tester);
	TPLGETDEBUGINVAR(_in, 16, &Prober);
	TPLGETDEBUGINVAR(_in, 17, &Utility);
	TPLGETDEBUGINVAR(_in, 18, &Device);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);
	TPLGETDEBUGOUTVAR(_out, 1, &Error);
	TPLGETDEBUGOUTVAR(_out, 2, &Ndetail);
	TPLGETDEBUGOUTVAR(_out, 3, &Detail);

	/* Algorithm invocation */
	FA_TPLBLD2(Rev_flag,Brk_chr,Waf_dir,Prb_dir,Die_dir,Tst_dir,Mod_dir,Tpl_dir,Waf,Prb,Die,Tst,Mod,Tpl,Meas,Tester,Prober,Utility,Device,&Status,&Error,&Ndetail,&Detail);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
	TPLPUTDEBUGOUTVAR(_out, 1, &Error);
	TPLPUTDEBUGOUTVAR(_out, 2, &Ndetail);
	TPLPUTDEBUGOUTVAR(_out, 3, &Detail);
}
