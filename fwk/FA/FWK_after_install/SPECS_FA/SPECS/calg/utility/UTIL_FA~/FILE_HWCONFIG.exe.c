#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_FILE_HWCONFIG(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;

	/* Local input/output variable definition */
	STRING	File;
	STRING	Config[50];

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&File, _TYPES, 0, 0);
	TPLINITMEM(&Config, _TYPES, 50, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &File);
	TPLGETEXECINVAR(_in, 1, &Config);
	TPLPUTLASTINVAR(__in, 0, &File);
	TPLPUTLASTINVAR(__in, 1, &Config);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	FILE_HWCONFIG(File,Config);

	/* Algorithm output variable setting */
}

void
__FILE_HWCONFIG(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;

	/* Local input/output variable definition */
	STRING	File;
	STRING	Config[50];

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);

	/* Local variable initialization */
	TPLINITMEM(&File, _TYPES, 0, 0);
	TPLINITMEM(&Config, _TYPES, 50, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &File);
	TPLGETLASTINVAR(__in, 1, &Config);

	/* Algorithm output variable setting */

	/* Algorithm invocation */
	FILE_HWCONFIG(File,Config);

	/* Algorithm output variable setting */
}
