#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_RCP_EXEC_CMD(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Cmd;
	STRING	Result;
	INTEGER	Status;
	STRING	Errmsg;
	INTEGER	Ndetail;
	STRING	Detail[10];
	INTEGER	Cmd_ret;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Cmd, _TYPES, 0, 0);
	TPLINITMEM(&Result, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Errmsg, _TYPES, 0, 0);
	TPLINITMEM(&Ndetail, _TYPEI, 0, 0);
	TPLINITMEM(&Detail, _TYPES, 10, 0);
	TPLINITMEM(&Cmd_ret, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Cmd);
	TPLGETEXECINVAR(_in, 1, &Result);
	TPLPUTLASTINVAR(__in, 0, &Cmd);
	TPLPUTLASTINVAR(__in, 1, &Result);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Status);
	TPLGETEXECOUTVAR(_out, 1, &Errmsg);
	TPLGETEXECOUTVAR(_out, 2, &Ndetail);
	TPLGETEXECOUTVAR(_out, 3, &Detail);
	TPLGETEXECOUTVAR(_out, 4, &Cmd_ret);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Errmsg);
	TPLPUTLASTOUTVAR(__out, 2, &Ndetail);
	TPLPUTLASTOUTVAR(__out, 3, &Detail);
	TPLPUTLASTOUTVAR(__out, 4, &Cmd_ret);

	/* Algorithm invocation */
	RCP_EXEC_CMD(Cmd,Result,&Status,&Errmsg,&Ndetail,&Detail,&Cmd_ret);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Status);
	TPLPUTEXECOUTVAR(_out, 1, &Errmsg);
	TPLPUTEXECOUTVAR(_out, 2, &Ndetail);
	TPLPUTEXECOUTVAR(_out, 3, &Detail);
	TPLPUTEXECOUTVAR(_out, 4, &Cmd_ret);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Errmsg);
	TPLPUTLASTOUTVAR(__out, 2, &Ndetail);
	TPLPUTLASTOUTVAR(__out, 3, &Detail);
	TPLPUTLASTOUTVAR(__out, 4, &Cmd_ret);
}

void
__RCP_EXEC_CMD(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Cmd;
	STRING	Result;
	INTEGER	Status;
	STRING	Errmsg;
	INTEGER	Ndetail;
	STRING	Detail[10];
	INTEGER	Cmd_ret;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Cmd, _TYPES, 0, 0);
	TPLINITMEM(&Result, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Errmsg, _TYPES, 0, 0);
	TPLINITMEM(&Ndetail, _TYPEI, 0, 0);
	TPLINITMEM(&Detail, _TYPES, 10, 0);
	TPLINITMEM(&Cmd_ret, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Cmd);
	TPLGETLASTINVAR(__in, 1, &Result);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Status);
	TPLGETLASTOUTVAR(__out, 1, &Errmsg);
	TPLGETLASTOUTVAR(__out, 2, &Ndetail);
	TPLGETLASTOUTVAR(__out, 3, &Detail);
	TPLGETLASTOUTVAR(__out, 4, &Cmd_ret);

	/* Algorithm invocation */
	RCP_EXEC_CMD(Cmd,Result,&Status,&Errmsg,&Ndetail,&Detail,&Cmd_ret);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Errmsg);
	TPLPUTLASTOUTVAR(__out, 2, &Ndetail);
	TPLPUTLASTOUTVAR(__out, 3, &Detail);
	TPLPUTLASTOUTVAR(__out, 4, &Cmd_ret);
}
