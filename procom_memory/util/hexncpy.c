#include <stdio.h>

char *PackHEX(unsigned char *str, unsigned char *hex, int sz) {
	int c, i = 0, j = 0;

	while (sz-- > 0) {
		c = toupper(*(hex + j++));
		if ((c >= 'A') && (c <= 'F'))
			*(str + i) = (c - 'A' + 10) << 4;
		else
			*(str + i) = (c & 0x0f) << 4;

		c = toupper(*(hex + j++));
		if ((c >= 'A') && (c <= 'F'))
			*(str + i++) += c - 'A' + 10;
		else
			*(str + i++) += (c & 0x0f);
	}
	return ((char *) str);
}

char *hexncpy(char *str, char *hex, int sz) {
	return (PackHEX((unsigned char*) str, (unsigned char*) hex, sz));
}
