#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_FA_QUERY_COND(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Key;
	STRING	Level;
	STRING	Filename;
	STRING	Tco[16];
	STRING	Limf;
	STRING	DieLabel[256];
	STRING	DieType[256];
	STRING	ModLabel[256];
	STRING	Item[32];
	INTEGER	Status;
	STRING	Errmsg;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Key, _TYPES, 0, 0);
	TPLINITMEM(&Level, _TYPES, 0, 0);
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Tco, _TYPES, 16, 0);
	TPLINITMEM(&Limf, _TYPES, 0, 0);
	TPLINITMEM(&DieLabel, _TYPES, 256, 0);
	TPLINITMEM(&DieType, _TYPES, 256, 0);
	TPLINITMEM(&ModLabel, _TYPES, 256, 0);
	TPLINITMEM(&Item, _TYPES, 32, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Errmsg, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Key);
	TPLGETEXECINVAR(_in, 1, &Level);
	TPLGETEXECINVAR(_in, 2, &Filename);
	TPLPUTLASTINVAR(__in, 0, &Key);
	TPLPUTLASTINVAR(__in, 1, &Level);
	TPLPUTLASTINVAR(__in, 2, &Filename);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Tco);
	TPLGETEXECOUTVAR(_out, 1, &Limf);
	TPLGETEXECOUTVAR(_out, 2, &DieLabel);
	TPLGETEXECOUTVAR(_out, 3, &DieType);
	TPLGETEXECOUTVAR(_out, 4, &ModLabel);
	TPLGETEXECOUTVAR(_out, 5, &Item);
	TPLGETEXECOUTVAR(_out, 6, &Status);
	TPLGETEXECOUTVAR(_out, 7, &Errmsg);
	TPLPUTLASTOUTVAR(__out, 0, &Tco);
	TPLPUTLASTOUTVAR(__out, 1, &Limf);
	TPLPUTLASTOUTVAR(__out, 2, &DieLabel);
	TPLPUTLASTOUTVAR(__out, 3, &DieType);
	TPLPUTLASTOUTVAR(__out, 4, &ModLabel);
	TPLPUTLASTOUTVAR(__out, 5, &Item);
	TPLPUTLASTOUTVAR(__out, 6, &Status);
	TPLPUTLASTOUTVAR(__out, 7, &Errmsg);

	/* Algorithm invocation */
	FA_QUERY_COND(Key,Level,Filename,&Tco,&Limf,&DieLabel,&DieType,&ModLabel,&Item,&Status,&Errmsg);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Tco);
	TPLPUTEXECOUTVAR(_out, 1, &Limf);
	TPLPUTEXECOUTVAR(_out, 2, &DieLabel);
	TPLPUTEXECOUTVAR(_out, 3, &DieType);
	TPLPUTEXECOUTVAR(_out, 4, &ModLabel);
	TPLPUTEXECOUTVAR(_out, 5, &Item);
	TPLPUTEXECOUTVAR(_out, 6, &Status);
	TPLPUTEXECOUTVAR(_out, 7, &Errmsg);
	TPLPUTLASTOUTVAR(__out, 0, &Tco);
	TPLPUTLASTOUTVAR(__out, 1, &Limf);
	TPLPUTLASTOUTVAR(__out, 2, &DieLabel);
	TPLPUTLASTOUTVAR(__out, 3, &DieType);
	TPLPUTLASTOUTVAR(__out, 4, &ModLabel);
	TPLPUTLASTOUTVAR(__out, 5, &Item);
	TPLPUTLASTOUTVAR(__out, 6, &Status);
	TPLPUTLASTOUTVAR(__out, 7, &Errmsg);
}

void
__FA_QUERY_COND(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Key;
	STRING	Level;
	STRING	Filename;
	STRING	Tco[16];
	STRING	Limf;
	STRING	DieLabel[256];
	STRING	DieType[256];
	STRING	ModLabel[256];
	STRING	Item[32];
	INTEGER	Status;
	STRING	Errmsg;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Key, _TYPES, 0, 0);
	TPLINITMEM(&Level, _TYPES, 0, 0);
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Tco, _TYPES, 16, 0);
	TPLINITMEM(&Limf, _TYPES, 0, 0);
	TPLINITMEM(&DieLabel, _TYPES, 256, 0);
	TPLINITMEM(&DieType, _TYPES, 256, 0);
	TPLINITMEM(&ModLabel, _TYPES, 256, 0);
	TPLINITMEM(&Item, _TYPES, 32, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Errmsg, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Key);
	TPLGETLASTINVAR(__in, 1, &Level);
	TPLGETLASTINVAR(__in, 2, &Filename);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Tco);
	TPLGETLASTOUTVAR(__out, 1, &Limf);
	TPLGETLASTOUTVAR(__out, 2, &DieLabel);
	TPLGETLASTOUTVAR(__out, 3, &DieType);
	TPLGETLASTOUTVAR(__out, 4, &ModLabel);
	TPLGETLASTOUTVAR(__out, 5, &Item);
	TPLGETLASTOUTVAR(__out, 6, &Status);
	TPLGETLASTOUTVAR(__out, 7, &Errmsg);

	/* Algorithm invocation */
	FA_QUERY_COND(Key,Level,Filename,&Tco,&Limf,&DieLabel,&DieType,&ModLabel,&Item,&Status,&Errmsg);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Tco);
	TPLPUTLASTOUTVAR(__out, 1, &Limf);
	TPLPUTLASTOUTVAR(__out, 2, &DieLabel);
	TPLPUTLASTOUTVAR(__out, 3, &DieType);
	TPLPUTLASTOUTVAR(__out, 4, &ModLabel);
	TPLPUTLASTOUTVAR(__out, 5, &Item);
	TPLPUTLASTOUTVAR(__out, 6, &Status);
	TPLPUTLASTOUTVAR(__out, 7, &Errmsg);
}
