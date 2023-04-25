#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_GET_VGEMDEFAULT(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Rcpmode;
	STRING	Rcpfilename;
	INTEGER	Status;

	/* P-code pointer initialization */
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Rcpmode, _TYPES, 0, 0);
	TPLINITMEM(&Rcpfilename, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Rcpmode);
	TPLGETEXECOUTVAR(_out, 1, &Rcpfilename);
	TPLGETEXECOUTVAR(_out, 2, &Status);
	TPLPUTLASTOUTVAR(__out, 0, &Rcpmode);
	TPLPUTLASTOUTVAR(__out, 1, &Rcpfilename);
	TPLPUTLASTOUTVAR(__out, 2, &Status);

	/* Algorithm invocation */
	GET_VGEMDEFAULT(&Rcpmode,&Rcpfilename,&Status);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Rcpmode);
	TPLPUTEXECOUTVAR(_out, 1, &Rcpfilename);
	TPLPUTEXECOUTVAR(_out, 2, &Status);
	TPLPUTLASTOUTVAR(__out, 0, &Rcpmode);
	TPLPUTLASTOUTVAR(__out, 1, &Rcpfilename);
	TPLPUTLASTOUTVAR(__out, 2, &Status);
}

void
__GET_VGEMDEFAULT(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__out;

	/* Local input/output variable definition */
	STRING	Rcpmode;
	STRING	Rcpfilename;
	INTEGER	Status;

	/* P-code pointer initialization */
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Rcpmode, _TYPES, 0, 0);
	TPLINITMEM(&Rcpfilename, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Rcpmode);
	TPLGETLASTOUTVAR(__out, 1, &Rcpfilename);
	TPLGETLASTOUTVAR(__out, 2, &Status);

	/* Algorithm invocation */
	GET_VGEMDEFAULT(&Rcpmode,&Rcpfilename,&Status);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Rcpmode);
	TPLPUTLASTOUTVAR(__out, 1, &Rcpfilename);
	TPLPUTLASTOUTVAR(__out, 2, &Status);
}
