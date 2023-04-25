#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_MASTER_LOOKUP(void *_alg)
{
}

void
__MASTER_LOOKUP(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	File;
	STRING	Key;
	INTEGER	Fnum;
	STRING	Field;
	INTEGER	Stat;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&File, _TYPES, 0, 0);
	TPLINITMEM(&Key, _TYPES, 0, 0);
	TPLINITMEM(&Fnum, _TYPEI, 0, 0);
	TPLINITMEM(&Field, _TYPES, 0, 0);
	TPLINITMEM(&Stat, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &File);
	TPLGETDEBUGINVAR(_in, 1, &Key);
	TPLGETDEBUGINVAR(_in, 2, &Fnum);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Field);
	TPLGETDEBUGOUTVAR(_out, 1, &Stat);

	/* Algorithm invocation */
	MASTER_LOOKUP(File,Key,Fnum,&Field,&Stat);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Field);
	TPLPUTDEBUGOUTVAR(_out, 1, &Stat);
}
