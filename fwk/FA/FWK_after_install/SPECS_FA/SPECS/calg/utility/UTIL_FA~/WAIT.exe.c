#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_WAIT(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;

	/* Local input/output variable definition */
	REAL	Wait;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Wait, _TYPER, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Wait);
	TPLPUTLASTINVAR(__in, 0, &Wait);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	WAIT(Wait);

	/* Algorithm output variable setting */
}

void
__WAIT(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;

	/* Local input/output variable definition */
	REAL	Wait;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Wait, _TYPER, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Wait);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	WAIT(Wait);

	/* Algorithm output variable setting */
}
