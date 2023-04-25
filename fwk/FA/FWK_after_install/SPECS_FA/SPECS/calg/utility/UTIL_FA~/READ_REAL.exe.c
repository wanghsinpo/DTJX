#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_READ_REAL(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Format;
	STRING	String;
	REAL	Value;
	INTEGER	Stat;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Format, _TYPES, 0, 0);
	TPLINITMEM(&String, _TYPES, 0, 0);
	TPLINITMEM(&Value, _TYPER, 0, 0);
	TPLINITMEM(&Stat, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Format);
	TPLGETEXECINVAR(_in, 1, &String);
	TPLPUTLASTINVAR(__in, 0, &Format);
	TPLPUTLASTINVAR(__in, 1, &String);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &Value);
	TPLGETEXECOUTVAR(_out, 1, &Stat);
	TPLPUTLASTOUTVAR(__out, 0, &Value);
	TPLPUTLASTOUTVAR(__out, 1, &Stat);

	/* Algorithm invocation */
	READ_REAL(Format,String,&Value,&Stat);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &Value);
	TPLPUTEXECOUTVAR(_out, 1, &Stat);
	TPLPUTLASTOUTVAR(__out, 0, &Value);
	TPLPUTLASTOUTVAR(__out, 1, &Stat);
}

void
__READ_REAL(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Format;
	STRING	String;
	REAL	Value;
	INTEGER	Stat;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Format, _TYPES, 0, 0);
	TPLINITMEM(&String, _TYPES, 0, 0);
	TPLINITMEM(&Value, _TYPER, 0, 0);
	TPLINITMEM(&Stat, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Format);
	TPLGETLASTINVAR(__in, 1, &String);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &Value);
	TPLGETLASTOUTVAR(__out, 1, &Stat);

	/* Algorithm invocation */
	READ_REAL(Format,String,&Value,&Stat);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &Value);
	TPLPUTLASTOUTVAR(__out, 1, &Stat);
}
