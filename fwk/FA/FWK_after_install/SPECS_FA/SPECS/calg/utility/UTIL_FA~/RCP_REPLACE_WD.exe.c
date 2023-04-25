#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_RCP_REPLACE_WD(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Format;
	STRING	Find_wd[5];
	STRING	Replace_wd[5];
	STRING	String;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Format, _TYPES, 0, 0);
	TPLINITMEM(&Find_wd, _TYPES, 5, 0);
	TPLINITMEM(&Replace_wd, _TYPES, 5, 0);
	TPLINITMEM(&String, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Format);
	TPLGETEXECINVAR(_in, 1, &Find_wd);
	TPLGETEXECINVAR(_in, 2, &Replace_wd);
	TPLPUTLASTINVAR(__in, 0, &Format);
	TPLPUTLASTINVAR(__in, 1, &Find_wd);
	TPLPUTLASTINVAR(__in, 2, &Replace_wd);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &String);
	TPLPUTLASTOUTVAR(__out, 0, &String);

	/* Algorithm invocation */
	RCP_REPLACE_WD(Format,Find_wd,Replace_wd,&String);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &String);
	TPLPUTLASTOUTVAR(__out, 0, &String);
}

void
__RCP_REPLACE_WD(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Format;
	STRING	Find_wd[5];
	STRING	Replace_wd[5];
	STRING	String;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Format, _TYPES, 0, 0);
	TPLINITMEM(&Find_wd, _TYPES, 5, 0);
	TPLINITMEM(&Replace_wd, _TYPES, 5, 0);
	TPLINITMEM(&String, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Format);
	TPLGETLASTINVAR(__in, 1, &Find_wd);
	TPLGETLASTINVAR(__in, 2, &Replace_wd);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &String);

	/* Algorithm invocation */
	RCP_REPLACE_WD(Format,Find_wd,Replace_wd,&String);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &String);
}
