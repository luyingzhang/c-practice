#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <setjmp.h>
#include <signal.h>

#define  TCP_STATUS_NORMAL 1
#define  TCP_STATUS_ERROR -1
#define  TCP_STATUS_TIMEOUT -2
#define  TCP_DATA_LEN 32767

#define  TCP_MAX_LEN 4096
#define  ICONHLEN 100
#define  RSMLEN 20
#define  CSMLEN 12


unsigned char TCPSendBuff[TCP_DATA_LEN];
unsigned char TCPRecvBuff[TCP_DATA_LEN];

int TCPSendLen, TCPRecvLen;
