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
#include <sys/types.h>
#include <sys/stat.h>
enum {
	NORMAL_TYPE,
	DIRECTORY_TYPE,
	SPECIAL_TYPE
};
struct file_t {
	STRING  Symbol;
	INTEGER Index;
} FileType[] = {
	{"Normal",    NORMAL_TYPE},
	{"Directory", DIRECTORY_TYPE},
	{"Special",   SPECIAL_TYPE}
};
INTEGER numType = sizeof(FileType) / sizeof(struct file_t);

static int
CHECK_FILETYPE(mode_t Mode, INTEGER Index);
static void
CHECK_USER_PERMISSION(mode_t Mode, INTEGER* R, INTEGER* W, INTEGER* E);
static void
CHECK_GROUP_PERMISSION(mode_t Mode, INTEGER* R, INTEGER* W, INTEGER* E);
static void
CHECK_OTHER_PERMISSION(mode_t Mode, INTEGER* R, INTEGER* W, INTEGER* E);
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : VERIFY_FILE
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
  2 Type            S    -                                        

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Exist           I    -                                        
  2 Readable        I    -                                        
  3 Writable        I    -                                        
  4 Executable      I    -                                        

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
VERIFY_FILE(STRING Filename,STRING Type,INTEGER *Exist,INTEGER *Readable,INTEGER *Writable,INTEGER *Executable)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	INTEGER j;
	struct stat buffer;

	*Exist = 0;
	*Readable = 0;
	*Writable = 0;
	*Executable = 0;

	if (lstat(Filename, &buffer) == -1) {
		printf("VERIFY_FILE ERROR: %s is not accessible.\n", Filename);
		return;
	}

	for (j = 0; j < numType; j++) {
		if (strcmp(Type, FileType[j].Symbol) == 0) {
			if (CHECK_FILETYPE(buffer.st_mode, FileType[j].Index) == -1) {
				return;
			}
			break;
		}
	}
	if (j == numType) {
		return;
	}

	*Exist = 1;
	if (getuid() == buffer.st_uid) {
		CHECK_USER_PERMISSION(buffer.st_mode, Readable, Writable, Executable);
	}
	else if (getgid() == buffer.st_gid) {
		CHECK_GROUP_PERMISSION(buffer.st_mode, Readable, Writable, Executable);
	}
	else {
		CHECK_OTHER_PERMISSION(buffer.st_mode, Readable, Writable, Executable);
	}

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/

static int
CHECK_FILETYPE(mode_t Mode, INTEGER Index)
{
	switch (Index) {
	case NORMAL_TYPE:
		if (S_ISREG(Mode) || S_ISLNK(Mode)) {
			return(0);
		}
		return(-1);
	case DIRECTORY_TYPE:
		if (S_ISDIR(Mode)) {
			return(0);
		}
		return(-1);
	case SPECIAL_TYPE:
		if (S_ISREG(Mode) || S_ISLNK(Mode) || S_ISDIR(Mode)) {
			return(-1);
		}
		return(0);
	}

	return(-1);
}

static void
CHECK_USER_PERMISSION(mode_t Mode, INTEGER* R, INTEGER* W, INTEGER* E)
{
	*R = 0;
	*W = 0;
	*E = 0;

	if (Mode & S_IRUSR) {
		*R = 1;
	}
	if (Mode & S_IWUSR) {
		*W = 1;
	}
	if (Mode & S_IXUSR) {
		*E = 1;
	}

	return;
}

static void
CHECK_GROUP_PERMISSION(mode_t Mode, INTEGER* R, INTEGER* W, INTEGER* E)
{
	*R = 0;
	*W = 0;
	*E = 0;

	if (Mode & S_IRGRP) {
		*R = 1;
	}
	if (Mode & S_IWGRP) {
		*W = 1;
	}
	if (Mode & S_IXGRP) {
		*E = 1;
	}

	return;
}

static void
CHECK_OTHER_PERMISSION(mode_t Mode, INTEGER* R, INTEGER* W, INTEGER* E)
{
	*R = 0;
	*W = 0;
	*E = 0;

	if (Mode & S_IROTH) {
		*R = 1;
	}
	if (Mode & S_IWOTH) {
		*W = 1;
	}
	if (Mode & S_IXOTH) {
		*E = 1;
	}

	return;
}
