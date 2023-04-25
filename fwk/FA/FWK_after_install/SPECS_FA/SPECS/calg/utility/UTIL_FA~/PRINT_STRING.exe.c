#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_PRINT_STRING(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;

	/* Local input/output variable definition */
	STRING	Format;
	STRING	Value;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Format, _TYPES, 0, 0);
	TPLINITMEM(&Value, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Format);
	TPLGETEXECINVAR(_in, 1, &Value);
	TPLPUTLASTINVAR(__in, 0, &Format);
	TPLPUTLASTINVAR(__in, 1, &Value);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	PRINT_STRING(Format,Value);

	/* Algorithm output variable setting */
}

void
__PRINT_STRING(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;

	/* Local input/output variable definition */
	STRING	Format;
	STRING	Value;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Format, _TYPES, 0, 0);
	TPLINITMEM(&Value, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Format);
	TPLGETLASTINVAR(__in, 1, &Value);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	PRINT_STRING(Format,Value);

	/* Algorithm output variable setting */
}
