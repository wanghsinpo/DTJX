#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_RCP_MK_FILENAME(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Dirname;
	STRING	Filename;
	STRING	Suffix;
	STRING	Fullfile;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Dirname, _TYPES, 0, 0);
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Suffix, _TYPES, 0, 0);
	TPLINITMEM(&Fullfile, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Dirname);
	TPLGETEXECINVAR(_in, 1, &Filename);
	TPLGETEXECINVAR(_in, 2, &Suffix);
	TPLPUTLASTINVAR(__in, 0, &Dirname);
	TPLPUTLASTINVAR(__in, 1, &Filename);
	TPLPUTLASTINVAR(__in, 2, &Suffix);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Fullfile);
	TPLPUTLASTOUTVAR(__out, 0, &Fullfile);

	/* Algorithm invocation */
	RCP_MK_FILENAME(Dirname,Filename,Suffix,&Fullfile);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Fullfile);
	TPLPUTLASTOUTVAR(__out, 0, &Fullfile);
}

void
__RCP_MK_FILENAME(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Dirname;
	STRING	Filename;
	STRING	Suffix;
	STRING	Fullfile;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Dirname, _TYPES, 0, 0);
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Suffix, _TYPES, 0, 0);
	TPLINITMEM(&Fullfile, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Dirname);
	TPLGETLASTINVAR(__in, 1, &Filename);
	TPLGETLASTINVAR(__in, 2, &Suffix);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Fullfile);

	/* Algorithm invocation */
	RCP_MK_FILENAME(Dirname,Filename,Suffix,&Fullfile);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Fullfile);
}
