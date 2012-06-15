#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

/*Message Queue*/
#define  QUEUE_PRIVILEGE    0666
#define  QUEUE_LEN          2060

typedef struct Msg Msg;
struct Msg {
	long int msg_type; /*for Message Queue API*/
	long int len;
	char data[2048];
};
int inQ, outQ[5];
