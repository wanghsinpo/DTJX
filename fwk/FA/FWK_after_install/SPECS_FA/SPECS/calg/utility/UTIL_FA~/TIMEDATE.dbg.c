#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_TIMEDATE(void *_alg)
{
}

void
__TIMEDATE(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Digit;
	STRING	Date;
	STRING	Time;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Digit, _TYPEI, 0, 0);
	TPLINITMEM(&Date, _TYPES, 0, 0);
	TPLINITMEM(&Time, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Digit);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Date);
	TPLGETDEBUGOUTVAR(_out, 1, &Time);

	/* Algorithm invocation */
	TIMEDATE(Digit,&Date,&Time);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Date);
	TPLPUTDEBUGOUTVAR(_out, 1, &Time);
}
