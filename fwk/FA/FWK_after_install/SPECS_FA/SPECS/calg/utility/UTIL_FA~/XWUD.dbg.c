#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_XWUD(void *_alg)
{
}

void
__XWUD(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;

	/* Local input/output variable definition */
	STRING	File;
	INTEGER	Xpos;
	INTEGER	Ypos;
	INTEGER	Noclick;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);

	/* Local variable initialization */
	TPLINITMEM(&File, _TYPES, 0, 0);
	TPLINITMEM(&Xpos, _TYPEI, 0, 0);
	TPLINITMEM(&Ypos, _TYPEI, 0, 0);
	TPLINITMEM(&Noclick, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &File);
	TPLGETDEBUGINVAR(_in, 1, &Xpos);
	TPLGETDEBUGINVAR(_in, 2, &Ypos);
	TPLGETDEBUGINVAR(_in, 3, &Noclick);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	XWUD(File,Xpos,Ypos,Noclick);

	/* Algorithm output variable setting */
}
