#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_FA_CHK_MEASLIB(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Revcont;
	STRING	Lib[256];
	INTEGER	Libnum;
	STRING	Delimiter;
	INTEGER	Status;
	STRING	Error;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Revcont, _TYPEI, 0, 0);
	TPLINITMEM(&Lib, _TYPES, 256, 0);
	TPLINITMEM(&Libnum, _TYPEI, 0, 0);
	TPLINITMEM(&Delimiter, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Revcont);
	TPLGETEXECINVAR(_in, 1, &Lib);
	TPLGETEXECINVAR(_in, 2, &Libnum);
	TPLGETEXECINVAR(_in, 3, &Delimiter);
	TPLPUTLASTINVAR(__in, 0, &Revcont);
	TPLPUTLASTINVAR(__in, 1, &Lib);
	TPLPUTLASTINVAR(__in, 2, &Libnum);
	TPLPUTLASTINVAR(__in, 3, &Delimiter);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Status);
	TPLGETEXECOUTVAR(_out, 1, &Error);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Error);

	/* Algorithm invocation */
	FA_CHK_MEASLIB(Revcont,Lib,Libnum,Delimiter,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Status);
	TPLPUTEXECOUTVAR(_out, 1, &Error);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Error);
}

void
__FA_CHK_MEASLIB(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Revcont;
	STRING	Lib[256];
	INTEGER	Libnum;
	STRING	Delimiter;
	INTEGER	Status;
	STRING	Error;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Revcont, _TYPEI, 0, 0);
	TPLINITMEM(&Lib, _TYPES, 256, 0);
	TPLINITMEM(&Libnum, _TYPEI, 0, 0);
	TPLINITMEM(&Delimiter, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Revcont);
	TPLGETLASTINVAR(__in, 1, &Lib);
	TPLGETLASTINVAR(__in, 2, &Libnum);
	TPLGETLASTINVAR(__in, 3, &Delimiter);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Status);
	TPLGETLASTOUTVAR(__out, 1, &Error);

	/* Algorithm invocation */
	FA_CHK_MEASLIB(Revcont,Lib,Libnum,Delimiter,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Error);
}
