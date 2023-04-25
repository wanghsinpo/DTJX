#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_RCP_QUERY_RECIP(void *_alg)
{
}

void
__RCP_QUERY_RECIP(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

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
	STRING	Mlib[6];
	STRING	Item[32];
	INTEGER	Status;
	STRING	Errmsg;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

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
	TPLINITMEM(&Mlib, _TYPES, 6, 0);
	TPLINITMEM(&Item, _TYPES, 32, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Errmsg, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Key);
	TPLGETDEBUGINVAR(_in, 1, &Filename);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Waf);
	TPLGETDEBUGOUTVAR(_out, 1, &Die);
	TPLGETDEBUGOUTVAR(_out, 2, &Mod);
	TPLGETDEBUGOUTVAR(_out, 3, &Tst);
	TPLGETDEBUGOUTVAR(_out, 4, &Prb);
	TPLGETDEBUGOUTVAR(_out, 5, &Lms);
	TPLGETDEBUGOUTVAR(_out, 6, &Tco);
	TPLGETDEBUGOUTVAR(_out, 7, &Mlib);
	TPLGETDEBUGOUTVAR(_out, 8, &Item);
	TPLGETDEBUGOUTVAR(_out, 9, &Status);
	TPLGETDEBUGOUTVAR(_out, 10, &Errmsg);

	/* Algorithm invocation */
	RCP_QUERY_RECIP(Key,Filename,&Waf,&Die,&Mod,&Tst,&Prb,&Lms,&Tco,&Mlib,&Item,&Status,&Errmsg);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Waf);
	TPLPUTDEBUGOUTVAR(_out, 1, &Die);
	TPLPUTDEBUGOUTVAR(_out, 2, &Mod);
	TPLPUTDEBUGOUTVAR(_out, 3, &Tst);
	TPLPUTDEBUGOUTVAR(_out, 4, &Prb);
	TPLPUTDEBUGOUTVAR(_out, 5, &Lms);
	TPLPUTDEBUGOUTVAR(_out, 6, &Tco);
	TPLPUTDEBUGOUTVAR(_out, 7, &Mlib);
	TPLPUTDEBUGOUTVAR(_out, 8, &Item);
	TPLPUTDEBUGOUTVAR(_out, 9, &Status);
	TPLPUTDEBUGOUTVAR(_out, 10, &Errmsg);
}
