#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_SETUSRBIN_LPBGN(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;

	/* Local input/output variable definition */
	INTEGER	Waftgt;
	INTEGER	Lottgt;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Waftgt, _TYPEI, 0, 0);
	TPLINITMEM(&Lottgt, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Waftgt);
	TPLGETEXECINVAR(_in, 1, &Lottgt);
	TPLPUTLASTINVAR(__in, 0, &Waftgt);
	TPLPUTLASTINVAR(__in, 1, &Lottgt);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	SETUSRBIN_LPBGN(Waftgt,Lottgt);

	/* Algorithm output variable setting */
}

void
__SETUSRBIN_LPBGN(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;

	/* Local input/output variable definition */
	INTEGER	Waftgt;
	INTEGER	Lottgt;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Waftgt, _TYPEI, 0, 0);
	TPLINITMEM(&Lottgt, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Waftgt);
	TPLGETLASTINVAR(__in, 1, &Lottgt);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	SETUSRBIN_LPBGN(Waftgt,Lottgt);

	/* Algorithm output variable setting */
}
