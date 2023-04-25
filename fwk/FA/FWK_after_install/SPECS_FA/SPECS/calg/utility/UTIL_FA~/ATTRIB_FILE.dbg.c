#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_ATTRIB_FILE(void *_alg)
{
}

void
__ATTRIB_FILE(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Filename;
	STRING	Permission;
	STRING	Owner;
	STRING	Group;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Permission, _TYPES, 0, 0);
	TPLINITMEM(&Owner, _TYPES, 0, 0);
	TPLINITMEM(&Group, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Filename);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Permission);
	TPLGETDEBUGOUTVAR(_out, 1, &Owner);
	TPLGETDEBUGOUTVAR(_out, 2, &Group);

	/* Algorithm invocation */
	ATTRIB_FILE(Filename,&Permission,&Owner,&Group);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Permission);
	TPLPUTDEBUGOUTVAR(_out, 1, &Owner);
	TPLPUTDEBUGOUTVAR(_out, 2, &Group);
}
