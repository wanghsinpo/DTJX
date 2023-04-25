#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_LOG_LOT_BEGIN(void *_alg)
{
}

void
__LOG_LOT_BEGIN(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;

	/* Local input/output variable definition */
	STRING	Session;
	STRING	Lotid;
	STRING	Testplan;
	STRING	Algorithm;
	STRING	Limitfile;
	STRING	Operator;
	STRING	Date;
	STRING	Time;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Lotid, _TYPES, 0, 0);
	TPLINITMEM(&Testplan, _TYPES, 0, 0);
	TPLINITMEM(&Algorithm, _TYPES, 0, 0);
	TPLINITMEM(&Limitfile, _TYPES, 0, 0);
	TPLINITMEM(&Operator, _TYPES, 0, 0);
	TPLINITMEM(&Date, _TYPES, 0, 0);
	TPLINITMEM(&Time, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Session);
	TPLGETDEBUGINVAR(_in, 1, &Lotid);
	TPLGETDEBUGINVAR(_in, 2, &Testplan);
	TPLGETDEBUGINVAR(_in, 3, &Algorithm);
	TPLGETDEBUGINVAR(_in, 4, &Limitfile);
	TPLGETDEBUGINVAR(_in, 5, &Operator);
	TPLGETDEBUGINVAR(_in, 6, &Date);
	TPLGETDEBUGINVAR(_in, 7, &Time);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	LOG_LOT_BEGIN(Session,Lotid,Testplan,Algorithm,Limitfile,Operator,Date,Time);

	/* Algorithm output variable setting */
}
