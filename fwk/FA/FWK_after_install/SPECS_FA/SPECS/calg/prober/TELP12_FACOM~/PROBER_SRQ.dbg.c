#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_PROBER_SRQ(void *_alg)
{
}

void
__PROBER_SRQ(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Timeout;
	INTEGER	Statusbyte;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Timeout, _TYPEI, 0, 0);
	TPLINITMEM(&Statusbyte, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Timeout);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Statusbyte);

	/* Algorithm invocation */
	PROBER_SRQ(Timeout,&Statusbyte);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Statusbyte);
}
