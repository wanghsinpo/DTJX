#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_FA_WAFERDUMP(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Dir;
	STRING	File;
	INTEGER	Slot;
	STRING	Adtfmt;
	STRING	Session;
	INTEGER	Status;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Dir, _TYPES, 0, 0);
	TPLINITMEM(&File, _TYPES, 0, 0);
	TPLINITMEM(&Slot, _TYPEI, 0, 0);
	TPLINITMEM(&Adtfmt, _TYPES, 0, 0);
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Dir);
	TPLGETEXECINVAR(_in, 1, &File);
	TPLGETEXECINVAR(_in, 2, &Slot);
	TPLGETEXECINVAR(_in, 3, &Adtfmt);
	TPLGETEXECINVAR(_in, 4, &Session);
	TPLPUTLASTINVAR(__in, 0, &Dir);
	TPLPUTLASTINVAR(__in, 1, &File);
	TPLPUTLASTINVAR(__in, 2, &Slot);
	TPLPUTLASTINVAR(__in, 3, &Adtfmt);
	TPLPUTLASTINVAR(__in, 4, &Session);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 0, &Status);

	/* Algorithm invocation */
	FA_WAFERDUMP(Dir,File,Slot,Adtfmt,Session,&Status);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
}

void
__FA_WAFERDUMP(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Dir;
	STRING	File;
	INTEGER	Slot;
	STRING	Adtfmt;
	STRING	Session;
	INTEGER	Status;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Dir, _TYPES, 0, 0);
	TPLINITMEM(&File, _TYPES, 0, 0);
	TPLINITMEM(&Slot, _TYPEI, 0, 0);
	TPLINITMEM(&Adtfmt, _TYPES, 0, 0);
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Dir);
	TPLGETLASTINVAR(__in, 1, &File);
	TPLGETLASTINVAR(__in, 2, &Slot);
	TPLGETLASTINVAR(__in, 3, &Adtfmt);
	TPLGETLASTINVAR(__in, 4, &Session);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Status);

	/* Algorithm invocation */
	FA_WAFERDUMP(Dir,File,Slot,Adtfmt,Session,&Status);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Status);
}
