#if !defined(ISTD_TEST_H)
#define ISTD_TEST_H

#include "core.h"

ISTD_EXTERN_C

typedef struct {
	bool passed;
	const char* err_msg;
} istd_test_msg;

typedef istd_test_msg (istd_stdcall* istd_pfn_test)(void);

istd_api void istd_stdcall istd_test(
	istd_pfn_test test_fun, 
	const char* test_name
);

ISTD_END_EXTERN_C

#endif
