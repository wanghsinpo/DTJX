#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_FA_RUNP_CREATE(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Meas_dir;
	STRING	Fwk_dir;
	STRING	Meas;
	STRING	Fwk;
	INTEGER	Status;
	STRING	Error;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Meas_dir, _TYPES, 0, 0);
	TPLINITMEM(&Fwk_dir, _TYPES, 0, 0);
	TPLINITMEM(&Meas, _TYPES, 0, 0);
	TPLINITMEM(&Fwk, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Meas_dir);
	TPLGETEXECINVAR(_in, 1, &Fwk_dir);
	TPLGETEXECINVAR(_in, 2, &Meas);
	TPLGETEXECINVAR(_in, 3, &Fwk);
	TPLPUTLASTINVAR(__in, 0, &Meas_dir);
	TPLPUTLASTINVAR(__in, 1, &Fwk_dir);
	TPLPUTLASTINVAR(__in, 2, &Meas);
	TPLPUTLASTINVAR(__in, 3, &Fwk);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Status);
	TPLGETEXECOUTVAR(_out, 1, &Error);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Error);

	/* Algorithm invocation */
	FA_RUNP_CREATE(Meas_dir,Fwk_dir,Meas,Fwk,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Status);
	TPLPUTEXECOUTVAR(_out, 1, &Error);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Error);
}

void
__FA_RUNP_CREATE(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Meas_dir;
	STRING	Fwk_dir;
	STRING	Meas;
	STRING	Fwk;
	INTEGER	Status;
	STRING	Error;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Meas_dir, _TYPES, 0, 0);
	TPLINITMEM(&Fwk_dir, _TYPES, 0, 0);
	TPLINITMEM(&Meas, _TYPES, 0, 0);
	TPLINITMEM(&Fwk, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Meas_dir);
	TPLGETLASTINVAR(__in, 1, &Fwk_dir);
	TPLGETLASTINVAR(__in, 2, &Meas);
	TPLGETLASTINVAR(__in, 3, &Fwk);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Status);
	TPLGETLASTOUTVAR(__out, 1, &Error);

	/* Algorithm invocation */
	FA_RUNP_CREATE(Meas_dir,Fwk_dir,Meas,Fwk,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Error);
}
