#include "../CuTest/CuTest.h"
#include <stdio.h>

CuSuite* testSuite();
//void TestStrToUpper(CuTest);

void RunAllTests(void) {
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

	CuSuiteAddSuite(suite, testSuite());

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}

void testM3000adt(CuTest *tc) {
	char* input = strdup("hello world");
	char* actual = StrToUpper(input);
	char* expected = "HELLO WORLD";
	CuAssertStrEquals(tc, expected, actual);
}

CuSuite* testSuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, testM3000adt);
	return suite;
}

int main(void) {
	RunAllTests();
}
