#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_WRITE_WAFER_SUM(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Slot;
	STRING	Lot;
	STRING	Wafer;
	REAL	Yld_item;
	REAL	Yld_die;
	INTEGER	Judge;
	STRING	Summary;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Slot, _TYPEI, 0, 0);
	TPLINITMEM(&Lot, _TYPES, 0, 0);
	TPLINITMEM(&Wafer, _TYPES, 0, 0);
	TPLINITMEM(&Yld_item, _TYPER, 0, 0);
	TPLINITMEM(&Yld_die, _TYPER, 0, 0);
	TPLINITMEM(&Judge, _TYPEI, 0, 0);
	TPLINITMEM(&Summary, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Slot);
	TPLGETEXECINVAR(_in, 1, &Lot);
	TPLGETEXECINVAR(_in, 2, &Wafer);
	TPLGETEXECINVAR(_in, 3, &Yld_item);
	TPLGETEXECINVAR(_in, 4, &Yld_die);
	TPLGETEXECINVAR(_in, 5, &Judge);
	TPLPUTLASTINVAR(__in, 0, &Slot);
	TPLPUTLASTINVAR(__in, 1, &Lot);
	TPLPUTLASTINVAR(__in, 2, &Wafer);
	TPLPUTLASTINVAR(__in, 3, &Yld_item);
	TPLPUTLASTINVAR(__in, 4, &Yld_die);
	TPLPUTLASTINVAR(__in, 5, &Judge);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Summary);
	TPLPUTLASTOUTVAR(__out, 0, &Summary);

	/* Algorithm invocation */
	WRITE_WAFER_SUM(Slot,Lot,Wafer,Yld_item,Yld_die,Judge,&Summary);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Summary);
	TPLPUTLASTOUTVAR(__out, 0, &Summary);
}

void
__WRITE_WAFER_SUM(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Slot;
	STRING	Lot;
	STRING	Wafer;
	REAL	Yld_item;
	REAL	Yld_die;
	INTEGER	Judge;
	STRING	Summary;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Slot, _TYPEI, 0, 0);
	TPLINITMEM(&Lot, _TYPES, 0, 0);
	TPLINITMEM(&Wafer, _TYPES, 0, 0);
	TPLINITMEM(&Yld_item, _TYPER, 0, 0);
	TPLINITMEM(&Yld_die, _TYPER, 0, 0);
	TPLINITMEM(&Judge, _TYPEI, 0, 0);
	TPLINITMEM(&Summary, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Slot);
	TPLGETLASTINVAR(__in, 1, &Lot);
	TPLGETLASTINVAR(__in, 2, &Wafer);
	TPLGETLASTINVAR(__in, 3, &Yld_item);
	TPLGETLASTINVAR(__in, 4, &Yld_die);
	TPLGETLASTINVAR(__in, 5, &Judge);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Summary);

	/* Algorithm invocation */
	WRITE_WAFER_SUM(Slot,Lot,Wafer,Yld_item,Yld_die,Judge,&Summary);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Summary);
}
