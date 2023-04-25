#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_MERGE_DATAFILE(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Original;
	STRING	New;
	STRING	Format;
	INTEGER	Numwaf;
	STRING	Waferid[50];
	INTEGER	Stat;
	STRING	Error;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Original, _TYPES, 0, 0);
	TPLINITMEM(&New, _TYPES, 0, 0);
	TPLINITMEM(&Format, _TYPES, 0, 0);
	TPLINITMEM(&Numwaf, _TYPEI, 0, 0);
	TPLINITMEM(&Waferid, _TYPES, 50, 0);
	TPLINITMEM(&Stat, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Original);
	TPLGETEXECINVAR(_in, 1, &New);
	TPLGETEXECINVAR(_in, 2, &Format);
	TPLGETEXECINVAR(_in, 3, &Numwaf);
	TPLGETEXECINVAR(_in, 4, &Waferid);
	TPLPUTLASTINVAR(__in, 0, &Original);
	TPLPUTLASTINVAR(__in, 1, &New);
	TPLPUTLASTINVAR(__in, 2, &Format);
	TPLPUTLASTINVAR(__in, 3, &Numwaf);
	TPLPUTLASTINVAR(__in, 4, &Waferid);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Stat);
	TPLGETEXECOUTVAR(_out, 1, &Error);
	TPLPUTLASTOUTVAR(__out, 0, &Stat);
	TPLPUTLASTOUTVAR(__out, 1, &Error);

	/* Algorithm invocation */
	MERGE_DATAFILE(Original,New,Format,Numwaf,Waferid,&Stat,&Error);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Stat);
	TPLPUTEXECOUTVAR(_out, 1, &Error);
	TPLPUTLASTOUTVAR(__out, 0, &Stat);
	TPLPUTLASTOUTVAR(__out, 1, &Error);
}

void
__MERGE_DATAFILE(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Original;
	STRING	New;
	STRING	Format;
	INTEGER	Numwaf;
	STRING	Waferid[50];
	INTEGER	Stat;
	STRING	Error;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Original, _TYPES, 0, 0);
	TPLINITMEM(&New, _TYPES, 0, 0);
	TPLINITMEM(&Format, _TYPES, 0, 0);
	TPLINITMEM(&Numwaf, _TYPEI, 0, 0);
	TPLINITMEM(&Waferid, _TYPES, 50, 0);
	TPLINITMEM(&Stat, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Original);
	TPLGETLASTINVAR(__in, 1, &New);
	TPLGETLASTINVAR(__in, 2, &Format);
	TPLGETLASTINVAR(__in, 3, &Numwaf);
	TPLGETLASTINVAR(__in, 4, &Waferid);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Stat);
	TPLGETLASTOUTVAR(__out, 1, &Error);

	/* Algorithm invocation */
	MERGE_DATAFILE(Original,New,Format,Numwaf,Waferid,&Stat,&Error);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Stat);
	TPLPUTLASTOUTVAR(__out, 1, &Error);
}
