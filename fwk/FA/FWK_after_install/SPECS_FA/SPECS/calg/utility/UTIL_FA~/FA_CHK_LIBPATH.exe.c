#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_FA_CHK_LIBPATH(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Orig;
	INTEGER	Status;
	INTEGER	Pathflug;
	STRING	Path;
	STRING	Filename;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Orig, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Pathflug, _TYPEI, 0, 0);
	TPLINITMEM(&Path, _TYPES, 0, 0);
	TPLINITMEM(&Filename, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Orig);
	TPLPUTLASTINVAR(__in, 0, &Orig);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Status);
	TPLGETEXECOUTVAR(_out, 1, &Pathflug);
	TPLGETEXECOUTVAR(_out, 2, &Path);
	TPLGETEXECOUTVAR(_out, 3, &Filename);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Pathflug);
	TPLPUTLASTOUTVAR(__out, 2, &Path);
	TPLPUTLASTOUTVAR(__out, 3, &Filename);

	/* Algorithm invocation */
	FA_CHK_LIBPATH(Orig,&Status,&Pathflug,&Path,&Filename);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Status);
	TPLPUTEXECOUTVAR(_out, 1, &Pathflug);
	TPLPUTEXECOUTVAR(_out, 2, &Path);
	TPLPUTEXECOUTVAR(_out, 3, &Filename);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Pathflug);
	TPLPUTLASTOUTVAR(__out, 2, &Path);
	TPLPUTLASTOUTVAR(__out, 3, &Filename);
}

void
__FA_CHK_LIBPATH(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Orig;
	INTEGER	Status;
	INTEGER	Pathflug;
	STRING	Path;
	STRING	Filename;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Orig, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Pathflug, _TYPEI, 0, 0);
	TPLINITMEM(&Path, _TYPES, 0, 0);
	TPLINITMEM(&Filename, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Orig);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Status);
	TPLGETLASTOUTVAR(__out, 1, &Pathflug);
	TPLGETLASTOUTVAR(__out, 2, &Path);
	TPLGETLASTOUTVAR(__out, 3, &Filename);

	/* Algorithm invocation */
	FA_CHK_LIBPATH(Orig,&Status,&Pathflug,&Path,&Filename);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Pathflug);
	TPLPUTLASTOUTVAR(__out, 2, &Path);
	TPLPUTLASTOUTVAR(__out, 3, &Filename);
}
