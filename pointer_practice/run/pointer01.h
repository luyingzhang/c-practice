/*
 * pointer01.h
 *
 *  Created on: 2011/8/17
 *      Author: boris
 */
#include <stdio.h>
#include <stdlib.h>

void run01 (void)
{
    int a=2;
    int *b=&a;
    // 這跟int *b; b=&a;的效果一樣.
    *b=3;
    // b  的是&a, a的記憶體所在位置.
    // *b 的意思是, 要設定數值時, 到b所記的那個記憶體位址中去設定數值

    printf("b的值會影響a: %d\n",a);
    // 所以可以發現a的數值被改變了.


}

