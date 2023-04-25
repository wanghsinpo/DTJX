
#include <stdio.h>
#include <string.h>

#define DEFAULT_ENVNAME  "RFTAGPORT"
static char szEnvName[128], szDefEnvName[] = DEFAULT_ENVNAME;
static char szWriteCount[128];
static int iWriteCount = 0;
static int iTargetID = 2;

#define SERIAL_RETRY  3

static char szTagName[] = "Agilent";

static int iMaxCount = 0;
static int iCurrentCount = 0;
static int iTotalCount = 0;
static char szProbeID[20] = "";



static int ProcessCommandLine(int argc, char **argv)
{
    int      c;                      /* current character             */
    int      argno = 1;              /* Number of current argument    */
    int      env = 0;

    while(argno < argc){
        if(argv[argno][0] == '-'){
            c = tolower(argv[argno][1]);

            if(c == 'e'){
                if((argno+1) < argc){
                    env = 1;
                    argno++;
                    strcpy(szEnvName, argv[argno]);
                }
            }else if(c == 'c'){
                if((argno+1) < argc){
                    iWriteCount = 1;
                    argno++;
                    strcpy(szWriteCount, argv[argno]);
                    iCurrentCount = atoi(szWriteCount);
                }
            }else if(c == 't'){
                if((argno+1) < argc){
                    iWriteCount = 1;
                    argno++;
                    strcpy(szWriteCount, argv[argno]);
                    iTotalCount = atoi(szWriteCount);
                }
            }else if(c == 'i'){
                if((argno+1) < argc){
                    argno++;
                    iTargetID = atoi(argv[argno]);
                }
            }
        }else{
            break;
        }
        argno++;
    }

    if(env == 0)
        strcpy(szEnvName, szDefEnvName);

    return 0;
}


static char *CheckInputLine(char *buf, char *check)
{
    char chk[256], *point;

    sprintf(chk, "%02d %s", iTargetID, check);

    if(strncmp(chk, buf, strlen(chk)) != 0){
#ifdef DEBUG
        printf("Input Line check error 1[%s:%s]\n", chk, buf);
#endif
        return NULL;
    }
    point = buf + strlen(chk) + 1;
    if(!strlen(point)){
#ifdef DEBUG
        printf("Input Line check error 2[%s]\n", point);
#endif
        return NULL;
    }

    return point;
}


struct getdata
{
    char *data;
    char *check;
    int  type;
}
get[] = {{"HCS R",                      "HCA D NO",     0},
         {"HCS WAR CID_MAX_LENGTH 48",  "HCA WADA NO",  0},
         {"HCS WAR CID_JUSTIFY R",      "HCA WADA NO",  0},
         {"HCS WAR CARRIERIDOFFSET 0",  "HCA WADA NO",  0},
         {"HCS WAR CARRIERIDLENGTH 7",  "HCA WADA NO",  0},
         {"HCS RMID",                   "HCA RMIDA NO", 1},
         {"HCS WAR CARRIERIDOFFSET 8",  "HCA WADA NO",  0},
         {"HCS WAR CARRIERIDLENGTH 9",  "HCA WADA NO",  0},
         {"HCS RMID",                   "HCA RMIDA NO", 2},
         {"HCS WAR CARRIERIDOFFSET 17", "HCA WADA NO",  0},
         {"HCS WAR CARRIERIDLENGTH 8",  "HCA WADA NO",  0},
         {"HCS RMID",                   "HCA RMIDA NO", 3},
         {"HCS WAR CARRIERIDOFFSET 25", "HCA WADA NO",  0},
         {"HCS WAR CARRIERIDLENGTH 8",  "HCA WADA NO",  0},
         {"HCS RMID",                   "HCA RMIDA NO", 4},
         {"HCS WAR CARRIERIDOFFSET 33", "HCA WADA NO",  0},
         {"HCS WAR CARRIERIDLENGTH 8",  "HCA WADA NO",  0},
         {"HCS RMID",                   "HCA RMIDA NO", 5},
         {NULL, NULL, 0}};


static int GetTagData()
{
    int i, j, k, l, ret;
    char receive[256], send[256];
    char *point;

    if((ret = SerialOpen()) != -1){
        for(j=0; j < SERIAL_RETRY; j++){
            ret = 0;
            for(i=0; get[i].data; i++){
                sprintf(send, "%02d %s", iTargetID, get[i].data);
                if((ret = SerialWrite(send)) == -1) break;
                if((ret = SerialRead(receive)) == -1) break;
                point = CheckInputLine(receive, get[i].check);
                if(point == NULL){
                    ret = -1;
                    break;
                }

                switch(get[i].type){
                case 1:
                    if(strlen(point) != 7){
                        ret = -1;
                    }else{
                        if(strncmp(szTagName, point, strlen(szTagName)) != 0)
                            ret = -1;
                    }
                    break;
                case 2:
                    if(strlen(point) != 9){
                        ret = -1;
                    }else{
                        strcpy(szProbeID, point);
                        for(k = strlen(szProbeID); (k-1) >= 0 && szProbeID[(k-1)] == ' '; k--){
                            szProbeID[(k-1)] = '\0';
                        }
                    }
                    break;
                case 3:
                    if(strlen(point) != 8)
                        ret = -1;
                    else
                        iMaxCount = atoi(point);
                        break;
                case 4:

                    if(strlen(point) != 8)
                        ret = -1;
                    else
                        iCurrentCount = atoi(point);
                    break;
                case 5:
                    if(strlen(point) != 8)
                        ret = -1;
                    else
                        iTotalCount = atoi(point);
                    break;
                default:
                    break;
                }
                if(ret == -1) break;
            }
            if(ret == 0) break;
        }
        SerialClose();
    }

    return ret;
}


struct putdata
{
    char *data;
    char *check;
    int  type;
}
put[] = {{"HCS R",                      "HCA D NO",     0},
         {"HCS WAR CARRIERIDOFFSET 0",  "HCA WADA NO",  0},
         {"HCS WAR CARRIERIDLENGTH 8",  "HCA WADA NO",  0},
         {"HCS WAR CID_MAX_LENGTH 48",  "HCA WADA NO",  0},
         {"HCS WAR CID_JUSTIFY R",      "HCA WADA NO",  0},
         {"HCS WAR MANTWRITEONLY DI",   "HCA WADA NO",  0},
         {"HCS WAR CARRIERIDOFFSET 25", "HCA WADA NO",  0},
         {"HCS WMID",                   "HCA WMIDA NO", 1},
         {"HCS WAR CARRIERIDOFFSET 33", "HCA WADA NO",  0},
         {"HCS WMID",                   "HCA WMIDA NO", 2},
         {NULL, NULL, 0}};


static int PutTagData()
{
    int i, j, ret;
    char receive[256], send[256], *point;

    if((ret = SerialOpen()) != -1){
        for(j=0; j < SERIAL_RETRY; j++){
            ret = 0;
            for(i=0; put[i].data; i++){
                switch(put[i].type){
                case 0:
                    sprintf(send, "%02d %s", iTargetID, put[i].data);
                    break;
                case 1:
                    sprintf(send, "%02d %s %08d", iTargetID, put[i].data,
                                                             iCurrentCount);
                    break;
                case 2:
                    sprintf(send, "%02d %s %08d", iTargetID, put[i].data,
                                                             iTotalCount);
                    break;
                default:
                    break;
                }
                
                if((ret = SerialWrite(send)) == -1) break;
                if((ret = SerialRead(receive)) == -1) break;
                point = CheckInputLine(receive, put[i].check);
                if(point == NULL){
                    ret = -1;
                    break;
                }
            }
            if(ret == 0) break;
        }

        SerialClose();
    }

    return ret;
}


#ifndef TEC
int main(int argc, char **argv)
{
    int ret;

    ProcessCommandLine(argc, argv);

    GetEnvironmentVariable(szEnvName);

    if(iWriteCount == 0){
        ret = GetTagData();
    }else{
        ret = PutTagData();
    }

    if(ret == -1){
        printf("error\n");
    }else{
        if(iWriteCount == 0)
            printf("%s,%d,%d,%d\n", szProbeID,  iMaxCount, iCurrentCount, iTotalCount);
        else
            printf("OK\n");
    }
    return ret;
}
#else
int rftag(char *pname)
{
    int ret;

    GetEnvironmentVariable(szEnvName);

    ret = GetTagData();

    if(ret == -1){
        sprintf(pname, "000000000");
    }else{
        sprintf(pname, "%-9s", szProbeID);
        }

        return ret;
}
#endif
