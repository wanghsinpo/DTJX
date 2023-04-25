#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FA_MK_DATANAME(void *_alg)
{
}

void
__FA_MK_DATANAME(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Dir;
	STRING	File;
	INTEGER	Slot;
	STRING	Adtfmt;
	STRING	Session;
	STRING	Datadir;
	STRING	Dataname;
	INTEGER	Status;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Dir, _TYPES, 0, 0);
	TPLINITMEM(&File, _TYPES, 0, 0);
	TPLINITMEM(&Slot, _TYPEI, 0, 0);
	TPLINITMEM(&Adtfmt, _TYPES, 0, 0);
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Datadir, _TYPES, 0, 0);
	TPLINITMEM(&Dataname, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Dir);
	TPLGETDEBUGINVAR(_in, 1, &File);
	TPLGETDEBUGINVAR(_in, 2, &Slot);
	TPLGETDEBUGINVAR(_in, 3, &Adtfmt);
	TPLGETDEBUGINVAR(_in, 4, &Session);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Datadir);
	TPLGETDEBUGOUTVAR(_out, 1, &Dataname);
	TPLGETDEBUGOUTVAR(_out, 2, &Status);

	/* Algorithm invocation */
	FA_MK_DATANAME(Dir,File,Slot,Adtfmt,Session,&Datadir,&Dataname,&Status);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Datadir);
	TPLPUTDEBUGOUTVAR(_out, 1, &Dataname);
	TPLPUTDEBUGOUTVAR(_out, 2, &Status);
}
