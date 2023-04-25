#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_CHECK_PROBER(void *_alg)
{
}

void
__CHECK_PROBER(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Symbol;
	STRING	Vendor;
	STRING	Model;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Symbol, _TYPES, 0, 0);
	TPLINITMEM(&Vendor, _TYPES, 0, 0);
	TPLINITMEM(&Model, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Symbol);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Vendor);
	TPLGETDEBUGOUTVAR(_out, 1, &Model);

	/* Algorithm invocation */
	CHECK_PROBER(Symbol,&Vendor,&Model);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Vendor);
	TPLPUTDEBUGOUTVAR(_out, 1, &Model);
}
