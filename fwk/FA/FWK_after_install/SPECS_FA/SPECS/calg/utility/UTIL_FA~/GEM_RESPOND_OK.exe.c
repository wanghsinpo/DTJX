#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_GEM_RESPOND_OK(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	ReplyMailbox;
	REAL	Timeout;
	INTEGER	Status;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&ReplyMailbox, _TYPES, 0, 0);
	TPLINITMEM(&Timeout, _TYPER, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &ReplyMailbox);
	TPLGETEXECINVAR(_in, 1, &Timeout);
	TPLPUTLASTINVAR(__in, 0, &ReplyMailbox);
	TPLPUTLASTINVAR(__in, 1, &Timeout);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 0, &Status);

	/* Algorithm invocation */
	GEM_RESPOND_OK(ReplyMailbox,Timeout,&Status);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
}

void
__GEM_RESPOND_OK(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	ReplyMailbox;
	REAL	Timeout;
	INTEGER	Status;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&ReplyMailbox, _TYPES, 0, 0);
	TPLINITMEM(&Timeout, _TYPER, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &ReplyMailbox);
	TPLGETLASTINVAR(__in, 1, &Timeout);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Status);

	/* Algorithm invocation */
	GEM_RESPOND_OK(ReplyMailbox,Timeout,&Status);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Status);
}
