#ifndef  FACOMCSUB_H
#include <csubdecl.h>
#include <SPECS.h>
#include <time.h>
#include <stdio.h>
#endif


/* GEM_INIT */
void FA_INIT(binteger_parm);

/* GEM_RESPOND_NOK */
void FA_RESPOND_NOK(dimentryptr, bstring_parm,   /* ReplyMailbox */
                    binteger_parm);              /* Status */

/* GEM_RESPOND_OK */
void FA_RESPOND_OK(dimentryptr, bstring_parm,    /* ReplyMailbox */
		   breal_parm,                   /* Timeout */
                   binteger_parm);               /* Status */

typedef struct str_type {
	int     len;
	STRING  c;
} *bparms_parm;

/* GEM_GETCMD */
void FA_GETCMD(dimentryptr, bstring_parm,      /* Cmd */
	       dimentryptr, bstring_parm,      /* Rply */
	       dimentryptr, bparms_parm);     /* Parms */

/* GEM_SENDEVENT */
void FA_SENDEVENT(dimentryptr, bstring_parm,      /* Event */
	          dimentryptr, bparms_parm,      /* Parms */
	          binteger_parm);                 /* Status */

/* GEM_LMPDISP */
void FA_LMPDISP(dimentryptr, bstring_parm,      /* Event */
                dimentryptr, bstring_parm,      /* Lnth */
                dimentryptr, bstring_parm,      /* Label */
                dimentryptr, bstring_parm,      /* Value */
                dimentryptr, bstring_parm,      /* Fgc */
                dimentryptr, bstring_parm,      /* Bgc */
	        binteger_parm);                 /* Status */

/* GEM_UPDVAR */
void FA_UPDVAR(dimentryptr, bstring_parm,      /* CEID */
               dimentryptr, bstring_parm,      /* VarName */
               dimentryptr, bstring_parm,      /* VarData */
	       binteger_parm);                 /* Status */

/* GEM_UPDLVAR */
void FA_UPDLISTVAR(dimentryptr, bstring_parm,      /* CEID */
               dimentryptr, bstring_parm,      /* VarName */
               dimentryptr, bstring_parm,      /* VarNum */
	       dimentryptr, bparms_parm,       /* VarData */
	       binteger_parm);                 /* Status */

