#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_PROBER_CASSINFO(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Slotno;
	INTEGER	Cassno;
	INTEGER	Wafcount;
	INTEGER	Casscount;
	STRING	Status;
	STRING	Error;

	/* P-code pointer initialization */
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Slotno, _TYPEI, 0, 0);
	TPLINITMEM(&Cassno, _TYPEI, 0, 0);
	TPLINITMEM(&Wafcount, _TYPEI, 0, 0);
	TPLINITMEM(&Casscount, _TYPEI, 0, 0);
	TPLINITMEM(&Status, _TYPES, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Slotno);
	TPLGETEXECOUTVAR(_out, 1, &Cassno);
	TPLGETEXECOUTVAR(_out, 2, &Wafcount);
	TPLGETEXECOUTVAR(_out, 3, &Casscount);
	TPLGETEXECOUTVAR(_out, 4, &Status);
	TPLGETEXECOUTVAR(_out, 5, &Error);
	TPLPUTLASTOUTVAR(__out, 0, &Slotno);
	TPLPUTLASTOUTVAR(__out, 1, &Cassno);
	TPLPUTLASTOUTVAR(__out, 2, &Wafcount);
	TPLPUTLASTOUTVAR(__out, 3, &Casscount);
	TPLPUTLASTOUTVAR(__out, 4, &Status);
	TPLPUTLASTOUTVAR(__out, 5, &Error);

	/* Algorithm invocation */
	PROBER_CASSINFO(&Slotno,&Cassno,&Wafcount,&Casscount,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Slotno);
	TPLPUTEXECOUTVAR(_out, 1, &Cassno);
	TPLPUTEXECOUTVAR(_out, 2, &Wafcount);
	TPLPUTEXECOUTVAR(_out, 3, &Casscount);
	TPLPUTEXECOUTVAR(_out, 4, &Status);
	TPLPUTEXECOUTVAR(_out, 5, &Error);
	TPLPUTLASTOUTVAR(__out, 0, &Slotno);
	TPLPUTLASTOUTVAR(__out, 1, &Cassno);
	TPLPUTLASTOUTVAR(__out, 2, &Wafcount);
	TPLPUTLASTOUTVAR(__out, 3, &Casscount);
	TPLPUTLASTOUTVAR(__out, 4, &Status);
	TPLPUTLASTOUTVAR(__out, 5, &Error);
}

void
__PROBER_CASSINFO(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Slotno;
	INTEGER	Cassno;
	INTEGER	Wafcount;
	INTEGER	Casscount;
	STRING	Status;
	STRING	Error;

	/* P-code pointer initialization */
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Slotno, _TYPEI, 0, 0);
	TPLINITMEM(&Cassno, _TYPEI, 0, 0);
	TPLINITMEM(&Wafcount, _TYPEI, 0, 0);
	TPLINITMEM(&Casscount, _TYPEI, 0, 0);
	TPLINITMEM(&Status, _TYPES, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Slotno);
	TPLGETLASTOUTVAR(__out, 1, &Cassno);
	TPLGETLASTOUTVAR(__out, 2, &Wafcount);
	TPLGETLASTOUTVAR(__out, 3, &Casscount);
	TPLGETLASTOUTVAR(__out, 4, &Status);
	TPLGETLASTOUTVAR(__out, 5, &Error);

	/* Algorithm invocation */
	PROBER_CASSINFO(&Slotno,&Cassno,&Wafcount,&Casscount,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Slotno);
	TPLPUTLASTOUTVAR(__out, 1, &Cassno);
	TPLPUTLASTOUTVAR(__out, 2, &Wafcount);
	TPLPUTLASTOUTVAR(__out, 3, &Casscount);
	TPLPUTLASTOUTVAR(__out, 4, &Status);
	TPLPUTLASTOUTVAR(__out, 5, &Error);
}
