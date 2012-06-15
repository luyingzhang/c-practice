/*
 * pointer04.h
 *  Created on: 2012/4/6
 *      Author: boris
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

void run04(void) {
	char a[6];
	int addr = (int) &a;
	char *s = a;
    printf( "\ns initial address: %X", s );
	char c;

    for (c = 'a'; c <= 'e'; c++){
        *s = c;
        printf( "\ns address: %X, s: %c, c: %c", s, *s, c );
        s++;
    }
    *s = '\0';
    s = (int*)addr;
    printf( "\naddr : %X, %s", addr, s );
    for (c = 'a'; c <= 'e'; c++){
        printf( "\ns address: %X, s: %c", s, *s );
        s++;
    }
    printf( "\naddr : %X, %s", addr, (int*)addr );
    putchar('\n');
}
