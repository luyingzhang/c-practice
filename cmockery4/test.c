/*
 * test.c
 * 模擬（mock）開檔
 *  Created on: 2012/6/23
 *      Author: http://www.51testing.com/html/09/n-170909.html
 */
#include <stdarg.h>

#include <stddef.h>

#include <setjmp.h>

#include <stdio.h>

#include "google/cmockery.h"

#include "biz.h"

FILE *fopen(const char *filename, const char *mode) {
	return (FILE*)mock();
}

void test_biz_operation_return_succ(void **state) {
	will_return(fopen, 0x1234);
	assert_true(biz_operation("foo.txt") == 0);
}

void test_biz_operation_return_fail(void **state) {
	will_return(fopen, NULL);
	assert_true(biz_operation("foo.txt") == 1);
}

int main() {
	const UnitTest tests[] = { unit_test(test_biz_operation_return_succ),
			unit_test(test_biz_operation_return_fail), };
	return run_tests(tests);
}

