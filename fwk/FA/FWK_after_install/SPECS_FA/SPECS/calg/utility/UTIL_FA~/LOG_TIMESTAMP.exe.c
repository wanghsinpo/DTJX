#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_LOG_TIMESTAMP(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Timestamp;

	/* P-code pointer initialization */
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Timestamp, _TYPES, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Timestamp);
	TPLPUTLASTOUTVAR(__out, 0, &Timestamp);

	/* Algorithm invocation */
	LOG_TIMESTAMP(&Timestamp);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Timestamp);
	TPLPUTLASTOUTVAR(__out, 0, &Timestamp);
}

void
__LOG_TIMESTAMP(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__out;

	/* Local input/output variable definition */
	STRING	Timestamp;

	/* P-code pointer initialization */
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Timestamp, _TYPES, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Timestamp);

	/* Algorithm invocation */
	LOG_TIMESTAMP(&Timestamp);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Timestamp);
}
