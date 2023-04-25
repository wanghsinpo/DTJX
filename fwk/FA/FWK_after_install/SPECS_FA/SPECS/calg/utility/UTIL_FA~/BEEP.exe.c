#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_BEEP(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;

	/* Local input/output variable definition */
	REAL	Freq;
	REAL	Dur;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Freq, _TYPER, 0, 0);
	TPLINITMEM(&Dur, _TYPER, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Freq);
	TPLGETEXECINVAR(_in, 1, &Dur);
	TPLPUTLASTINVAR(__in, 0, &Freq);
	TPLPUTLASTINVAR(__in, 1, &Dur);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	BEEP(Freq,Dur);

	/* Algorithm output variable setting */
}

void
__BEEP(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;

	/* Local input/output variable definition */
	REAL	Freq;
	REAL	Dur;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Freq, _TYPER, 0, 0);
	TPLINITMEM(&Dur, _TYPER, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Freq);
	TPLGETLASTINVAR(__in, 1, &Dur);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	BEEP(Freq,Dur);

	/* Algorithm output variable setting */
}
