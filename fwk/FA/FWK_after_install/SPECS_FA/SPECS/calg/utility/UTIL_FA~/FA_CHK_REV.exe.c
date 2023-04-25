#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_FA_CHK_REV(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Session;
	STRING	Kinds;
	INTEGER	Status;
	STRING	Filename;
	STRING	Rev;
	STRING	Path;
	STRING	BasicPath;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Kinds, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Rev, _TYPES, 0, 0);
	TPLINITMEM(&Path, _TYPES, 0, 0);
	TPLINITMEM(&BasicPath, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Session);
	TPLGETEXECINVAR(_in, 1, &Kinds);
	TPLPUTLASTINVAR(__in, 0, &Session);
	TPLPUTLASTINVAR(__in, 1, &Kinds);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Status);
	TPLGETEXECOUTVAR(_out, 1, &Filename);
	TPLGETEXECOUTVAR(_out, 2, &Rev);
	TPLGETEXECOUTVAR(_out, 3, &Path);
	TPLGETEXECOUTVAR(_out, 4, &BasicPath);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Filename);
	TPLPUTLASTOUTVAR(__out, 2, &Rev);
	TPLPUTLASTOUTVAR(__out, 3, &Path);
	TPLPUTLASTOUTVAR(__out, 4, &BasicPath);

	/* Algorithm invocation */
	FA_CHK_REV(Session,Kinds,&Status,&Filename,&Rev,&Path,&BasicPath);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Status);
	TPLPUTEXECOUTVAR(_out, 1, &Filename);
	TPLPUTEXECOUTVAR(_out, 2, &Rev);
	TPLPUTEXECOUTVAR(_out, 3, &Path);
	TPLPUTEXECOUTVAR(_out, 4, &BasicPath);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Filename);
	TPLPUTLASTOUTVAR(__out, 2, &Rev);
	TPLPUTLASTOUTVAR(__out, 3, &Path);
	TPLPUTLASTOUTVAR(__out, 4, &BasicPath);
}

void
__FA_CHK_REV(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Session;
	STRING	Kinds;
	INTEGER	Status;
	STRING	Filename;
	STRING	Rev;
	STRING	Path;
	STRING	BasicPath;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Kinds, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Rev, _TYPES, 0, 0);
	TPLINITMEM(&Path, _TYPES, 0, 0);
	TPLINITMEM(&BasicPath, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Session);
	TPLGETLASTINVAR(__in, 1, &Kinds);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Status);
	TPLGETLASTOUTVAR(__out, 1, &Filename);
	TPLGETLASTOUTVAR(__out, 2, &Rev);
	TPLGETLASTOUTVAR(__out, 3, &Path);
	TPLGETLASTOUTVAR(__out, 4, &BasicPath);

	/* Algorithm invocation */
	FA_CHK_REV(Session,Kinds,&Status,&Filename,&Rev,&Path,&BasicPath);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Filename);
	TPLPUTLASTOUTVAR(__out, 2, &Rev);
	TPLPUTLASTOUTVAR(__out, 3, &Path);
	TPLPUTLASTOUTVAR(__out, 4, &BasicPath);
}
