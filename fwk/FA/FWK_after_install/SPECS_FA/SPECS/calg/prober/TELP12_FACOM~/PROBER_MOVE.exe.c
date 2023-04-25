#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_PROBER_MOVE(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	REAL	DieX;
	REAL	DieY;
	REAL	ModX;
	REAL	ModY;
	STRING	Status;
	STRING	Error;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&DieX, _TYPER, 0, 0);
	TPLINITMEM(&DieY, _TYPER, 0, 0);
	TPLINITMEM(&ModX, _TYPER, 0, 0);
	TPLINITMEM(&ModY, _TYPER, 0, 0);
	TPLINITMEM(&Status, _TYPES, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &DieX);
	TPLGETEXECINVAR(_in, 1, &DieY);
	TPLGETEXECINVAR(_in, 2, &ModX);
	TPLGETEXECINVAR(_in, 3, &ModY);
	TPLPUTLASTINVAR(__in, 0, &DieX);
	TPLPUTLASTINVAR(__in, 1, &DieY);
	TPLPUTLASTINVAR(__in, 2, &ModX);
	TPLPUTLASTINVAR(__in, 3, &ModY);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Status);
	TPLGETEXECOUTVAR(_out, 1, &Error);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Error);

	/* Algorithm invocation */
	PROBER_MOVE(DieX,DieY,ModX,ModY,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Status);
	TPLPUTEXECOUTVAR(_out, 1, &Error);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Error);
}

void
__PROBER_MOVE(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	REAL	DieX;
	REAL	DieY;
	REAL	ModX;
	REAL	ModY;
	STRING	Status;
	STRING	Error;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&DieX, _TYPER, 0, 0);
	TPLINITMEM(&DieY, _TYPER, 0, 0);
	TPLINITMEM(&ModX, _TYPER, 0, 0);
	TPLINITMEM(&ModY, _TYPER, 0, 0);
	TPLINITMEM(&Status, _TYPES, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &DieX);
	TPLGETLASTINVAR(__in, 1, &DieY);
	TPLGETLASTINVAR(__in, 2, &ModX);
	TPLGETLASTINVAR(__in, 3, &ModY);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Status);
	TPLGETLASTOUTVAR(__out, 1, &Error);

	/* Algorithm invocation */
	PROBER_MOVE(DieX,DieY,ModX,ModY,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Error);
}
