#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_PROBER_INITIAL(void *_alg)
{
}

void
__PROBER_INITIAL(void *_alg)
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
	REAL	StepX;
	REAL	StepY;
	INTEGER	Coord;
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
	TPLINITMEM(&StepX, _TYPER, 0, 0);
	TPLINITMEM(&StepY, _TYPER, 0, 0);
	TPLINITMEM(&Coord, _TYPEI, 0, 0);
	TPLINITMEM(&Status, _TYPES, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &DieX);
	TPLGETDEBUGINVAR(_in, 1, &DieY);
	TPLGETDEBUGINVAR(_in, 2, &ModX);
	TPLGETDEBUGINVAR(_in, 3, &ModY);
	TPLGETDEBUGINVAR(_in, 4, &StepX);
	TPLGETDEBUGINVAR(_in, 5, &StepY);
	TPLGETDEBUGINVAR(_in, 6, &Coord);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);
	TPLGETDEBUGOUTVAR(_out, 1, &Error);

	/* Algorithm invocation */
	PROBER_INITIAL(DieX,DieY,ModX,ModY,StepX,StepY,Coord,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
	TPLPUTDEBUGOUTVAR(_out, 1, &Error);
}
