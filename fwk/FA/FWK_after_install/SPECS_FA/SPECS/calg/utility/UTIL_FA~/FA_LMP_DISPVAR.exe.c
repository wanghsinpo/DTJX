#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_FA_LMP_DISPVAR(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	LineNth;
	STRING	DispLabel;
	INTEGER	DispVar;
	STRING	DispFgc;
	STRING	DispBgc;
	INTEGER	Status;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&LineNth, _TYPEI, 0, 0);
	TPLINITMEM(&DispLabel, _TYPES, 0, 0);
	TPLINITMEM(&DispVar, _TYPEI, 0, 0);
	TPLINITMEM(&DispFgc, _TYPES, 0, 0);
	TPLINITMEM(&DispBgc, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &LineNth);
	TPLGETEXECINVAR(_in, 1, &DispLabel);
	TPLGETEXECINVAR(_in, 2, &DispVar);
	TPLGETEXECINVAR(_in, 3, &DispFgc);
	TPLGETEXECINVAR(_in, 4, &DispBgc);
	TPLPUTLASTINVAR(__in, 0, &LineNth);
	TPLPUTLASTINVAR(__in, 1, &DispLabel);
	TPLPUTLASTINVAR(__in, 2, &DispVar);
	TPLPUTLASTINVAR(__in, 3, &DispFgc);
	TPLPUTLASTINVAR(__in, 4, &DispBgc);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 0, &Status);

	/* Algorithm invocation */
	FA_LMP_DISPVAR(LineNth,DispLabel,DispVar,DispFgc,DispBgc,&Status);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
}

void
__FA_LMP_DISPVAR(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	INTEGER	LineNth;
	STRING	DispLabel;
	INTEGER	DispVar;
	STRING	DispFgc;
	STRING	DispBgc;
	INTEGER	Status;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&LineNth, _TYPEI, 0, 0);
	TPLINITMEM(&DispLabel, _TYPES, 0, 0);
	TPLINITMEM(&DispVar, _TYPEI, 0, 0);
	TPLINITMEM(&DispFgc, _TYPES, 0, 0);
	TPLINITMEM(&DispBgc, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &LineNth);
	TPLGETLASTINVAR(__in, 1, &DispLabel);
	TPLGETLASTINVAR(__in, 2, &DispVar);
	TPLGETLASTINVAR(__in, 3, &DispFgc);
	TPLGETLASTINVAR(__in, 4, &DispBgc);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Status);

	/* Algorithm invocation */
	FA_LMP_DISPVAR(LineNth,DispLabel,DispVar,DispFgc,DispBgc,&Status);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Status);
}
