#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FA_UPDATE_CARD(void *_alg)
{
}

void
__FA_UPDATE_CARD(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	CardPath;
	STRING	CardName;
	REAL	TotalCount;
	INTEGER	Status;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&CardPath, _TYPES, 0, 0);
	TPLINITMEM(&CardName, _TYPES, 0, 0);
	TPLINITMEM(&TotalCount, _TYPER, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &CardPath);
	TPLGETDEBUGINVAR(_in, 1, &CardName);
	TPLGETDEBUGINVAR(_in, 2, &TotalCount);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);

	/* Algorithm invocation */
	FA_UPDATE_CARD(CardPath,CardName,TotalCount,&Status);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
}
