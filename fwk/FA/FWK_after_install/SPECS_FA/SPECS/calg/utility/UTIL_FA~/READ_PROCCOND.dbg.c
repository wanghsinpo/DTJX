#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_READ_PROCCOND(void *_alg)
{
}

void
__READ_PROCCOND(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Filename;
	INTEGER	Ret;
	INTEGER	Readnum;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Ret, _TYPEI, 0, 0);
	TPLINITMEM(&Readnum, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Filename);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Ret);
	TPLGETDEBUGOUTVAR(_out, 1, &Readnum);

	/* Algorithm invocation */
	READ_PROCCOND(Filename,&Ret,&Readnum);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Ret);
	TPLPUTDEBUGOUTVAR(_out, 1, &Readnum);
}
