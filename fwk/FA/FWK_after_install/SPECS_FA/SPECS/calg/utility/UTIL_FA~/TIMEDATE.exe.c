#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_TIMEDATE(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Digit;
	STRING	Date;
	STRING	Time;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Digit, _TYPEI, 0, 0);
	TPLINITMEM(&Date, _TYPES, 0, 0);
	TPLINITMEM(&Time, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Digit);
	TPLPUTLASTINVAR(__in, 0, &Digit);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Date);
	TPLGETEXECOUTVAR(_out, 1, &Time);
	TPLPUTLASTOUTVAR(__out, 0, &Date);
	TPLPUTLASTOUTVAR(__out, 1, &Time);

	/* Algorithm invocation */
	TIMEDATE(Digit,&Date,&Time);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Date);
	TPLPUTEXECOUTVAR(_out, 1, &Time);
	TPLPUTLASTOUTVAR(__out, 0, &Date);
	TPLPUTLASTOUTVAR(__out, 1, &Time);
}

void
__TIMEDATE(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Digit;
	STRING	Date;
	STRING	Time;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Digit, _TYPEI, 0, 0);
	TPLINITMEM(&Date, _TYPES, 0, 0);
	TPLINITMEM(&Time, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Digit);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Date);
	TPLGETLASTOUTVAR(__out, 1, &Time);

	/* Algorithm invocation */
	TIMEDATE(Digit,&Date,&Time);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Date);
	TPLPUTLASTOUTVAR(__out, 1, &Time);
}
