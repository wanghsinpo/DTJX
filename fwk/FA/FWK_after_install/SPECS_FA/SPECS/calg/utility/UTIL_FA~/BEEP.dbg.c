#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_BEEP(void *_alg)
{
}

void
__BEEP(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;

	/* Local input/output variable definition */
	REAL	Freq;
	REAL	Dur;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Freq, _TYPER, 0, 0);
	TPLINITMEM(&Dur, _TYPER, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Freq);
	TPLGETDEBUGINVAR(_in, 1, &Dur);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	BEEP(Freq,Dur);

	/* Algorithm output variable setting */
}
