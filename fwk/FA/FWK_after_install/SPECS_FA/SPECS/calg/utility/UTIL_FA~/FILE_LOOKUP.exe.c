#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_FILE_LOOKUP(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Dir;
	STRING	Suffix;
	STRING	Files[1024];
	INTEGER	Count;
	INTEGER	Depth;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Dir, _TYPES, 0, 0);
	TPLINITMEM(&Suffix, _TYPES, 0, 0);
	TPLINITMEM(&Files, _TYPES, 1024, 0);
	TPLINITMEM(&Count, _TYPEI, 0, 0);
	TPLINITMEM(&Depth, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Dir);
	TPLGETEXECINVAR(_in, 1, &Suffix);
	TPLPUTLASTINVAR(__in, 0, &Dir);
	TPLPUTLASTINVAR(__in, 1, &Suffix);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Files);
	TPLGETEXECOUTVAR(_out, 1, &Count);
	TPLGETEXECOUTVAR(_out, 2, &Depth);
	TPLPUTLASTOUTVAR(__out, 0, &Files);
	TPLPUTLASTOUTVAR(__out, 1, &Count);
	TPLPUTLASTOUTVAR(__out, 2, &Depth);

	/* Algorithm invocation */
	FILE_LOOKUP(Dir,Suffix,&Files,&Count,&Depth);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Files);
	TPLPUTEXECOUTVAR(_out, 1, &Count);
	TPLPUTEXECOUTVAR(_out, 2, &Depth);
	TPLPUTLASTOUTVAR(__out, 0, &Files);
	TPLPUTLASTOUTVAR(__out, 1, &Count);
	TPLPUTLASTOUTVAR(__out, 2, &Depth);
}

void
__FILE_LOOKUP(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Dir;
	STRING	Suffix;
	STRING	Files[1024];
	INTEGER	Count;
	INTEGER	Depth;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Dir, _TYPES, 0, 0);
	TPLINITMEM(&Suffix, _TYPES, 0, 0);
	TPLINITMEM(&Files, _TYPES, 1024, 0);
	TPLINITMEM(&Count, _TYPEI, 0, 0);
	TPLINITMEM(&Depth, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Dir);
	TPLGETLASTINVAR(__in, 1, &Suffix);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Files);
	TPLGETLASTOUTVAR(__out, 1, &Count);
	TPLGETLASTOUTVAR(__out, 2, &Depth);

	/* Algorithm invocation */
	FILE_LOOKUP(Dir,Suffix,&Files,&Count,&Depth);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Files);
	TPLPUTLASTOUTVAR(__out, 1, &Count);
	TPLPUTLASTOUTVAR(__out, 2, &Depth);
}
