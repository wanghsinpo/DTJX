#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_SET_TAG_INTEGER(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;

	/* Local input/output variable definition */
	STRING	Name;
	INTEGER	Value;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Name, _TYPES, 0, 0);
	TPLINITMEM(&Value, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Name);
	TPLGETEXECINVAR(_in, 1, &Value);
	TPLPUTLASTINVAR(__in, 0, &Name);
	TPLPUTLASTINVAR(__in, 1, &Value);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	SET_TAG_INTEGER(Name,Value);

	/* Algorithm output variable setting */
}

void
__SET_TAG_INTEGER(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;

	/* Local input/output variable definition */
	STRING	Name;
	INTEGER	Value;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Name, _TYPES, 0, 0);
	TPLINITMEM(&Value, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Name);
	TPLGETLASTINVAR(__in, 1, &Value);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	SET_TAG_INTEGER(Name,Value);

	/* Algorithm output variable setting */
}
