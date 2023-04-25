#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_SAVE_TMPDATA(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Path;
	STRING	Name;
	STRING	Format;
	STRING	Session;
	INTEGER	Stat;
	STRING	Error;
	STRING	Pubname;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Path, _TYPES, 0, 0);
	TPLINITMEM(&Name, _TYPES, 0, 0);
	TPLINITMEM(&Format, _TYPES, 0, 0);
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Stat, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);
	TPLINITMEM(&Pubname, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Path);
	TPLGETEXECINVAR(_in, 1, &Name);
	TPLGETEXECINVAR(_in, 2, &Format);
	TPLGETEXECINVAR(_in, 3, &Session);
	TPLPUTLASTINVAR(__in, 0, &Path);
	TPLPUTLASTINVAR(__in, 1, &Name);
	TPLPUTLASTINVAR(__in, 2, &Format);
	TPLPUTLASTINVAR(__in, 3, &Session);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Stat);
	TPLGETEXECOUTVAR(_out, 1, &Error);
	TPLGETEXECOUTVAR(_out, 2, &Pubname);
	TPLPUTLASTOUTVAR(__out, 0, &Stat);
	TPLPUTLASTOUTVAR(__out, 1, &Error);
	TPLPUTLASTOUTVAR(__out, 2, &Pubname);

	/* Algorithm invocation */
	SAVE_TMPDATA(Path,Name,Format,Session,&Stat,&Error,&Pubname);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Stat);
	TPLPUTEXECOUTVAR(_out, 1, &Error);
	TPLPUTEXECOUTVAR(_out, 2, &Pubname);
	TPLPUTLASTOUTVAR(__out, 0, &Stat);
	TPLPUTLASTOUTVAR(__out, 1, &Error);
	TPLPUTLASTOUTVAR(__out, 2, &Pubname);
}

void
__SAVE_TMPDATA(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Path;
	STRING	Name;
	STRING	Format;
	STRING	Session;
	INTEGER	Stat;
	STRING	Error;
	STRING	Pubname;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Path, _TYPES, 0, 0);
	TPLINITMEM(&Name, _TYPES, 0, 0);
	TPLINITMEM(&Format, _TYPES, 0, 0);
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Stat, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);
	TPLINITMEM(&Pubname, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Path);
	TPLGETLASTINVAR(__in, 1, &Name);
	TPLGETLASTINVAR(__in, 2, &Format);
	TPLGETLASTINVAR(__in, 3, &Session);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Stat);
	TPLGETLASTOUTVAR(__out, 1, &Error);
	TPLGETLASTOUTVAR(__out, 2, &Pubname);

	/* Algorithm invocation */
	SAVE_TMPDATA(Path,Name,Format,Session,&Stat,&Error,&Pubname);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Stat);
	TPLPUTLASTOUTVAR(__out, 1, &Error);
	TPLPUTLASTOUTVAR(__out, 2, &Pubname);
}
