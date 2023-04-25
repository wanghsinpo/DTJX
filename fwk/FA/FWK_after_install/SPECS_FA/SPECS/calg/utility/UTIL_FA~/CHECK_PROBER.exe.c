#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_CHECK_PROBER(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Symbol;
	STRING	Vendor;
	STRING	Model;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Symbol, _TYPES, 0, 0);
	TPLINITMEM(&Vendor, _TYPES, 0, 0);
	TPLINITMEM(&Model, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Symbol);
	TPLPUTLASTINVAR(__in, 0, &Symbol);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Vendor);
	TPLGETEXECOUTVAR(_out, 1, &Model);
	TPLPUTLASTOUTVAR(__out, 0, &Vendor);
	TPLPUTLASTOUTVAR(__out, 1, &Model);

	/* Algorithm invocation */
	CHECK_PROBER(Symbol,&Vendor,&Model);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Vendor);
	TPLPUTEXECOUTVAR(_out, 1, &Model);
	TPLPUTLASTOUTVAR(__out, 0, &Vendor);
	TPLPUTLASTOUTVAR(__out, 1, &Model);
}

void
__CHECK_PROBER(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Symbol;
	STRING	Vendor;
	STRING	Model;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Symbol, _TYPES, 0, 0);
	TPLINITMEM(&Vendor, _TYPES, 0, 0);
	TPLINITMEM(&Model, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Symbol);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Vendor);
	TPLGETLASTOUTVAR(__out, 1, &Model);

	/* Algorithm invocation */
	CHECK_PROBER(Symbol,&Vendor,&Model);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Vendor);
	TPLPUTLASTOUTVAR(__out, 1, &Model);
}
