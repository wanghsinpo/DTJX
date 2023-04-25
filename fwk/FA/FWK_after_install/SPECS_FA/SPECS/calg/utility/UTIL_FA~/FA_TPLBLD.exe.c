#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_FA_TPLBLD(void *_alg, void *__alg)
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
	STRING	Tpl_dir;
	STRING	Waf;
	STRING	Prb;
	STRING	Die[32];
	STRING	Tst[32];
	STRING	Tpl;
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
	TPLINITMEM(&Tpl_dir, _TYPES, 0, 0);
	TPLINITMEM(&Waf, _TYPES, 0, 0);
	TPLINITMEM(&Prb, _TYPES, 0, 0);
	TPLINITMEM(&Die, _TYPES, 32, 0);
	TPLINITMEM(&Tst, _TYPES, 32, 0);
	TPLINITMEM(&Tpl, _TYPES, 0, 0);
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
	TPLGETEXECINVAR(_in, 6, &Tpl_dir);
	TPLGETEXECINVAR(_in, 7, &Waf);
	TPLGETEXECINVAR(_in, 8, &Prb);
	TPLGETEXECINVAR(_in, 9, &Die);
	TPLGETEXECINVAR(_in, 10, &Tst);
	TPLGETEXECINVAR(_in, 11, &Tpl);
	TPLPUTLASTINVAR(__in, 0, &Rev_flag);
	TPLPUTLASTINVAR(__in, 1, &Brk_chr);
	TPLPUTLASTINVAR(__in, 2, &Waf_dir);
	TPLPUTLASTINVAR(__in, 3, &Prb_dir);
	TPLPUTLASTINVAR(__in, 4, &Die_dir);
	TPLPUTLASTINVAR(__in, 5, &Tst_dir);
	TPLPUTLASTINVAR(__in, 6, &Tpl_dir);
	TPLPUTLASTINVAR(__in, 7, &Waf);
	TPLPUTLASTINVAR(__in, 8, &Prb);
	TPLPUTLASTINVAR(__in, 9, &Die);
	TPLPUTLASTINVAR(__in, 10, &Tst);
	TPLPUTLASTINVAR(__in, 11, &Tpl);

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
	FA_TPLBLD(Rev_flag,Brk_chr,Waf_dir,Prb_dir,Die_dir,Tst_dir,Tpl_dir,Waf,Prb,Die,Tst,Tpl,&Status,&Error,&Ndetail,&Detail);

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
__FA_TPLBLD(void *__alg)
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
	STRING	Tpl_dir;
	STRING	Waf;
	STRING	Prb;
	STRING	Die[32];
	STRING	Tst[32];
	STRING	Tpl;
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
	TPLINITMEM(&Tpl_dir, _TYPES, 0, 0);
	TPLINITMEM(&Waf, _TYPES, 0, 0);
	TPLINITMEM(&Prb, _TYPES, 0, 0);
	TPLINITMEM(&Die, _TYPES, 32, 0);
	TPLINITMEM(&Tst, _TYPES, 32, 0);
	TPLINITMEM(&Tpl, _TYPES, 0, 0);
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
	TPLGETLASTINVAR(__in, 6, &Tpl_dir);
	TPLGETLASTINVAR(__in, 7, &Waf);
	TPLGETLASTINVAR(__in, 8, &Prb);
	TPLGETLASTINVAR(__in, 9, &Die);
	TPLGETLASTINVAR(__in, 10, &Tst);
	TPLGETLASTINVAR(__in, 11, &Tpl);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Status);
	TPLGETLASTOUTVAR(__out, 1, &Error);
	TPLGETLASTOUTVAR(__out, 2, &Ndetail);
	TPLGETLASTOUTVAR(__out, 3, &Detail);

	/* Algorithm invocation */
	FA_TPLBLD(Rev_flag,Brk_chr,Waf_dir,Prb_dir,Die_dir,Tst_dir,Tpl_dir,Waf,Prb,Die,Tst,Tpl,&Status,&Error,&Ndetail,&Detail);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Error);
	TPLPUTLASTOUTVAR(__out, 2, &Ndetail);
	TPLPUTLASTOUTVAR(__out, 3, &Detail);
}
