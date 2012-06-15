#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "comm_queue.h"
#include "fisc_log.h"
#include "fisc_shm.h"

int log_queue = 0;
//void getMs(char *time_str, char *time_fmt) {
//	char tmpStr[100];
//	struct tm * timeinfo;
//	memset(&tmpStr, 0x00, sizeof(tmpStr));
//	struct timeval tms;
//	gettimeofday(&tms, NULL);
//
//	time_t bintime;
//	time(&bintime);
//	timeinfo = localtime(&bintime);
//	strftime(tmpStr, sizeof(tmpStr), time_fmt, timeinfo);
//	sprintf(time_str, "%s.%03d", tmpStr, tms.tv_usec / 1000);
//}
/*--------------------------------------------------------------------------
 * Function ID:
 * Description:	output message to log file and/or stdout
 * Parameters:	none
 * Return:	none
 --------------------------------------------------------------------------*/
void dmplog(char msg_id, char *fmt, ...) {
	char log_msg[256];
	char tmp_msg[256];
	va_list argptr;
	char time_str[32];
	char *msg_type;
	if (log_queue == 0) {
		if (shm != NULL)
			log_queue = attachQueue(shm->log_queue);
		else
			return;
	}

	va_start(argptr, fmt);
	vsprintf(log_msg, fmt, argptr);
	va_end(argptr);
	memset(time_str, 0x00, sizeof(time_str));
	getMs(time_str, "%H%M%S");
	switch (msg_id) {
	case 'I':
		msg_type = "MSG";
		break;
	case 'E':
		msg_type = "ERR";
		break;
	case 'D':
		msg_type = "DMP";
		break;
	default:
		msg_type = "LOG";
		break;
	}
	sprintf(logmsg.log_text, "%-15s:%s:%s:%s\n", service, time_str, msg_type,
			log_msg);

	logmsg.log_type = msg_id;
	logmsg.qtype = 1;
	msgsnd(log_queue, (void *) &logmsg, sizeof(logmsg), IPC_NOWAIT);
}

/*--------------------------------------------------------------------------
 * Function ID:	DumpBuf_TX
 * Description:	output message to log file and/or stdout
 * Parameters:	none
 * Return:	none
 --------------------------------------------------------------------------*/
void DumpBuf_TX(unsigned char mode, unsigned char *buf, int len) {
	int cnt, i, cntl1, cntl2;
	unsigned char xbuf[25], abuf[9], pbuf[78];
	char lbuf[13], tmpx[4];
	unsigned char *p;

	memset(lbuf, 0x00, sizeof(lbuf));
	memset(xbuf, 0x00, sizeof(xbuf));
	memset(abuf, 0x00, sizeof(abuf));
	memset(pbuf, 0x00, sizeof(pbuf));

	p = buf;
	cnt = 1;
	cntl1 = 1;
	cntl2 = 0;

	while (cnt <= len) {
		memset(lbuf, ' ', sizeof(lbuf) - 1);
		memset(xbuf, ' ', sizeof(xbuf) - 1);
		memset(abuf, ' ', sizeof(abuf) - 1);
		memset(pbuf, ' ', sizeof(pbuf) - 1);

		for (i = 0; i < 8; i++) {
			sprintf(tmpx, "%02x ", p[i]);
			memcpy(xbuf + i * 3, tmpx, 3);
			if (!isprint(p[i]))
				abuf[i] = '.';
			else
				abuf[i] = p[i];
			cnt++;
			cntl2++;
			if (cnt > len)
				break;
		}

		sprintf(pbuf, "%05d-%05d %s %s", cntl1, cntl2, xbuf, abuf);
		cntl1 = cntl2 + 1; /* increase offset */
		dmplog(mode, "%s", pbuf);
		p = buf + cnt - 1;
	}
	dmplog(mode, " ");
}
