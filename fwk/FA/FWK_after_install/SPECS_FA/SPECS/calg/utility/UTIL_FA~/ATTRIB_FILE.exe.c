#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_ATTRIB_FILE(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Filename;
	STRING	Permission;
	STRING	Owner;
	STRING	Group;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Permission, _TYPES, 0, 0);
	TPLINITMEM(&Owner, _TYPES, 0, 0);
	TPLINITMEM(&Group, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Filename);
	TPLPUTLASTINVAR(__in, 0, &Filename);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Permission);
	TPLGETEXECOUTVAR(_out, 1, &Owner);
	TPLGETEXECOUTVAR(_out, 2, &Group);
	TPLPUTLASTOUTVAR(__out, 0, &Permission);
	TPLPUTLASTOUTVAR(__out, 1, &Owner);
	TPLPUTLASTOUTVAR(__out, 2, &Group);

	/* Algorithm invocation */
	ATTRIB_FILE(Filename,&Permission,&Owner,&Group);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Permission);
	TPLPUTEXECOUTVAR(_out, 1, &Owner);
	TPLPUTEXECOUTVAR(_out, 2, &Group);
	TPLPUTLASTOUTVAR(__out, 0, &Permission);
	TPLPUTLASTOUTVAR(__out, 1, &Owner);
	TPLPUTLASTOUTVAR(__out, 2, &Group);
}

void
__ATTRIB_FILE(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Filename;
	STRING	Permission;
	STRING	Owner;
	STRING	Group;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Permission, _TYPES, 0, 0);
	TPLINITMEM(&Owner, _TYPES, 0, 0);
	TPLINITMEM(&Group, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Filename);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Permission);
	TPLGETLASTOUTVAR(__out, 1, &Owner);
	TPLGETLASTOUTVAR(__out, 2, &Group);

	/* Algorithm invocation */
	ATTRIB_FILE(Filename,&Permission,&Owner,&Group);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Permission);
	TPLPUTLASTOUTVAR(__out, 1, &Owner);
	TPLPUTLASTOUTVAR(__out, 2, &Group);
}
