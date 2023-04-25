#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_STRING_SPLIT(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Src;
	STRING	Del;
	STRING	Elem[128];
	INTEGER	Count;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Src, _TYPES, 0, 0);
	TPLINITMEM(&Del, _TYPES, 0, 0);
	TPLINITMEM(&Elem, _TYPES, 128, 0);
	TPLINITMEM(&Count, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Src);
	TPLGETEXECINVAR(_in, 1, &Del);
	TPLPUTLASTINVAR(__in, 0, &Src);
	TPLPUTLASTINVAR(__in, 1, &Del);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Elem);
	TPLGETEXECOUTVAR(_out, 1, &Count);
	TPLPUTLASTOUTVAR(__out, 0, &Elem);
	TPLPUTLASTOUTVAR(__out, 1, &Count);

	/* Algorithm invocation */
	STRING_SPLIT(Src,Del,&Elem,&Count);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Elem);
	TPLPUTEXECOUTVAR(_out, 1, &Count);
	TPLPUTLASTOUTVAR(__out, 0, &Elem);
	TPLPUTLASTOUTVAR(__out, 1, &Count);
}

void
__STRING_SPLIT(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Src;
	STRING	Del;
	STRING	Elem[128];
	INTEGER	Count;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Src, _TYPES, 0, 0);
	TPLINITMEM(&Del, _TYPES, 0, 0);
	TPLINITMEM(&Elem, _TYPES, 128, 0);
	TPLINITMEM(&Count, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Src);
	TPLGETLASTINVAR(__in, 1, &Del);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Elem);
	TPLGETLASTOUTVAR(__out, 1, &Count);

	/* Algorithm invocation */
	STRING_SPLIT(Src,Del,&Elem,&Count);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Elem);
	TPLPUTLASTOUTVAR(__out, 1, &Count);
}
