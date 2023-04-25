#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_SET_SAMELEN(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Original;
	STRING	Reference;
	STRING	Modified;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Original, _TYPES, 0, 0);
	TPLINITMEM(&Reference, _TYPES, 0, 0);
	TPLINITMEM(&Modified, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Original);
	TPLGETEXECINVAR(_in, 1, &Reference);
	TPLPUTLASTINVAR(__in, 0, &Original);
	TPLPUTLASTINVAR(__in, 1, &Reference);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Modified);
	TPLPUTLASTOUTVAR(__out, 0, &Modified);

	/* Algorithm invocation */
	SET_SAMELEN(Original,Reference,&Modified);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Modified);
	TPLPUTLASTOUTVAR(__out, 0, &Modified);
}

void
__SET_SAMELEN(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Original;
	STRING	Reference;
	STRING	Modified;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Original, _TYPES, 0, 0);
	TPLINITMEM(&Reference, _TYPES, 0, 0);
	TPLINITMEM(&Modified, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Original);
	TPLGETLASTINVAR(__in, 1, &Reference);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Modified);

	/* Algorithm invocation */
	SET_SAMELEN(Original,Reference,&Modified);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Modified);
}
