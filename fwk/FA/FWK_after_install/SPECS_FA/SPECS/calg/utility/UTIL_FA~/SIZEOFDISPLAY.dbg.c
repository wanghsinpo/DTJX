#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_SIZEOFDISPLAY(void *_alg)
{
}

void
__SIZEOFDISPLAY(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Width;
	INTEGER	Height;

	/* Data pointer initialization */
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Width, _TYPEI, 0, 0);
	TPLINITMEM(&Height, _TYPEI, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Width);
	TPLGETDEBUGOUTVAR(_out, 1, &Height);

	/* Algorithm invocation */
	SIZEOFDISPLAY(&Width,&Height);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Width);
	TPLPUTDEBUGOUTVAR(_out, 1, &Height);
}
