#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_RCP_MK_FILENAME(void *_alg)
{
}

void
__RCP_MK_FILENAME(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Dirname;
	STRING	Filename;
	STRING	Suffix;
	STRING	Fullfile;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Dirname, _TYPES, 0, 0);
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Suffix, _TYPES, 0, 0);
	TPLINITMEM(&Fullfile, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Dirname);
	TPLGETDEBUGINVAR(_in, 1, &Filename);
	TPLGETDEBUGINVAR(_in, 2, &Suffix);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Fullfile);

	/* Algorithm invocation */
	RCP_MK_FILENAME(Dirname,Filename,Suffix,&Fullfile);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Fullfile);
}
