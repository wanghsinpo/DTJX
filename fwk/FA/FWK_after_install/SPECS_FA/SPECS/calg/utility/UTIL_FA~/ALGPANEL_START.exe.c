#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_ALGPANEL_START(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;

	/* Local input/output variable definition */
	INTEGER	Mode;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Mode, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Mode);
	TPLPUTLASTINVAR(__in, 0, &Mode);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	ALGPANEL_START(Mode);

	/* Algorithm output variable setting */
}

void
__ALGPANEL_START(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;

	/* Local input/output variable definition */
	INTEGER	Mode;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Mode, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Mode);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	ALGPANEL_START(Mode);

	/* Algorithm output variable setting */
}
