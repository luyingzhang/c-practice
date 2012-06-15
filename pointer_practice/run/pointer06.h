/*
 * pointer06.h
 *  Created on: 2012/4/6
 *      Author: boris
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

void run06(void) {
	int my_array[] = { 1, 23, 17, 4, -5, 100 };
	int *ptr;
	int i;
	ptr = &my_array[0]; /* point our pointer to the first element of the array */
	printf("\n");
	for (i = 0; i < 6; i++) {
		printf("my_array[%d] = %d ", i, my_array[i]); /*<-- A */
//		printf("ptr + %d = %d\n", i, *(ptr + i));     /*<-- B */
		printf("ptr + %d = %d\n",i, *ptr++);          /*<-- C *///和上一行的結果相同
	}
}

