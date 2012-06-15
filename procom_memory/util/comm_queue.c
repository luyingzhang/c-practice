#include "comm_queue.h"

/*--------------------------------------------------------------------------
 * Function ID:
 * Description:
 * Parameters:	none
 * Return:	none
 --------------------------------------------------------------------------*/
int createQueue(int key) {
	int msgid = 0;
	msgid = msgget((key_t) key, QUEUE_PRIVILEGE | IPC_CREAT);
	return msgid;
}

/*--------------------------------------------------------------------------
 * Function ID:
 * Description:
 * Parameters:	none
 * Return:	none
 --------------------------------------------------------------------------*/
int attachQueue(int key) {
	int msgid;
	msgid = msgget((key_t) key, QUEUE_PRIVILEGE);
	return msgid;
}

/*--------------------------------------------------------------------------
 * Function ID:
 * Description:
 * Parameters:	none
 * Return:	none
 --------------------------------------------------------------------------*/
int receiveQueue(int id, Msg *msg, int size, int key, int timeout) {
	int msgid, rc, count;

	if (timeout == 0) {
		rc = msgrcv(id, msg, size, key, 0);
	} else {
		count = 0;
		while (1) {
			rc = msgrcv(id, msg, size, key, IPC_NOWAIT);
			count++;
			if (rc > 0)
				break;
			if (rc < 0 && errno != 42)
				break;
			if (count > (timeout * 10)) {
				rc = 0;
				break;
			}
			usleep(100);
		}
	}

	return rc;
}
