#include "dynamic_array/dynamic_array.h"

#include <stdio.h>

typedef struct test_t {
	uint32_t x, y, z;
} test;

int main() {
	istd_allocator defualt_allocator = istd_get_defualt_allocator();

	istd_dynamic_array* dynamic_array = istd_dynamic_array_create(int, 2, &defualt_allocator);

	*istd_dynamic_array_at(int, dynamic_array, 0) = 1;
	*istd_dynamic_array_at(int, dynamic_array, 1) = 5;

	int val = 10;
	istd_dynamic_array_push_back(dynamic_array, &val, &defualt_allocator);

	printf("Values: %i, %i, %i\n", *istd_dynamic_array_at(int, dynamic_array, 0), *istd_dynamic_array_at(int, dynamic_array, 1), *istd_dynamic_array_at(int, dynamic_array, 2));

	istd_dynamic_array_pop_back(dynamic_array);

	printf("Length: %zu, Capacity: %zu\n", istd_dynamic_array_length(dynamic_array), istd_dynamic_array_capacity(dynamic_array));

	// istd_dynamic_array_shrink_to_fit(dynamic_array, &defualt_allocator);

	val = 20;
	istd_dynamic_array_push_back(dynamic_array, &val, &defualt_allocator);

	printf("Length: %zu, Capacity: %zu\n", istd_dynamic_array_length(dynamic_array), istd_dynamic_array_capacity(dynamic_array));

	printf("Values: %i, %i, %i\n", *istd_dynamic_array_at(int, dynamic_array, 0), *istd_dynamic_array_at(int, dynamic_array, 1), *istd_dynamic_array_at(int, dynamic_array, 2));

	istd_dynamic_array_free(dynamic_array, &defualt_allocator);
}