#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_SETUSRBIN_LPBGN(void *_alg)
{
}

void
__SETUSRBIN_LPBGN(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;

	/* Local input/output variable definition */
	INTEGER	Waftgt;
	INTEGER	Lottgt;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Waftgt, _TYPEI, 0, 0);
	TPLINITMEM(&Lottgt, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Waftgt);
	TPLGETDEBUGINVAR(_in, 1, &Lottgt);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	SETUSRBIN_LPBGN(Waftgt,Lottgt);

	/* Algorithm output variable setting */
}
