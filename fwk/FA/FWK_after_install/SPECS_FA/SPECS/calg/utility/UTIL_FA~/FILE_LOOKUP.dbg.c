#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FILE_LOOKUP(void *_alg)
{
}

void
__FILE_LOOKUP(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Dir;
	STRING	Suffix;
	STRING	Files[1024];
	INTEGER	Count;
	INTEGER	Depth;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Dir, _TYPES, 0, 0);
	TPLINITMEM(&Suffix, _TYPES, 0, 0);
	TPLINITMEM(&Files, _TYPES, 1024, 0);
	TPLINITMEM(&Count, _TYPEI, 0, 0);
	TPLINITMEM(&Depth, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Dir);
	TPLGETDEBUGINVAR(_in, 1, &Suffix);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Files);
	TPLGETDEBUGOUTVAR(_out, 1, &Count);
	TPLGETDEBUGOUTVAR(_out, 2, &Depth);

	/* Algorithm invocation */
	FILE_LOOKUP(Dir,Suffix,&Files,&Count,&Depth);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Files);
	TPLPUTDEBUGOUTVAR(_out, 1, &Count);
	TPLPUTDEBUGOUTVAR(_out, 2, &Depth);
}
