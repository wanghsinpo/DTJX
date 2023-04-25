#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_FA_LIMFMT(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	INTEGER	Rev_flag;
	STRING	Brk_chr;
	STRING	Src_lim_dir;
	STRING	Script_dir;
	STRING	Dst_lim_dir;
	STRING	Src_lim;
	STRING	Script;
	STRING	Dst_lim;
	INTEGER	Status;
	STRING	Error;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Rev_flag, _TYPEI, 0, 0);
	TPLINITMEM(&Brk_chr, _TYPES, 0, 0);
	TPLINITMEM(&Src_lim_dir, _TYPES, 0, 0);
	TPLINITMEM(&Script_dir, _TYPES, 0, 0);
	TPLINITMEM(&Dst_lim_dir, _TYPES, 0, 0);
	TPLINITMEM(&Src_lim, _TYPES, 0, 0);
	TPLINITMEM(&Script, _TYPES, 0, 0);
	TPLINITMEM(&Dst_lim, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Rev_flag);
	TPLGETEXECINVAR(_in, 1, &Brk_chr);
	TPLGETEXECINVAR(_in, 2, &Src_lim_dir);
	TPLGETEXECINVAR(_in, 3, &Script_dir);
	TPLGETEXECINVAR(_in, 4, &Dst_lim_dir);
	TPLGETEXECINVAR(_in, 5, &Src_lim);
	TPLGETEXECINVAR(_in, 6, &Script);
	TPLGETEXECINVAR(_in, 7, &Dst_lim);
	TPLPUTLASTINVAR(__in, 0, &Rev_flag);
	TPLPUTLASTINVAR(__in, 1, &Brk_chr);
	TPLPUTLASTINVAR(__in, 2, &Src_lim_dir);
	TPLPUTLASTINVAR(__in, 3, &Script_dir);
	TPLPUTLASTINVAR(__in, 4, &Dst_lim_dir);
	TPLPUTLASTINVAR(__in, 5, &Src_lim);
	TPLPUTLASTINVAR(__in, 6, &Script);
	TPLPUTLASTINVAR(__in, 7, &Dst_lim);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Status);
	TPLGETEXECOUTVAR(_out, 1, &Error);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Error);

	/* Algorithm invocation */
	FA_LIMFMT(Rev_flag,Brk_chr,Src_lim_dir,Script_dir,Dst_lim_dir,Src_lim,Script,Dst_lim,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Status);
	TPLPUTEXECOUTVAR(_out, 1, &Error);
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Error);
}

void
__FA_LIMFMT(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	INTEGER	Rev_flag;
	STRING	Brk_chr;
	STRING	Src_lim_dir;
	STRING	Script_dir;
	STRING	Dst_lim_dir;
	STRING	Src_lim;
	STRING	Script;
	STRING	Dst_lim;
	INTEGER	Status;
	STRING	Error;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Rev_flag, _TYPEI, 0, 0);
	TPLINITMEM(&Brk_chr, _TYPES, 0, 0);
	TPLINITMEM(&Src_lim_dir, _TYPES, 0, 0);
	TPLINITMEM(&Script_dir, _TYPES, 0, 0);
	TPLINITMEM(&Dst_lim_dir, _TYPES, 0, 0);
	TPLINITMEM(&Src_lim, _TYPES, 0, 0);
	TPLINITMEM(&Script, _TYPES, 0, 0);
	TPLINITMEM(&Dst_lim, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&Error, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Rev_flag);
	TPLGETLASTINVAR(__in, 1, &Brk_chr);
	TPLGETLASTINVAR(__in, 2, &Src_lim_dir);
	TPLGETLASTINVAR(__in, 3, &Script_dir);
	TPLGETLASTINVAR(__in, 4, &Dst_lim_dir);
	TPLGETLASTINVAR(__in, 5, &Src_lim);
	TPLGETLASTINVAR(__in, 6, &Script);
	TPLGETLASTINVAR(__in, 7, &Dst_lim);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Status);
	TPLGETLASTOUTVAR(__out, 1, &Error);

	/* Algorithm invocation */
	FA_LIMFMT(Rev_flag,Brk_chr,Src_lim_dir,Script_dir,Dst_lim_dir,Src_lim,Script,Dst_lim,&Status,&Error);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Status);
	TPLPUTLASTOUTVAR(__out, 1, &Error);
}
