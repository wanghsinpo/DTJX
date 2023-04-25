#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_FA_CHKRUN_FWK(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Name;
	STRING	Status;
	INTEGER	numFile;
	INTEGER	numRunning;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Name, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPES, 0, 0);
	TPLINITMEM(&numFile, _TYPEI, 0, 0);
	TPLINITMEM(&numRunning, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Name);
	TPLGETEXECINVAR(_in, 1, &Status);
	TPLPUTLASTINVAR(__in, 0, &Name);
	TPLPUTLASTINVAR(__in, 1, &Status);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &numFile);
	TPLGETEXECOUTVAR(_out, 1, &numRunning);
	TPLPUTLASTOUTVAR(__out, 0, &numFile);
	TPLPUTLASTOUTVAR(__out, 1, &numRunning);

	/* Algorithm invocation */
	FA_CHKRUN_FWK(Name,Status,&numFile,&numRunning);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &numFile);
	TPLPUTEXECOUTVAR(_out, 1, &numRunning);
	TPLPUTLASTOUTVAR(__out, 0, &numFile);
	TPLPUTLASTOUTVAR(__out, 1, &numRunning);
}

void
__FA_CHKRUN_FWK(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Name;
	STRING	Status;
	INTEGER	numFile;
	INTEGER	numRunning;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Name, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPES, 0, 0);
	TPLINITMEM(&numFile, _TYPEI, 0, 0);
	TPLINITMEM(&numRunning, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Name);
	TPLGETLASTINVAR(__in, 1, &Status);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &numFile);
	TPLGETLASTOUTVAR(__out, 1, &numRunning);

	/* Algorithm invocation */
	FA_CHKRUN_FWK(Name,Status,&numFile,&numRunning);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &numFile);
	TPLPUTLASTOUTVAR(__out, 1, &numRunning);
}
