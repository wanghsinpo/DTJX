#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_FA_QUERY_RECIP(void *_alg, void *__alg)
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
	STRING	Die[256];
	STRING	Mod[256];
	STRING	Tst[256];
	STRING	Prb;
	STRING	Lms[256];
	STRING	Tco[16];
	STRING	Tpl;
	STRING	Lim;
	STRING	Rcp;
	STRING	Lt_id;
	STRING	Pt_id;
	STRING	Ps_id;
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
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Waf, _TYPES, 0, 0);
	TPLINITMEM(&Die, _TYPES, 256, 0);
	TPLINITMEM(&Mod, _TYPES, 256, 0);
	TPLINITMEM(&Tst, _TYPES, 256, 0);
	TPLINITMEM(&Prb, _TYPES, 0, 0);
	TPLINITMEM(&Lms, _TYPES, 256, 0);
	TPLINITMEM(&Tco, _TYPES, 16, 0);
	TPLINITMEM(&Tpl, _TYPES, 0, 0);
	TPLINITMEM(&Lim, _TYPES, 0, 0);
	TPLINITMEM(&Rcp, _TYPES, 0, 0);
	TPLINITMEM(&Lt_id, _TYPES, 0, 0);
	TPLINITMEM(&Pt_id, _TYPES, 0, 0);
	TPLINITMEM(&Ps_id, _TYPES, 0, 0);
	TPLINITMEM(&Item, _TYPES, 32, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Errmsg, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Key);
	TPLGETEXECINVAR(_in, 1, &Filename);
	TPLPUTLASTINVAR(__in, 0, &Key);
	TPLPUTLASTINVAR(__in, 1, &Filename);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Waf);
	TPLGETEXECOUTVAR(_out, 1, &Die);
	TPLGETEXECOUTVAR(_out, 2, &Mod);
	TPLGETEXECOUTVAR(_out, 3, &Tst);
	TPLGETEXECOUTVAR(_out, 4, &Prb);
	TPLGETEXECOUTVAR(_out, 5, &Lms);
	TPLGETEXECOUTVAR(_out, 6, &Tco);
	TPLGETEXECOUTVAR(_out, 7, &Tpl);
	TPLGETEXECOUTVAR(_out, 8, &Lim);
	TPLGETEXECOUTVAR(_out, 9, &Rcp);
	TPLGETEXECOUTVAR(_out, 10, &Lt_id);
	TPLGETEXECOUTVAR(_out, 11, &Pt_id);
	TPLGETEXECOUTVAR(_out, 12, &Ps_id);
	TPLGETEXECOUTVAR(_out, 13, &Item);
	TPLGETEXECOUTVAR(_out, 14, &Status);
	TPLGETEXECOUTVAR(_out, 15, &Errmsg);
	TPLPUTLASTOUTVAR(__out, 0, &Waf);
	TPLPUTLASTOUTVAR(__out, 1, &Die);
	TPLPUTLASTOUTVAR(__out, 2, &Mod);
	TPLPUTLASTOUTVAR(__out, 3, &Tst);
	TPLPUTLASTOUTVAR(__out, 4, &Prb);
	TPLPUTLASTOUTVAR(__out, 5, &Lms);
	TPLPUTLASTOUTVAR(__out, 6, &Tco);
	TPLPUTLASTOUTVAR(__out, 7, &Tpl);
	TPLPUTLASTOUTVAR(__out, 8, &Lim);
	TPLPUTLASTOUTVAR(__out, 9, &Rcp);
	TPLPUTLASTOUTVAR(__out, 10, &Lt_id);
	TPLPUTLASTOUTVAR(__out, 11, &Pt_id);
	TPLPUTLASTOUTVAR(__out, 12, &Ps_id);
	TPLPUTLASTOUTVAR(__out, 13, &Item);
	TPLPUTLASTOUTVAR(__out, 14, &Status);
	TPLPUTLASTOUTVAR(__out, 15, &Errmsg);

	/* Algorithm invocation */
	FA_QUERY_RECIP(Key,Filename,&Waf,&Die,&Mod,&Tst,&Prb,&Lms,&Tco,&Tpl,&Lim,&Rcp,&Lt_id,&Pt_id,&Ps_id,&Item,&Status,&Errmsg);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Waf);
	TPLPUTEXECOUTVAR(_out, 1, &Die);
	TPLPUTEXECOUTVAR(_out, 2, &Mod);
	TPLPUTEXECOUTVAR(_out, 3, &Tst);
	TPLPUTEXECOUTVAR(_out, 4, &Prb);
	TPLPUTEXECOUTVAR(_out, 5, &Lms);
	TPLPUTEXECOUTVAR(_out, 6, &Tco);
	TPLPUTEXECOUTVAR(_out, 7, &Tpl);
	TPLPUTEXECOUTVAR(_out, 8, &Lim);
	TPLPUTEXECOUTVAR(_out, 9, &Rcp);
	TPLPUTEXECOUTVAR(_out, 10, &Lt_id);
	TPLPUTEXECOUTVAR(_out, 11, &Pt_id);
	TPLPUTEXECOUTVAR(_out, 12, &Ps_id);
	TPLPUTEXECOUTVAR(_out, 13, &Item);
	TPLPUTEXECOUTVAR(_out, 14, &Status);
	TPLPUTEXECOUTVAR(_out, 15, &Errmsg);
	TPLPUTLASTOUTVAR(__out, 0, &Waf);
	TPLPUTLASTOUTVAR(__out, 1, &Die);
	TPLPUTLASTOUTVAR(__out, 2, &Mod);
	TPLPUTLASTOUTVAR(__out, 3, &Tst);
	TPLPUTLASTOUTVAR(__out, 4, &Prb);
	TPLPUTLASTOUTVAR(__out, 5, &Lms);
	TPLPUTLASTOUTVAR(__out, 6, &Tco);
	TPLPUTLASTOUTVAR(__out, 7, &Tpl);
	TPLPUTLASTOUTVAR(__out, 8, &Lim);
	TPLPUTLASTOUTVAR(__out, 9, &Rcp);
	TPLPUTLASTOUTVAR(__out, 10, &Lt_id);
	TPLPUTLASTOUTVAR(__out, 11, &Pt_id);
	TPLPUTLASTOUTVAR(__out, 12, &Ps_id);
	TPLPUTLASTOUTVAR(__out, 13, &Item);
	TPLPUTLASTOUTVAR(__out, 14, &Status);
	TPLPUTLASTOUTVAR(__out, 15, &Errmsg);
}

void
__FA_QUERY_RECIP(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Key;
	STRING	Filename;
	STRING	Waf;
	STRING	Die[256];
	STRING	Mod[256];
	STRING	Tst[256];
	STRING	Prb;
	STRING	Lms[256];
	STRING	Tco[16];
	STRING	Tpl;
	STRING	Lim;
	STRING	Rcp;
	STRING	Lt_id;
	STRING	Pt_id;
	STRING	Ps_id;
	STRING	Item[32];
	INTEGER	Status;
	STRING	Errmsg;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Key, _TYPES, 0, 0);
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Waf, _TYPES, 0, 0);
	TPLINITMEM(&Die, _TYPES, 256, 0);
	TPLINITMEM(&Mod, _TYPES, 256, 0);
	TPLINITMEM(&Tst, _TYPES, 256, 0);
	TPLINITMEM(&Prb, _TYPES, 0, 0);
	TPLINITMEM(&Lms, _TYPES, 256, 0);
	TPLINITMEM(&Tco, _TYPES, 16, 0);
	TPLINITMEM(&Tpl, _TYPES, 0, 0);
	TPLINITMEM(&Lim, _TYPES, 0, 0);
	TPLINITMEM(&Rcp, _TYPES, 0, 0);
	TPLINITMEM(&Lt_id, _TYPES, 0, 0);
	TPLINITMEM(&Pt_id, _TYPES, 0, 0);
	TPLINITMEM(&Ps_id, _TYPES, 0, 0);
	TPLINITMEM(&Item, _TYPES, 32, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Errmsg, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Key);
	TPLGETLASTINVAR(__in, 1, &Filename);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Waf);
	TPLGETLASTOUTVAR(__out, 1, &Die);
	TPLGETLASTOUTVAR(__out, 2, &Mod);
	TPLGETLASTOUTVAR(__out, 3, &Tst);
	TPLGETLASTOUTVAR(__out, 4, &Prb);
	TPLGETLASTOUTVAR(__out, 5, &Lms);
	TPLGETLASTOUTVAR(__out, 6, &Tco);
	TPLGETLASTOUTVAR(__out, 7, &Tpl);
	TPLGETLASTOUTVAR(__out, 8, &Lim);
	TPLGETLASTOUTVAR(__out, 9, &Rcp);
	TPLGETLASTOUTVAR(__out, 10, &Lt_id);
	TPLGETLASTOUTVAR(__out, 11, &Pt_id);
	TPLGETLASTOUTVAR(__out, 12, &Ps_id);
	TPLGETLASTOUTVAR(__out, 13, &Item);
	TPLGETLASTOUTVAR(__out, 14, &Status);
	TPLGETLASTOUTVAR(__out, 15, &Errmsg);

	/* Algorithm invocation */
	FA_QUERY_RECIP(Key,Filename,&Waf,&Die,&Mod,&Tst,&Prb,&Lms,&Tco,&Tpl,&Lim,&Rcp,&Lt_id,&Pt_id,&Ps_id,&Item,&Status,&Errmsg);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Waf);
	TPLPUTLASTOUTVAR(__out, 1, &Die);
	TPLPUTLASTOUTVAR(__out, 2, &Mod);
	TPLPUTLASTOUTVAR(__out, 3, &Tst);
	TPLPUTLASTOUTVAR(__out, 4, &Prb);
	TPLPUTLASTOUTVAR(__out, 5, &Lms);
	TPLPUTLASTOUTVAR(__out, 6, &Tco);
	TPLPUTLASTOUTVAR(__out, 7, &Tpl);
	TPLPUTLASTOUTVAR(__out, 8, &Lim);
	TPLPUTLASTOUTVAR(__out, 9, &Rcp);
	TPLPUTLASTOUTVAR(__out, 10, &Lt_id);
	TPLPUTLASTOUTVAR(__out, 11, &Pt_id);
	TPLPUTLASTOUTVAR(__out, 12, &Ps_id);
	TPLPUTLASTOUTVAR(__out, 13, &Item);
	TPLPUTLASTOUTVAR(__out, 14, &Status);
	TPLPUTLASTOUTVAR(__out, 15, &Errmsg);
}
