/*
 * demo.c
 * 立德給的 sample
 *  Created on: 2012/4/13
 *      Author: boris
 */
#define UPPER(x) (((x) >= 'a') && ((x) <= 'z')) ? ((x) -= 0x20) : (x);

void pack(unsigned char *str_out, unsigned char *str_in, int len) {
	register int index;
	unsigned char data;

	printf("str_in: %d\n", str_in);

	for (index = 0; index < (len >> 1); index++) {

		printf("str_in: %d\n", str_in);

		data = UPPER(*str_in);

		printf("index: %d\n", index);
		printf("data: %c\n", data);

		str_in++;

		((data >= '0') && (data <= '9')) ?
				(data -= '0') : (data = data - 'A' + 10);
		*str_out = data << 4;

		data = UPPER(*str_in);
		str_in++;

		((data >= '0') && (data <= '9')) ?
				(data -= '0') : (data = data - 'A' + 10);
		*str_out |= data;
		str_out++;
		printf("str_out size: %d\n", sizeof(str_out));

	}
}

void unpack(unsigned char *str_out, unsigned char *str_in, int len) {
	register int index;
	unsigned char HexTable[16] = "0123456789ABCDEF";

	for (index = 0; index < len; index++) {
		*str_out = HexTable[(str_in[index] & 0xF0) >> 4];
		str_out++;
		*str_out = HexTable[str_in[index] & 0x0F];
		str_out++;
	}
}

main() {
	unsigned char* out = {'a','b'};
	unsigned char* in = {'x','y'};
	printf("pack..sizeof(in):%d\n", sizeof(in));
	pack(&out, &in, sizeof(in));
}

