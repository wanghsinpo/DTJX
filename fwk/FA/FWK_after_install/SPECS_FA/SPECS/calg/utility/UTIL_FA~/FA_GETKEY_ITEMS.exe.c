#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_FA_GETKEY_ITEMS(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Key;
	STRING	Filename;
	STRING	Waf;
	STRING	Die;
	STRING	Tst;
	STRING	Prb;
	STRING	Tpl;
	STRING	Lim;
	STRING	Rcp;
	STRING	Lot_id;
	STRING	Product_id;
	STRING	Process_id;
	INTEGER	Status;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Key, _TYPES, 0, 0);
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Waf, _TYPES, 0, 0);
	TPLINITMEM(&Die, _TYPES, 0, 0);
	TPLINITMEM(&Tst, _TYPES, 0, 0);
	TPLINITMEM(&Prb, _TYPES, 0, 0);
	TPLINITMEM(&Tpl, _TYPES, 0, 0);
	TPLINITMEM(&Lim, _TYPES, 0, 0);
	TPLINITMEM(&Rcp, _TYPES, 0, 0);
	TPLINITMEM(&Lot_id, _TYPES, 0, 0);
	TPLINITMEM(&Product_id, _TYPES, 0, 0);
	TPLINITMEM(&Process_id, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Key);
	TPLGETEXECINVAR(_in, 1, &Filename);
	TPLPUTLASTINVAR(__in, 0, &Key);
	TPLPUTLASTINVAR(__in, 1, &Filename);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Waf);
	TPLGETEXECOUTVAR(_out, 1, &Die);
	TPLGETEXECOUTVAR(_out, 2, &Tst);
	TPLGETEXECOUTVAR(_out, 3, &Prb);
	TPLGETEXECOUTVAR(_out, 4, &Tpl);
	TPLGETEXECOUTVAR(_out, 5, &Lim);
	TPLGETEXECOUTVAR(_out, 6, &Rcp);
	TPLGETEXECOUTVAR(_out, 7, &Lot_id);
	TPLGETEXECOUTVAR(_out, 8, &Product_id);
	TPLGETEXECOUTVAR(_out, 9, &Process_id);
	TPLGETEXECOUTVAR(_out, 10, &Status);
	TPLPUTLASTOUTVAR(__out, 0, &Waf);
	TPLPUTLASTOUTVAR(__out, 1, &Die);
	TPLPUTLASTOUTVAR(__out, 2, &Tst);
	TPLPUTLASTOUTVAR(__out, 3, &Prb);
	TPLPUTLASTOUTVAR(__out, 4, &Tpl);
	TPLPUTLASTOUTVAR(__out, 5, &Lim);
	TPLPUTLASTOUTVAR(__out, 6, &Rcp);
	TPLPUTLASTOUTVAR(__out, 7, &Lot_id);
	TPLPUTLASTOUTVAR(__out, 8, &Product_id);
	TPLPUTLASTOUTVAR(__out, 9, &Process_id);
	TPLPUTLASTOUTVAR(__out, 10, &Status);

	/* Algorithm invocation */
	FA_GETKEY_ITEMS(Key,Filename,&Waf,&Die,&Tst,&Prb,&Tpl,&Lim,&Rcp,&Lot_id,&Product_id,&Process_id,&Status);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Waf);
	TPLPUTEXECOUTVAR(_out, 1, &Die);
	TPLPUTEXECOUTVAR(_out, 2, &Tst);
	TPLPUTEXECOUTVAR(_out, 3, &Prb);
	TPLPUTEXECOUTVAR(_out, 4, &Tpl);
	TPLPUTEXECOUTVAR(_out, 5, &Lim);
	TPLPUTEXECOUTVAR(_out, 6, &Rcp);
	TPLPUTEXECOUTVAR(_out, 7, &Lot_id);
	TPLPUTEXECOUTVAR(_out, 8, &Product_id);
	TPLPUTEXECOUTVAR(_out, 9, &Process_id);
	TPLPUTEXECOUTVAR(_out, 10, &Status);
	TPLPUTLASTOUTVAR(__out, 0, &Waf);
	TPLPUTLASTOUTVAR(__out, 1, &Die);
	TPLPUTLASTOUTVAR(__out, 2, &Tst);
	TPLPUTLASTOUTVAR(__out, 3, &Prb);
	TPLPUTLASTOUTVAR(__out, 4, &Tpl);
	TPLPUTLASTOUTVAR(__out, 5, &Lim);
	TPLPUTLASTOUTVAR(__out, 6, &Rcp);
	TPLPUTLASTOUTVAR(__out, 7, &Lot_id);
	TPLPUTLASTOUTVAR(__out, 8, &Product_id);
	TPLPUTLASTOUTVAR(__out, 9, &Process_id);
	TPLPUTLASTOUTVAR(__out, 10, &Status);
}

void
__FA_GETKEY_ITEMS(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Key;
	STRING	Filename;
	STRING	Waf;
	STRING	Die;
	STRING	Tst;
	STRING	Prb;
	STRING	Tpl;
	STRING	Lim;
	STRING	Rcp;
	STRING	Lot_id;
	STRING	Product_id;
	STRING	Process_id;
	INTEGER	Status;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Key, _TYPES, 0, 0);
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Waf, _TYPES, 0, 0);
	TPLINITMEM(&Die, _TYPES, 0, 0);
	TPLINITMEM(&Tst, _TYPES, 0, 0);
	TPLINITMEM(&Prb, _TYPES, 0, 0);
	TPLINITMEM(&Tpl, _TYPES, 0, 0);
	TPLINITMEM(&Lim, _TYPES, 0, 0);
	TPLINITMEM(&Rcp, _TYPES, 0, 0);
	TPLINITMEM(&Lot_id, _TYPES, 0, 0);
	TPLINITMEM(&Product_id, _TYPES, 0, 0);
	TPLINITMEM(&Process_id, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Key);
	TPLGETLASTINVAR(__in, 1, &Filename);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Waf);
	TPLGETLASTOUTVAR(__out, 1, &Die);
	TPLGETLASTOUTVAR(__out, 2, &Tst);
	TPLGETLASTOUTVAR(__out, 3, &Prb);
	TPLGETLASTOUTVAR(__out, 4, &Tpl);
	TPLGETLASTOUTVAR(__out, 5, &Lim);
	TPLGETLASTOUTVAR(__out, 6, &Rcp);
	TPLGETLASTOUTVAR(__out, 7, &Lot_id);
	TPLGETLASTOUTVAR(__out, 8, &Product_id);
	TPLGETLASTOUTVAR(__out, 9, &Process_id);
	TPLGETLASTOUTVAR(__out, 10, &Status);

	/* Algorithm invocation */
	FA_GETKEY_ITEMS(Key,Filename,&Waf,&Die,&Tst,&Prb,&Tpl,&Lim,&Rcp,&Lot_id,&Product_id,&Process_id,&Status);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Waf);
	TPLPUTLASTOUTVAR(__out, 1, &Die);
	TPLPUTLASTOUTVAR(__out, 2, &Tst);
	TPLPUTLASTOUTVAR(__out, 3, &Prb);
	TPLPUTLASTOUTVAR(__out, 4, &Tpl);
	TPLPUTLASTOUTVAR(__out, 5, &Lim);
	TPLPUTLASTOUTVAR(__out, 6, &Rcp);
	TPLPUTLASTOUTVAR(__out, 7, &Lot_id);
	TPLPUTLASTOUTVAR(__out, 8, &Product_id);
	TPLPUTLASTOUTVAR(__out, 9, &Process_id);
	TPLPUTLASTOUTVAR(__out, 10, &Status);
}
