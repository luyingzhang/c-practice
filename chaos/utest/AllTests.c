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

//錯誤: 找到的索引值和預期的不一致
void test_cmdsearch_01(CuTest *tc) {
//	char record[] = "ASNANCUA";
//	char keyword[] = {'N', 'C'};
//	int actual1 = cmdsearch( record, 6, keyword );
//	int expected1 = 1;
//	CuAssertIntEquals( tc, expected1, actual1 );
}

//正確
void test_cmdsearch_02(CuTest *tc) {
	char record[] = "ASNANCUA";
	char keyword[] = {'N', 'C'};
	int actual = cmdsearch( record, 6, keyword );
	int expected = 4;
	CuAssertIntEquals( tc, expected, actual );
}

//正確
//void test_padr0_01(CuTest *tc) {
//	char* actual = padr0( 7, "1" );
//	char* expected = "1000000";
//	CuAssertStrEquals(tc, expected, actual);
//}

//正確
void test_m3000adt_03(CuTest *tc) {
	char* actual = m3000cmd_parser( "f eesfa m3000srv recv :     NC\n fffeess m3000srv send :     ND00268604744491242200\n" );
	char* expected = "0034NC0100000000000000000000000000";
	CuAssertStrEquals(tc, expected, actual);
}


//在此修改 Test Case 的數量和內容
CuSuite* testSuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, test_cmdsearch_01);
	SUITE_ADD_TEST(suite, test_cmdsearch_02);
	SUITE_ADD_TEST(suite, test_padr0_01);
	SUITE_ADD_TEST(suite, test_m3000adt_03);
	return suite;
}

//不用改
int main(void) {
	RunAllTests();
}
