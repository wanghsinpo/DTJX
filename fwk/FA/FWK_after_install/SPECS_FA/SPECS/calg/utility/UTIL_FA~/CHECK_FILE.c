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

#define MAX_BUF_LENG 1024
#define MAX_NAM_LENG 1024
#define MAX_VER_LENG 128
extern  FILE *popen(const char*, const char*);
/****** <BEGIN> ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ****
===============================================================================
  Type : Algorithm
  Name : CHECK_FILE
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
  1 Testplan        S    -                                        
  2 Limit           S    -                                        

  Output Variables:

 #  Name            Type Size     Description                     
--- --------------- ---- -------- --------------------------------
    Output Parameters:
  1 Result          I    -        0: OK 1: File Mismatch: 2: Revis

******* <END>   ALGORITHM DOCUMENTATION * DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
void
CHECK_FILE(STRING Testplan,STRING Limit,INTEGER *Result)
{
/****** <END>   ALGORITHM DECLARATION *** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <BEGIN> VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/****** <END>   VARIABLE DECLARATION **** DON'T EDIT FROM <BEGIN> TO <END> ***/
/*===========================================================================*/



	STRING	sysconf = "/opt/SPECS/sys/config/sysconf";		/* AVPATH_ */
	STRING	format1 = "/opt/SPECS/sys/bin/tplattr -t %s %s";	/* AVPATH_ */
	STRING	format2 = "/opt/SPECS/sys/bin/tplattr -A -t %s %s";	/* AVPATH_ */
	STRING	command;
	STRING	tplname, tplvers;
	STRING	spcname, spcvers, spctype;
	char	limname[MAX_NAM_LENG], limvers[MAX_VER_LENG];
	char	limtplname[MAX_NAM_LENG], limtplvers[MAX_VER_LENG];
	int	tplnums, limnums;
	int	verify_limit, revcont, j;
	char	buffer[MAX_BUF_LENG];
	FILE	*fp;
	const char *tplsffx, *limsffx;

	*Result = 0;

	verify_limit = 1;
	if ((fp = fopen(sysconf, "r")) != NULL) {
		while (fgets(buffer, MAX_BUF_LENG, fp)) {
			if (strncmp(buffer, "VERIFYLIMIT=", strlen("VERIFYLIMIT=")) == 0) {
				if (strcmp(buffer + strlen("VERIFYLIMIT="), "FALSE\n") == 0) {
					verify_limit = 0;
				}
				break;
			}
		}
		fclose(fp);
	}
	TPLGETREVCONT(&revcont);

	if (tplsffx = strrchr(Testplan, '.')) {
		if (strcmp(tplsffx, ".tpl") == 0) {
			Testplan[strlen(Testplan) - strlen(tplsffx)] = '\0';
		}
	}
	if (limsffx = strrchr(Limit, '.')) {
		if (strcmp(limsffx, ".lim") == 0) {
			Limit[strlen(Limit) - strlen(limsffx)] = '\0';
		}
	}

	if (strlen(Testplan) == 0) {
		TPLFILETPL(&tplname, &tplvers, &tplnums);
		if (strlen(tplname) == 0) {
			*Result = -1;
			return;
		}
		strcat(tplname, ".tpl");
		if (strcmp(tplvers, "1") == 0) {
			strcpy(tplvers, "");
		}
	}
	else {
		sprintf(command, format1, "tpl", Testplan);

		if ((fp = popen(command, "r")) == NULL) {
			printf("CHECK_FILE: popen failed\n");
			*Result = -1;
			return;
		}

		sprintf(tplname, "%s.tpl", Testplan);
		while (fgets(buffer, MAX_BUF_LENG, fp)) {
			if (strncmp(buffer, "$Vers", strlen("$Vers")) == 0) {
				strcpy(tplvers, buffer + strlen("$Vers\t"));
				if (tplvers[strlen(tplvers) - 1] == '\n') {
					tplvers[strlen(tplvers) - 1] = '\0';
				}
			}
		}

		pclose(fp);
	}

	if (strlen(Limit) == 0) {
		strcpy(limvers, " ");
		strcpy(limtplname, tplname);
		strcpy(limtplvers, tplvers);
	}
	else {
		sprintf(command, format1, "lim", Limit);

		if ((fp = popen(command, "r")) == NULL) {
			printf("CHECK_FILE: popen failed\n");
			*Result = -1;
			return;
		}

		sprintf(limname, "%s.lim", Limit);
		while (fgets(buffer, MAX_BUF_LENG, fp)) {
			if (strncmp(buffer, "$Vers", strlen("$Vers")) == 0) {
				strcpy(limvers, buffer + strlen("$Vers\t"));
				if (limvers[strlen(limvers) - 1] == '\n') {
					limvers[strlen(limvers) - 1] = '\0';
				}
			}
			else if (strncmp(buffer, "$TplName", strlen("$TplName")) == 0) {
				strcpy(limtplname, buffer + strlen("$TplName\t"));
				if (limtplname[strlen(limtplname) - 1] == '\n') {
					limtplname[strlen(limtplname) - 1] = '\0';
				}
			}
			else if (strncmp(buffer, "$TplVers", strlen("$TplVers")) == 0) {
				strcpy(limtplvers, buffer + strlen("$TplVers\t"));
				if (limtplvers[strlen(limtplvers) - 1] == '\n') {
					limtplvers[strlen(limtplvers) - 1] = '\0';
				}
			}
		}

		pclose(fp);
	}

	if (verify_limit == 1 && strcmp(tplname, limtplname) != 0) {
		*Result = 1;
		return;
	}
	if (verify_limit == 1 && strcmp(tplvers, limtplvers) != 0) {
		*Result = 2;
		return;
	}
	if (revcont == 1 && strlen(tplvers) == 0) {
		if (strlen(Testplan) == 0) {
			for (j = 0; j < tplnums; j++) {
				TPLFILESPCTPL(j, &spcname, &spctype, &spcvers);
				if (strcmp(spcvers, "1") == 0) {
					*Result = 3;
					break;
				}
			}
		}
		else {
			sprintf(command, format2, "tpl", Testplan);

			if ((fp = popen(command, "r")) == NULL) {
				printf("CHECK_FILE: popen failed\n");
				*Result = -1;
				return;
			}

			while (fgets(buffer, MAX_BUF_LENG, fp)) {
				if (strncmp(buffer, "$Vers", strlen("$Vers")) == 0) {
					strcpy(tplvers, buffer + strlen("$Vers\t"));
					if (tplvers[strlen(tplvers) - 1] == '\n') {
						tplvers[strlen(tplvers) - 1] = '\0';
					}
					if (strlen(tplvers) == 0) {
						*Result = 3;
						break;
					}
				}
			}

			pclose(fp);
		}

		if (*Result == 3) {
			return;
		}
	}
	if (revcont == 1 && strlen(limvers) == 0) {
		*Result = 4;
		return;
	}

	return;



/*===========================================================================*/
/****** <BEGIN> ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
}
/****** <END>   ALGORITHM TAIL ********** DON'T EDIT FROM <BEGIN> TO <END> ***/
