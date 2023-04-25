#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_ARRAY_LOOKUP3(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Src[256];
	INTEGER	Pos[256];
	STRING	Sub[256];

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Src, _TYPES, 256, 0);
	TPLINITMEM(&Pos, _TYPEI, 256, 0);
	TPLINITMEM(&Sub, _TYPES, 256, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Src);
	TPLGETEXECINVAR(_in, 1, &Pos);
	TPLPUTLASTINVAR(__in, 0, &Src);
	TPLPUTLASTINVAR(__in, 1, &Pos);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Sub);
	TPLPUTLASTOUTVAR(__out, 0, &Sub);

	/* Algorithm invocation */
	ARRAY_LOOKUP3(Src,Pos,&Sub);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Sub);
	TPLPUTLASTOUTVAR(__out, 0, &Sub);
}

void
__ARRAY_LOOKUP3(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Src[256];
	INTEGER	Pos[256];
	STRING	Sub[256];

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Src, _TYPES, 256, 0);
	TPLINITMEM(&Pos, _TYPEI, 256, 0);
	TPLINITMEM(&Sub, _TYPES, 256, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Src);
	TPLGETLASTINVAR(__in, 1, &Pos);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Sub);

	/* Algorithm invocation */
	ARRAY_LOOKUP3(Src,Pos,&Sub);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Sub);
}
