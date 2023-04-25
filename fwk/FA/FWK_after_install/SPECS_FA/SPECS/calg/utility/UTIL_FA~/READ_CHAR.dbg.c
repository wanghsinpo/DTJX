#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_READ_CHAR(void *_alg)
{
}

void
__READ_CHAR(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Format;
	STRING	String;
	CHARACTER	Value;
	INTEGER	Stat;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Format, _TYPES, 0, 0);
	TPLINITMEM(&String, _TYPES, 0, 0);
	TPLINITMEM(&Value, _TYPEC, 0, 0);
	TPLINITMEM(&Stat, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Format);
	TPLGETDEBUGINVAR(_in, 1, &String);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Value);
	TPLGETDEBUGOUTVAR(_out, 1, &Stat);

	/* Algorithm invocation */
	READ_CHAR(Format,String,&Value,&Stat);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Value);
	TPLPUTDEBUGOUTVAR(_out, 1, &Stat);
}
