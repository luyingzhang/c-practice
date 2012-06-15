#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct fisc_data_struct FISC_DATA;
struct fisc_data_struct {
	unsigned char system_head[3];
	unsigned char msg_code[4];
	unsigned char proc_code[4];
	unsigned char stan[7];
	unsigned char src_bank[7];
	unsigned char dst_bank[7];
	unsigned char datetime[12];
	unsigned char rsp_code[4];
	unsigned char key_sync[4];
	unsigned char bit_map[8];
	unsigned char data[512];
};
