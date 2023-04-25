#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_PROBER_FLATCOMP(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Tpl_OriFla;
	INTEGER	Prb_OriFla;
	STRING	Status;
	STRING	Error;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Tpl_OriFla, _TYPEI, 0, 0);
	TPLINITMEM(&Prb_OriFla, _TYPEI, 0, 0);
	TPLINITMEM(&Status, _TYPES, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Tpl_OriFla);
	TPLPUTLASTINVAR(__in, 0, &Tpl_OriFla);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Prb_OriFla);
	TPLGETEXECOUTVAR(_out, 1, &Status);
	TPLGETEXECOUTVAR(_out, 2, &Error);
	TPLPUTLASTOUTVAR(__out, 0, &Prb_OriFla);
	TPLPUTLASTOUTVAR(__out, 1, &Status);
	TPLPUTLASTOUTVAR(__out, 2, &Error);

	/* Algorithm invocation */
	PROBER_FLATCOMP(Tpl_OriFla,&Prb_OriFla,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Prb_OriFla);
	TPLPUTEXECOUTVAR(_out, 1, &Status);
	TPLPUTEXECOUTVAR(_out, 2, &Error);
	TPLPUTLASTOUTVAR(__out, 0, &Prb_OriFla);
	TPLPUTLASTOUTVAR(__out, 1, &Status);
	TPLPUTLASTOUTVAR(__out, 2, &Error);
}

void
__PROBER_FLATCOMP(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Tpl_OriFla;
	INTEGER	Prb_OriFla;
	STRING	Status;
	STRING	Error;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Tpl_OriFla, _TYPEI, 0, 0);
	TPLINITMEM(&Prb_OriFla, _TYPEI, 0, 0);
	TPLINITMEM(&Status, _TYPES, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Tpl_OriFla);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Prb_OriFla);
	TPLGETLASTOUTVAR(__out, 1, &Status);
	TPLGETLASTOUTVAR(__out, 2, &Error);

	/* Algorithm invocation */
	PROBER_FLATCOMP(Tpl_OriFla,&Prb_OriFla,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Prb_OriFla);
	TPLPUTLASTOUTVAR(__out, 1, &Status);
	TPLPUTLASTOUTVAR(__out, 2, &Error);
}
