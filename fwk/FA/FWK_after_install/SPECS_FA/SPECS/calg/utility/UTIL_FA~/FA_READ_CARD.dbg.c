#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FA_READ_CARD(void *_alg)
{
}

void
__FA_READ_CARD(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	CardPath;
	STRING	CardType;
	STRING	CardName;
	REAL	TotalCount;
	REAL	LimitCount;
	INTEGER	Status;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&CardPath, _TYPES, 0, 0);
	TPLINITMEM(&CardType, _TYPES, 0, 0);
	TPLINITMEM(&CardName, _TYPES, 0, 0);
	TPLINITMEM(&TotalCount, _TYPER, 0, 0);
	TPLINITMEM(&LimitCount, _TYPER, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &CardPath);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &CardType);
	TPLGETDEBUGOUTVAR(_out, 1, &CardName);
	TPLGETDEBUGOUTVAR(_out, 2, &TotalCount);
	TPLGETDEBUGOUTVAR(_out, 3, &LimitCount);
	TPLGETDEBUGOUTVAR(_out, 4, &Status);

	/* Algorithm invocation */
	FA_READ_CARD(CardPath,&CardType,&CardName,&TotalCount,&LimitCount,&Status);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &CardType);
	TPLPUTDEBUGOUTVAR(_out, 1, &CardName);
	TPLPUTDEBUGOUTVAR(_out, 2, &TotalCount);
	TPLPUTDEBUGOUTVAR(_out, 3, &LimitCount);
	TPLPUTDEBUGOUTVAR(_out, 4, &Status);
}
