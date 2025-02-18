#include "dynamic_array.h"

#include <string.h>

typedef struct __istd_dynamic_array_t {
	size_t length;
	size_t capacity;
	size_t typeSize;
	void* buf;
	istd_allocator allocator;
} __istd_dynamic_array;

istd_dynamic_array __istd_dynamic_array_create(
	size_t typeSize, 
	size_t length, 
	istd_allocator* allocator
) {
	istd_allocator alloc = istd_check_allocator(allocator);

	__istd_dynamic_array* arr = alloc.malloc(sizeof(__istd_dynamic_array));
	arr->typeSize = typeSize;
	arr->length = length;
	arr->capacity = length;
	arr->buf = alloc.malloc(typeSize * length);
	arr->allocator = alloc;
	return (istd_dynamic_array)arr;
}

void* __istd_dynamic_array_at(
	istd_dynamic_array arr, 
	size_t index
) {
	__istd_dynamic_array* dynamic_arr = (__istd_dynamic_array*)arr;

	// Trying to access out of bounds.
	ISTD_ASSERT(index < dynamic_arr->length, "__istd_dynamic_array_at() failed. Trying to access out of array bounds.");

	uint8_t* bytes = dynamic_arr->buf;
	return (void*)(bytes + (index * dynamic_arr->typeSize));
}

void istd_dynamic_array_push_back(
	istd_dynamic_array arr, 
	void* val 
) {
	__istd_dynamic_array* dynamic_arr = (__istd_dynamic_array*)arr;

	dynamic_arr->length++;
	if (dynamic_arr->length > dynamic_arr->capacity) {
		dynamic_arr->buf = dynamic_arr->allocator.realloc(dynamic_arr->buf, dynamic_arr->length * dynamic_arr->typeSize);
		dynamic_arr->capacity = dynamic_arr->length;
	}

	memcpy((uint8_t*)dynamic_arr->buf + (dynamic_arr->length - 1) * dynamic_arr->typeSize, val, dynamic_arr->typeSize);
}

void istd_dynamic_array_pop_back(
	istd_dynamic_array arr
) {
	__istd_dynamic_array* dynamic_arr = (__istd_dynamic_array*)arr;
	ISTD_ASSERT(dynamic_arr->length != 0, "istd_dynamic_array_pop_back() failed. Trying to pop back an empty array.");
	dynamic_arr->length--;
}

size_t istd_dynamic_array_length(
	istd_dynamic_array arr
) {
	return ((__istd_dynamic_array*)(arr))->length;
}

size_t istd_dynamic_array_capacity(
	istd_dynamic_array arr
) {
	return ((__istd_dynamic_array*)(arr))->capacity;
}

void* __istd_dynamic_array_buffer(
	istd_dynamic_array arr
) {
	return ((__istd_dynamic_array*)(arr))->buf;
}

void istd_dynamic_array_shrink_to_fit(
	istd_dynamic_array arr
) {
	__istd_dynamic_array* dynamic_arr = (__istd_dynamic_array*)arr;
	ISTD_ASSERT(dynamic_arr->length < dynamic_arr->capacity, "istd_dynamic_array_shrink_to_fit() failed. The dynamic array length must be smaller than the capacity.");
	dynamic_arr->buf = dynamic_arr->allocator.realloc(dynamic_arr->buf, dynamic_arr->length * dynamic_arr->typeSize);
	dynamic_arr->capacity = dynamic_arr->length;
}

void istd_dynamic_array_resize(
	istd_dynamic_array arr, 
	size_t new_length
) {
	ISTD_ASSERT(new_length != 0, "istd_dynamic_array_resize() failed. Given size must be greater than 0.");

	__istd_dynamic_array* dynamic_array = (__istd_dynamic_array*)arr;

	dynamic_array->length = new_length;

	if (dynamic_array->length > dynamic_array->capacity)
		dynamic_array->buf = dynamic_array->allocator.realloc(dynamic_array->buf, dynamic_array->typeSize * dynamic_array->length);
}

void istd_dynamic_array_free(
	istd_dynamic_array arr
) {
	__istd_dynamic_array* dynamic_array = (__istd_dynamic_array*)arr;

	dynamic_array->allocator.free(dynamic_array->buf);
	dynamic_array->allocator.free(dynamic_array);
	arr = istd_nullhnd;
}
