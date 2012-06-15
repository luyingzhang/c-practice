#include  <stdio.h>
#include  <sys/termios.h>
#include  <sys/ioctl.h>
#include  <sys/types.h>
#include  <stdlib.h>
#include  <memory.h>

static struct termio TermATTR;
#ifndef CTRL
#define  CTRL(c)	(c & 037)
#endif

static void PwdECHOon(void) {
	(void) ioctl(0, TCSETAF, &TermATTR);
}

static void PwdECHOoff(void) {
	struct termio termbuf;

	(void) ioctl(fileno(stdin), TCGETA, &TermATTR);
	memcpy((char*) &termbuf, (char*) &TermATTR, sizeof(TermATTR));
	termbuf.c_iflag &= ~(INLCR | ICRNL | IUCLC | ISTRIP | IXON | BRKINT);
	termbuf.c_oflag &= ~OPOST;
	termbuf.c_lflag &= ~(ICANON | ISIG | ECHO);
	termbuf.c_cflag |= (CLOCAL | CS8);
	termbuf.c_cc[VMIN] = 1;
	termbuf.c_cc[VTIME] = 128;
	(void) ioctl(fileno(stdin), TCSETAF, &termbuf);
}

int password(char* pwd, int n) {
	int i = 0, c, n1 = n;

	if (n < 0)
		n = -n;
	PwdECHOoff();
	memset(pwd, 0, n);
	while (i < n) {
		if ((c = getchar()) == '\r')
			break;
		if (c == 0x7f) { /* backspace */
			if (i) {
				printf("\b \b");
				fflush(stdout);
				i--;
				*(pwd + i) = '\0';
			}
			continue;
		}
		if (n1 < 0)
			putchar(c);
		else
			putchar('*');
		fflush(stdout);
		*(pwd + i++) = c;
	}
	PwdECHOon();
	printf("\n");
	return (i);
}
