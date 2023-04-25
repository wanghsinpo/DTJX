#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_SIZEOFDISPLAY(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Width;
	INTEGER	Height;

	/* P-code pointer initialization */
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Width, _TYPEI, 0, 0);
	TPLINITMEM(&Height, _TYPEI, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Width);
	TPLGETEXECOUTVAR(_out, 1, &Height);
	TPLPUTLASTOUTVAR(__out, 0, &Width);
	TPLPUTLASTOUTVAR(__out, 1, &Height);

	/* Algorithm invocation */
	SIZEOFDISPLAY(&Width,&Height);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Width);
	TPLPUTEXECOUTVAR(_out, 1, &Height);
	TPLPUTLASTOUTVAR(__out, 0, &Width);
	TPLPUTLASTOUTVAR(__out, 1, &Height);
}

void
__SIZEOFDISPLAY(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Width;
	INTEGER	Height;

	/* P-code pointer initialization */
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Width, _TYPEI, 0, 0);
	TPLINITMEM(&Height, _TYPEI, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Width);
	TPLGETLASTOUTVAR(__out, 1, &Height);

	/* Algorithm invocation */
	SIZEOFDISPLAY(&Width,&Height);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Width);
	TPLPUTLASTOUTVAR(__out, 1, &Height);
}
