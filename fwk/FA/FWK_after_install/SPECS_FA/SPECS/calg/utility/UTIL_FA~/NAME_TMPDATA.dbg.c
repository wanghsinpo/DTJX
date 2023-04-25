#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_NAME_TMPDATA(void *_alg)
{
}

void
__NAME_TMPDATA(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Basename;
	STRING	Session;
	STRING	Tmpname;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Basename, _TYPES, 0, 0);
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Tmpname, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Basename);
	TPLGETDEBUGINVAR(_in, 1, &Session);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Tmpname);

	/* Algorithm invocation */
	NAME_TMPDATA(Basename,Session,&Tmpname);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Tmpname);
}
