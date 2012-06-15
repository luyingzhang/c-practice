#include  <stdio.h>
#include  <stdlib.h>
#include  <fcntl.h>
#include  <string.h>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <time.h>
#include  <stdarg.h>

int NUMBER(unsigned char* cmd, int sz) {
	while (sz-- > 0) {
		if (*cmd < '0' || *cmd > '9')
			return (0);
		cmd++;
	}
	return (1);
}

int HEXDECIMAL(unsigned char* cmd, int sz) {
	while (sz-- > 0) {
		if (*cmd >= '0' && *cmd <= '9') {
			cmd++;
			continue;
		}
		*cmd = toupper(*cmd);
		if (*cmd < 'A' || *cmd > 'F')
			return (0);
		cmd++;
	}
	return (1);
}

int hexdec(unsigned char* cmds, ...) {
	int ofs, sz, rc = 1;
	va_list arg_marker;

	va_start(arg_marker, cmds);
	for ( ofs=va_arg(arg_marker,int);
			ofs >= 0;
			ofs=va_arg(arg_marker,int) ) {
				if ( (sz = va_arg(arg_marker, int)) < 0 ) { /* Numeric digit only */
					if ( (rc = NUMBER(cmds+ofs, -sz)) == 0 ) break;
				}
				else
				if ( (rc = HEXDECIMAL(cmds+ofs, sz)) == 0 ) break;
			}
			va_end(arg_marker);
			return (rc);
		}
