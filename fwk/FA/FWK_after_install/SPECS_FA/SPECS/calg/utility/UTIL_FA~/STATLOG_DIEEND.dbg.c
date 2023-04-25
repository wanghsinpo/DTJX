#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_STATLOG_DIEEND(void *_alg)
{
}

void
__STATLOG_DIEEND(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;

	/* Local input/output variable definition */
	STRING	Filename;
	INTEGER	Mode;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Mode, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Filename);
	TPLGETDEBUGINVAR(_in, 1, &Mode);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	STATLOG_DIEEND(Filename,Mode);

	/* Algorithm output variable setting */
}
