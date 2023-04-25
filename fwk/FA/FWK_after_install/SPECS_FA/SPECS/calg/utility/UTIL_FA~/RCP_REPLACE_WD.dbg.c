#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_RCP_REPLACE_WD(void *_alg)
{
}

void
__RCP_REPLACE_WD(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Format;
	STRING	Find_wd[5];
	STRING	Replace_wd[5];
	STRING	String;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Format, _TYPES, 0, 0);
	TPLINITMEM(&Find_wd, _TYPES, 5, 0);
	TPLINITMEM(&Replace_wd, _TYPES, 5, 0);
	TPLINITMEM(&String, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Format);
	TPLGETDEBUGINVAR(_in, 1, &Find_wd);
	TPLGETDEBUGINVAR(_in, 2, &Replace_wd);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &String);

	/* Algorithm invocation */
	RCP_REPLACE_WD(Format,Find_wd,Replace_wd,&String);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &String);
}
