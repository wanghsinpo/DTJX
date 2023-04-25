#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_LOG_WAFER_END(void *_alg)
{
}

void
__LOG_WAFER_END(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;

	/* Local input/output variable definition */
	STRING	Session;
	STRING	State;
	INTEGER	Result;
	STRING	Time;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&State, _TYPES, 0, 0);
	TPLINITMEM(&Result, _TYPEI, 0, 0);
	TPLINITMEM(&Time, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Session);
	TPLGETDEBUGINVAR(_in, 1, &State);
	TPLGETDEBUGINVAR(_in, 2, &Result);
	TPLGETDEBUGINVAR(_in, 3, &Time);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	LOG_WAFER_END(Session,State,Result,Time);

	/* Algorithm output variable setting */
}
