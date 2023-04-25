#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FA_QUERY_COND(void *_alg)
{
}

void
__FA_QUERY_COND(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

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

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

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
	TPLGETDEBUGINVAR(_in, 0, &Key);
	TPLGETDEBUGINVAR(_in, 1, &Level);
	TPLGETDEBUGINVAR(_in, 2, &Filename);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Tco);
	TPLGETDEBUGOUTVAR(_out, 1, &Limf);
	TPLGETDEBUGOUTVAR(_out, 2, &DieLabel);
	TPLGETDEBUGOUTVAR(_out, 3, &DieType);
	TPLGETDEBUGOUTVAR(_out, 4, &ModLabel);
	TPLGETDEBUGOUTVAR(_out, 5, &Item);
	TPLGETDEBUGOUTVAR(_out, 6, &Status);
	TPLGETDEBUGOUTVAR(_out, 7, &Errmsg);

	/* Algorithm invocation */
	FA_QUERY_COND(Key,Level,Filename,&Tco,&Limf,&DieLabel,&DieType,&ModLabel,&Item,&Status,&Errmsg);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Tco);
	TPLPUTDEBUGOUTVAR(_out, 1, &Limf);
	TPLPUTDEBUGOUTVAR(_out, 2, &DieLabel);
	TPLPUTDEBUGOUTVAR(_out, 3, &DieType);
	TPLPUTDEBUGOUTVAR(_out, 4, &ModLabel);
	TPLPUTDEBUGOUTVAR(_out, 5, &Item);
	TPLPUTDEBUGOUTVAR(_out, 6, &Status);
	TPLPUTDEBUGOUTVAR(_out, 7, &Errmsg);
}
