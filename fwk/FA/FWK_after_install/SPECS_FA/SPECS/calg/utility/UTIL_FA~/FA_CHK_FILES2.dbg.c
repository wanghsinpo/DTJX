#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_DBG.h>

void
_FA_CHK_FILES2(void *_alg)
{
}

void
__FA_CHK_FILES2(void *_alg)
/* _alg points to AlgorithmDefinition */
{
	/* Data pointer definition */
	void *_in;
	void *_out;

	/* Local input/output variable definition */
	INTEGER	Rev_flag;
	STRING	Dir;
	STRING	Filename_rev;
	STRING	Suffix;
	STRING	Brk_chr;
	INTEGER	Status;
	STRING	File_name;
	STRING	Full;
	STRING	Rev;

	/* Data pointer initialization */
	_in = TPLDEBUGIN(_alg);
	_out = TPLDEBUGOUT(_alg);

	/* Local variable initialization */
	TPLINITMEM(&Rev_flag, _TYPEI, 0, 0);
	TPLINITMEM(&Dir, _TYPES, 0, 0);
	TPLINITMEM(&Filename_rev, _TYPES, 0, 0);
	TPLINITMEM(&Suffix, _TYPES, 0, 0);
	TPLINITMEM(&Brk_chr, _TYPES, 0, 0);
	TPLINITMEM(&Status, _TYPEI, 0, 0);
	TPLINITMEM(&File_name, _TYPES, 0, 0);
	TPLINITMEM(&Full, _TYPES, 0, 0);
	TPLINITMEM(&Rev, _TYPES, 0, 0);

	/* Algorithm input variable setting */
	TPLGETDEBUGINVAR(_in, 0, &Rev_flag);
	TPLGETDEBUGINVAR(_in, 1, &Dir);
	TPLGETDEBUGINVAR(_in, 2, &Filename_rev);
	TPLGETDEBUGINVAR(_in, 3, &Suffix);
	TPLGETDEBUGINVAR(_in, 4, &Brk_chr);

	/* Algorithm output variable setting */
	TPLGETDEBUGOUTVAR(_out, 0, &Status);
	TPLGETDEBUGOUTVAR(_out, 1, &File_name);
	TPLGETDEBUGOUTVAR(_out, 2, &Full);
	TPLGETDEBUGOUTVAR(_out, 3, &Rev);

	/* Algorithm invocation */
	FA_CHK_FILES2(Rev_flag,Dir,Filename_rev,Suffix,Brk_chr,&Status,&File_name,&Full,&Rev);

	/* Algorithm output variable setting */
	TPLPUTDEBUGOUTVAR(_out, 0, &Status);
	TPLPUTDEBUGOUTVAR(_out, 1, &File_name);
	TPLPUTDEBUGOUTVAR(_out, 2, &Full);
	TPLPUTDEBUGOUTVAR(_out, 3, &Rev);
}
