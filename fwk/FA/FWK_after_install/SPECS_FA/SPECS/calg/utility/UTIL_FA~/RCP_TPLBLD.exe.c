#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_RCP_TPLBLD(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

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

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

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
	TPLGETEXECINVAR(_in, 0, &Waf_dir);
	TPLGETEXECINVAR(_in, 1, &Prb_dir);
	TPLGETEXECINVAR(_in, 2, &Die_dir);
	TPLGETEXECINVAR(_in, 3, &Mod_dir);
	TPLGETEXECINVAR(_in, 4, &Tst_dir);
	TPLGETEXECINVAR(_in, 5, &Tpl_dir);
	TPLGETEXECINVAR(_in, 6, &Waf);
	TPLGETEXECINVAR(_in, 7, &Prb);
	TPLGETEXECINVAR(_in, 8, &Die);
	TPLGETEXECINVAR(_in, 9, &Mod);
	TPLGETEXECINVAR(_in, 10, &Tst);
	TPLGETEXECINVAR(_in, 11, &Mlib);
	TPLGETEXECINVAR(_in, 12, &Tpl);
	TPLPUTLASTINVAR(__in, 0, &Waf_dir);
	TPLPUTLASTINVAR(__in, 1, &Prb_dir);
	TPLPUTLASTINVAR(__in, 2, &Die_dir);
	TPLPUTLASTINVAR(__in, 3, &Mod_dir);
	TPLPUTLASTINVAR(__in, 4, &Tst_dir);
	TPLPUTLASTINVAR(__in, 5, &Tpl_dir);
	TPLPUTLASTINVAR(__in, 6, &Waf);
	TPLPUTLASTINVAR(__in, 7, &Prb);
	TPLPUTLASTINVAR(__in, 8, &Die);
	TPLPUTLASTINVAR(__in, 9, &Mod);
	TPLPUTLASTINVAR(__in, 10, &Tst);
	TPLPUTLASTINVAR(__in, 11, &Mlib);
	TPLPUTLASTINVAR(__in, 12, &Tpl);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Status);
	TPLGETEXECOUTVAR(_out, 1, &Errmsg);
	TPLGETEXECOUTVAR(_out, 2, &Ndetail);
	TPLGETEXECOUTVAR(_out, 3, &Detail);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Errmsg);
	TPLPUTLASTOUTVAR(__out, 2, &Ndetail);
	TPLPUTLASTOUTVAR(__out, 3, &Detail);

	/* Algorithm invocation */
	RCP_TPLBLD(Waf_dir,Prb_dir,Die_dir,Mod_dir,Tst_dir,Tpl_dir,Waf,Prb,Die,Mod,Tst,Mlib,Tpl,&Status,&Errmsg,&Ndetail,&Detail);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Status);
	TPLPUTEXECOUTVAR(_out, 1, &Errmsg);
	TPLPUTEXECOUTVAR(_out, 2, &Ndetail);
	TPLPUTEXECOUTVAR(_out, 3, &Detail);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Errmsg);
	TPLPUTLASTOUTVAR(__out, 2, &Ndetail);
	TPLPUTLASTOUTVAR(__out, 3, &Detail);
}

void
__RCP_TPLBLD(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

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

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

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
	TPLGETLASTINVAR(__in, 0, &Waf_dir);
	TPLGETLASTINVAR(__in, 1, &Prb_dir);
	TPLGETLASTINVAR(__in, 2, &Die_dir);
	TPLGETLASTINVAR(__in, 3, &Mod_dir);
	TPLGETLASTINVAR(__in, 4, &Tst_dir);
	TPLGETLASTINVAR(__in, 5, &Tpl_dir);
	TPLGETLASTINVAR(__in, 6, &Waf);
	TPLGETLASTINVAR(__in, 7, &Prb);
	TPLGETLASTINVAR(__in, 8, &Die);
	TPLGETLASTINVAR(__in, 9, &Mod);
	TPLGETLASTINVAR(__in, 10, &Tst);
	TPLGETLASTINVAR(__in, 11, &Mlib);
	TPLGETLASTINVAR(__in, 12, &Tpl);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Status);
	TPLGETLASTOUTVAR(__out, 1, &Errmsg);
	TPLGETLASTOUTVAR(__out, 2, &Ndetail);
	TPLGETLASTOUTVAR(__out, 3, &Detail);

	/* Algorithm invocation */
	RCP_TPLBLD(Waf_dir,Prb_dir,Die_dir,Mod_dir,Tst_dir,Tpl_dir,Waf,Prb,Die,Mod,Tst,Mlib,Tpl,&Status,&Errmsg,&Ndetail,&Detail);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Errmsg);
	TPLPUTLASTOUTVAR(__out, 2, &Ndetail);
	TPLPUTLASTOUTVAR(__out, 3, &Detail);
}
