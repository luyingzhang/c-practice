/*
 * biz.c
 *
 *  Created on: 2012/6/23
 *      Author: http://www.51testing.com/html/09/n-170909.html
 */

#include "biz.h"

int biz_operation(char *fname) {

	FILE *fp = NULL;
	fp = fopen(fname, "r");
	if (fp == NULL) {
		printf("fail to open fle!\n");
		return 1;
	} else {
		printf("succeed to open file!\n");
		return 0;
	}
}

