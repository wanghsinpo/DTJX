#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_FA_READ_CARD(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	CardPath;
	STRING	CardType;
	STRING	CardName;
	REAL	TotalCount;
	REAL	LimitCount;
	INTEGER	Status;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&CardPath, _TYPES, 0, 0);
	TPLINITMEM(&CardType, _TYPES, 0, 0);
	TPLINITMEM(&CardName, _TYPES, 0, 0);
	TPLINITMEM(&TotalCount, _TYPER, 0, 0);
	TPLINITMEM(&LimitCount, _TYPER, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &CardPath);
	TPLPUTLASTINVAR(__in, 0, &CardPath);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &CardType);
	TPLGETEXECOUTVAR(_out, 1, &CardName);
	TPLGETEXECOUTVAR(_out, 2, &TotalCount);
	TPLGETEXECOUTVAR(_out, 3, &LimitCount);
	TPLGETEXECOUTVAR(_out, 4, &Status);
	TPLPUTLASTOUTVAR(__out, 0, &CardType);
	TPLPUTLASTOUTVAR(__out, 1, &CardName);
	TPLPUTLASTOUTVAR(__out, 2, &TotalCount);
	TPLPUTLASTOUTVAR(__out, 3, &LimitCount);
	TPLPUTLASTOUTVAR(__out, 4, &Status);

	/* Algorithm invocation */
	FA_READ_CARD(CardPath,&CardType,&CardName,&TotalCount,&LimitCount,&Status);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &CardType);
	TPLPUTEXECOUTVAR(_out, 1, &CardName);
	TPLPUTEXECOUTVAR(_out, 2, &TotalCount);
	TPLPUTEXECOUTVAR(_out, 3, &LimitCount);
	TPLPUTEXECOUTVAR(_out, 4, &Status);
	TPLPUTLASTOUTVAR(__out, 0, &CardType);
	TPLPUTLASTOUTVAR(__out, 1, &CardName);
	TPLPUTLASTOUTVAR(__out, 2, &TotalCount);
	TPLPUTLASTOUTVAR(__out, 3, &LimitCount);
	TPLPUTLASTOUTVAR(__out, 4, &Status);
}

void
__FA_READ_CARD(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	CardPath;
	STRING	CardType;
	STRING	CardName;
	REAL	TotalCount;
	REAL	LimitCount;
	INTEGER	Status;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&CardPath, _TYPES, 0, 0);
	TPLINITMEM(&CardType, _TYPES, 0, 0);
	TPLINITMEM(&CardName, _TYPES, 0, 0);
	TPLINITMEM(&TotalCount, _TYPER, 0, 0);
	TPLINITMEM(&LimitCount, _TYPER, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &CardPath);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &CardType);
	TPLGETLASTOUTVAR(__out, 1, &CardName);
	TPLGETLASTOUTVAR(__out, 2, &TotalCount);
	TPLGETLASTOUTVAR(__out, 3, &LimitCount);
	TPLGETLASTOUTVAR(__out, 4, &Status);

	/* Algorithm invocation */
	FA_READ_CARD(CardPath,&CardType,&CardName,&TotalCount,&LimitCount,&Status);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &CardType);
	TPLPUTLASTOUTVAR(__out, 1, &CardName);
	TPLPUTLASTOUTVAR(__out, 2, &TotalCount);
	TPLPUTLASTOUTVAR(__out, 3, &LimitCount);
	TPLPUTLASTOUTVAR(__out, 4, &Status);
}
