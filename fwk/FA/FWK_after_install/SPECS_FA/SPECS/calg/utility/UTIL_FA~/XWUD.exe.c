#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_XWUD(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;

	/* Local input/output variable definition */
	STRING	File;
	INTEGER	Xpos;
	INTEGER	Ypos;
	INTEGER	Noclick;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&File, _TYPES, 0, 0);
	TPLINITMEM(&Xpos, _TYPEI, 0, 0);
	TPLINITMEM(&Ypos, _TYPEI, 0, 0);
	TPLINITMEM(&Noclick, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &File);
	TPLGETEXECINVAR(_in, 1, &Xpos);
	TPLGETEXECINVAR(_in, 2, &Ypos);
	TPLGETEXECINVAR(_in, 3, &Noclick);
	TPLPUTLASTINVAR(__in, 0, &File);
	TPLPUTLASTINVAR(__in, 1, &Xpos);
	TPLPUTLASTINVAR(__in, 2, &Ypos);
	TPLPUTLASTINVAR(__in, 3, &Noclick);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	XWUD(File,Xpos,Ypos,Noclick);

	/* Algorithm output variable setting */
}

void
__XWUD(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;

	/* Local input/output variable definition */
	STRING	File;
	INTEGER	Xpos;
	INTEGER	Ypos;
	INTEGER	Noclick;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&File, _TYPES, 0, 0);
	TPLINITMEM(&Xpos, _TYPEI, 0, 0);
	TPLINITMEM(&Ypos, _TYPEI, 0, 0);
	TPLINITMEM(&Noclick, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &File);
	TPLGETLASTINVAR(__in, 1, &Xpos);
	TPLGETLASTINVAR(__in, 2, &Ypos);
	TPLGETLASTINVAR(__in, 3, &Noclick);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	XWUD(File,Xpos,Ypos,Noclick);

	/* Algorithm output variable setting */
}
