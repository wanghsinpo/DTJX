/****** <BEGIN> INCLUDE FILES *********** DON'T EDIT FROM <BEGIN> TO <END> ***/
#include <stdio.h>
#include <stdlib.h>
#include <SPECS.h>
#include <ALGUTIL.h>
#include <TOOLCTRL.h>
#include <CALDB.h>
#include <UTILITY.h>
#include <PROBER.h>
/****** <END>   INCLUDE FILES *********** DON'T EDIT FROM <BEGIN> TO <END> ***/
#include <sys/types.h>
#ifdef __linux
#include <sys/wait.h>
#endif
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <fcntl.h>
#ifdef __linux
#include <errno.h>
#endif
#define AVE_Write_SysLog(_a) AVE_Write_Log_same(_a)
#ifndef MAX_LOG
#define MAX_LOG (708)
#endif
int AVE_LockF_same(unsigned long offset, int mode );
int AVE_Write_Log_same(char *estr_buf);
int read_oneline_same(FILE *fp, const char *search_key, char *rtn_line);
int SysConfig_same(const char *key, char *value);

/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : CALL_ERRHANDLER
  Vers : 1
  Desc : Error Handler.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 ErrorNo         S    -        ErrorCode  .ex  "12-34567"      
  2 Message         S    -        Error Message                   
  3 MoreInfo        S    -        More Info                       

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Status          I    -        0: OK, -1: Exec Err, -2: No File
  2 Errmsg          S    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
CALL_ERRHANDLER(STRING ErrorNo,STRING Message,STRING MoreInfo,INTEGER *Status,STRING *Errmsg)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/
  char eflag[1024], ecommand[1024], op_lang[1024];
  char val_name[1024];
  int ch_pid;
  char logmess[4096];
  char tmp_ErrNo[1024];
  char tmp_Message[1024];
  char errormsg_filebase[] = "/opt/SPECS/usr/fwk/HPSTD_%s~/%s/%s";
  char message_filename[1024];
  char *pc_tmp;
  FILE *fp;

  *Status = 0;
  strcpy(*Errmsg, "");

  /* syslog entory get. */
  strcpy(val_name, "ERR_HANDLER");
  if(0 != SysConfig_same(val_name, eflag) || 0 != strcasecmp(eflag, "TRUE")){
    return;
  }

  strcpy(val_name, "ERR_HANDLER_SCRIPT");
  if(0 != SysConfig_same(val_name, ecommand)){
     ecommand[0] = '\0';
  }

  /*strcpy(val_name, "OP_LANG");
    if(0 != SysConfig_same(val_name, op_lang)){
       ecommand[0] = '\0';
    }*/
  strcpy(op_lang, "C");
  
  memset(tmp_ErrNo, 0, sizeof(tmp_ErrNo));
  memset(tmp_Message, 0, sizeof(tmp_Message));

  if(ErrorNo[0] == '$'){
    sprintf(message_filename, errormsg_filebase, Message, op_lang, ErrorNo + 1);
    /* file access */
    if(-1 == access(ecommand, R_OK))
      goto STD_ARG_POINT;
    fp = fopen(message_filename, "r");
    if(fp == NULL)
      goto STD_ARG_POINT;
    for(;;){
      if(NULL == fgets(tmp_ErrNo, 1024, fp) && 0 != ferror(fp)){
	fclose(fp);
	goto STD_ARG_POINT;
      }
      if(0 == strlen(tmp_ErrNo) && 0 == feof(fp))
	continue;
      break;
    }
    if(0 == fread(tmp_Message, sizeof(char), sizeof(tmp_Message)-1, fp) && 0 != ferror(fp)){
      fclose(fp);
      goto STD_ARG_POINT;
    }
    fclose(fp);
    goto FILE_ARG_POINT;
  }
  
 STD_ARG_POINT: /* normal command arg */
  /* log message output */
  strncpy(tmp_ErrNo,   ErrorNo, 1023);
  strncpy(tmp_Message, Message, 1023);
 FILE_ARG_POINT:
  sprintf(logmess,
	  " Start     : Error Handler.\n Command   : %s\n---------------\nERROR CODE : %s\n%s\n---------------\n",
	  ecommand, tmp_ErrNo, tmp_Message);
  AVE_Write_SysLog(logmess);

  /* command name check */  
  if(0 == strlen(ecommand)){
    sprintf(logmess, "Command is \"\".");
    strcpy(*Errmsg, logmess);
    *Status = -2;
    return;
  }
  if(-1 == access(ecommand, F_OK)){
    sprintf(logmess, "Command not exist.");
    strcpy(*Errmsg, logmess);
    *Status = -2;
    return;
  }
  if(-1 == access(ecommand, X_OK)){
    sprintf(logmess, "Command not parmition.");
    strcpy(*Errmsg, logmess);
    *Status = -2;
    return;
  }

  /* child process fork & exec */
  errno = 0;
  if(0 == (ch_pid = fork())){
    errno = 0;
    if(0 > execlp(ecommand, ecommand, tmp_ErrNo, tmp_Message, MoreInfo, NULL)){
      exit(999);
    }
  }
  else if(-1 == ch_pid){
    sprintf(logmess, "fork() Error\n");
    strcpy(*Errmsg, logmess);
    *Status = -1;
  }
  else{
    int stat;
    int w_re;
    for(;;){                         /* child wait retry loop              */
      errno = 0;
      w_re = waitpid(ch_pid, &stat, 0);
      if(-1 == w_re){                /* wait error                         */
	if(errno == EINTR)           /* signal interrupt                   */
          continue;
	else                         /* you add SIGCHILD harndler & wait?  */
	  break;
      }
      else if(0 == w_re)             /* you change waitpid arg.?           */
        break;
      else if(0 != WIFSTOPPED(stat)) /* debug trace ?                      */
        continue;
      else                           /* child process end.                 */
        break;
    }
    if(0 < w_re){                    /* child process end.                 */
      if(0 != WIFEXITED(stat)){      /* child process exit()               */
	if(WEXITSTATUS(stat) == 999){/* 999 code is exec() errror. see up. */
	  *Status = -1;
	  sprintf(logmess, "exec() Error");
	  strcpy(*Errmsg, logmess);
	}
	else{                        /* exit-code set arg.                 */
	  *Status = WEXITSTATUS(stat);
	  sprintf(logmess, "exit(%d)", WEXITSTATUS(stat));
	  strcpy(*Errmsg, logmess);
	}
      }
      else if(0 != WIFSIGNALED(stat)){/*child process signal end.          */
	*Status = 0;
	sprintf(logmess, "signal(%d)", WTERMSIG(stat));
	strcpy(*Errmsg, logmess);
      }
    }
    else{                            /*you change this code ?              */
      sprintf(logmess, "Unknown sequence.");
      strcpy(*Errmsg, logmess);
      *Status = -1;
    }
  }
  return;

/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/

int AVE_LockF_same(unsigned long offset, int mode )
{
    int rtn;
    static FILE *lockf_fd=NULL;

    if(mode == F_TLOCK) {
       if((lockf_fd = fopen("/opt/SPECS/sys/tmp/slog_lockf", "a+")) == (FILE *)0) {
          return(-1);
       }
    }
    (void)fcntl(fileno(lockf_fd), F_SETFD, FD_CLOEXEC);

    if(fseek(lockf_fd,offset,0) == -1) {
      fclose(lockf_fd);
      return(-1);
    }

    if((rtn = lockf(fileno(lockf_fd),mode,1)) == -1) {
      fclose(lockf_fd);
      if(errno != EACCES && errno != EINTR && errno != ENOLCK) {
         return(-1);
      }
      return( errno );
    }
    if(mode == F_ULOCK) {
      if(lockf_fd != NULL)
	fclose(lockf_fd);
      lockf_fd=NULL;
    }

    return(0);
}
int AVE_Write_Log_same(char *estr_buf)
{
    FILE *fd;
    int  len;
    int  i;
    char f_name[] = "/var/opt/SPECS/log/syslog";

    char time_str[1024];
    char *tstr_ptr = time_str;
    time_t  itime;
    char hostname[1024];

    char log_str[4096];

    if((AVE_LockF_same((unsigned long)0, F_TLOCK)) != 0 ) {
       return(-1);
    }

    if((fd=fopen(f_name, "a+")) == (FILE *)0) {
      (void)AVE_LockF_same((unsigned long)0, F_ULOCK);
       return(-1);
    }

    (void)fcntl(fileno(fd), F_SETFD, FD_CLOEXEC);
    /* Get time and convert it ASCII strings */
    /* NLS should be supported in the future */
    time(&itime);
    tstr_ptr = (char *)ctime(&itime);
    len = strlen(tstr_ptr);
    *(tstr_ptr+len-1) = '\0';

    /* Clear Logging Buffer */
    memset(log_str, 0, sizeof(log_str));
    /* Generate Logging Message String */
    gethostname(hostname, sizeof(hostname));
    sprintf(log_str,"%s  %s:%s\n%s\n",tstr_ptr, hostname,"CALL_ERRHANDLER utirity algorithm",estr_buf);

    if(strlen(log_str)>=MAX_LOG) {
       *(log_str+MAX_LOG-1) = '\0';
    }

    len = strlen(log_str);

    if(fwrite(log_str,len,1,fd) == 0 ) {
      (void)AVE_LockF_same((unsigned long)0,F_ULOCK);
      return(-1);
    }

    fclose(fd);

    if((AVE_LockF_same((unsigned long)0,F_ULOCK)) != 0) {
      return(-1);
    }

    return(0);
}
int read_oneline_same(FILE *fp, const char *search_key, char *rtn_line)
{
  unsigned int  size;
  unsigned int  len;
  char read_buf[1024];
  int  flag = 1;
  int  rst;
  char *rtn;

  size = 0;
  while(flag) {
    rtn = fgets(read_buf, 1024, fp);
    if(rtn == NULL) {
      rtn_line[0] = '\0';
      return -1;
    }
    if((rst = strncmp((char *)read_buf, search_key, strlen(search_key))) == 0) {
      len = strlen(read_buf);
      if((read_buf[len-3] == '\\') && (read_buf[len-2] == 'n')) {
        strncpy(rtn_line,read_buf,len-3);
        size = len-3;
        rtn = fgets(read_buf, 1024, fp);
        if(rtn == NULL) { /* Error */
          rtn_line = '\0';
          return -1;
        }
        strncpy((rtn_line+len),read_buf,len-1);
        strcat(rtn_line,'\0');
        size += len-1;
      }
      else {
        strncpy(rtn_line,read_buf,len-1);
        rtn_line[len-1] = '\0';
        size = len-1;
      }
      flag = 0;
    }
    else {  /* Read the next line */
      flag = 1;
    }
  }
  fflush(fp);
  return size;
}
int SysConfig_same(const char *key, char *value)
{
    FILE *f;
    char buf[2048];
    char *p;
    int ret = 0, n = 0;

    memset(buf, 0, sizeof(buf));
    memset(value, 0, sizeof(value));

    f = fopen("/opt/SPECS/sys/config/sysconf", "r");
    if(f == NULL) 
        return -1;
    ret = read_oneline_same(f, key, buf);
    fclose(f);
    if(ret < 0)
        return -1;

    n = strchr(buf, '=') - buf;
    if(n < 0) 
        return -1;

    strcpy(value, buf + n + 1);
    p = value + strlen(value);
    while (p > value) {
        if (! isspace(*--p)) {
            ++p;
            break;
        }
    }
    *p = '\0';

    return 0;
}
