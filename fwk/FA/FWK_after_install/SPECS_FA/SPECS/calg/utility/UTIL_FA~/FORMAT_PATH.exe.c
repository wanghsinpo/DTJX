#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_FORMAT_PATH(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Original;
	STRING	Path;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Original, _TYPES, 0, 0);
	TPLINITMEM(&Path, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Original);
	TPLPUTLASTINVAR(__in, 0, &Original);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Path);
	TPLPUTLASTOUTVAR(__out, 0, &Path);

	/* Algorithm invocation */
	FORMAT_PATH(Original,&Path);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Path);
	TPLPUTLASTOUTVAR(__out, 0, &Path);
}

void
__FORMAT_PATH(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Original;
	STRING	Path;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Original, _TYPES, 0, 0);
	TPLINITMEM(&Path, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Original);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Path);

	/* Algorithm invocation */
	FORMAT_PATH(Original,&Path);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Path);
}
