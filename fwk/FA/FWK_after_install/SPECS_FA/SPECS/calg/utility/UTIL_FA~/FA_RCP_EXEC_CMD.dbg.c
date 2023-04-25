#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FA_RCP_EXEC_CMD(void *_alg)
{
}

void
__FA_RCP_EXEC_CMD(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Cmd;
	STRING	Result;
	INTEGER	Status;
	STRING	Errmsg;
	INTEGER	Ndetail;
	STRING	Detail[10];
	INTEGER	Cmd_ret;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Cmd, _TYPES, 0, 0);
	TPLINITMEM(&Result, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Errmsg, _TYPES, 0, 0);
	TPLINITMEM(&Ndetail, _TYPEI, 0, 0);
	TPLINITMEM(&Detail, _TYPES, 10, 0);
	TPLINITMEM(&Cmd_ret, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Cmd);
	TPLGETDEBUGINVAR(_in, 1, &Result);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);
	TPLGETDEBUGOUTVAR(_out, 1, &Errmsg);
	TPLGETDEBUGOUTVAR(_out, 2, &Ndetail);
	TPLGETDEBUGOUTVAR(_out, 3, &Detail);
	TPLGETDEBUGOUTVAR(_out, 4, &Cmd_ret);

	/* Algorithm invocation */
	FA_RCP_EXEC_CMD(Cmd,Result,&Status,&Errmsg,&Ndetail,&Detail,&Cmd_ret);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
	TPLPUTDEBUGOUTVAR(_out, 1, &Errmsg);
	TPLPUTDEBUGOUTVAR(_out, 2, &Ndetail);
	TPLPUTDEBUGOUTVAR(_out, 3, &Detail);
	TPLPUTDEBUGOUTVAR(_out, 4, &Cmd_ret);
}
