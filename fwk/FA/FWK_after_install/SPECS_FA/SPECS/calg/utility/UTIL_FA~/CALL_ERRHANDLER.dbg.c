#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_CALL_ERRHANDLER(void *_alg)
{
}

void
__CALL_ERRHANDLER(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	ErrorNo;
	STRING	Message;
	STRING	MoreInfo;
	INTEGER	Status;
	STRING	Errmsg;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&ErrorNo, _TYPES, 0, 0);
	TPLINITMEM(&Message, _TYPES, 0, 0);
	TPLINITMEM(&MoreInfo, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Errmsg, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &ErrorNo);
	TPLGETDEBUGINVAR(_in, 1, &Message);
	TPLGETDEBUGINVAR(_in, 2, &MoreInfo);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);
	TPLGETDEBUGOUTVAR(_out, 1, &Errmsg);

	/* Algorithm invocation */
	CALL_ERRHANDLER(ErrorNo,Message,MoreInfo,&Status,&Errmsg);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
	TPLPUTDEBUGOUTVAR(_out, 1, &Errmsg);
}
