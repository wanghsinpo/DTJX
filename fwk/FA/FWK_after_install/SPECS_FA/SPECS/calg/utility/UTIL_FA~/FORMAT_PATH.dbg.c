#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FORMAT_PATH(void *_alg)
{
}

void
__FORMAT_PATH(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Original;
	STRING	Path;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Original, _TYPES, 0, 0);
	TPLINITMEM(&Path, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Original);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Path);

	/* Algorithm invocation */
	FORMAT_PATH(Original,&Path);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Path);
}
