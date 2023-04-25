#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_STRING_TIME(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	REAL	Time;
	STRING	Symbol;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Time, _TYPER, 0, 0);
	TPLINITMEM(&Symbol, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Time);
	TPLPUTLASTINVAR(__in, 0, &Time);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Symbol);
	TPLPUTLASTOUTVAR(__out, 0, &Symbol);

	/* Algorithm invocation */
	STRING_TIME(Time,&Symbol);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Symbol);
	TPLPUTLASTOUTVAR(__out, 0, &Symbol);
}

void
__STRING_TIME(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	REAL	Time;
	STRING	Symbol;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Time, _TYPER, 0, 0);
	TPLINITMEM(&Symbol, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Time);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Symbol);

	/* Algorithm invocation */
	STRING_TIME(Time,&Symbol);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Symbol);
}
