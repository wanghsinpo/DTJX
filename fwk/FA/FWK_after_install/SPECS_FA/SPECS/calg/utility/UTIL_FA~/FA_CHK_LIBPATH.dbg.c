#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FA_CHK_LIBPATH(void *_alg)
{
}

void
__FA_CHK_LIBPATH(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Orig;
	INTEGER	Status;
	INTEGER	Pathflug;
	STRING	Path;
	STRING	Filename;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Orig, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Pathflug, _TYPEI, 0, 0);
	TPLINITMEM(&Path, _TYPES, 0, 0);
	TPLINITMEM(&Filename, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Orig);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);
	TPLGETDEBUGOUTVAR(_out, 1, &Pathflug);
	TPLGETDEBUGOUTVAR(_out, 2, &Path);
	TPLGETDEBUGOUTVAR(_out, 3, &Filename);

	/* Algorithm invocation */
	FA_CHK_LIBPATH(Orig,&Status,&Pathflug,&Path,&Filename);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
	TPLPUTDEBUGOUTVAR(_out, 1, &Pathflug);
	TPLPUTDEBUGOUTVAR(_out, 2, &Path);
	TPLPUTDEBUGOUTVAR(_out, 3, &Filename);
}
