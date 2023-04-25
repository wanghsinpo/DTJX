#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_RCP_LIMBLD(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Tpl_dir;
	STRING	Lms_dir;
	STRING	Lim_dir;
	STRING	Tpl;
	STRING	Lms[256];
	STRING	Lim;
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
	TPLINITMEM(&Tpl_dir, _TYPES, 0, 0);
	TPLINITMEM(&Lms_dir, _TYPES, 0, 0);
	TPLINITMEM(&Lim_dir, _TYPES, 0, 0);
	TPLINITMEM(&Tpl, _TYPES, 0, 0);
	TPLINITMEM(&Lms, _TYPES, 256, 0);
	TPLINITMEM(&Lim, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Errmsg, _TYPES, 0, 0);
	TPLINITMEM(&Ndetail, _TYPEI, 0, 0);
	TPLINITMEM(&Detail, _TYPES, 10, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Tpl_dir);
	TPLGETEXECINVAR(_in, 1, &Lms_dir);
	TPLGETEXECINVAR(_in, 2, &Lim_dir);
	TPLGETEXECINVAR(_in, 3, &Tpl);
	TPLGETEXECINVAR(_in, 4, &Lms);
	TPLGETEXECINVAR(_in, 5, &Lim);
	TPLPUTLASTINVAR(__in, 0, &Tpl_dir);
	TPLPUTLASTINVAR(__in, 1, &Lms_dir);
	TPLPUTLASTINVAR(__in, 2, &Lim_dir);
	TPLPUTLASTINVAR(__in, 3, &Tpl);
	TPLPUTLASTINVAR(__in, 4, &Lms);
	TPLPUTLASTINVAR(__in, 5, &Lim);

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
	RCP_LIMBLD(Tpl_dir,Lms_dir,Lim_dir,Tpl,Lms,Lim,&Status,&Errmsg,&Ndetail,&Detail);

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
__RCP_LIMBLD(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Tpl_dir;
	STRING	Lms_dir;
	STRING	Lim_dir;
	STRING	Tpl;
	STRING	Lms[256];
	STRING	Lim;
	INTEGER	Status;
	STRING	Errmsg;
	INTEGER	Ndetail;
	STRING	Detail[10];

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Tpl_dir, _TYPES, 0, 0);
	TPLINITMEM(&Lms_dir, _TYPES, 0, 0);
	TPLINITMEM(&Lim_dir, _TYPES, 0, 0);
	TPLINITMEM(&Tpl, _TYPES, 0, 0);
	TPLINITMEM(&Lms, _TYPES, 256, 0);
	TPLINITMEM(&Lim, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Errmsg, _TYPES, 0, 0);
	TPLINITMEM(&Ndetail, _TYPEI, 0, 0);
	TPLINITMEM(&Detail, _TYPES, 10, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Tpl_dir);
	TPLGETLASTINVAR(__in, 1, &Lms_dir);
	TPLGETLASTINVAR(__in, 2, &Lim_dir);
	TPLGETLASTINVAR(__in, 3, &Tpl);
	TPLGETLASTINVAR(__in, 4, &Lms);
	TPLGETLASTINVAR(__in, 5, &Lim);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Status);
	TPLGETLASTOUTVAR(__out, 1, &Errmsg);
	TPLGETLASTOUTVAR(__out, 2, &Ndetail);
	TPLGETLASTOUTVAR(__out, 3, &Detail);

	/* Algorithm invocation */
	RCP_LIMBLD(Tpl_dir,Lms_dir,Lim_dir,Tpl,Lms,Lim,&Status,&Errmsg,&Ndetail,&Detail);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Errmsg);
	TPLPUTLASTOUTVAR(__out, 2, &Ndetail);
	TPLPUTLASTOUTVAR(__out, 3, &Detail);
}
