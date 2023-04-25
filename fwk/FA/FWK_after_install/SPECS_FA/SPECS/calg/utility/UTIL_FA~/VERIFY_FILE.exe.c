#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_VERIFY_FILE(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Filename;
	STRING	Type;
	INTEGER	Exist;
	INTEGER	Readable;
	INTEGER	Writable;
	INTEGER	Executable;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Type, _TYPES, 0, 0);
	TPLINITMEM(&Exist, _TYPEI, 0, 0);
	TPLINITMEM(&Readable, _TYPEI, 0, 0);
	TPLINITMEM(&Writable, _TYPEI, 0, 0);
	TPLINITMEM(&Executable, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Filename);
	TPLGETEXECINVAR(_in, 1, &Type);
	TPLPUTLASTINVAR(__in, 0, &Filename);
	TPLPUTLASTINVAR(__in, 1, &Type);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Exist);
	TPLGETEXECOUTVAR(_out, 1, &Readable);
	TPLGETEXECOUTVAR(_out, 2, &Writable);
	TPLGETEXECOUTVAR(_out, 3, &Executable);
	TPLPUTLASTOUTVAR(__out, 0, &Exist);
	TPLPUTLASTOUTVAR(__out, 1, &Readable);
	TPLPUTLASTOUTVAR(__out, 2, &Writable);
	TPLPUTLASTOUTVAR(__out, 3, &Executable);

	/* Algorithm invocation */
	VERIFY_FILE(Filename,Type,&Exist,&Readable,&Writable,&Executable);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Exist);
	TPLPUTEXECOUTVAR(_out, 1, &Readable);
	TPLPUTEXECOUTVAR(_out, 2, &Writable);
	TPLPUTEXECOUTVAR(_out, 3, &Executable);
	TPLPUTLASTOUTVAR(__out, 0, &Exist);
	TPLPUTLASTOUTVAR(__out, 1, &Readable);
	TPLPUTLASTOUTVAR(__out, 2, &Writable);
	TPLPUTLASTOUTVAR(__out, 3, &Executable);
}

void
__VERIFY_FILE(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Filename;
	STRING	Type;
	INTEGER	Exist;
	INTEGER	Readable;
	INTEGER	Writable;
	INTEGER	Executable;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Filename, _TYPES, 0, 0);
	TPLINITMEM(&Type, _TYPES, 0, 0);
	TPLINITMEM(&Exist, _TYPEI, 0, 0);
	TPLINITMEM(&Readable, _TYPEI, 0, 0);
	TPLINITMEM(&Writable, _TYPEI, 0, 0);
	TPLINITMEM(&Executable, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Filename);
	TPLGETLASTINVAR(__in, 1, &Type);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Exist);
	TPLGETLASTOUTVAR(__out, 1, &Readable);
	TPLGETLASTOUTVAR(__out, 2, &Writable);
	TPLGETLASTOUTVAR(__out, 3, &Executable);

	/* Algorithm invocation */
	VERIFY_FILE(Filename,Type,&Exist,&Readable,&Writable,&Executable);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Exist);
	TPLPUTLASTOUTVAR(__out, 1, &Readable);
	TPLPUTLASTOUTVAR(__out, 2, &Writable);
	TPLPUTLASTOUTVAR(__out, 3, &Executable);
}
