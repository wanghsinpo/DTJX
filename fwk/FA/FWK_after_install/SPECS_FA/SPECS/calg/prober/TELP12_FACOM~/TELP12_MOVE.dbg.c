#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_TELP12_MOVE(void *_alg)
{
}

void
__TELP12_MOVE(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	REAL	DieX;
	REAL	DieY;
	REAL	ModX;
	REAL	ModY;
	STRING	Status;
	STRING	Error;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&DieX, _TYPER, 0, 0);
	TPLINITMEM(&DieY, _TYPER, 0, 0);
	TPLINITMEM(&ModX, _TYPER, 0, 0);
	TPLINITMEM(&ModY, _TYPER, 0, 0);
	TPLINITMEM(&Status, _TYPES, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &DieX);
	TPLGETDEBUGINVAR(_in, 1, &DieY);
	TPLGETDEBUGINVAR(_in, 2, &ModX);
	TPLGETDEBUGINVAR(_in, 3, &ModY);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);
	TPLGETDEBUGOUTVAR(_out, 1, &Error);

	/* Algorithm invocation */
	TELP12_MOVE(DieX,DieY,ModX,ModY,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
	TPLPUTDEBUGOUTVAR(_out, 1, &Error);
}
