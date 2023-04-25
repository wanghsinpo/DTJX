#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_RCP_TPLBLD(void *_alg)
{
}

void
__RCP_TPLBLD(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Waf_dir;
	STRING	Prb_dir;
	STRING	Die_dir;
	STRING	Mod_dir;
	STRING	Tst_dir;
	STRING	Tpl_dir;
	STRING	Waf;
	STRING	Prb;
	STRING	Die[256];
	STRING	Mod[256];
	STRING	Tst[256];
	STRING	Mlib[6];
	STRING	Tpl;
	INTEGER	Status;
	STRING	Errmsg;
	INTEGER	Ndetail;
	STRING	Detail[10];

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Waf_dir, _TYPES, 0, 0);
	TPLINITMEM(&Prb_dir, _TYPES, 0, 0);
	TPLINITMEM(&Die_dir, _TYPES, 0, 0);
	TPLINITMEM(&Mod_dir, _TYPES, 0, 0);
	TPLINITMEM(&Tst_dir, _TYPES, 0, 0);
	TPLINITMEM(&Tpl_dir, _TYPES, 0, 0);
	TPLINITMEM(&Waf, _TYPES, 0, 0);
	TPLINITMEM(&Prb, _TYPES, 0, 0);
	TPLINITMEM(&Die, _TYPES, 256, 0);
	TPLINITMEM(&Mod, _TYPES, 256, 0);
	TPLINITMEM(&Tst, _TYPES, 256, 0);
	TPLINITMEM(&Mlib, _TYPES, 6, 0);
	TPLINITMEM(&Tpl, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Errmsg, _TYPES, 0, 0);
	TPLINITMEM(&Ndetail, _TYPEI, 0, 0);
	TPLINITMEM(&Detail, _TYPES, 10, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Waf_dir);
	TPLGETDEBUGINVAR(_in, 1, &Prb_dir);
	TPLGETDEBUGINVAR(_in, 2, &Die_dir);
	TPLGETDEBUGINVAR(_in, 3, &Mod_dir);
	TPLGETDEBUGINVAR(_in, 4, &Tst_dir);
	TPLGETDEBUGINVAR(_in, 5, &Tpl_dir);
	TPLGETDEBUGINVAR(_in, 6, &Waf);
	TPLGETDEBUGINVAR(_in, 7, &Prb);
	TPLGETDEBUGINVAR(_in, 8, &Die);
	TPLGETDEBUGINVAR(_in, 9, &Mod);
	TPLGETDEBUGINVAR(_in, 10, &Tst);
	TPLGETDEBUGINVAR(_in, 11, &Mlib);
	TPLGETDEBUGINVAR(_in, 12, &Tpl);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);
	TPLGETDEBUGOUTVAR(_out, 1, &Errmsg);
	TPLGETDEBUGOUTVAR(_out, 2, &Ndetail);
	TPLGETDEBUGOUTVAR(_out, 3, &Detail);

	/* Algorithm invocation */
	RCP_TPLBLD(Waf_dir,Prb_dir,Die_dir,Mod_dir,Tst_dir,Tpl_dir,Waf,Prb,Die,Mod,Tst,Mlib,Tpl,&Status,&Errmsg,&Ndetail,&Detail);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
	TPLPUTDEBUGOUTVAR(_out, 1, &Errmsg);
	TPLPUTDEBUGOUTVAR(_out, 2, &Ndetail);
	TPLPUTDEBUGOUTVAR(_out, 3, &Detail);
}
