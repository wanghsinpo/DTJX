#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_TELP12_CASSMAP(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Cassmap[50];
	STRING	Status;
	STRING	Error;

	/* P-code pointer initialization */
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Cassmap, _TYPEI, 50, 0);
	TPLINITMEM(&Status, _TYPES, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Cassmap);
	TPLGETEXECOUTVAR(_out, 1, &Status);
	TPLGETEXECOUTVAR(_out, 2, &Error);
	TPLPUTLASTOUTVAR(__out, 0, &Cassmap);
	TPLPUTLASTOUTVAR(__out, 1, &Status);
	TPLPUTLASTOUTVAR(__out, 2, &Error);

	/* Algorithm invocation */
	TELP12_CASSMAP(&Cassmap,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Cassmap);
	TPLPUTEXECOUTVAR(_out, 1, &Status);
	TPLPUTEXECOUTVAR(_out, 2, &Error);
	TPLPUTLASTOUTVAR(__out, 0, &Cassmap);
	TPLPUTLASTOUTVAR(__out, 1, &Status);
	TPLPUTLASTOUTVAR(__out, 2, &Error);
}

void
__TELP12_CASSMAP(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Cassmap[50];
	STRING	Status;
	STRING	Error;

	/* P-code pointer initialization */
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Cassmap, _TYPEI, 50, 0);
	TPLINITMEM(&Status, _TYPES, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Cassmap);
	TPLGETLASTOUTVAR(__out, 1, &Status);
	TPLGETLASTOUTVAR(__out, 2, &Error);

	/* Algorithm invocation */
	TELP12_CASSMAP(&Cassmap,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Cassmap);
	TPLPUTLASTOUTVAR(__out, 1, &Status);
	TPLPUTLASTOUTVAR(__out, 2, &Error);
}
