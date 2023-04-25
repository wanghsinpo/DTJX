#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_PRBINFO(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Index;
	INTEGER	Pad;
	INTEGER	Pin;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Index, _TYPEI, 0, 0);
	TPLINITMEM(&Pad, _TYPEI, 0, 0);
	TPLINITMEM(&Pin, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Index);
	TPLPUTLASTINVAR(__in, 0, &Index);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Pad);
	TPLGETEXECOUTVAR(_out, 1, &Pin);
	TPLPUTLASTOUTVAR(__out, 0, &Pad);
	TPLPUTLASTOUTVAR(__out, 1, &Pin);

	/* Algorithm invocation */
	PRBINFO(Index,&Pad,&Pin);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Pad);
	TPLPUTEXECOUTVAR(_out, 1, &Pin);
	TPLPUTLASTOUTVAR(__out, 0, &Pad);
	TPLPUTLASTOUTVAR(__out, 1, &Pin);
}

void
__PRBINFO(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Index;
	INTEGER	Pad;
	INTEGER	Pin;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Index, _TYPEI, 0, 0);
	TPLINITMEM(&Pad, _TYPEI, 0, 0);
	TPLINITMEM(&Pin, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Index);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Pad);
	TPLGETLASTOUTVAR(__out, 1, &Pin);

	/* Algorithm invocation */
	PRBINFO(Index,&Pad,&Pin);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Pad);
	TPLPUTLASTOUTVAR(__out, 1, &Pin);
}
