#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_GET_VGEMDEFAULT(void *_alg)
{
}

void
__GET_VGEMDEFAULT(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_out;

	/* Local input/output variable definition */
	STRING	Rcpmode;
	STRING	Rcpfilename;
	INTEGER	Status;

	/* Data pointer initialization */
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Rcpmode, _TYPES, 0, 0);
	TPLINITMEM(&Rcpfilename, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Rcpmode);
	TPLGETDEBUGOUTVAR(_out, 1, &Rcpfilename);
	TPLGETDEBUGOUTVAR(_out, 2, &Status);

	/* Algorithm invocation */
	GET_VGEMDEFAULT(&Rcpmode,&Rcpfilename,&Status);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Rcpmode);
	TPLPUTDEBUGOUTVAR(_out, 1, &Rcpfilename);
	TPLPUTDEBUGOUTVAR(_out, 2, &Status);
}
