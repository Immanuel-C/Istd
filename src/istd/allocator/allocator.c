#include "allocator.h"

#include <stdlib.h>

istd_allocator istd_get_defualt_allocator(void) {
	return (istd_allocator) {
		.malloc = malloc,
		.free = free,
		.realloc = realloc,
		.calloc = calloc
	};
}

istd_allocator istd_check_allocator(istd_allocator* allocator) {
	if (allocator == NULL) 
		return istd_get_defualt_allocator();

	return *allocator;
}

const char* istd_result_to_string(istd_result result) {
	switch (result) {
	case ISTD_RESULT_SUCCESS:
		return "ISTD_RESULT_SUCCESS";
	case ISTD_RESULT_ALLOCATION_FAILED:
		return "ISTD_RESULT_ALLOCATION_FAILED";
	case ISTD_RESULT_NOT_FOUND:
		return "ISTD_RESULT_NOT_FOUND";
	case ISTD_RESULT_PARAMETER_NULL:
		return "ISTD_RESULT_PARAMETER_NULL";
	case ISTD_RESULT_PARAMETER_INVALID:
		return "ISTD_RESULT_PARAMETER_INVALID";
	case ISTD_RESULT_ACCESS_OUT_OF_BOUNDS:
		return "ISTD_RESULT_ACCESS_OUT_OF_BOUNDS";
	case ISTD_RESULT_FILE_COULD_NOT_OPEN:
		return "ISTD_RESULT_FILE_COULD_NOT_OPEN";
	case ISTD_RESULT_FILE_TOO_BIG:
		return "ISTD_RESULT_FILE_TOO_BIG";
	case ISTD_RESULT_FORMAT_NOT_SUPPORTED:
		return "ISTD_RESULT_FORMAT_NOT_SUPPORTED";
	case ISTD_RESULT_MEM_OP_FAILED:
		return "ISTD_RESULT_MEM_OP_FAILED";
	default:
		return "Unknown result";
	}
}
