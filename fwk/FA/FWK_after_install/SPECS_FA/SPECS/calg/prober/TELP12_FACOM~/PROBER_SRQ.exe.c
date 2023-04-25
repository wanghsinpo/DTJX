#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_PROBER_SRQ(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Timeout;
	INTEGER	Statusbyte;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Timeout, _TYPEI, 0, 0);
	TPLINITMEM(&Statusbyte, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Timeout);
	TPLPUTLASTINVAR(__in, 0, &Timeout);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Statusbyte);
	TPLPUTLASTOUTVAR(__out, 0, &Statusbyte);

	/* Algorithm invocation */
	PROBER_SRQ(Timeout,&Statusbyte);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Statusbyte);
	TPLPUTLASTOUTVAR(__out, 0, &Statusbyte);
}

void
__PROBER_SRQ(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Timeout;
	INTEGER	Statusbyte;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Timeout, _TYPEI, 0, 0);
	TPLINITMEM(&Statusbyte, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Timeout);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Statusbyte);

	/* Algorithm invocation */
	PROBER_SRQ(Timeout,&Statusbyte);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Statusbyte);
}
