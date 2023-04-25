#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_IS_CALG(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Lang;

	/* P-code pointer initialization */
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Lang, _TYPEI, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Lang);
	TPLPUTLASTOUTVAR(__out, 0, &Lang);

	/* Algorithm invocation */
	IS_CALG(&Lang);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Lang);
	TPLPUTLASTOUTVAR(__out, 0, &Lang);
}

void
__IS_CALG(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Lang;

	/* P-code pointer initialization */
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Lang, _TYPEI, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Lang);

	/* Algorithm invocation */
	IS_CALG(&Lang);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Lang);
}
