#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_QUERY_LAUNCH(void *_alg)
{
}

void
__QUERY_LAUNCH(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;

	/* Local input/output variable definition */
	STRING	Session;
	STRING	Port;
	STRING	Project;
	STRING	Hostname;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Port, _TYPES, 0, 0);
	TPLINITMEM(&Project, _TYPES, 0, 0);
	TPLINITMEM(&Hostname, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Session);
	TPLGETDEBUGINVAR(_in, 1, &Port);
	TPLGETDEBUGINVAR(_in, 2, &Project);
	TPLGETDEBUGINVAR(_in, 3, &Hostname);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	QUERY_LAUNCH(Session,Port,Project,Hostname);

	/* Algorithm output variable setting */
}
