#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_YIELDLOG_WAFEND(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;

	/* Local input/output variable definition */
	STRING	Filename;
	INTEGER	Dieyield;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Dieyield, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Filename);
	TPLGETEXECINVAR(_in, 1, &Dieyield);
	TPLPUTLASTINVAR(__in, 0, &Filename);
	TPLPUTLASTINVAR(__in, 1, &Dieyield);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	YIELDLOG_WAFEND(Filename,Dieyield);

	/* Algorithm output variable setting */
}

void
__YIELDLOG_WAFEND(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;

	/* Local input/output variable definition */
	STRING	Filename;
	INTEGER	Dieyield;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Dieyield, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Filename);
	TPLGETLASTINVAR(__in, 1, &Dieyield);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	YIELDLOG_WAFEND(Filename,Dieyield);

	/* Algorithm output variable setting */
}
