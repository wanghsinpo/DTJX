#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FA_GETKEY_ITEMS(void *_alg)
{
}

void
__FA_GETKEY_ITEMS(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

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

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

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
	TPLGETDEBUGINVAR(_in, 0, &Key);
	TPLGETDEBUGINVAR(_in, 1, &Filename);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Waf);
	TPLGETDEBUGOUTVAR(_out, 1, &Die);
	TPLGETDEBUGOUTVAR(_out, 2, &Tst);
	TPLGETDEBUGOUTVAR(_out, 3, &Prb);
	TPLGETDEBUGOUTVAR(_out, 4, &Tpl);
	TPLGETDEBUGOUTVAR(_out, 5, &Lim);
	TPLGETDEBUGOUTVAR(_out, 6, &Rcp);
	TPLGETDEBUGOUTVAR(_out, 7, &Lot_id);
	TPLGETDEBUGOUTVAR(_out, 8, &Product_id);
	TPLGETDEBUGOUTVAR(_out, 9, &Process_id);
	TPLGETDEBUGOUTVAR(_out, 10, &Status);

	/* Algorithm invocation */
	FA_GETKEY_ITEMS(Key,Filename,&Waf,&Die,&Tst,&Prb,&Tpl,&Lim,&Rcp,&Lot_id,&Product_id,&Process_id,&Status);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Waf);
	TPLPUTDEBUGOUTVAR(_out, 1, &Die);
	TPLPUTDEBUGOUTVAR(_out, 2, &Tst);
	TPLPUTDEBUGOUTVAR(_out, 3, &Prb);
	TPLPUTDEBUGOUTVAR(_out, 4, &Tpl);
	TPLPUTDEBUGOUTVAR(_out, 5, &Lim);
	TPLPUTDEBUGOUTVAR(_out, 6, &Rcp);
	TPLPUTDEBUGOUTVAR(_out, 7, &Lot_id);
	TPLPUTDEBUGOUTVAR(_out, 8, &Product_id);
	TPLPUTDEBUGOUTVAR(_out, 9, &Process_id);
	TPLPUTDEBUGOUTVAR(_out, 10, &Status);
}
