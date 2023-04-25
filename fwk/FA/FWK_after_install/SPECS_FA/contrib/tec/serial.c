
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#define BAUDRATE B9600           /* 通信速度の設定 */

#define DEFAULT_PORTNAME  "/dev/tty0p0"

#define INVALID_HANDLE_COM    -1

static int pDev = INVALID_HANDLE_COM;
struct termios oldtio, newtio; /* 通信ポートを制御するためのインターフェイス */

static char gszDevName[128] = "";
static char szDevName[128], szDefDevName[] = DEFAULT_PORTNAME;


void GetEnvironmentVariable(char *env)
{
    char *env_port;

    if((env == NULL) || (strlen(env) == 0)){
        strcpy(szDevName, szDefDevName);
    }else{
        env_port = getenv(env);
        if(env_port == NULL){
            strcpy(szDevName, szDefDevName);
        }else{
            strcpy(szDevName, env_port);
        }
    }
}


int SerialOpen(void)
{
    int ret;

    if((pDev=open(szDevName, O_RDWR | O_NOCTTY))== -1){
#ifdef DEBUG
        printf("COM Open Error\n");
#endif
        return -1;
    }

    fcntl(pDev, F_SETFL);

    if((ret = tcgetattr (pDev, &oldtio)) < 0){
        /*
        errno
        */
    }
    memset (&newtio, 0, sizeof(newtio));

    newtio.c_cflag |= BAUDRATE;
    newtio.c_cflag |= CS8;     /* 8 databits */
#if 0
    newtio.c_cflag |= CSTOPB;  /* 2 stopbits */
#endif
    newtio.c_cflag |= CLOCAL;  /* should always be enabled */
    newtio.c_cflag |= CREAD;   /* should always be enabled */
#if 0
    newtio.c_oflag |= ONLCR;
#endif

    /* It returuns, when 1 byte is received or timeout. */
    newtio.c_cc[VMIN]   = 1;    /* [6] = 001; min. count of chars to return from read() */
    newtio.c_cc[VTIME]  = 0;    /* [5] = 000; timeout for read() in 1/10 s steps. */

    if((ret = tcsetattr (pDev, TCSANOW, &newtio)) < 0){
#if 0
        errno;
#endif
    }

    return 0;
}


void SerialClose(void)
{
    if(tcsetattr (pDev, TCSANOW, &oldtio) < 0){
#if 0
        errno;
#endif
    }

    close(pDev);
    pDev = INVALID_HANDLE_COM;
}


int SerialWrite(char *buf)
{
    int len, i, ret;
    char send[512];

    if(pDev == INVALID_HANDLE_COM) return -1;

    sprintf(send, "%s\r\n", buf);
    /*
    len = strlen(send);
    ret = write(pDev, send, len);
    */
    len = strlen(send);
    for (i = 0; i < len; i++) {

        ret = write (pDev, &(send[i]),  1);

        if(ret <= 0){
#ifdef DEBUG
            printf("Read Error\n");
#endif
            return -1;
        }
    }
#ifdef DEBUG
    printf("< %s", send);
#endif

  return 0;
}


int SerialRead(char *buf)
{
    int len, i, ret;
    char in;

    if(pDev == INVALID_HANDLE_COM) return -1;

    i = 0;
    in = 0x20;
    while(1){
        ret = read(pDev, &in, 1);
        if(ret <= 0){
#ifdef DEBUG
            printf("Read Error\n");
#endif
            return -1;
        }
        buf[i] = in;
        if(i >= 1 && (buf[i-1] == 0x0D && buf[i] == 0x0A)){
             buf[i-1] = '\0';
             break;
        }
        i++;
    }

#ifdef DEBUG
    printf("> %s\n", buf);
#endif

    return 0;
}

