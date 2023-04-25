#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FA_UPD_VGEMVAR(void *_alg)
{
}

void
__FA_UPD_VGEMVAR(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	INTEGER	SendCEID;
	STRING	VarName;
	STRING	VarData;
	INTEGER	Status;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&SendCEID, _TYPEI, 0, 0);
	TPLINITMEM(&VarName, _TYPES, 0, 0);
	TPLINITMEM(&VarData, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &SendCEID);
	TPLGETDEBUGINVAR(_in, 1, &VarName);
	TPLGETDEBUGINVAR(_in, 2, &VarData);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);

	/* Algorithm invocation */
	FA_UPD_VGEMVAR(SendCEID,VarName,VarData,&Status);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
}
