#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_QUERY_DIR(void *_alg)
{
}

void
__QUERY_DIR(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Dir;
	INTEGER	Stat;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Dir, _TYPES, 0, 0);
	TPLINITMEM(&Stat, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Dir);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Stat);

	/* Algorithm invocation */
	QUERY_DIR(Dir,&Stat);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Stat);
}
