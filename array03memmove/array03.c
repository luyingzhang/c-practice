/*
 * array03.c
 *
 *  Created on: 2012/7/28
 *      Author: boris
 */

#include <string.h>
#include <stdio.h>

int main()
{
    char s[] = "zengxiaolong";

    memmove(s, s+4, strlen(s)-4);
    s[strlen(s)-4] = '\0';
    printf("*s = %s\n", s);

    return 0;
}
