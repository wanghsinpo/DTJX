#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_READ_PROCCOND(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Filename;
	INTEGER	Ret;
	INTEGER	Readnum;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Ret, _TYPEI, 0, 0);
	TPLINITMEM(&Readnum, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Filename);
	TPLPUTLASTINVAR(__in, 0, &Filename);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Ret);
	TPLGETEXECOUTVAR(_out, 1, &Readnum);
	TPLPUTLASTOUTVAR(__out, 0, &Ret);
	TPLPUTLASTOUTVAR(__out, 1, &Readnum);

	/* Algorithm invocation */
	READ_PROCCOND(Filename,&Ret,&Readnum);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Ret);
	TPLPUTEXECOUTVAR(_out, 1, &Readnum);
	TPLPUTLASTOUTVAR(__out, 0, &Ret);
	TPLPUTLASTOUTVAR(__out, 1, &Readnum);
}

void
__READ_PROCCOND(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Filename;
	INTEGER	Ret;
	INTEGER	Readnum;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Ret, _TYPEI, 0, 0);
	TPLINITMEM(&Readnum, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Filename);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Ret);
	TPLGETLASTOUTVAR(__out, 1, &Readnum);

	/* Algorithm invocation */
	READ_PROCCOND(Filename,&Ret,&Readnum);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Ret);
	TPLPUTLASTOUTVAR(__out, 1, &Readnum);
}
