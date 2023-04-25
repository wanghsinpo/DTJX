#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_UPDATE_FWKCONF(void *_alg)
{
}

void
__UPDATE_FWKCONF(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	File;
	INTEGER	Type;
	INTEGER	Errno;
	STRING	Errmsg;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&File, _TYPES, 0, 0);
	TPLINITMEM(&Type, _TYPEI, 0, 0);
	TPLINITMEM(&Errno, _TYPEI, 0, 0);
	TPLINITMEM(&Errmsg, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &File);
	TPLGETDEBUGINVAR(_in, 1, &Type);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Errno);
	TPLGETDEBUGOUTVAR(_out, 1, &Errmsg);

	/* Algorithm invocation */
	UPDATE_FWKCONF(File,Type,&Errno,&Errmsg);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Errno);
	TPLPUTDEBUGOUTVAR(_out, 1, &Errmsg);
}
