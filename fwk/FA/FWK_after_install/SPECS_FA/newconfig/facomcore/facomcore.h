#ifndef FACOMCORE_H
#define FACOMCORE_H
  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern int gemInit(void);
extern int gemReplyOK(char *rplymbx, double timeout);
extern int gemReplyNotOK(char *rplymbx);
extern int gemUpdVar(char *Ceid, char *VarName, char *VarData, int *Status);
extern int gemUpdListVar(char *Ceid, char *VarName, char *VarNum, char **VarData, int *Status);
extern int gemLmpDisp(char *event, char *Lnth, char *Dlabel, char *Dval, char *Dfgc, char *Dbgc, int *Status);
extern int gemSendEvent(char *event, char **parms, int *status);
extern int gemGetCmd(char *cmd, char *rply, char **parms);

#define C_WAFERLIST_BRK1	"|"
#define C_WAFERLIST_BRK2	','
#define	C_WAFERLIST_MAX		25

#define	C_DIETSTLIST_BRK1	"|"
#define C_DIETSTLIST_BRK2	','
#define	C_DIETSTLIST_MAX	32

#define C_MEASLIBLIST_BRK1	"|"
#define	C_MEASLIBLIST_MAX	6

#define C_TCOLIST_BRK1		"|"
#define	C_TCOLIST_MAX	        16

#define	C_SVVALLIST_BRK1	"|"
#define C_SVVALLIST_BRK2	','
#define	C_SVVALLIST_MAX	        32

enum ceGEMMSG_INDEX {
	IDX_PORTID		=0,
	IDX_CARRIERID,			/* [Event]   RCPVERIFIED */
					/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_LOTID,			/* [Event]   LOTSTART | PROBERRCP | PROBERRCPTUNE | RCPVERIFIED */
					/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_PPEXEC,			/* [Event]   RCPVERIFIED */
					/* [Command] PP-SELECT | PP-RECIPETUNE | EXTRACT-PROBER-RECIPE */
	IDX_OPEID,			/* [Event]   RCPVERIFIED */
					/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_PRODUCTID,			/* [Event]   RCPVERIFIED */
					/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_PROCESSID,			/* [Event]   RCPVERIFIED */
	IDX_WAF			=9,	/* [Event]   RCPVERIFIED */
					/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_PRB,			/* [Event]   RCPVERIFIED */
					/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_TPL,			/* [Event]   RCPVERIFIED */
					/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_LIM,			/* [Event]   RCPVERIFIED */
					/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_MDD,			/* [Event]   RCPVERIFIED */
					/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_F_PROBCARD		=14,	/* [Event]   INITCOMP | RCPVERIFIED */
	IDX_R_PROBCARD,			/* [Event]   RCPVERIFIED */
					/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_TSTBOARD_ID,		/* [Event]   INITCOMP | RCPVERIFIED */
	IDX_C_OCR_STATE,		/* [Event]   LOTSTART | RCPVERIFIED | WAFERSTART | OCRMODE */
	IDX_R_OCR_STATE,		/* [Command] CHANGE-OCR-STATE */
	IDX_EQ_ID,			/* [Event]   INITCOMP */
	IDX_EQ_TYPE,			/* [Event]   INITCOMP */
	IDX_SOFT_REV,			/* [Event]   INITCOMP */
	IDX_TSTFILE_PARAMS,		/* [Event]   RCPVERIFIED */
	IDX_HCACK		=24,	/* [Command] ProberStatus */
	IDX_PRB_RECIPE,			/* [Event]   PROBERRCP | PROBERRCP-EXTRACT | PROBERRCPTUNE */
					/* [Command] PP-SELECT */
	IDX_RETEST_WFR		=29,	/* [Event]   LOTSTART */
	IDX_WFR_RESULT		=49,	/* [Event]   WAFEREND */
	IDX_SUBLOT_ID,			/* [Event]   WAFERSTART */
	IDX_WFR_SLOT,			/* [Event]   WAFERSTART */
	IDX_RESULT_FILE,		/* [Event]   WAFERSTART */
	IDX_LOG,			/* [Event]   WAFERSTART */
	IDX_RESULT_LASTDIE,		/* [Event]   DIEEND */
	IDX_C_DIE_FILE,			/* [Event]   DIESTART */
	IDX_DIE_POS_X,			/* [Event]   DIESTART */
	IDX_DIE_POS_Y,			/* [Event]   DIESTART */
	IDX_ALARM_TXT		=59,	/* [Event]   ALARM */
	IDX_ALARM_ID,			/* [Event]   ALARM */
	IDX_ALARM_DETAILS,		/* [Event]   ALARM */
	IDX_WFR_NUM		=99,	/* [Command] PP-SELECT | PP-RECIPETUNE | RETEST */
	IDX_WFR_EXIST		=100,	/* [Event]   RCPVERIFIED */
					/* [Command] PP-SELECT | PP-RECIPETUNE | RETEST */
	IDX_WFR_ID		=125,	/* [Event]   RCPVERIFIED */
					/* [Command] PP-SELECT | PP-RECIPETUNE | RETEST */
	IDX_DIETST_NUM		=199,	/* [Event]   RCPVERIFIED */
					/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_DIE			=200,	/* [Event]   RCPVERIFIED */
					/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_TST			=250,	/* [Event]   RCPVERIFIED */
					/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_STATUS		=401,	/* [Event]   LOTCANCEL | LOTFINISH | PPBADCOMPILE */
					/* [Event]   PP-RCPTUNEOK | PP-RCPTUNENG | RCPVERIFIED */
	IDX_IWCONDITION		=402,	/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_IWNUMOFDIE		=403,	/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_IWDIELABEL		=404,	/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_IWJUDGERULE		=405,	/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_IWJUDGETLEVEL	=406,	/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_BWCONDITION		=407,	/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_BWNUMOFWAF		=408,	/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_BWWAFID		=409,	/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_BWJUDGERULE		=410,	/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_BWJUDGETLEVEL	=411,	/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_RECIPEFNAME		=412,	/* [Command] PP-SELECT | PP-RECIPETUNE | EXTRACT-PROBER-RECIPE*/
	IDX_TESTCONDFNAME	=413,	/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_CONDLEVEL		=414,	/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_WAFERTEST		=415,	/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_PJEBWCONDITION	=416,	/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_PJEBWJUDGERULE	=417,	/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_PJEBWJUDGETLEVEL	=418,	/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_ADAPTIVEMETHOD	=419,	/* [Command] PP-SELECT | PP-RECIPETUNE */
	IDX_EXECUTIONLEVEL	=420,	/* [Event]   INITCOMP | LOTCANCEL | LOTEND | PENDINGCOMP */
	IDX_EXECUTEATTRIBUTE	=421,	/* [Event]   INITCOMP | LOTCANCEL | LOTEND | PENDINGCOMP */
	IDX_REQUESTREASON	=422,	/* [Command] PJPAUSEREQUEST | CJPAUSEREQUEST */
	IDX_REQUESTVALUE	=423,	/* [Command] PJPAUSEREQUEST | CJPAUSEREQUEST */
	IDX_MEASLIBNAME		=424,	/* [Command] PP-SELECT */
	IDX_DEVICELIBNAME	=425,	/* [Command] PP-SELECT */
	IDX_COMPATIMODE		=426,	/* [Event]   SET-COMPATIMODE */
	IDX_DIAGNOSTICS		=427,	/* [Command] RUN-DIAGNOSTICS */
	IDX_PRBEVENT   		=428,
	IDX_PRBEVENT2  		=429,
	IDX_MEASLIB_LIST	=430,	/* [Command] PP-SELECT(430-435) | PP-RECIPETUNE(430-435) */
	IDX_MEASLIB_NUM		=436,	/* [Command] PP-SELECT | PP-RECIPETUNE */
        IDX_PRJOBID             =437,   /* [Command] PP-SELECT */
        IDX_CTRLJOBID           =438,   /* [Command] PP-SELECT */
	IDX_SV_UPDNAME		=440,	/* [Command] DATAUPDATE | LDATAUPDATE */
	IDX_SV_VAL 		=441,	/* [Command] DATAUPDATE | LDATAUPDATE(441-472) */
	IDX_TCO_LIST		=450,	/* [Command] PP-SELECT(450-465) | PP-RECIPETUNE(450-465) */
	IDX_TCO_NUM		=467,	/* [Command] PP-SELECT | PP-RECIPETUNE */
					/* IDX_TCO_LIST and IDX_TCO_NUM are assign to parts of IDX_SV_VAL. */
					/* But those parameters are used by the different commands. */
	IDX_SVLIST_NUM		=473,	/* [Command] LDATAUPDATE */
	IDX_RESERVED		=474
};

#endif // FACOMCORE_H
