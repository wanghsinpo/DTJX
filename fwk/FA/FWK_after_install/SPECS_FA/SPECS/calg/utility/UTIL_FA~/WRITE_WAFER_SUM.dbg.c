#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_WRITE_WAFER_SUM(void *_alg)
{
}

void
__WRITE_WAFER_SUM(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Slot;
	STRING	Lot;
	STRING	Wafer;
	REAL	Yld_item;
	REAL	Yld_die;
	INTEGER	Judge;
	STRING	Summary;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Slot, _TYPEI, 0, 0);
	TPLINITMEM(&Lot, _TYPES, 0, 0);
	TPLINITMEM(&Wafer, _TYPES, 0, 0);
	TPLINITMEM(&Yld_item, _TYPER, 0, 0);
	TPLINITMEM(&Yld_die, _TYPER, 0, 0);
	TPLINITMEM(&Judge, _TYPEI, 0, 0);
	TPLINITMEM(&Summary, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Slot);
	TPLGETDEBUGINVAR(_in, 1, &Lot);
	TPLGETDEBUGINVAR(_in, 2, &Wafer);
	TPLGETDEBUGINVAR(_in, 3, &Yld_item);
	TPLGETDEBUGINVAR(_in, 4, &Yld_die);
	TPLGETDEBUGINVAR(_in, 5, &Judge);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Summary);

	/* Algorithm invocation */
	WRITE_WAFER_SUM(Slot,Lot,Wafer,Yld_item,Yld_die,Judge,&Summary);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Summary);
}
