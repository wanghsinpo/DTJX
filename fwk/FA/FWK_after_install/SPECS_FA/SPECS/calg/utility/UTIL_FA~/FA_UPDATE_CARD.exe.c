#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_FA_UPDATE_CARD(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	CardPath;
	STRING	CardName;
	REAL	TotalCount;
	INTEGER	Status;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&CardPath, _TYPES, 0, 0);
	TPLINITMEM(&CardName, _TYPES, 0, 0);
	TPLINITMEM(&TotalCount, _TYPER, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &CardPath);
	TPLGETEXECINVAR(_in, 1, &CardName);
	TPLGETEXECINVAR(_in, 2, &TotalCount);
	TPLPUTLASTINVAR(__in, 0, &CardPath);
	TPLPUTLASTINVAR(__in, 1, &CardName);
	TPLPUTLASTINVAR(__in, 2, &TotalCount);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 0, &Status);

	/* Algorithm invocation */
	FA_UPDATE_CARD(CardPath,CardName,TotalCount,&Status);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
}

void
__FA_UPDATE_CARD(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	CardPath;
	STRING	CardName;
	REAL	TotalCount;
	INTEGER	Status;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&CardPath, _TYPES, 0, 0);
	TPLINITMEM(&CardName, _TYPES, 0, 0);
	TPLINITMEM(&TotalCount, _TYPER, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &CardPath);
	TPLGETLASTINVAR(__in, 1, &CardName);
	TPLGETLASTINVAR(__in, 2, &TotalCount);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Status);

	/* Algorithm invocation */
	FA_UPDATE_CARD(CardPath,CardName,TotalCount,&Status);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Status);
}
