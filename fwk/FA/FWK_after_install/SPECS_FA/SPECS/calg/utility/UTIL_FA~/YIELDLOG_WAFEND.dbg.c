#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_YIELDLOG_WAFEND(void *_alg)
{
}

void
__YIELDLOG_WAFEND(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;

	/* Local input/output variable definition */
	STRING	Filename;
	INTEGER	Dieyield;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Dieyield, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Filename);
	TPLGETDEBUGINVAR(_in, 1, &Dieyield);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	YIELDLOG_WAFEND(Filename,Dieyield);

	/* Algorithm output variable setting */
}
