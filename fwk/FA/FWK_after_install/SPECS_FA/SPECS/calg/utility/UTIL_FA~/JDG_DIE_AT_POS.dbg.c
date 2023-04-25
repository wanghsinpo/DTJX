#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_JDG_DIE_AT_POS(void *_alg)
{
}

void
__JDG_DIE_AT_POS(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Die_pos;
	INTEGER	Tgt_yld;
	INTEGER	Last;
	INTEGER	Jdg;
	REAL	Yld;
	INTEGER	Pass_cnt;
	INTEGER	Fail_cnt;
	INTEGER	Total_cnt;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Die_pos, _TYPEI, 0, 0);
	TPLINITMEM(&Tgt_yld, _TYPEI, 0, 0);
	TPLINITMEM(&Last, _TYPEI, 0, 0);
	TPLINITMEM(&Jdg, _TYPEI, 0, 0);
	TPLINITMEM(&Yld, _TYPER, 0, 0);
	TPLINITMEM(&Pass_cnt, _TYPEI, 0, 0);
	TPLINITMEM(&Fail_cnt, _TYPEI, 0, 0);
	TPLINITMEM(&Total_cnt, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Die_pos);
	TPLGETDEBUGINVAR(_in, 1, &Tgt_yld);
	TPLGETDEBUGINVAR(_in, 2, &Last);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Jdg);
	TPLGETDEBUGOUTVAR(_out, 1, &Yld);
	TPLGETDEBUGOUTVAR(_out, 2, &Pass_cnt);
	TPLGETDEBUGOUTVAR(_out, 3, &Fail_cnt);
	TPLGETDEBUGOUTVAR(_out, 4, &Total_cnt);

	/* Algorithm invocation */
	JDG_DIE_AT_POS(Die_pos,Tgt_yld,Last,&Jdg,&Yld,&Pass_cnt,&Fail_cnt,&Total_cnt);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Jdg);
	TPLPUTDEBUGOUTVAR(_out, 1, &Yld);
	TPLPUTDEBUGOUTVAR(_out, 2, &Pass_cnt);
	TPLPUTDEBUGOUTVAR(_out, 3, &Fail_cnt);
	TPLPUTDEBUGOUTVAR(_out, 4, &Total_cnt);
}
