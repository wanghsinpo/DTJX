#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FA_CHK_REV(void *_alg)
{
}

void
__FA_CHK_REV(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Session;
	STRING	Kinds;
	INTEGER	Status;
	STRING	Filename;
	STRING	Rev;
	STRING	Path;
	STRING	BasicPath;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Kinds, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Rev, _TYPES, 0, 0);
	TPLINITMEM(&Path, _TYPES, 0, 0);
	TPLINITMEM(&BasicPath, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Session);
	TPLGETDEBUGINVAR(_in, 1, &Kinds);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);
	TPLGETDEBUGOUTVAR(_out, 1, &Filename);
	TPLGETDEBUGOUTVAR(_out, 2, &Rev);
	TPLGETDEBUGOUTVAR(_out, 3, &Path);
	TPLGETDEBUGOUTVAR(_out, 4, &BasicPath);

	/* Algorithm invocation */
	FA_CHK_REV(Session,Kinds,&Status,&Filename,&Rev,&Path,&BasicPath);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
	TPLPUTDEBUGOUTVAR(_out, 1, &Filename);
	TPLPUTDEBUGOUTVAR(_out, 2, &Rev);
	TPLPUTDEBUGOUTVAR(_out, 3, &Path);
	TPLPUTDEBUGOUTVAR(_out, 4, &BasicPath);
}
