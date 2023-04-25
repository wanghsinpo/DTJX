#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_CLOCK(void *_alg)
{
}

void
__CLOCK(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Digit;
	INTEGER	Year;
	INTEGER	Month;
	INTEGER	Day;
	INTEGER	Hour;
	INTEGER	Minute;
	INTEGER	Second;
	REAL	Value;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

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
	TPLGETDEBUGINVAR(_in, 0, &Digit);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Year);
	TPLGETDEBUGOUTVAR(_out, 1, &Month);
	TPLGETDEBUGOUTVAR(_out, 2, &Day);
	TPLGETDEBUGOUTVAR(_out, 3, &Hour);
	TPLGETDEBUGOUTVAR(_out, 4, &Minute);
	TPLGETDEBUGOUTVAR(_out, 5, &Second);
	TPLGETDEBUGOUTVAR(_out, 6, &Value);

	/* Algorithm invocation */
	CLOCK(Digit,&Year,&Month,&Day,&Hour,&Minute,&Second,&Value);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Year);
	TPLPUTDEBUGOUTVAR(_out, 1, &Month);
	TPLPUTDEBUGOUTVAR(_out, 2, &Day);
	TPLPUTDEBUGOUTVAR(_out, 3, &Hour);
	TPLPUTDEBUGOUTVAR(_out, 4, &Minute);
	TPLPUTDEBUGOUTVAR(_out, 5, &Second);
	TPLPUTDEBUGOUTVAR(_out, 6, &Value);
}
