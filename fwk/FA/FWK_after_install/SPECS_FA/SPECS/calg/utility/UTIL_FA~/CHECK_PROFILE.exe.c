#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_CHECK_PROFILE(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Result;

	/* P-code pointer initialization */
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Result, _TYPEI, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Result);
	TPLPUTLASTOUTVAR(__out, 0, &Result);

	/* Algorithm invocation */
	CHECK_PROFILE(&Result);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Result);
	TPLPUTLASTOUTVAR(__out, 0, &Result);
}

void
__CHECK_PROFILE(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Result;

	/* P-code pointer initialization */
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Result, _TYPEI, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Result);

	/* Algorithm invocation */
	CHECK_PROFILE(&Result);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Result);
}
