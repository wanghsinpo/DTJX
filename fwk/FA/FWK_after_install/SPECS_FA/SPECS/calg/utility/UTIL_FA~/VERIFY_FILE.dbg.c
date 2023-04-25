#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_VERIFY_FILE(void *_alg)
{
}

void
__VERIFY_FILE(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Filename;
	STRING	Type;
	INTEGER	Exist;
	INTEGER	Readable;
	INTEGER	Writable;
	INTEGER	Executable;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Type, _TYPES, 0, 0);
	TPLINITMEM(&Exist, _TYPEI, 0, 0);
	TPLINITMEM(&Readable, _TYPEI, 0, 0);
	TPLINITMEM(&Writable, _TYPEI, 0, 0);
	TPLINITMEM(&Executable, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Filename);
	TPLGETDEBUGINVAR(_in, 1, &Type);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Exist);
	TPLGETDEBUGOUTVAR(_out, 1, &Readable);
	TPLGETDEBUGOUTVAR(_out, 2, &Writable);
	TPLGETDEBUGOUTVAR(_out, 3, &Executable);

	/* Algorithm invocation */
	VERIFY_FILE(Filename,Type,&Exist,&Readable,&Writable,&Executable);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Exist);
	TPLPUTDEBUGOUTVAR(_out, 1, &Readable);
	TPLPUTDEBUGOUTVAR(_out, 2, &Writable);
	TPLPUTDEBUGOUTVAR(_out, 3, &Executable);
}
