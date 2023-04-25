#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_PRBCOUNT(void *_alg)
{
}

void
__PRBCOUNT(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Count;

	/* Data pointer initialization */
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Count, _TYPEI, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Count);

	/* Algorithm invocation */
	PRBCOUNT(&Count);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Count);
}
