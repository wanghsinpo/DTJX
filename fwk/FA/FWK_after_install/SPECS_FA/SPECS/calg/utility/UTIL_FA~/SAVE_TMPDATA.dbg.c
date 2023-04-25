#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_SAVE_TMPDATA(void *_alg)
{
}

void
__SAVE_TMPDATA(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Path;
	STRING	Name;
	STRING	Format;
	STRING	Session;
	INTEGER	Stat;
	STRING	Error;
	STRING	Pubname;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Path, _TYPES, 0, 0);
	TPLINITMEM(&Name, _TYPES, 0, 0);
	TPLINITMEM(&Format, _TYPES, 0, 0);
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Stat, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);
	TPLINITMEM(&Pubname, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Path);
	TPLGETDEBUGINVAR(_in, 1, &Name);
	TPLGETDEBUGINVAR(_in, 2, &Format);
	TPLGETDEBUGINVAR(_in, 3, &Session);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Stat);
	TPLGETDEBUGOUTVAR(_out, 1, &Error);
	TPLGETDEBUGOUTVAR(_out, 2, &Pubname);

	/* Algorithm invocation */
	SAVE_TMPDATA(Path,Name,Format,Session,&Stat,&Error,&Pubname);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Stat);
	TPLPUTDEBUGOUTVAR(_out, 1, &Error);
	TPLPUTDEBUGOUTVAR(_out, 2, &Pubname);
}
