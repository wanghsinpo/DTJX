#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_UPDATE_FWKCONF(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	File;
	INTEGER	Type;
	INTEGER	Errno;
	STRING	Errmsg;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&File, _TYPES, 0, 0);
	TPLINITMEM(&Type, _TYPEI, 0, 0);
	TPLINITMEM(&Errno, _TYPEI, 0, 0);
	TPLINITMEM(&Errmsg, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &File);
	TPLGETEXECINVAR(_in, 1, &Type);
	TPLPUTLASTINVAR(__in, 0, &File);
	TPLPUTLASTINVAR(__in, 1, &Type);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Errno);
	TPLGETEXECOUTVAR(_out, 1, &Errmsg);
	TPLPUTLASTOUTVAR(__out, 0, &Errno);
	TPLPUTLASTOUTVAR(__out, 1, &Errmsg);

	/* Algorithm invocation */
	UPDATE_FWKCONF(File,Type,&Errno,&Errmsg);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Errno);
	TPLPUTEXECOUTVAR(_out, 1, &Errmsg);
	TPLPUTLASTOUTVAR(__out, 0, &Errno);
	TPLPUTLASTOUTVAR(__out, 1, &Errmsg);
}

void
__UPDATE_FWKCONF(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	File;
	INTEGER	Type;
	INTEGER	Errno;
	STRING	Errmsg;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&File, _TYPES, 0, 0);
	TPLINITMEM(&Type, _TYPEI, 0, 0);
	TPLINITMEM(&Errno, _TYPEI, 0, 0);
	TPLINITMEM(&Errmsg, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &File);
	TPLGETLASTINVAR(__in, 1, &Type);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Errno);
	TPLGETLASTOUTVAR(__out, 1, &Errmsg);

	/* Algorithm invocation */
	UPDATE_FWKCONF(File,Type,&Errno,&Errmsg);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Errno);
	TPLPUTLASTOUTVAR(__out, 1, &Errmsg);
}
