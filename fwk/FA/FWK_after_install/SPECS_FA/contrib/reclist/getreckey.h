/*---------------------------------------------------------------------
 **********************************************************************
 *
 *                     MODULE  : getreckey.h
 *
 *---------------------------------------------------------------------
 *
 *        (c) Copyright Keysight Technologies,2005-2015
 *
 *---------------------------------------------------------------------
 *
 *  CONTENTS: This is the main header file for getreckey.h example.
 *
 **********************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FILE_NAME_MAX 256
#define MAX_LINE      2048
#define RECIPEFILE "/opt/SPECS/usr/tpl/FA_recipe2.rec"
#define RECIPEFILE_TAG  "RecipeFile"

#define RECIPELIST "/opt/SPECS_FA/sys/tmp/S7F19_list.txt"
#define RECIPELIST_TAG "recipeFile"

#define DEFAULTFILE     "/opt/SPECS_FA/dmh/vgem/defaults.ini"
#define DEFAULTFILE_TAG "VGEM"
