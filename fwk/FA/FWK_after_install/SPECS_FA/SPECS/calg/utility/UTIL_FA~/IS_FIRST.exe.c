#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_IS_FIRST(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	First;

	/* P-code pointer initialization */
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&First, _TYPEI, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &First);
	TPLPUTLASTOUTVAR(__out, 0, &First);

	/* Algorithm invocation */
	IS_FIRST(&First);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &First);
	TPLPUTLASTOUTVAR(__out, 0, &First);
}

void
__IS_FIRST(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__out;

	/* Local input/output variable definition */
	INTEGER	First;

	/* P-code pointer initialization */
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&First, _TYPEI, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &First);

	/* Algorithm invocation */
	IS_FIRST(&First);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &First);
}
