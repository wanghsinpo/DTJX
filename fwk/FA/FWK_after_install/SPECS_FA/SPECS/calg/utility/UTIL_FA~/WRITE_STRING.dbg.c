#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_WRITE_STRING(void *_alg)
{
}

void
__WRITE_STRING(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Format;
	STRING	Value;
	STRING	String;
	INTEGER	Length;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Format, _TYPES, 0, 0);
	TPLINITMEM(&Value, _TYPES, 0, 0);
	TPLINITMEM(&String, _TYPES, 0, 0);
	TPLINITMEM(&Length, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Format);
	TPLGETDEBUGINVAR(_in, 1, &Value);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &String);
	TPLGETDEBUGOUTVAR(_out, 1, &Length);

	/* Algorithm invocation */
	WRITE_STRING(Format,Value,&String,&Length);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &String);
	TPLPUTDEBUGOUTVAR(_out, 1, &Length);
}
