#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_NAME_TMPDATA(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Basename;
	STRING	Session;
	STRING	Tmpname;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Basename, _TYPES, 0, 0);
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Tmpname, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Basename);
	TPLGETEXECINVAR(_in, 1, &Session);
	TPLPUTLASTINVAR(__in, 0, &Basename);
	TPLPUTLASTINVAR(__in, 1, &Session);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Tmpname);
	TPLPUTLASTOUTVAR(__out, 0, &Tmpname);

	/* Algorithm invocation */
	NAME_TMPDATA(Basename,Session,&Tmpname);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Tmpname);
	TPLPUTLASTOUTVAR(__out, 0, &Tmpname);
}

void
__NAME_TMPDATA(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Basename;
	STRING	Session;
	STRING	Tmpname;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Basename, _TYPES, 0, 0);
	TPLINITMEM(&Session, _TYPES, 0, 0);
	TPLINITMEM(&Tmpname, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Basename);
	TPLGETLASTINVAR(__in, 1, &Session);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Tmpname);

	/* Algorithm invocation */
	NAME_TMPDATA(Basename,Session,&Tmpname);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Tmpname);
}
