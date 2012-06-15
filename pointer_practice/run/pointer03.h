/*
 * pointer03.h
 * http://pydoing.blogspot.com/2010/07/c-malloc.html
 *  Created on: 2011/8/17
 *      Author: boris
 */

#include <stdio.h>
#include <stdlib.h>

void run03(void) {
	int *a;
	a = (int *) malloc(sizeof(int));
	// 向作業系統要求sizeof(int)個byte的空間來使用.
	if (a == NULL) {
		printf("建立記憶體空間失敗\n");
	} else {
		printf("建立記憶體空間成功\n");
	}
	*a = 12;
	// 把數值3放到剛剛得到的記憶體空間中
	printf("放到動態配置空間的值: %d\n", *a);
	free(a);
}
