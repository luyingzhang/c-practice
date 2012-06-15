#include <stdio.h>
#define UPPER(x) (((x) >= 'a') && ((x) <= 'z')) ? ((x) -= 0x20) : (x);

/*--------------------------------------------------------------------------
 * Function ID:
 * Description:
 * Parameters:
 * Return:	none
 --------------------------------------------------------------------------*/
void pack(unsigned char *str_out, unsigned char *str_in, int len) {
	register int index;
	unsigned char data;

	for (index = 0; index < (len >> 1); index++) {
		data = UPPER(*str_in);
		str_in++;

		((data >= '0') && (data <= '9')) ? (data -= '0') : (data = data - 'A'
				+ 10);
		*str_out = data << 4;

		data = UPPER(*str_in);
		str_in++;

		((data >= '0') && (data <= '9')) ? (data -= '0') : (data = data - 'A'
				+ 10);
		*str_out |= data;
		str_out++;
	}
}
