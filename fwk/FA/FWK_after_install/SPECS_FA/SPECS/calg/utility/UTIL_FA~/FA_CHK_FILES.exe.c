#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_FA_CHK_FILES(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Rev_flag;
	STRING	Dir;
	STRING	Filename_rev;
	STRING	Suffix;
	STRING	Brk_chr;
	INTEGER	Status;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Rev_flag, _TYPEI, 0, 0);
	TPLINITMEM(&Dir, _TYPES, 0, 0);
	TPLINITMEM(&Filename_rev, _TYPES, 0, 0);
	TPLINITMEM(&Suffix, _TYPES, 0, 0);
	TPLINITMEM(&Brk_chr, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Rev_flag);
	TPLGETEXECINVAR(_in, 1, &Dir);
	TPLGETEXECINVAR(_in, 2, &Filename_rev);
	TPLGETEXECINVAR(_in, 3, &Suffix);
	TPLGETEXECINVAR(_in, 4, &Brk_chr);
	TPLPUTLASTINVAR(__in, 0, &Rev_flag);
	TPLPUTLASTINVAR(__in, 1, &Dir);
	TPLPUTLASTINVAR(__in, 2, &Filename_rev);
	TPLPUTLASTINVAR(__in, 3, &Suffix);
	TPLPUTLASTINVAR(__in, 4, &Brk_chr);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 0, &Status);

	/* Algorithm invocation */
	FA_CHK_FILES(Rev_flag,Dir,Filename_rev,Suffix,Brk_chr,&Status);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
}

void
__FA_CHK_FILES(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Rev_flag;
	STRING	Dir;
	STRING	Filename_rev;
	STRING	Suffix;
	STRING	Brk_chr;
	INTEGER	Status;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Rev_flag, _TYPEI, 0, 0);
	TPLINITMEM(&Dir, _TYPES, 0, 0);
	TPLINITMEM(&Filename_rev, _TYPES, 0, 0);
	TPLINITMEM(&Suffix, _TYPES, 0, 0);
	TPLINITMEM(&Brk_chr, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Rev_flag);
	TPLGETLASTINVAR(__in, 1, &Dir);
	TPLGETLASTINVAR(__in, 2, &Filename_rev);
	TPLGETLASTINVAR(__in, 3, &Suffix);
	TPLGETLASTINVAR(__in, 4, &Brk_chr);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Status);

	/* Algorithm invocation */
	FA_CHK_FILES(Rev_flag,Dir,Filename_rev,Suffix,Brk_chr,&Status);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Status);
}
