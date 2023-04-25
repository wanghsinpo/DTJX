#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_FA_TPLBLD3(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

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
	STRING	Die[256];
	STRING	Tst[256];
	STRING	Mod[256];
	STRING	Tpl;
	STRING	Meas[256];
	STRING	Tester;
	STRING	Prober;
	STRING	Utility;
	STRING	Device;
	INTEGER	Status;
	STRING	Error;
	INTEGER	Ndetail;
	STRING	Detail[10];

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

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
	TPLINITMEM(&Die, _TYPES, 256, 0);
	TPLINITMEM(&Tst, _TYPES, 256, 0);
	TPLINITMEM(&Mod, _TYPES, 256, 0);
	TPLINITMEM(&Tpl, _TYPES, 0, 0);
	TPLINITMEM(&Meas, _TYPES, 256, 0);
	TPLINITMEM(&Tester, _TYPES, 0, 0);
	TPLINITMEM(&Prober, _TYPES, 0, 0);
	TPLINITMEM(&Utility, _TYPES, 0, 0);
	TPLINITMEM(&Device, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);
	TPLINITMEM(&Ndetail, _TYPEI, 0, 0);
	TPLINITMEM(&Detail, _TYPES, 10, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Rev_flag);
	TPLGETEXECINVAR(_in, 1, &Brk_chr);
	TPLGETEXECINVAR(_in, 2, &Waf_dir);
	TPLGETEXECINVAR(_in, 3, &Prb_dir);
	TPLGETEXECINVAR(_in, 4, &Die_dir);
	TPLGETEXECINVAR(_in, 5, &Tst_dir);
	TPLGETEXECINVAR(_in, 6, &Mod_dir);
	TPLGETEXECINVAR(_in, 7, &Tpl_dir);
	TPLGETEXECINVAR(_in, 8, &Waf);
	TPLGETEXECINVAR(_in, 9, &Prb);
	TPLGETEXECINVAR(_in, 10, &Die);
	TPLGETEXECINVAR(_in, 11, &Tst);
	TPLGETEXECINVAR(_in, 12, &Mod);
	TPLGETEXECINVAR(_in, 13, &Tpl);
	TPLGETEXECINVAR(_in, 14, &Meas);
	TPLGETEXECINVAR(_in, 15, &Tester);
	TPLGETEXECINVAR(_in, 16, &Prober);
	TPLGETEXECINVAR(_in, 17, &Utility);
	TPLGETEXECINVAR(_in, 18, &Device);
	TPLPUTLASTINVAR(__in, 0, &Rev_flag);
	TPLPUTLASTINVAR(__in, 1, &Brk_chr);
	TPLPUTLASTINVAR(__in, 2, &Waf_dir);
	TPLPUTLASTINVAR(__in, 3, &Prb_dir);
	TPLPUTLASTINVAR(__in, 4, &Die_dir);
	TPLPUTLASTINVAR(__in, 5, &Tst_dir);
	TPLPUTLASTINVAR(__in, 6, &Mod_dir);
	TPLPUTLASTINVAR(__in, 7, &Tpl_dir);
	TPLPUTLASTINVAR(__in, 8, &Waf);
	TPLPUTLASTINVAR(__in, 9, &Prb);
	TPLPUTLASTINVAR(__in, 10, &Die);
	TPLPUTLASTINVAR(__in, 11, &Tst);
	TPLPUTLASTINVAR(__in, 12, &Mod);
	TPLPUTLASTINVAR(__in, 13, &Tpl);
	TPLPUTLASTINVAR(__in, 14, &Meas);
	TPLPUTLASTINVAR(__in, 15, &Tester);
	TPLPUTLASTINVAR(__in, 16, &Prober);
	TPLPUTLASTINVAR(__in, 17, &Utility);
	TPLPUTLASTINVAR(__in, 18, &Device);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Status);
	TPLGETEXECOUTVAR(_out, 1, &Error);
	TPLGETEXECOUTVAR(_out, 2, &Ndetail);
	TPLGETEXECOUTVAR(_out, 3, &Detail);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Error);
	TPLPUTLASTOUTVAR(__out, 2, &Ndetail);
	TPLPUTLASTOUTVAR(__out, 3, &Detail);

	/* Algorithm invocation */
	FA_TPLBLD3(Rev_flag,Brk_chr,Waf_dir,Prb_dir,Die_dir,Tst_dir,Mod_dir,Tpl_dir,Waf,Prb,Die,Tst,Mod,Tpl,Meas,Tester,Prober,Utility,Device,&Status,&Error,&Ndetail,&Detail);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Status);
	TPLPUTEXECOUTVAR(_out, 1, &Error);
	TPLPUTEXECOUTVAR(_out, 2, &Ndetail);
	TPLPUTEXECOUTVAR(_out, 3, &Detail);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Error);
	TPLPUTLASTOUTVAR(__out, 2, &Ndetail);
	TPLPUTLASTOUTVAR(__out, 3, &Detail);
}

void
__FA_TPLBLD3(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

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
	STRING	Die[256];
	STRING	Tst[256];
	STRING	Mod[256];
	STRING	Tpl;
	STRING	Meas[256];
	STRING	Tester;
	STRING	Prober;
	STRING	Utility;
	STRING	Device;
	INTEGER	Status;
	STRING	Error;
	INTEGER	Ndetail;
	STRING	Detail[10];

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

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
	TPLINITMEM(&Die, _TYPES, 256, 0);
	TPLINITMEM(&Tst, _TYPES, 256, 0);
	TPLINITMEM(&Mod, _TYPES, 256, 0);
	TPLINITMEM(&Tpl, _TYPES, 0, 0);
	TPLINITMEM(&Meas, _TYPES, 256, 0);
	TPLINITMEM(&Tester, _TYPES, 0, 0);
	TPLINITMEM(&Prober, _TYPES, 0, 0);
	TPLINITMEM(&Utility, _TYPES, 0, 0);
	TPLINITMEM(&Device, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);
	TPLINITMEM(&Ndetail, _TYPEI, 0, 0);
	TPLINITMEM(&Detail, _TYPES, 10, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Rev_flag);
	TPLGETLASTINVAR(__in, 1, &Brk_chr);
	TPLGETLASTINVAR(__in, 2, &Waf_dir);
	TPLGETLASTINVAR(__in, 3, &Prb_dir);
	TPLGETLASTINVAR(__in, 4, &Die_dir);
	TPLGETLASTINVAR(__in, 5, &Tst_dir);
	TPLGETLASTINVAR(__in, 6, &Mod_dir);
	TPLGETLASTINVAR(__in, 7, &Tpl_dir);
	TPLGETLASTINVAR(__in, 8, &Waf);
	TPLGETLASTINVAR(__in, 9, &Prb);
	TPLGETLASTINVAR(__in, 10, &Die);
	TPLGETLASTINVAR(__in, 11, &Tst);
	TPLGETLASTINVAR(__in, 12, &Mod);
	TPLGETLASTINVAR(__in, 13, &Tpl);
	TPLGETLASTINVAR(__in, 14, &Meas);
	TPLGETLASTINVAR(__in, 15, &Tester);
	TPLGETLASTINVAR(__in, 16, &Prober);
	TPLGETLASTINVAR(__in, 17, &Utility);
	TPLGETLASTINVAR(__in, 18, &Device);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Status);
	TPLGETLASTOUTVAR(__out, 1, &Error);
	TPLGETLASTOUTVAR(__out, 2, &Ndetail);
	TPLGETLASTOUTVAR(__out, 3, &Detail);

	/* Algorithm invocation */
	FA_TPLBLD3(Rev_flag,Brk_chr,Waf_dir,Prb_dir,Die_dir,Tst_dir,Mod_dir,Tpl_dir,Waf,Prb,Die,Tst,Mod,Tpl,Meas,Tester,Prober,Utility,Device,&Status,&Error,&Ndetail,&Detail);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Error);
	TPLPUTLASTOUTVAR(__out, 2, &Ndetail);
	TPLPUTLASTOUTVAR(__out, 3, &Detail);
}
