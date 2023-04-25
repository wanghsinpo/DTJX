#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_GEM_RESPOND_OK(void *_alg)
{
}

void
__GEM_RESPOND_OK(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	ReplyMailbox;
	REAL	Timeout;
	INTEGER	Status;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&ReplyMailbox, _TYPES, 0, 0);
	TPLINITMEM(&Timeout, _TYPER, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &ReplyMailbox);
	TPLGETDEBUGINVAR(_in, 1, &Timeout);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);

	/* Algorithm invocation */
	GEM_RESPOND_OK(ReplyMailbox,Timeout,&Status);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
}
