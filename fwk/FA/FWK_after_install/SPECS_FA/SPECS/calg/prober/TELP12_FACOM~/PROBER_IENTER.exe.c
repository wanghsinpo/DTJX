#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_PROBER_IENTER(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Timeout;
	STRING	Dt;
	INTEGER	Status;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Timeout, _TYPEI, 0, 0);
	TPLINITMEM(&Dt, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Timeout);
	TPLPUTLASTINVAR(__in, 0, &Timeout);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Dt);
	TPLGETEXECOUTVAR(_out, 1, &Status);
	TPLPUTLASTOUTVAR(__out, 0, &Dt);
	TPLPUTLASTOUTVAR(__out, 1, &Status);

	/* Algorithm invocation */
	PROBER_IENTER(Timeout,&Dt,&Status);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Dt);
	TPLPUTEXECOUTVAR(_out, 1, &Status);
	TPLPUTLASTOUTVAR(__out, 0, &Dt);
	TPLPUTLASTOUTVAR(__out, 1, &Status);
}

void
__PROBER_IENTER(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Timeout;
	STRING	Dt;
	INTEGER	Status;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Timeout, _TYPEI, 0, 0);
	TPLINITMEM(&Dt, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Timeout);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Dt);
	TPLGETLASTOUTVAR(__out, 1, &Status);

	/* Algorithm invocation */
	PROBER_IENTER(Timeout,&Dt,&Status);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Dt);
	TPLPUTLASTOUTVAR(__out, 1, &Status);
}
