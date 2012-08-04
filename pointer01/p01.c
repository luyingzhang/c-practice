/*
 * p01.c
 *
 *  Created on: 2012/7/27
 *      Author: boris
 */
#include <stdio.h>
#include <string.h>

int main(){

    char a[] = {'1','2','3','4','\0'};

    printf( "a=%s\n\n", a );

//    char *c = a; // 等同於 char *c = &a[0] 或以下的二行式寫法
    char *c;
    c = &a[0];

    printf( "c =%s\n", c );
    printf( "c =%p\n", c );
    printf( "*c=%c\n", *c );//*c代表該索引的值
    printf( "*c=%p\n", &*c );//c = &*c 代表該索引的記憶體位址
    printf( "c len=%d\n\n", strlen(c) );

    c ++;

    printf( "c=%s\n", c );
    printf( "c=%p\n", c );
    printf( "*c=%c\n", *c );
    printf( "c len=%d\n\n", strlen(c) );

    c += 1;

    printf( "c=%s\n", c );
    printf( "c=%p\n", c );
    printf( "*c=%c\n", *c );
    printf( "c len=%d\n\n", strlen(c) );

    return 0;
}

