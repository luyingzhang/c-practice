#include "CuTest/CuTest.h"
#include <stdio.h>

//不用改
CuSuite* testSuite();

int binsearch(char *str[], int max, char *value);

//不用改
void RunAllTests(void) {
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

	CuSuiteAddSuite(suite, testSuite());

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}

//正確
void test_padr0_01(CuTest *tc) {
	char* actual = padr0( 7, "1" );
	char* expected = "1000000";
	CuAssertStrEquals(tc, expected, actual);
}

//在此修改 Test Case 的數量和內容
CuSuite* testSuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, test_padr0_01);
	return suite;
}

//不用改
int main(void) {
	RunAllTests();
}
