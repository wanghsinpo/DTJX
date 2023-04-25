#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_GEM_GETCMD(void *_alg)
{
}

void
__GEM_GETCMD(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_out;

	/* Local input/output variable definition */
	STRING	Cmd;
	STRING	Rply;
	STRING	Parms[500];

	/* Data pointer initialization */
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Cmd, _TYPES, 0, 0);
	TPLINITMEM(&Rply, _TYPES, 0, 0);
	TPLINITMEM(&Parms, _TYPES, 500, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Cmd);
	TPLGETDEBUGOUTVAR(_out, 1, &Rply);
	TPLGETDEBUGOUTVAR(_out, 2, &Parms);

	/* Algorithm invocation */
	GEM_GETCMD(&Cmd,&Rply,&Parms);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Cmd);
	TPLPUTDEBUGOUTVAR(_out, 1, &Rply);
	TPLPUTDEBUGOUTVAR(_out, 2, &Parms);
}
