#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_MERGE_DATAFILE(void *_alg)
{
}

void
__MERGE_DATAFILE(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Original;
	STRING	New;
	STRING	Format;
	INTEGER	Numwaf;
	STRING	Waferid[50];
	INTEGER	Stat;
	STRING	Error;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Original, _TYPES, 0, 0);
	TPLINITMEM(&New, _TYPES, 0, 0);
	TPLINITMEM(&Format, _TYPES, 0, 0);
	TPLINITMEM(&Numwaf, _TYPEI, 0, 0);
	TPLINITMEM(&Waferid, _TYPES, 50, 0);
	TPLINITMEM(&Stat, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Original);
	TPLGETDEBUGINVAR(_in, 1, &New);
	TPLGETDEBUGINVAR(_in, 2, &Format);
	TPLGETDEBUGINVAR(_in, 3, &Numwaf);
	TPLGETDEBUGINVAR(_in, 4, &Waferid);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Stat);
	TPLGETDEBUGOUTVAR(_out, 1, &Error);

	/* Algorithm invocation */
	MERGE_DATAFILE(Original,New,Format,Numwaf,Waferid,&Stat,&Error);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Stat);
	TPLPUTDEBUGOUTVAR(_out, 1, &Error);
}
