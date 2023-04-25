/**************************************************/
/* Comment                                        */
/* DATE: Feb.27.2001 K.Nakano : LYNX Revision 0.0 */
/* DATE: Oct.6.2001 M.Nakamura: LYNX Revision 1.0 */
/**************************************************/

#include <string.h>
#include "FACOMCSUB.h"

/*---------------------------------------------------------------------------------*/
void FA_INIT(binteger_parm status_ptr)
{
  *status_ptr=gemInit();
  /* printf("Output : status = %d\n", *status_ptr); */
}

/*---------------------------------------------------------------------------------*/
void FA_RESPOND_NOK(dimentryptr replymailbox_dim, bstring_parm replymailbox_ary, /* ReplyMailbox */
                    binteger_parm status_ptr)                                    /* Status */
{
  STRING ReplyMailbox;
  strcpy(ReplyMailbox, replymailbox_ary->c);
  ReplyMailbox[ replymailbox_ary->len]='\0';
  /*printf("Input : ReplyMailbox      = %s\n", ReplyMailbox);*/
  *status_ptr=gemReplyNotOK(ReplyMailbox);
}


/*---------------------------------------------------------------------------------*/
void FA_RESPOND_OK(dimentryptr replymailbox_dim, bstring_parm replymailbox_ary, /* ReplyMailbox */
		   breal_parm  timeout_ptr,                                     /* Timeout */
                   binteger_parm status_ptr)                                    /* Status */
{
  STRING ReplyMailbox;
  strcpy(ReplyMailbox, replymailbox_ary->c);
  ReplyMailbox[ replymailbox_ary->len]='\0';
  /*printf("Input : ReplyMailbox      = %s\n", ReplyMailbox);*/
  /*printf("Input : Timeout           = %f\n", *timeout_ptr);*/
  *status_ptr=gemReplyOK(ReplyMailbox, *timeout_ptr);
}


/*---------------------------------------------------------------------------------*/
void FA_GETCMD(dimentryptr cmd_dim,      bstring_parm cmd_ary,      /* Cmd */
	       dimentryptr rply_dim,     bstring_parm rply_ary,     /* Rply */
	       dimentryptr parm_dim,     bparms_parm  parms)        /* Parms */
{
  int    i;
  char   *ptr[500];
  STRING Cmd;
  STRING Rply;
  
  strcpy(Cmd,"");
  strcpy(Rply,"");
  for (i=0;i<500;i++){
	strcpy(parms[i].c, "");
	ptr[i] = parms[i].c;
  }
  gemGetCmd(Cmd, Rply, ptr);

  strcpy(cmd_ary->c, Cmd);
  strcpy(rply_ary->c, Rply);
  cmd_ary->len=strlen(Cmd);
  rply_ary->len=strlen(Rply);
  for (i=0;i<500;i++){
	parms[i].len=strlen(parms[i].c);
  }
  return;
}

/*---------------------------------------------------------------------------------*/
void FA_SENDEVENT(dimentryptr event_dim,      bstring_parm event,        /* Event */
	          dimentryptr parm_dim,       bparms_parm  parms,        /* Parms */
		  binteger_parm status)
{

  int    i;
  int    len;
  int    Rtn;
  char   *ptr[500];
  STRING str1;
  STRING STR[500];
  STRING Event;
  FILE *fp;

  /*
  fp=fopen("/usr/tmp/event.log","a");
  fprintf(fp, "csub:parms[0]=%s\n", parms[0].c);
  fprintf(fp, "csub:parms[1]=%s,%d\n", parms[1].c, parms[1].len);
  fprintf(fp, "csub:parms[2]=%s\n", parms[2].c);
  fclose(fp);
  */
  
  strcpy(Event,event->c);
  Event[event->len] = '\0';

  for (i=0;i<500;i++){
	strcpy(str1, parms[i].c);
	len=parms[i].len;
	str1[len] = '\0';
	strcpy(STR[i], str1);
	ptr[i] = STR[i];
  }
  
  gemSendEvent(Event, ptr, &Rtn); 
  *status=Rtn;
  /*printf("Output : status = %d\n", *status);*/

  return;
}

/*---------------------------------------------------------------------------------*/
void FA_LMPDISP(dimentryptr event_dim,      bstring_parm event,        /* Event */
                dimentryptr lnth_dim,       bstring_parm lnth,         /* lnth  */
                dimentryptr label_dim,      bstring_parm label,        /* label */
                dimentryptr value_dim,      bstring_parm value,        /* value */
                dimentryptr fgc_dim,        bstring_parm fgc,          /* fgc   */
                dimentryptr bgc_dim,        bstring_parm bgc,          /* bgc   */
		binteger_parm status)
{

  STRING Event;
  STRING Lnth;
  STRING Label;
  STRING Value;
  STRING Fgc;
  STRING Bgc;
  int    Rtn;
  int    rtn;

  strcpy(Event,event->c);
  Event[event->len] = '\0';

  strcpy(Lnth,lnth->c);
  Lnth[lnth->len] = '\0';
  
  strcpy(Label,label->c);
  Label[label->len] = '\0';

  strcpy(Value,value->c);
  Value[value->len] = '\0';

  strcpy(Fgc,fgc->c);
  Fgc[fgc->len] = '\0';

  strcpy(Bgc,bgc->c);
  Bgc[bgc->len] = '\0';

  rtn = gemLmpDisp(Event, Lnth, Label, Value, Fgc, Bgc, &Rtn);
  *status = Rtn;
  /*printf("Output : status = %d\n", *status);*/

  return;
}

/*---------------------------------------------------------------------------------*/
void FA_UPDVAR(dimentryptr ceid_dim,      bstring_parm ceid,        /* CEID     */
               dimentryptr vname_dim,     bstring_parm vname,       /* VarName  */
               dimentryptr vdata_dim,     bstring_parm vdata,       /* VarData  */
	       binteger_parm status)
{

  STRING Ceid;
  STRING Vname;
  STRING Vdata;
  int    Rtn;
  int    rtn;

  strcpy(Ceid,ceid->c);
  Ceid[ceid->len] = '\0';

  strcpy(Vname,vname->c);
  Vname[vname->len] = '\0';

  strcpy(Vdata,vdata->c);
  Vdata[vdata->len] = '\0';

  rtn=gemUpdVar(Ceid,Vname,Vdata,&Rtn);
  *status=Rtn;

  return;
}

/*---------------------------------------------------------------------------------*/
void FA_UPDLISTVAR(dimentryptr ceid_dim,     bstring_parm ceid,        /* CEID     */
               dimentryptr vname_dim,     bstring_parm vname,       /* VarName  */
               dimentryptr vnum_dim,     bstring_parm vnum,        /* VarNum  */
	       dimentryptr vdata_dim,     bparms_parm  vdata,       /* VarData */
	       binteger_parm status)
{

  STRING Ceid;
  STRING Vname;
  STRING Vnum;
  STRING STR[32];
  char   *ptr[32];
  STRING str1;
  int    i;
  int    len;
  int    Rtn;
  int    rtn;

  strcpy(Ceid,ceid->c);
  Ceid[ceid->len] = '\0';

  strcpy(Vname,vname->c);
  Vname[vname->len] = '\0';

  strcpy(Vnum,vnum->c);
  Vnum[vnum->len] = '\0';

  for (i=0;i<32;i++){
        ptr[i] = NULL;
        strcpy(STR[i],"");
        strcpy(STR[i], str1);
        strcpy(str1, vdata[i].c);
        len=vdata[i].len;
        str1[len] = '\0';
        strcpy(STR[i], str1);
        ptr[i] = STR[i];
  }

  rtn=gemUpdListVar(Ceid,Vname,Vnum,ptr,&Rtn);
  *status=Rtn;

  return;
}

