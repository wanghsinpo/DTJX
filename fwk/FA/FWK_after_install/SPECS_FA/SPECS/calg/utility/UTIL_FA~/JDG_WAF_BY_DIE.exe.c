#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_JDG_WAF_BY_DIE(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Tgt_wafyld;
	INTEGER	Tgt_dieyld;
	INTEGER	Last;
	INTEGER	Jdg;
	REAL	Yld;
	INTEGER	Pass_cnt;
	INTEGER	Fail_cnt;
	INTEGER	Total_cnt;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Tgt_wafyld, _TYPEI, 0, 0);
	TPLINITMEM(&Tgt_dieyld, _TYPEI, 0, 0);
	TPLINITMEM(&Last, _TYPEI, 0, 0);
	TPLINITMEM(&Jdg, _TYPEI, 0, 0);
	TPLINITMEM(&Yld, _TYPER, 0, 0);
	TPLINITMEM(&Pass_cnt, _TYPEI, 0, 0);
	TPLINITMEM(&Fail_cnt, _TYPEI, 0, 0);
	TPLINITMEM(&Total_cnt, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Tgt_wafyld);
	TPLGETEXECINVAR(_in, 1, &Tgt_dieyld);
	TPLGETEXECINVAR(_in, 2, &Last);
	TPLPUTLASTINVAR(__in, 0, &Tgt_wafyld);
	TPLPUTLASTINVAR(__in, 1, &Tgt_dieyld);
	TPLPUTLASTINVAR(__in, 2, &Last);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Jdg);
	TPLGETEXECOUTVAR(_out, 1, &Yld);
	TPLGETEXECOUTVAR(_out, 2, &Pass_cnt);
	TPLGETEXECOUTVAR(_out, 3, &Fail_cnt);
	TPLGETEXECOUTVAR(_out, 4, &Total_cnt);
	TPLPUTLASTOUTVAR(__out, 0, &Jdg);
	TPLPUTLASTOUTVAR(__out, 1, &Yld);
	TPLPUTLASTOUTVAR(__out, 2, &Pass_cnt);
	TPLPUTLASTOUTVAR(__out, 3, &Fail_cnt);
	TPLPUTLASTOUTVAR(__out, 4, &Total_cnt);

	/* Algorithm invocation */
	JDG_WAF_BY_DIE(Tgt_wafyld,Tgt_dieyld,Last,&Jdg,&Yld,&Pass_cnt,&Fail_cnt,&Total_cnt);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Jdg);
	TPLPUTEXECOUTVAR(_out, 1, &Yld);
	TPLPUTEXECOUTVAR(_out, 2, &Pass_cnt);
	TPLPUTEXECOUTVAR(_out, 3, &Fail_cnt);
	TPLPUTEXECOUTVAR(_out, 4, &Total_cnt);
	TPLPUTLASTOUTVAR(__out, 0, &Jdg);
	TPLPUTLASTOUTVAR(__out, 1, &Yld);
	TPLPUTLASTOUTVAR(__out, 2, &Pass_cnt);
	TPLPUTLASTOUTVAR(__out, 3, &Fail_cnt);
	TPLPUTLASTOUTVAR(__out, 4, &Total_cnt);
}

void
__JDG_WAF_BY_DIE(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Tgt_wafyld;
	INTEGER	Tgt_dieyld;
	INTEGER	Last;
	INTEGER	Jdg;
	REAL	Yld;
	INTEGER	Pass_cnt;
	INTEGER	Fail_cnt;
	INTEGER	Total_cnt;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Tgt_wafyld, _TYPEI, 0, 0);
	TPLINITMEM(&Tgt_dieyld, _TYPEI, 0, 0);
	TPLINITMEM(&Last, _TYPEI, 0, 0);
	TPLINITMEM(&Jdg, _TYPEI, 0, 0);
	TPLINITMEM(&Yld, _TYPER, 0, 0);
	TPLINITMEM(&Pass_cnt, _TYPEI, 0, 0);
	TPLINITMEM(&Fail_cnt, _TYPEI, 0, 0);
	TPLINITMEM(&Total_cnt, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Tgt_wafyld);
	TPLGETLASTINVAR(__in, 1, &Tgt_dieyld);
	TPLGETLASTINVAR(__in, 2, &Last);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Jdg);
	TPLGETLASTOUTVAR(__out, 1, &Yld);
	TPLGETLASTOUTVAR(__out, 2, &Pass_cnt);
	TPLGETLASTOUTVAR(__out, 3, &Fail_cnt);
	TPLGETLASTOUTVAR(__out, 4, &Total_cnt);

	/* Algorithm invocation */
	JDG_WAF_BY_DIE(Tgt_wafyld,Tgt_dieyld,Last,&Jdg,&Yld,&Pass_cnt,&Fail_cnt,&Total_cnt);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Jdg);
	TPLPUTLASTOUTVAR(__out, 1, &Yld);
	TPLPUTLASTOUTVAR(__out, 2, &Pass_cnt);
	TPLPUTLASTOUTVAR(__out, 3, &Fail_cnt);
	TPLPUTLASTOUTVAR(__out, 4, &Total_cnt);
}
