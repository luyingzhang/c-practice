#include <stdio.h>

void str_byte_xor(unsigned char *out, unsigned char *in1, unsigned char *in2) {
	int i;

	for (i = 0; i < 8; i++) {
		out[i] = in1[i] ^ in2[i];
	}
}
