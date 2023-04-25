#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_GEM_GETCMD(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Cmd;
	STRING	Rply;
	STRING	Parms[500];

	/* P-code pointer initialization */
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Cmd, _TYPES, 0, 0);
	TPLINITMEM(&Rply, _TYPES, 0, 0);
	TPLINITMEM(&Parms, _TYPES, 500, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Cmd);
	TPLGETEXECOUTVAR(_out, 1, &Rply);
	TPLGETEXECOUTVAR(_out, 2, &Parms);
	TPLPUTLASTOUTVAR(__out, 0, &Cmd);
	TPLPUTLASTOUTVAR(__out, 1, &Rply);
	TPLPUTLASTOUTVAR(__out, 2, &Parms);

	/* Algorithm invocation */
	GEM_GETCMD(&Cmd,&Rply,&Parms);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Cmd);
	TPLPUTEXECOUTVAR(_out, 1, &Rply);
	TPLPUTEXECOUTVAR(_out, 2, &Parms);
	TPLPUTLASTOUTVAR(__out, 0, &Cmd);
	TPLPUTLASTOUTVAR(__out, 1, &Rply);
	TPLPUTLASTOUTVAR(__out, 2, &Parms);
}

void
__GEM_GETCMD(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__out;

	/* Local input/output variable definition */
	STRING	Cmd;
	STRING	Rply;
	STRING	Parms[500];

	/* P-code pointer initialization */
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Cmd, _TYPES, 0, 0);
	TPLINITMEM(&Rply, _TYPES, 0, 0);
	TPLINITMEM(&Parms, _TYPES, 500, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Cmd);
	TPLGETLASTOUTVAR(__out, 1, &Rply);
	TPLGETLASTOUTVAR(__out, 2, &Parms);

	/* Algorithm invocation */
	GEM_GETCMD(&Cmd,&Rply,&Parms);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Cmd);
	TPLPUTLASTOUTVAR(__out, 1, &Rply);
	TPLPUTLASTOUTVAR(__out, 2, &Parms);
}
