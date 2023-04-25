#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_LOG_WAFER_BEGIN(void *_alg)
{
}

void
__LOG_WAFER_BEGIN(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;

	/* Local input/output variable definition */
	STRING	Session;
	STRING	Waferid;
	STRING	Time;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Waferid, _TYPES, 0, 0);
	TPLINITMEM(&Time, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Session);
	TPLGETDEBUGINVAR(_in, 1, &Waferid);
	TPLGETDEBUGINVAR(_in, 2, &Time);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	LOG_WAFER_BEGIN(Session,Waferid,Time);

	/* Algorithm output variable setting */
}
