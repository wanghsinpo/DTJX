#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_FA_LIMBLD2(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Rev_flag;
	STRING	Brk_chr;
	STRING	Tpl_dir;
	STRING	Lim_dir;
	STRING	Lms_dir;
	STRING	Tpl;
	STRING	Lim;
	STRING	Lms[256];
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
	TPLINITMEM(&Tpl_dir, _TYPES, 0, 0);
	TPLINITMEM(&Lim_dir, _TYPES, 0, 0);
	TPLINITMEM(&Lms_dir, _TYPES, 0, 0);
	TPLINITMEM(&Tpl, _TYPES, 0, 0);
	TPLINITMEM(&Lim, _TYPES, 0, 0);
	TPLINITMEM(&Lms, _TYPES, 256, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);
	TPLINITMEM(&Ndetail, _TYPEI, 0, 0);
	TPLINITMEM(&Detail, _TYPES, 10, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Rev_flag);
	TPLGETEXECINVAR(_in, 1, &Brk_chr);
	TPLGETEXECINVAR(_in, 2, &Tpl_dir);
	TPLGETEXECINVAR(_in, 3, &Lim_dir);
	TPLGETEXECINVAR(_in, 4, &Lms_dir);
	TPLGETEXECINVAR(_in, 5, &Tpl);
	TPLGETEXECINVAR(_in, 6, &Lim);
	TPLGETEXECINVAR(_in, 7, &Lms);
	TPLPUTLASTINVAR(__in, 0, &Rev_flag);
	TPLPUTLASTINVAR(__in, 1, &Brk_chr);
	TPLPUTLASTINVAR(__in, 2, &Tpl_dir);
	TPLPUTLASTINVAR(__in, 3, &Lim_dir);
	TPLPUTLASTINVAR(__in, 4, &Lms_dir);
	TPLPUTLASTINVAR(__in, 5, &Tpl);
	TPLPUTLASTINVAR(__in, 6, &Lim);
	TPLPUTLASTINVAR(__in, 7, &Lms);

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
	FA_LIMBLD2(Rev_flag,Brk_chr,Tpl_dir,Lim_dir,Lms_dir,Tpl,Lim,Lms,&Status,&Error,&Ndetail,&Detail);

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
__FA_LIMBLD2(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Rev_flag;
	STRING	Brk_chr;
	STRING	Tpl_dir;
	STRING	Lim_dir;
	STRING	Lms_dir;
	STRING	Tpl;
	STRING	Lim;
	STRING	Lms[256];
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
	TPLINITMEM(&Tpl_dir, _TYPES, 0, 0);
	TPLINITMEM(&Lim_dir, _TYPES, 0, 0);
	TPLINITMEM(&Lms_dir, _TYPES, 0, 0);
	TPLINITMEM(&Tpl, _TYPES, 0, 0);
	TPLINITMEM(&Lim, _TYPES, 0, 0);
	TPLINITMEM(&Lms, _TYPES, 256, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);
	TPLINITMEM(&Ndetail, _TYPEI, 0, 0);
	TPLINITMEM(&Detail, _TYPES, 10, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Rev_flag);
	TPLGETLASTINVAR(__in, 1, &Brk_chr);
	TPLGETLASTINVAR(__in, 2, &Tpl_dir);
	TPLGETLASTINVAR(__in, 3, &Lim_dir);
	TPLGETLASTINVAR(__in, 4, &Lms_dir);
	TPLGETLASTINVAR(__in, 5, &Tpl);
	TPLGETLASTINVAR(__in, 6, &Lim);
	TPLGETLASTINVAR(__in, 7, &Lms);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Status);
	TPLGETLASTOUTVAR(__out, 1, &Error);
	TPLGETLASTOUTVAR(__out, 2, &Ndetail);
	TPLGETLASTOUTVAR(__out, 3, &Detail);

	/* Algorithm invocation */
	FA_LIMBLD2(Rev_flag,Brk_chr,Tpl_dir,Lim_dir,Lms_dir,Tpl,Lim,Lms,&Status,&Error,&Ndetail,&Detail);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Error);
	TPLPUTLASTOUTVAR(__out, 2, &Ndetail);
	TPLPUTLASTOUTVAR(__out, 3, &Detail);
}
