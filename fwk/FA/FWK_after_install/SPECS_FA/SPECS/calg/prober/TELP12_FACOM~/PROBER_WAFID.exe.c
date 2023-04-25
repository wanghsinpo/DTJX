#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_PROBER_WAFID(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Wafid;
	STRING	Status;
	STRING	Error;

	/* P-code pointer initialization */
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Wafid, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPES, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Wafid);
	TPLGETEXECOUTVAR(_out, 1, &Status);
	TPLGETEXECOUTVAR(_out, 2, &Error);
	TPLPUTLASTOUTVAR(__out, 0, &Wafid);
	TPLPUTLASTOUTVAR(__out, 1, &Status);
	TPLPUTLASTOUTVAR(__out, 2, &Error);

	/* Algorithm invocation */
	PROBER_WAFID(&Wafid,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Wafid);
	TPLPUTEXECOUTVAR(_out, 1, &Status);
	TPLPUTEXECOUTVAR(_out, 2, &Error);
	TPLPUTLASTOUTVAR(__out, 0, &Wafid);
	TPLPUTLASTOUTVAR(__out, 1, &Status);
	TPLPUTLASTOUTVAR(__out, 2, &Error);
}

void
__PROBER_WAFID(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__out;

	/* Local input/output variable definition */
	STRING	Wafid;
	STRING	Status;
	STRING	Error;

	/* P-code pointer initialization */
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Wafid, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPES, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Wafid);
	TPLGETLASTOUTVAR(__out, 1, &Status);
	TPLGETLASTOUTVAR(__out, 2, &Error);

	/* Algorithm invocation */
	PROBER_WAFID(&Wafid,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Wafid);
	TPLPUTLASTOUTVAR(__out, 1, &Status);
	TPLPUTLASTOUTVAR(__out, 2, &Error);
}
