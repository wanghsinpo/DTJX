#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_GET_SLOT_NO(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Lotid;
	STRING	Waferid;
	INTEGER	Slotno;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Lotid, _TYPES, 0, 0);
	TPLINITMEM(&Waferid, _TYPES, 0, 0);
	TPLINITMEM(&Slotno, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Lotid);
	TPLGETEXECINVAR(_in, 1, &Waferid);
	TPLPUTLASTINVAR(__in, 0, &Lotid);
	TPLPUTLASTINVAR(__in, 1, &Waferid);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Slotno);
	TPLPUTLASTOUTVAR(__out, 0, &Slotno);

	/* Algorithm invocation */
	GET_SLOT_NO(Lotid,Waferid,&Slotno);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Slotno);
	TPLPUTLASTOUTVAR(__out, 0, &Slotno);
}

void
__GET_SLOT_NO(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Lotid;
	STRING	Waferid;
	INTEGER	Slotno;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Lotid, _TYPES, 0, 0);
	TPLINITMEM(&Waferid, _TYPES, 0, 0);
	TPLINITMEM(&Slotno, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Lotid);
	TPLGETLASTINVAR(__in, 1, &Waferid);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Slotno);

	/* Algorithm invocation */
	GET_SLOT_NO(Lotid,Waferid,&Slotno);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Slotno);
}
