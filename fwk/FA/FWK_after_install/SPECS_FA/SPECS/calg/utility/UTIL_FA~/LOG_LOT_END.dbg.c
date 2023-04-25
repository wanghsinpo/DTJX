#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_LOG_LOT_END(void *_alg)
{
}

void
__LOG_LOT_END(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;

	/* Local input/output variable definition */
	STRING	Session;
	STRING	State;
	INTEGER	Result;
	STRING	Datadir;
	STRING	Dataname;
	STRING	Time;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&State, _TYPES, 0, 0);
	TPLINITMEM(&Result, _TYPEI, 0, 0);
	TPLINITMEM(&Datadir, _TYPES, 0, 0);
	TPLINITMEM(&Dataname, _TYPES, 0, 0);
	TPLINITMEM(&Time, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Session);
	TPLGETDEBUGINVAR(_in, 1, &State);
	TPLGETDEBUGINVAR(_in, 2, &Result);
	TPLGETDEBUGINVAR(_in, 3, &Datadir);
	TPLGETDEBUGINVAR(_in, 4, &Dataname);
	TPLGETDEBUGINVAR(_in, 5, &Time);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	LOG_LOT_END(Session,State,Result,Datadir,Dataname,Time);

	/* Algorithm output variable setting */
}
