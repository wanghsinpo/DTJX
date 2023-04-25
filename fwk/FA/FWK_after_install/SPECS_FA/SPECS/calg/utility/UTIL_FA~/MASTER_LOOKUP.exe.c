#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_MASTER_LOOKUP(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	File;
	STRING	Key;
	INTEGER	Fnum;
	STRING	Field;
	INTEGER	Stat;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&File, _TYPES, 0, 0);
	TPLINITMEM(&Key, _TYPES, 0, 0);
	TPLINITMEM(&Fnum, _TYPEI, 0, 0);
	TPLINITMEM(&Field, _TYPES, 0, 0);
	TPLINITMEM(&Stat, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &File);
	TPLGETEXECINVAR(_in, 1, &Key);
	TPLGETEXECINVAR(_in, 2, &Fnum);
	TPLPUTLASTINVAR(__in, 0, &File);
	TPLPUTLASTINVAR(__in, 1, &Key);
	TPLPUTLASTINVAR(__in, 2, &Fnum);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Field);
	TPLGETEXECOUTVAR(_out, 1, &Stat);
	TPLPUTLASTOUTVAR(__out, 0, &Field);
	TPLPUTLASTOUTVAR(__out, 1, &Stat);

	/* Algorithm invocation */
	MASTER_LOOKUP(File,Key,Fnum,&Field,&Stat);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Field);
	TPLPUTEXECOUTVAR(_out, 1, &Stat);
	TPLPUTLASTOUTVAR(__out, 0, &Field);
	TPLPUTLASTOUTVAR(__out, 1, &Stat);
}

void
__MASTER_LOOKUP(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	File;
	STRING	Key;
	INTEGER	Fnum;
	STRING	Field;
	INTEGER	Stat;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&File, _TYPES, 0, 0);
	TPLINITMEM(&Key, _TYPES, 0, 0);
	TPLINITMEM(&Fnum, _TYPEI, 0, 0);
	TPLINITMEM(&Field, _TYPES, 0, 0);
	TPLINITMEM(&Stat, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &File);
	TPLGETLASTINVAR(__in, 1, &Key);
	TPLGETLASTINVAR(__in, 2, &Fnum);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Field);
	TPLGETLASTOUTVAR(__out, 1, &Stat);

	/* Algorithm invocation */
	MASTER_LOOKUP(File,Key,Fnum,&Field,&Stat);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Field);
	TPLPUTLASTOUTVAR(__out, 1, &Stat);
}
