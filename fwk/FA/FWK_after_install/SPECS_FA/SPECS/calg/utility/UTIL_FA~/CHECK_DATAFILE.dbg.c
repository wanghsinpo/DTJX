#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_CHECK_DATAFILE(void *_alg)
{
}

void
__CHECK_DATAFILE(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Filename;
	INTEGER	Valid;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Valid, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Filename);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Valid);

	/* Algorithm invocation */
	CHECK_DATAFILE(Filename,&Valid);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Valid);
}
