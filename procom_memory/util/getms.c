#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

void getMs(char *time_str, char *time_fmt) {
	char tmpStr[100];
	struct tm * timeinfo;
	memset(&tmpStr, 0x00, sizeof(tmpStr));
	struct timeval tms;
	gettimeofday(&tms, NULL);

	time_t bintime;
	time(&bintime);
	timeinfo = localtime(&bintime);
	strftime(tmpStr, sizeof(tmpStr), time_fmt, timeinfo);
	sprintf(time_str, "%s.%03d", tmpStr, tms.tv_usec / 1000);
}

