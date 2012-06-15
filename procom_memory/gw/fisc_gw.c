#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comm_queue.h"
#include "fisc_shm.h"
#include "fisc_log.h"
#include "fisc_msg.h"

int skey;
int des_queue, fep_queue;
/*--------------------------------------------------------------------------
 * Function ID:
 * Description:
 * Parameters:
 * Return:
 --------------------------------------------------------------------------*/
void genFiscRspMsg(FISC_DATA *in, Msg *fepMsg, Msg *replayMsg, char *item,
		char *mac) {
	FISC_DATA out_data;
	unsigned char data[512];
	memcpy(fepMsg->data, in, sizeof(FISC_DATA));

	memcpy(data, in->data, sizeof(data));
	memcpy(&out_data, in, sizeof(out_data));
	memset(&out_data.data, 0x00, sizeof(out_data.data));
	memset(&out_data.bit_map, 0x00, sizeof(out_data.bit_map));
	out_data.msg_code[2] = '1';
	if (memcmp(&out_data.rsp_code, "5017", 4) == 0)
		memcpy(&out_data.rsp_code, "0001", 4);
	memcpy(&out_data.key_sync, item, 4);
	memcpy(&out_data.data[0], &data[14], 21);
	setonBitmap(&out_data.bit_map, 3);
	setonBitmap(&out_data.bit_map, 8);
	memcpy(&out_data.data[21], mac, 4);
	setonBitmap(&out_data.bit_map, 64);
	replayMsg->msg_type = 1;
	replayMsg->len = 85;
	memcpy(replayMsg->data, &out_data, sizeof(out_data));
}

/*--------------------------------------------------------------------------
 * Function ID:
 * Description:
 * Parameters:
 * Return:
 --------------------------------------------------------------------------*/
int genFiscMac(unsigned char *mac_data, unsigned char *icv, unsigned char *mac) {
	Msg hsm_msg;
	unsigned char bankId[8];
	int rc, pid;
	memset(&hsm_msg, 0x00, sizeof(hsm_msg));
	pid = getpid();
	hsm_msg.msg_type = pid;
	hsm_msg.len = 44;
	hsm_msg.data[0] = 0xb1;
	hsm_msg.data[1] = 0x56;
	memcpy(&hsm_msg.data[2], icv, 8);
	memcpy(&hsm_msg.data[10], "16", 2);
	memcpy(&hsm_msg.data[12], mac_data, 16);
	msgsnd(des_queue, (void *) &hsm_msg, sizeof(hsm_msg), IPC_NOWAIT);
	memset(&hsm_msg, 0x00, sizeof(hsm_msg));
	rc = receiveQueue(fep_queue, &hsm_msg, sizeof(hsm_msg), pid, 0);
	if (rc > 0) {
		if (hsm_msg.data[0] != 0x00) {
			return -1;
		}
		memcpy(mac, &hsm_msg.data[9], 4);
	} else {
		return -1;
	}
	return 1;
}

/*--------------------------------------------------------------------------
 * Function ID:
 * Description:
 * Parameters:
 * Return:
 --------------------------------------------------------------------------*/
int genFiscCheckItem(unsigned char *rbank, unsigned char *ritem,
		unsigned char *sbank, unsigned char *sitem) {
	Msg hsm_msg;
	unsigned char bankId[8];
	unsigned char retcode[9];
	int rc, pid;
	memset(&hsm_msg, 0x00, sizeof(hsm_msg));
	pid = getpid();
	hsm_msg.msg_type = pid;
	hsm_msg.len = 19;
	hsm_msg.data[0] = 0xb2;
	hsm_msg.data[1] = 0x56;
	hsm_msg.data[2] = 'O';
	memset(bankId, 0x00, sizeof(bankId));
	memset(bankId, 0x30, 8);
	memcpy(bankId, rbank, 3);
	pack(&hsm_msg.data[3], &bankId, 8);
	memset(bankId, 0x00, sizeof(bankId));
	memset(bankId, 0x30, 8);
	memcpy(bankId, sbank, 3);
	pack(&hsm_msg.data[11], &bankId, 8);
	msgsnd(des_queue, (void *) &hsm_msg, sizeof(hsm_msg), IPC_NOWAIT);
	memset(&hsm_msg, 0x00, sizeof(hsm_msg));
	rc = receiveQueue(fep_queue, &hsm_msg, sizeof(hsm_msg), pid, 0);
	if (rc > 0) {
		if (hsm_msg.data[0] != 0x00) {
			return -1;
		}
		memcpy(ritem, &hsm_msg.data[9], 4);
		memcpy(sitem, &hsm_msg.data[17], 4);
	} else {
		return -1;
	}
	return 1;
}

/*--------------------------------------------------------------------------
 * Function ID:
 * Description:
 * Parameters:
 * Return:
 --------------------------------------------------------------------------*/
int checkFiscMsg(FISC_DATA *in_data, char *fisc_retcode, char *omac) {
	int pos = 0, itemp, len, tel_no;
	unsigned char temp[15], mac[4], icv[8], mac_data[16], tmac_data[32],
			ticv[16];
	unsigned char data[512];

	memcpy(data, in_data->data, sizeof(data));
	memset(tmac_data, 0x30, sizeof(tmac_data));
	memcpy(&tmac_data[20], &in_data->src_bank, 3);
	memcpy(&tmac_data[23], &in_data->rsp_code, 4);
	memset(ticv, 0x30, sizeof(ticv));
	memcpy(ticv, in_data->datetime, 6);
	pack(icv, ticv, 16);

	/*acc no*/
	if (checkBitmap(in_data->bit_map, 2)) {
		memset(temp, 0x00, sizeof(temp));
		memcpy(temp, &data[pos], 14);
		itemp = atoi(temp);
		if (itemp == 0) {
			memcpy(fisc_retcode, "0101", 4);
			dmplog('I', "account type error!!");
			return -1;
		}
		pos += 14;
	}
	/*amount*/
	if (checkBitmap(in_data->bit_map, 3)) {
		if (data[pos] != '+') {
			memcpy(fisc_retcode, "0101", 4);
			dmplog('I', "amount not have plus '+' !!");
			return -1;
		}
		pos += 1;
		memset(temp, 0x00, sizeof(temp));
		memcpy(temp, &data[pos], 13);
		itemp = atoi(temp);
		if (itemp == 0) {
			memcpy(fisc_retcode, "0101", 4);
			dmplog('I', "amount type error!!");
			return -1;
		}
		memcpy(&tmac_data[7], temp, 13);
		pos += 13;
	}

	/*tel_no*/
	if (checkBitmap(in_data->bit_map, 8)) {
		memset(temp, 0x00, sizeof(temp));
		memcpy(temp, &data[pos], 7);
		tel_no = atoi(temp);
		if (tel_no == 0) {
			memcpy(fisc_retcode, "0101", 4);
			dmplog('I', "tel_no type error!!");
			return -1;
		}
		if (shm->fisc_tx_no != 0 && tel_no != shm->fisc_tx_no + 1) {
			memcpy(fisc_retcode, "5001", 4);
			dmplog('I', "fisc tel_no[%d], procom tel_no[%d] of different!!",
					tel_no, shm->fisc_tx_no + 1);
			return -1;
		}
		memcpy(&tmac_data[0], temp, 7);
		pos += 7;
	}
	/*rmt_no*/
	if (checkBitmap(in_data->bit_map, 9)) {
		memset(temp, 0x00, sizeof(temp));
		memcpy(temp, &data[pos], 7);
		itemp = atoi(temp);
		if (itemp == 0) {
			memcpy(fisc_retcode, "0101", 4);
			dmplog('I', "rmt_no type error!!");
			return -1;
		}
		pos += 7;
	}
	if (checkBitmap(in_data->bit_map, 12)) {
		pos += 7;
	}
	/*s_bank*/
	if (checkBitmap(in_data->bit_map, 13)) {
		memset(temp, 0x00, sizeof(temp));
		memcpy(temp, &data[pos], 7);
		itemp = atoi(temp);
		if (itemp == 0) {
			memcpy(fisc_retcode, "0101", 4);
			dmplog('I', "s_bank type error!!");
			return -1;
		}
		pos += 7;
	}
	/*r_bank*/
	if (checkBitmap(in_data->bit_map, 14)) {
		memset(temp, 0x00, sizeof(temp));
		memcpy(temp, &data[pos], 7);
		itemp = atoi(temp);
		if (itemp == 0) {
			memcpy(fisc_retcode, "0101", 4);
			dmplog('I', "r_bank type error!!");
			return -1;
		}
		pos += 7;
	}
	if (checkBitmap(in_data->bit_map, 17)) {
		pos += 2;
	}
	if (checkBitmap(in_data->bit_map, 19)) {
		pos += 4;
	}
	if (checkBitmap(in_data->bit_map, 20)) {
		pos += 4;
	}
	/*member bank*/
	if (checkBitmap(in_data->bit_map, 21)) {
		len = (data[pos] * 256) + data[pos + 1];
		if (len > 24) {
			memcpy(fisc_retcode, "5004", 4);
			dmplog('I', "member bank Length > 80!!");
			return -1;
		}
		pos += len;
	}
	/*Beneficiary*/
	if (checkBitmap(in_data->bit_map, 22)) {
		len = (data[pos] * 256) + data[pos + 1];
		if (len > 80) {
			memcpy(fisc_retcode, "5004", 4);
			dmplog('I', "Beneficiary Length > 80!!");
			return -1;
		}
		pos += len;
	}
	/*Sender*/
	if (checkBitmap(in_data->bit_map, 23)) {
		len = (data[pos] * 256) + data[pos + 1];
		if (len > 80) {
			memcpy(fisc_retcode, "5004", 4);
			dmplog('I', "Sender Length > 80!!");
			return -1;
		}
		pos += len;
	}
	/*Postscript*/
	if (checkBitmap(in_data->bit_map, 24)) {
		len = (data[pos] * 256) + data[pos + 1];
		if (len > 80) {
			memcpy(fisc_retcode, "5004", 4);
			dmplog('I', "Postscript Length > 80!!");
			return -1;
		}
		pos += len;
	}
	/*date*/
	if (checkBitmap(in_data->bit_map, 33)) {
		memset(temp, 0x00, sizeof(temp));
		memcpy(temp, &data[pos], 6);
		itemp = atoi(temp);
		if (itemp == 0) {
			memcpy(fisc_retcode, "0101", 4);
			dmplog('I', "date of remittance type error!!");
			return -1;
		}
		pos += 6;
	}
	if (checkBitmap(in_data->bit_map, 35)) {
		pos += 4;
	}
	/*mac*/
	if (checkBitmap(in_data->bit_map, 64)) {
		pack(&mac_data, &tmac_data, 32);
		if (genFiscMac(mac_data, icv, mac) < 0) {
			memcpy(fisc_retcode, "0304", 4);
			dmplog('I', "gen mac hsm error!!");
			return -1;
		} else if (memcmp(&data[pos], mac, 4) != 0) {
			memcpy(fisc_retcode, "0302", 4);
			dmplog('I', "compare mac error!!");
			return -1;
		}
	}

	memcpy(fisc_retcode, "0001", 4);

	/*gen mac*/
	memcpy(&tmac_data[23], fisc_retcode, 4);
	pack(&mac_data, &tmac_data, 32);
	if (genFiscMac(mac_data, icv, omac) < 0) {
		memcpy(fisc_retcode, "0304", 4);
		dmplog('I', "gen mac hsm error!!");
		return -1;
	}
	shm->fisc_tx_no = tel_no;
	return 0;
}

/*--------------------------------------------------------------------------
 * Function ID:
 * Description:
 * Parameters:
 * Return:
 --------------------------------------------------------------------------*/
void fiscProcess(Msg *fiscMsg, Msg *fepMsg, Msg *replayMsg) {
	FISC_DATA in_data;
	unsigned char date[7], time[7], ritem[5], sitem[5], smac[5], stan[8];
	int idate, itime, tel_no;
	unsigned char fisc_retcode[5];

	memcpy(fepMsg, fiscMsg, sizeof(Msg));
	fepMsg->msg_type = 1;

	if (fiscMsg->len < 60) {
		dmplog('I', "fisc data length not enough, send to fep gen garbage");
		return;
	}
	memset(&in_data, 0x00, sizeof(in_data));
	memcpy(&in_data, fiscMsg->data, sizeof(in_data));
	memset(&stan, 0x00, sizeof(stan));
	memcpy(&stan, &in_data.stan, 7);
	memset(date, 0x00, sizeof(date));
	memcpy(date, in_data.datetime, 6);
	idate = atoi(date);
	memset(time, 0x00, sizeof(time));
	memcpy(time, &in_data.datetime[6], 6);
	itime = atoi(time);
	if (memcmp(&in_data.msg_code, "0200", 4) == 0) {
		if (memcmp(&in_data.proc_code, "1112", 4) == 0 || memcmp(
				&in_data.proc_code, "1122", 4) == 0 || memcmp(
				&in_data.proc_code, "1132", 4) == 0 || memcmp(
				&in_data.proc_code, "1172", 4) == 0 || memcmp(
				&in_data.proc_code, "1182", 4) == 0 || memcmp(
				&in_data.proc_code, "1192", 4) == 0) {
			dmplog('I', "start check ibrs msg!! stan[%s]", stan);
			if (idate == 0) {
				dmplog('I', "fisc head date error, send to fep gen garbage msg");
				return;
			}
			if (itime == 0) {
				dmplog('I', "fisc head date error, send to fep gen garbage msg");
				return;
			}
			memset(smac, 0x00, 4);
			/*check sync*/
			if (genFiscCheckItem(&in_data.dst_bank, ritem, &in_data.src_bank,
					sitem) < 1) {
				memcpy(&in_data.rsp_code, "0304", 4);
				genFiscRspMsg(&in_data, fepMsg, replayMsg, sitem, smac);
				dmplog('I', "gen sync hsm error!!");
				return;
			} else if (memcmp(&in_data.key_sync, ritem, 4) != 0) {
				memcpy(&in_data.rsp_code, "0301", 4);
				genFiscRspMsg(&in_data, fepMsg, replayMsg, sitem, smac);
				dmplog('I', "compare sync error!!");
				return;
			}
			memset(fisc_retcode, 0x00, sizeof(fisc_retcode));
			tel_no = 0;

			if (checkFiscMsg(&in_data, fisc_retcode, smac) < 0) {
				memcpy(&in_data.rsp_code, fisc_retcode, 4);
				genFiscRspMsg(&in_data, fepMsg, replayMsg, sitem, smac);
				return;
			}
			if (memcmp(&in_data.rsp_code, "0000", 4) == 0)
				memcpy(&in_data.rsp_code, "0001", 4);
			genFiscRspMsg(&in_data, fepMsg, replayMsg, sitem, smac);
		}
	} else if (memcmp(&in_data.msg_code, "0500", 4) == 0 && memcmp(
			&in_data.proc_code, "5102", 4) == 0) {
		dmplog('I', "get fisc settlement message, reset tx_no!!");
		shm->fisc_tx_no = 0;
	}
}
/*--------------------------------------------------------------------------
 * Function ID:
 * Description:
 * Parameters:
 * Return:
 --------------------------------------------------------------------------*/
void gwProcess(void) {
	int fisc_gw_queue, fep_con_queue, fisc_con_queue;
	Msg replayMsg, fiscMsg, fepMsg;
	int rc, recvLen;

	sprintf(service, "FISC_GW");
	shm->fisc_gw_pid = getpid();
	fisc_gw_queue = attachQueue(shm->fisc_gw_queue);
	if (fisc_gw_queue < 0) {
		dmplog('E', "attach fisc_gw_queue fail,errno=[%d]", errno);
		exit(0);
	}
	fep_con_queue = attachQueue(shm->fep_con_queue);
	if (fep_con_queue < 0) {
		dmplog('E', "attach fep_con_queue fail,errno=[%d]", errno);
		exit(0);
	}
	fisc_con_queue = attachQueue(shm->fisc_con_queue);
	if (fisc_con_queue < 0) {
		dmplog('E', "attach fisc_con_queue fail,errno=[%d]", errno);
		exit(0);
	}
	des_queue = attachQueue(0x5000 + skey);
	if (des_queue < 0) {
		dmplog('E', "attach des_queue fail,errno=[%d]", errno);
		exit(0);
	}
	fep_queue = attachQueue(0x6000 + skey);
	if (fep_queue < 0) {
		dmplog('E', "attach fep_queue fail,errno=[%d]", errno);
		exit(0);
	}

	dmplog('I', "gw start process!!");
	while (1) {
		rc = receiveQueue(fisc_gw_queue, &fiscMsg, sizeof(fiscMsg), 0, 0);
		if (rc > 0) {
			memset(&fepMsg, 0x00, sizeof(fepMsg));
			memset(&replayMsg, 0x00, sizeof(replayMsg));
			fiscProcess(&fiscMsg, &fepMsg, &replayMsg);
			if (fepMsg.msg_type > 0) {
				msgsnd(fep_con_queue, (void *) &fepMsg, sizeof(fepMsg),
						IPC_NOWAIT);
			}
			if (replayMsg.msg_type > 0) {
				msgsnd(fisc_con_queue, (void *) &replayMsg, sizeof(replayMsg),
						IPC_NOWAIT);
			}
		}
	}
}

/*--------------------------------------------------------------------------
 * Function ID:	main
 * Description:
 * Parameters:	none
 * Return:	none
 --------------------------------------------------------------------------*/
int main(int argc, char **argv) {
	int rc;
	unsigned char tmp[7], tmp1[3];

	if (argc < 2) {
		printf("USAGE:[uid]\n");
		exit(1);
	}
	sprintf(tmp, "%06d", atoi(argv[1]));

	printf( "tmp: %s\n", tmp );

	pack(tmp1, tmp, 6);

	printf( "tmp1: %d%d%d\n", tmp1[0], tmp1[1], tmp1[2] );

	// shm key = memory segment name
	skey = tmp1[0] * 65536 + tmp1[1] * 256 + tmp1[2];

	printf( "skey: %d\n", skey );


	if (fork()) {
		return (0);
	}

	rc = createSHM(0, skey);
	if (rc <= 0) {
		exit(0);
	}

	gwProcess();
}

