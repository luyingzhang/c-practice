#include <stdio.h>
#include <memory.h>

#define  ICONHLEN 100
#define  RSMLEN 20
#define  CSMLEN 12

char RSM[] = "*REQSTS*";

/*--------------------------------------------------------------------------
 * Function ID:
 * Description:
 * Parameters:
 * Return:
 --------------------------------------------------------------------------*/
void addFISCH(char *inputData, int DataLen, char mode, char role, int *first,
		char *client_id, char *check_code) {
	char NewData[4096];

	NewData[0] = 0x00;
	NewData[1] = 0x00;
	NewData[2] = (DataLen + ICONHLEN) / 256;
	NewData[3] = (DataLen + ICONHLEN) % 256;
	NewData[4] = 0x00;
	NewData[5] = 0x58;
	NewData[6] = 0x00;
	NewData[7] = 0x00;
	memcpy(NewData + 8, "FISCICON", 8);
	memset(NewData + 16, 0x00, 4);
	NewData[20] = 0x02;
	if (role == 'R') {
		NewData[21] = 0x64;
	} else {
		NewData[21] = 0xE9;
	}
	memcpy(NewData + 24, client_id, 8);
	memcpy(NewData + 76, check_code, 8);
	NewData[22] = 0x10;
	NewData[23] = 0x00;
	NewData[32] = 0x00;
	NewData[33] = 0x40;
	if (*first == 1) {
		NewData[34] = 0x81;
		*first = 0;
	} else {
		NewData[34] = 0x01;
	}
	NewData[35] = mode;
	memcpy(NewData + 36, "        ", 8);
	memcpy(NewData + 44, "        ", 8);
	memcpy(NewData + 52, "        ", 8);
	memcpy(NewData + 60, "        ", 8);
	memcpy(NewData + 68, "        ", 8);
	memcpy(NewData + 84, "        ", 8);
	NewData[92] = (DataLen + 4) / 256;
	NewData[93] = (DataLen + 4) % 256;
	memset(NewData + 94, 0x00, 2);
	memcpy(NewData + 96, inputData, DataLen);
	NewData[DataLen + 96] = 0x00;
	NewData[DataLen + 97] = 0x04;
	NewData[DataLen + 98] = 0x00;
	NewData[DataLen + 99] = 0x00;
	memcpy(inputData, NewData, DataLen + ICONHLEN);
}

/*--------------------------------------------------------------------------
 * Function ID:
 * Description:
 * Parameters:
 * Return:
 --------------------------------------------------------------------------*/
int checkFiscRSM(char *data, int recvLen) {
	int rc;
	char fiscMsg[4096];
	memset(fiscMsg, 0x00, sizeof(fiscMsg));
	memcpy(fiscMsg, data, recvLen);

	if (memcmp(fiscMsg + 4, RSM, 8) == 0) {
		dmplog('I', "get fisc rsm [0x%02X 0x%02X]!!", fiscMsg[15], fiscMsg[19]);
		if ((fiscMsg[15] == 0x08) && (fiscMsg[19] == 0x3B)) {
			dmplog('I', "get cancal timer!!");
			return -1;
		}
		if ((fiscMsg[15] == 0x08) && (fiscMsg[19] == 0x38)) {
			dmplog('I', "get cancal client id!!");
			return -2;
		}
		if (fiscMsg[15] == 0x2C) {
			if (fiscMsg[19] == 0x64) {
				dmplog('I', "get subsystem stop!!");
				return -1;
			}
		}
		if (fiscMsg[15] == 0x04) {
			if (fiscMsg[19] == 0x4A || fiscMsg[19] == 0x4B || fiscMsg[19]
					== 0x4C) {
				dmplog('I', "get subsystem stop!!");
				return -2;
			}
		}
	}
	return 1;
}
/*--------------------------------------------------------------------------
 * Function ID:
 * Description:
 * Parameters:
 * Return:	none
 --------------------------------------------------------------------------*/
void setonBitmap(char *bitmap, int index) {
	unsigned char tmp[9];
	int x, y;
	memcpy(&tmp, bitmap, 8);
	x = (index - 1) / 8;
	y = index % 8;
	if (y > 0)
		tmp[x] |= (0x01 << (8 - y));
	else
		tmp[x] |= 0x01;
	memcpy(bitmap, &tmp, 8);
}

/*--------------------------------------------------------------------------
 * Function ID:
 * Description:
 * Parameters:
 * Return:	none
 --------------------------------------------------------------------------*/
int checkBitmap(char *bitmap, int index) {
	unsigned char tmp[8];
	int x, y;
	memcpy(tmp, bitmap, 8);
	x = (index - 1) / 8;
	y = (index - 1) % 8;
	if (((bitmap[x] << y) & 0x80))
		return 1;
	else
		return 0;
}
