/*
 * ac01.c
 *
 *  Created on: 2012/7/28
 *      Author: boris
 */

#include <string.h>
#include <stdio.h>

int main()
{
    char s1[] = "xiaolong";
    char s2[] = "NC001234";
    char s3[16];

    memmove(s3, s1, 9);
    //memmove(s3, s2, 8);
    //s3[strlen(s3)] = '\0';
    printf("*s3 = %s\n", *s3);

    return 0;
}
