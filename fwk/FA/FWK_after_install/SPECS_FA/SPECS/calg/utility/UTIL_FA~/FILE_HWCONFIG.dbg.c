#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FILE_HWCONFIG(void *_alg)
{
}

void
__FILE_HWCONFIG(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;

	/* Local input/output variable definition */
	STRING	File;
	STRING	Config[50];

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);

	/* Local variable initialization */
	TPLINITMEM(&File, _TYPES, 0, 0);
	TPLINITMEM(&Config, _TYPES, 50, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &File);
	TPLGETDEBUGINVAR(_in, 1, &Config);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	FILE_HWCONFIG(File,Config);

	/* Algorithm output variable setting */
}
