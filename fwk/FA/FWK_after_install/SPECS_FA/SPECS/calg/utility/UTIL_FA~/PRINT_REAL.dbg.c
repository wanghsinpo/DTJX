#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_PRINT_REAL(void *_alg)
{
}

void
__PRINT_REAL(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;

	/* Local input/output variable definition */
	STRING	Format;
	REAL	Value;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Format, _TYPES, 0, 0);
	TPLINITMEM(&Value, _TYPER, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Format);
	TPLGETDEBUGINVAR(_in, 1, &Value);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	PRINT_REAL(Format,Value);

	/* Algorithm output variable setting */
}
