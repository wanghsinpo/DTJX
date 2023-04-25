#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_RCP_LIMBLD(void *_alg)
{
}

void
__RCP_LIMBLD(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	STRING	Tpl_dir;
	STRING	Lms_dir;
	STRING	Lim_dir;
	STRING	Tpl;
	STRING	Lms[256];
	STRING	Lim;
	INTEGER	Status;
	STRING	Errmsg;
	INTEGER	Ndetail;
	STRING	Detail[10];

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Tpl_dir, _TYPES, 0, 0);
	TPLINITMEM(&Lms_dir, _TYPES, 0, 0);
	TPLINITMEM(&Lim_dir, _TYPES, 0, 0);
	TPLINITMEM(&Tpl, _TYPES, 0, 0);
	TPLINITMEM(&Lms, _TYPES, 256, 0);
	TPLINITMEM(&Lim, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Errmsg, _TYPES, 0, 0);
	TPLINITMEM(&Ndetail, _TYPEI, 0, 0);
	TPLINITMEM(&Detail, _TYPES, 10, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Tpl_dir);
	TPLGETDEBUGINVAR(_in, 1, &Lms_dir);
	TPLGETDEBUGINVAR(_in, 2, &Lim_dir);
	TPLGETDEBUGINVAR(_in, 3, &Tpl);
	TPLGETDEBUGINVAR(_in, 4, &Lms);
	TPLGETDEBUGINVAR(_in, 5, &Lim);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);
	TPLGETDEBUGOUTVAR(_out, 1, &Errmsg);
	TPLGETDEBUGOUTVAR(_out, 2, &Ndetail);
	TPLGETDEBUGOUTVAR(_out, 3, &Detail);

	/* Algorithm invocation */
	RCP_LIMBLD(Tpl_dir,Lms_dir,Lim_dir,Tpl,Lms,Lim,&Status,&Errmsg,&Ndetail,&Detail);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
	TPLPUTDEBUGOUTVAR(_out, 1, &Errmsg);
	TPLPUTDEBUGOUTVAR(_out, 2, &Ndetail);
	TPLPUTDEBUGOUTVAR(_out, 3, &Detail);
}
