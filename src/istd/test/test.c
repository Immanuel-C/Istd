#include "test.h"

#define ISTD_TEST_DIVIDER "---------------------"

#include <stdio.h>

void istd_test(
	istd_pfn_test test_fun,
	const char* test_name
) {

	printf("%s Testing: %s %s\n", ISTD_TEST_DIVIDER, test_name, ISTD_TEST_DIVIDER);

	istd_test_msg msg = test_fun();

	if (msg.passed == true) {
		printf("%s Test Ended Successfully %s\n", ISTD_TEST_DIVIDER, ISTD_TEST_DIVIDER);
		return;
	}

	fprintf(stderr, "%s Test Failed: %s %s\n", ISTD_TEST_DIVIDER, msg.err_msg, ISTD_TEST_DIVIDER);
	ISTD_IGNORE_RETURN(getchar());
}
