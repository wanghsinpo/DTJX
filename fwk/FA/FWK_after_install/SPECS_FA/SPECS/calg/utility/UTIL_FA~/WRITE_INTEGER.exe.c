#include <SPECS.h>
#include <SPECS_SYS.h>
#include <SPECS_EXE.h>

void
_WRITE_INTEGER(void *_alg, void *__alg)
/* _alg points to ExeSpecDefRow */
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *_in, *__in;
	void *_out, *__out;

	/* Local input/output variable definition */
	STRING	Format;
	INTEGER	Value;
	STRING	String;
	INTEGER	Length;

	/* P-code pointer initialization */
	_in = TPLEXECIN(_alg);
	__in = TPLLASTIN(__alg);
	_out = TPLEXECOUT(_alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Format, _TYPES, 0, 0);
	TPLINITMEM(&Value, _TYPEI, 0, 0);
	TPLINITMEM(&String, _TYPES, 0, 0);
	TPLINITMEM(&Length, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETEXECINVAR(_in, 0, &Format);
	TPLGETEXECINVAR(_in, 1, &Value);
	TPLPUTLASTINVAR(__in, 0, &Format);
	TPLPUTLASTINVAR(__in, 1, &Value);

	/* Algorithm output variable setting */
	TPLGETEXECOUTVAR(_out, 0, &String);
	TPLGETEXECOUTVAR(_out, 1, &Length);
	TPLPUTLASTOUTVAR(__out, 0, &String);
	TPLPUTLASTOUTVAR(__out, 1, &Length);

	/* Algorithm invocation */
	WRITE_INTEGER(Format,Value,&String,&Length);

	/* Algorithm output variable setting */
	TPLPUTEXECOUTVAR(_out, 0, &String);
	TPLPUTEXECOUTVAR(_out, 1, &Length);
	TPLPUTLASTOUTVAR(__out, 0, &String);
	TPLPUTLASTOUTVAR(__out, 1, &Length);
}

void
__WRITE_INTEGER(void *__alg)
/* __alg points to AlgorithmSpecDefIndexEntry */
{
	/* P-code pointer definition */
	void *__in;
	void *__out;

	/* Local input/output variable definition */
	STRING	Format;
	INTEGER	Value;
	STRING	String;
	INTEGER	Length;

	/* P-code pointer initialization */
	__in = TPLLASTIN(__alg);
	__out = TPLLASTOUT(__alg);

	/* Local variable initialization */
	TPLINITMEM(&Format, _TYPES, 0, 0);
	TPLINITMEM(&Value, _TYPEI, 0, 0);
	TPLINITMEM(&String, _TYPES, 0, 0);
	TPLINITMEM(&Length, _TYPEI, 0, 0);

	/* Algorithm input variable setting */
	TPLGETLASTINVAR(__in, 0, &Format);
	TPLGETLASTINVAR(__in, 1, &Value);

	/* Algorithm output variable setting */
	TPLGETLASTOUTVAR(__out, 0, &String);
	TPLGETLASTOUTVAR(__out, 1, &Length);

	/* Algorithm invocation */
	WRITE_INTEGER(Format,Value,&String,&Length);

	/* Algorithm output variable setting */
	TPLPUTLASTOUTVAR(__out, 0, &String);
	TPLPUTLASTOUTVAR(__out, 1, &Length);
}
