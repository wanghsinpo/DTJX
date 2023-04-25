#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_CLOCK(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Digit;
	INTEGER	Year;
	INTEGER	Month;
	INTEGER	Day;
	INTEGER	Hour;
	INTEGER	Minute;
	INTEGER	Second;
	REAL	Value;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Digit, _TYPEI, 0, 0);
	TPLINITMEM(&Year, _TYPEI, 0, 0);
	TPLINITMEM(&Month, _TYPEI, 0, 0);
	TPLINITMEM(&Day, _TYPEI, 0, 0);
	TPLINITMEM(&Hour, _TYPEI, 0, 0);
	TPLINITMEM(&Minute, _TYPEI, 0, 0);
	TPLINITMEM(&Second, _TYPEI, 0, 0);
	TPLINITMEM(&Value, _TYPER, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Digit);
	TPLPUTLASTINVAR(__in, 0, &Digit);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Year);
	TPLGETEXECOUTVAR(_out, 1, &Month);
	TPLGETEXECOUTVAR(_out, 2, &Day);
	TPLGETEXECOUTVAR(_out, 3, &Hour);
	TPLGETEXECOUTVAR(_out, 4, &Minute);
	TPLGETEXECOUTVAR(_out, 5, &Second);
	TPLGETEXECOUTVAR(_out, 6, &Value);
	TPLPUTLASTOUTVAR(__out, 0, &Year);
	TPLPUTLASTOUTVAR(__out, 1, &Month);
	TPLPUTLASTOUTVAR(__out, 2, &Day);
	TPLPUTLASTOUTVAR(__out, 3, &Hour);
	TPLPUTLASTOUTVAR(__out, 4, &Minute);
	TPLPUTLASTOUTVAR(__out, 5, &Second);
	TPLPUTLASTOUTVAR(__out, 6, &Value);

	/* Algorithm invocation */
	CLOCK(Digit,&Year,&Month,&Day,&Hour,&Minute,&Second,&Value);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Year);
	TPLPUTEXECOUTVAR(_out, 1, &Month);
	TPLPUTEXECOUTVAR(_out, 2, &Day);
	TPLPUTEXECOUTVAR(_out, 3, &Hour);
	TPLPUTEXECOUTVAR(_out, 4, &Minute);
	TPLPUTEXECOUTVAR(_out, 5, &Second);
	TPLPUTEXECOUTVAR(_out, 6, &Value);
	TPLPUTLASTOUTVAR(__out, 0, &Year);
	TPLPUTLASTOUTVAR(__out, 1, &Month);
	TPLPUTLASTOUTVAR(__out, 2, &Day);
	TPLPUTLASTOUTVAR(__out, 3, &Hour);
	TPLPUTLASTOUTVAR(__out, 4, &Minute);
	TPLPUTLASTOUTVAR(__out, 5, &Second);
	TPLPUTLASTOUTVAR(__out, 6, &Value);
}

void
__CLOCK(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Digit;
	INTEGER	Year;
	INTEGER	Month;
	INTEGER	Day;
	INTEGER	Hour;
	INTEGER	Minute;
	INTEGER	Second;
	REAL	Value;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Digit, _TYPEI, 0, 0);
	TPLINITMEM(&Year, _TYPEI, 0, 0);
	TPLINITMEM(&Month, _TYPEI, 0, 0);
	TPLINITMEM(&Day, _TYPEI, 0, 0);
	TPLINITMEM(&Hour, _TYPEI, 0, 0);
	TPLINITMEM(&Minute, _TYPEI, 0, 0);
	TPLINITMEM(&Second, _TYPEI, 0, 0);
	TPLINITMEM(&Value, _TYPER, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Digit);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Year);
	TPLGETLASTOUTVAR(__out, 1, &Month);
	TPLGETLASTOUTVAR(__out, 2, &Day);
	TPLGETLASTOUTVAR(__out, 3, &Hour);
	TPLGETLASTOUTVAR(__out, 4, &Minute);
	TPLGETLASTOUTVAR(__out, 5, &Second);
	TPLGETLASTOUTVAR(__out, 6, &Value);

	/* Algorithm invocation */
	CLOCK(Digit,&Year,&Month,&Day,&Hour,&Minute,&Second,&Value);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Year);
	TPLPUTLASTOUTVAR(__out, 1, &Month);
	TPLPUTLASTOUTVAR(__out, 2, &Day);
	TPLPUTLASTOUTVAR(__out, 3, &Hour);
	TPLPUTLASTOUTVAR(__out, 4, &Minute);
	TPLPUTLASTOUTVAR(__out, 5, &Second);
	TPLPUTLASTOUTVAR(__out, 6, &Value);
}
