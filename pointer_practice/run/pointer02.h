/*
 * pointer02.h
 *
 *  Created on: 2011/8/17
 *      Author: boris
 */

#include <stdio.h>
#include <stdlib.h>

void run02 (void)
{
	int a;
	int *b=&a;
	// 這跟int *b; b=&a;的效果一樣.
	a=3;

	printf("a的值會影響b: %d\n",*b);
	// b記錄的是&a, a的記憶體所在位置.
	// *b的意思是, 要取出數值時, 到b所記錄的那個記憶體位址中去取數值


}
