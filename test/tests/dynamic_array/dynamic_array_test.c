#include "dynamic_array_test.h"

#include "dynamic_array/dynamic_array.h"

#include <stdio.h>

istd_test_msg istd_stdcall test_dynamic_array(void) {
	istd_test_msg msg = { 0 };

	istd_dynamic_array dynamic_array = istd_dynamic_array_create(int, 2, istd_nullptr);

	if (dynamic_array == istd_nullhnd) {
		msg.passed = false;
		msg.err_msg = "Failed to allocate a new dynamic array";
		return msg;
	}

	*istd_dynamic_array_at(int, dynamic_array, 0) = 1;
	*istd_dynamic_array_at(int, dynamic_array, 1) = 5;

	int val = 10;
	istd_dynamic_array_push_back(dynamic_array, &val);

	printf("Values: %i, %i, %i\n", *istd_dynamic_array_at(int, dynamic_array, 0), *istd_dynamic_array_at(int, dynamic_array, 1), *istd_dynamic_array_at(int, dynamic_array, 2));

	istd_dynamic_array_pop_back(dynamic_array);

	printf("Length: %zu, Capacity: %zu\n", istd_dynamic_array_length(dynamic_array), istd_dynamic_array_capacity(dynamic_array));

	istd_dynamic_array_shrink_to_fit(dynamic_array);

	val = 20;
	istd_dynamic_array_push_back(dynamic_array, &val);

	printf("Length: %zu, Capacity: %zu\n", istd_dynamic_array_length(dynamic_array), istd_dynamic_array_capacity(dynamic_array));

	printf("Values: %i, %i, %i\n", *istd_dynamic_array_at(int, dynamic_array, 0), *istd_dynamic_array_at(int, dynamic_array, 1), *istd_dynamic_array_at(int, dynamic_array, 2));

	istd_dynamic_array_free(dynamic_array);

	msg.passed = true;
	return msg;
}