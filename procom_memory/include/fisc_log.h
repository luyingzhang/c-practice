#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <errno.h>

char service[15];

struct {
	long qtype;
	char log_type;
	char log_text[1024];
} logmsg;
