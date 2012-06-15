/*
 * pointer05.h
 *  Created on: 2012/4/6
 *      Author: boris
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

void run05(void) {
	char c[4][5], ch[20], *cp;
	int i, j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 5; j++)
			c[i][j] = 65 + i * 5 + j;
	for (i = 0; i < 20; i++)
		ch[i] = 65 + i;
	cp = c;

	for (i = 0; i < 20; i++)
		putchar(*(cp + i));
	putchar('\n');
	cp = ch;
	for (i = 0; i < 20; i++)
		putchar(*(cp + i));
	putchar('\n');
}

