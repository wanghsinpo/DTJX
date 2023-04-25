#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_JDG_DIE_AT_POS2(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Die_pos;
	INTEGER	Tgt_yld;
	INTEGER	Last;
	INTEGER	Critical;
	INTEGER	Ignore;
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
	TPLINITMEM(&Die_pos, _TYPEI, 0, 0);
	TPLINITMEM(&Tgt_yld, _TYPEI, 0, 0);
	TPLINITMEM(&Last, _TYPEI, 0, 0);
	TPLINITMEM(&Critical, _TYPEI, 0, 0);
	TPLINITMEM(&Ignore, _TYPEI, 0, 0);
	TPLINITMEM(&Jdg, _TYPEI, 0, 0);
	TPLINITMEM(&Yld, _TYPER, 0, 0);
	TPLINITMEM(&Pass_cnt, _TYPEI, 0, 0);
	TPLINITMEM(&Fail_cnt, _TYPEI, 0, 0);
	TPLINITMEM(&Total_cnt, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Die_pos);
	TPLGETEXECINVAR(_in, 1, &Tgt_yld);
	TPLGETEXECINVAR(_in, 2, &Last);
	TPLGETEXECINVAR(_in, 3, &Critical);
	TPLGETEXECINVAR(_in, 4, &Ignore);
	TPLPUTLASTINVAR(__in, 0, &Die_pos);
	TPLPUTLASTINVAR(__in, 1, &Tgt_yld);
	TPLPUTLASTINVAR(__in, 2, &Last);
	TPLPUTLASTINVAR(__in, 3, &Critical);
	TPLPUTLASTINVAR(__in, 4, &Ignore);

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
	JDG_DIE_AT_POS2(Die_pos,Tgt_yld,Last,Critical,Ignore,&Jdg,&Yld,&Pass_cnt,&Fail_cnt,&Total_cnt);

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
__JDG_DIE_AT_POS2(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Die_pos;
	INTEGER	Tgt_yld;
	INTEGER	Last;
	INTEGER	Critical;
	INTEGER	Ignore;
	INTEGER	Jdg;
	REAL	Yld;
	INTEGER	Pass_cnt;
	INTEGER	Fail_cnt;
	INTEGER	Total_cnt;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Die_pos, _TYPEI, 0, 0);
	TPLINITMEM(&Tgt_yld, _TYPEI, 0, 0);
	TPLINITMEM(&Last, _TYPEI, 0, 0);
	TPLINITMEM(&Critical, _TYPEI, 0, 0);
	TPLINITMEM(&Ignore, _TYPEI, 0, 0);
	TPLINITMEM(&Jdg, _TYPEI, 0, 0);
	TPLINITMEM(&Yld, _TYPER, 0, 0);
	TPLINITMEM(&Pass_cnt, _TYPEI, 0, 0);
	TPLINITMEM(&Fail_cnt, _TYPEI, 0, 0);
	TPLINITMEM(&Total_cnt, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Die_pos);
	TPLGETLASTINVAR(__in, 1, &Tgt_yld);
	TPLGETLASTINVAR(__in, 2, &Last);
	TPLGETLASTINVAR(__in, 3, &Critical);
	TPLGETLASTINVAR(__in, 4, &Ignore);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Jdg);
	TPLGETLASTOUTVAR(__out, 1, &Yld);
	TPLGETLASTOUTVAR(__out, 2, &Pass_cnt);
	TPLGETLASTOUTVAR(__out, 3, &Fail_cnt);
	TPLGETLASTOUTVAR(__out, 4, &Total_cnt);

	/* Algorithm invocation */
	JDG_DIE_AT_POS2(Die_pos,Tgt_yld,Last,Critical,Ignore,&Jdg,&Yld,&Pass_cnt,&Fail_cnt,&Total_cnt);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Jdg);
	TPLPUTLASTOUTVAR(__out, 1, &Yld);
	TPLPUTLASTOUTVAR(__out, 2, &Pass_cnt);
	TPLPUTLASTOUTVAR(__out, 3, &Fail_cnt);
	TPLPUTLASTOUTVAR(__out, 4, &Total_cnt);
}
