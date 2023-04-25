#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_GET_PREV_MOD(void *_alg)
{
}

void
__GET_PREV_MOD(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Typeindex_c;
	INTEGER	Diex_c;
	INTEGER	Diey_c;
	STRING	Modname_c;
	INTEGER	Typeindex;
	INTEGER	Diex;
	INTEGER	Diey;
	STRING	Modname;
	INTEGER	Stat;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Typeindex_c, _TYPEI, 0, 0);
	TPLINITMEM(&Diex_c, _TYPEI, 0, 0);
	TPLINITMEM(&Diey_c, _TYPEI, 0, 0);
	TPLINITMEM(&Modname_c, _TYPES, 0, 0);
	TPLINITMEM(&Typeindex, _TYPEI, 0, 0);
	TPLINITMEM(&Diex, _TYPEI, 0, 0);
	TPLINITMEM(&Diey, _TYPEI, 0, 0);
	TPLINITMEM(&Modname, _TYPES, 0, 0);
	TPLINITMEM(&Stat, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Typeindex_c);
	TPLGETDEBUGINVAR(_in, 1, &Diex_c);
	TPLGETDEBUGINVAR(_in, 2, &Diey_c);
	TPLGETDEBUGINVAR(_in, 3, &Modname_c);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Typeindex);
	TPLGETDEBUGOUTVAR(_out, 1, &Diex);
	TPLGETDEBUGOUTVAR(_out, 2, &Diey);
	TPLGETDEBUGOUTVAR(_out, 3, &Modname);
	TPLGETDEBUGOUTVAR(_out, 4, &Stat);

	/* Algorithm invocation */
	GET_PREV_MOD(Typeindex_c,Diex_c,Diey_c,Modname_c,&Typeindex,&Diex,&Diey,&Modname,&Stat);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Typeindex);
	TPLPUTDEBUGOUTVAR(_out, 1, &Diex);
	TPLPUTDEBUGOUTVAR(_out, 2, &Diey);
	TPLPUTDEBUGOUTVAR(_out, 3, &Modname);
	TPLPUTDEBUGOUTVAR(_out, 4, &Stat);
}
