/*---------------------------------------------------------------------
 **********************************************************************
 *
 *                     MODULE  : getreckey.c
 *
 *---------------------------------------------------------------------
 *
 *        (c) Copyright Keysight Technologies, 2005-2015
 *
 *---------------------------------------------------------------------
 *
 * *  CONTENTS: This is an example that shows how to embed getreckey
 *            and the dmh inside a c program.
 *
 **********************************************************************/
 
#include <string.h>
#include "getreckey.h"

void setRecipeList(FILE *recipe_fd, FILE *list_fd);
int  chkDir(char *name);
char *skipSpace(char *buf);
char *serchSpace(char *buf);

/*
 * Check RECIPE KEY
 * Nobuhiko Yoshimura  April 21 2008
 */
int checkreckey(char *recipeid)
{
    FILE *recipe_fd;
    char recname[FILE_NAME_MAX], cmd[FILE_NAME_MAX];
    int  rtn_result;

    recname[0] = '\0';
    if(getdefaultvar(RECIPEFILE_TAG, recname) != 0) 
        strcpy(recname, RECIPEFILE);

    if(!(recipe_fd = fopen(recname, "r")))
        return -1;

    rtn_result = checkRecipeID(recipe_fd,recipeid);

    fclose(recipe_fd);

    return rtn_result;
}

/*
 * check Recipe ID
 * Nobuhiko Yoshimura  April 21 2008
 */
int checkRecipeID(FILE *recipe_fd, char *recipeid)
{
    char buff[MAX_LINE];
    char *cp, *end;
    int  rtn;

    while(fgets(buff, MAX_LINE, recipe_fd) != NULL){
        cp = skipSpace(buff);
        if(cp == NULL || *cp == '#')
            continue;
        end = serchSpace(cp);
        *end = '\0';
        if((rtn=strcmp(cp,recipeid)) == 0) {
          return 1;
        }
    }
    return 0;
}


/*
 * set RECIPE KEY List
 */
int getreckey()
{
    FILE *recipe_fd, *list_fd;
    char recname[FILE_NAME_MAX], listname[FILE_NAME_MAX], cmd[FILE_NAME_MAX];

    recname[0] = '\0';
    listname[0] = '\0';
    if(getdefaultvar(RECIPEFILE_TAG, recname) != 0) 
        strcpy(recname, RECIPEFILE);
    if(getdefaultvar(RECIPELIST_TAG, listname) != 0)
        strcpy(listname, RECIPELIST);

    if(!(recipe_fd = fopen(recname, "r")))
	return -1;

    if(!(list_fd = fopen(listname, "w")))
	return -1;

    setRecipeList(recipe_fd, list_fd);

    fclose(recipe_fd);
    fclose(list_fd);

    return 0;
}

int getdefaultvar(char *varname, char *buf)
{
    FILE *default_fd;
    char line[MAX_LINE];
    char *p, *b, *e;

    strcpy(buf, "");
    if((default_fd = fopen(DEFAULTFILE, "r")) == NULL)
        return -1;

    p = NULL;
    while(fgets(line, MAX_LINE, default_fd) != NULL){
        if(strncmp(line, DEFAULTFILE_TAG, strlen(DEFAULTFILE_TAG)) != 0)
            continue;
        p = strstr(line, varname);
        if(p != NULL)
            break;
    }

    fclose(default_fd);

    if(p == NULL)
        return -1;

    b = p + strlen(varname);
    while(1){
        if(isspace(*b) == 0)
            break;
        b++;
    }
    strcpy(buf, b);

    e = buf + strlen(buf);
    while(e > buf){
        if(isspace(*--e) == 0){
            ++e;
            break;
        }
    }
    *e = '\0';

    if(buf[0] != '/'){
        strcpy(buf, "");
        return -1;
    }

    return 0;
}

void setRecipeList(FILE *recipe_fd, FILE *list_fd)
{
    char buff[MAX_LINE];
    char *cp, *end;

    while(fgets(buff, MAX_LINE, recipe_fd) != NULL){
        cp = skipSpace(buff);
        if(cp == NULL || *cp == '#')
            continue;
        end = serchSpace(cp);
        *end = '\0';
        fprintf(list_fd, "%s\n", cp);
    }
    fflush(list_fd);
}

/*
 * Skip space & TAB
 */
char *skipSpace(char *buf)
{
    char *cp;
    int f;

    for(f = 0, cp = buf; cp != '\0'; cp++){
        if(*cp != ' ' && *cp != '\t'){
            if(*cp == 0x0a || *cp == 0x0d || *cp == '\0')
                return NULL;
            return cp;
        }
	if(*cp == '\t') 
	    return NULL;
    }
}

/*
 * Search space & TAB
 */
char *serchSpace(char *buf)
{
    char *cp;

    for(cp = buf; cp != '\0'; cp++){
        if(*cp == ' ' || *cp == '\t' || *cp == 0x0a || *cp == 0x0d || *cp == '\0')
            return cp;
    }
}

/*
 * Check Recipe List Dir
 */
int chkDir(char *name)
{
    struct stat buffer;

    if(lstat(name, &buffer) == -1)
	return -2;

    if(!S_ISDIR(buffer.st_mode))
	return -1;

    if(getuid() == buffer.st_uid){
        if(!(buffer.st_mode & S_IWUSR))
	    return -1;
    }else if(getgid() == buffer.st_gid){
        if(!(buffer.st_mode &S_IWGRP))
	    return -1;
    }else{
        if(!(buffer.st_mode & S_IWOTH))
	    return -1;
    }

    return 0;
}


/*
 * end of file
 */
