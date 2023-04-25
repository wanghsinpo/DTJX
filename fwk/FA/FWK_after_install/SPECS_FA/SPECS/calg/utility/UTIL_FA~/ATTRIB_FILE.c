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
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : ATTRIB_FILE
  Vers : 1
  Desc : Description for this Algorithm spec.
  Date : 11/15/2006
  Time : 03:40:00
  User : root
===============================================================================

  Input Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Measurement Parameters:
  1 Filename        S    -                                        

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Permission      S    -                                        
  2 Owner           S    -                                        
  3 Group           S    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
ATTRIB_FILE(STRING Filename,STRING *Permission,STRING *Owner,STRING *Group)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/

	struct stat filestat;
	struct passwd *pwent;
	struct group *grent;
	int mode;

	if (lstat(Filename, &filestat)) {
		printf("ATTRIB_FILE ERROR: %s is not accessible.\n", Filename);
		return;
	}

	mode = 0;
	if (filestat.st_mode & S_ISUID) mode += 4000;
#if __hpux
	if ((filestat.st_mode & S_ISGID) || (filestat.st_mode & S_ENFMT)) mode += 2000;
#else
	if ((filestat.st_mode & S_ISGID)) mode += 2000;
#endif
	if (filestat.st_mode & S_ISVTX) mode += 1000;
	if (filestat.st_mode & S_IRUSR) mode += 400;
	if (filestat.st_mode & S_IWUSR) mode += 200;
	if (filestat.st_mode & S_IXUSR) mode += 100;
	if (filestat.st_mode & S_IRGRP) mode += 40;
	if (filestat.st_mode & S_IWGRP) mode += 20;
	if (filestat.st_mode & S_IXGRP) mode += 10;
	if (filestat.st_mode & S_IROTH) mode += 4;
	if (filestat.st_mode & S_IWOTH) mode += 2;
	if (filestat.st_mode & S_IXOTH) mode += 1;
	sprintf((char*) Permission, "%d", mode); 

	pwent = getpwuid(filestat.st_uid);
	strcpy((char*) Owner, pwent->pw_name);

	grent = getgrgid(filestat.st_gid);
	strcpy((char*) Group, grent->gr_name);

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
