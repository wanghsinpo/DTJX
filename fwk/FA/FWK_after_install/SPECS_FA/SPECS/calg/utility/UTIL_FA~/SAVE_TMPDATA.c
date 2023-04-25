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
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#if __hpux
extern char *sys_errlist[];
#endif
extern int errno;
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : SAVE_TMPDATA
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
  1 Path            S    -                                        
  2 Name            S    -                                        
  3 Format          S    -                                        
  4 Session         S    -                                        

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Stat            I    -        0: No temporary file exists 1: S
  2 Error           S    -                                        
  3 Pubname         S    -        Official name                   

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
SAVE_TMPDATA(STRING Path,STRING Name,STRING Format,STRING Session,INTEGER *Stat,STRING *Error,STRING *Pubname)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	STRING	orgdir;
	STRING	tmpname1, tmpname2;
	STRING	buffer, name, suffix, serial;
	int	num, last, pos_comma, pos_us; /* us = under score */
        int     beginning = 0;

	DIR		*dptr;
	struct stat	dstat;
	struct dirent	*dinfo;

	*Stat = 1;
	strcpy(*Error, "");
	strcpy(*Pubname, "");

	if (getcwd(orgdir, 256) == NULL) {
		*Stat = -1;
		strcpy(*Error, sys_errlist[errno]);
		return;
	}

	if ((dptr = opendir(Path)) == 0) {
		*Stat = -1;
		strcpy(*Error, sys_errlist[errno]);
		return;
	}

	if (chdir(Path) < 0) {
		*Stat = -1;
		strcpy(*Error, sys_errlist[errno]);
                closedir(dptr);
		return;
	}

	NAME_TMPDATA(Name, Session, &tmpname1);
	sprintf(tmpname1, "%s.%s", tmpname1, Format);
	if (lstat(tmpname1, &dstat) == -1) {
		beginning = 1;
	}

	last = 0;
	while (dinfo = readdir(dptr)) {
		strcpy(buffer, dinfo->d_name);
		strcpy(name, "");
		strcpy(serial, "");
		strcpy(suffix, "");

		/* Scan file suffix */

		for (pos_comma = strlen(buffer) - 1; pos_comma >= 0; pos_comma--) {
			if (buffer[pos_comma] == '.') {
				break;
			}
	    	}

		if (pos_comma > 0) {
			strcpy(suffix, buffer + pos_comma + 1);
		}

		/* Scan serial number and name */

		for (pos_us = pos_comma - 1; pos_us >= 0; pos_us--) {
			if (buffer[pos_us] == '_') {
				break;
			}
			if (buffer[pos_us] < '0' || buffer[pos_us] > '9') {
				pos_us = 0;
				break;
			}
		}

		if (pos_us > 0) {
			strncpy(name, buffer, pos_us);
			strncpy(serial, buffer + pos_us + 1, pos_comma - pos_us - 1);
			name[pos_us] = 0; 
			serial[pos_comma - pos_us - 1] = 0; 
		}

		/* Count serial number */

		if (strcmp(name, Name) == 0 && strcmp(suffix, Format) == 0) {
			num = atoi(serial);
			if (num > last) {
				last = num;
			}
		}
	}
	closedir(dptr);

	sprintf(*Pubname, "%s_%d", Name, last + 1);
	if (!beginning) {
		sprintf(tmpname2, "%s.%s", *Pubname, Format);
		if (rename(tmpname1, tmpname2) != 0) {
			*Stat = -1;
			strcpy(*Error, sys_errlist[errno]);
			return;
		}
	}

	if (chdir(orgdir) < 0) {
		*Stat = -1;
		strcpy(*Error, sys_errlist[errno]);
		return;
	}

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
