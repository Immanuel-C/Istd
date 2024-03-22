#include "dynamic_array.h"

#include "safe/string_safe.h"

typedef struct {
	size_t length;
	size_t capacity;
	size_t typeSize;
	void* buf;
	istd_allocator allocator;
} __istd_dynamic_array;

istd_dynamic_array __istd_dynamic_array_create(
	_In_	 size_t typeSize, 
	_In_	 size_t length, 
	_In_opt_ istd_allocator* allocator
) {
	istd_allocator* alloc = allocator;

	if (allocator == istd_nullptr)
		alloc = istd_get_defualt_allocator();

	__istd_dynamic_array* arr = alloc->malloc(sizeof(__istd_dynamic_array));
	arr->typeSize = typeSize;
	arr->length = length;
	arr->capacity = length;
	arr->buf = alloc->malloc(typeSize * length);
	arr->allocator = *alloc;
	return (istd_dynamic_array)arr;
}

void* __istd_dynamic_array_at(
	_In_ istd_dynamic_array arr, 
	_In_ size_t index
) {
	__istd_dynamic_array* dynamic_arr = (__istd_dynamic_array*)arr;

	// Trying to access out of bounds.
	istd_assert(dynamic_arr->length <= dynamic_arr->capacity, "_istd_dynamic_array_at() failed. Trying to access out of array bounds.");

	uint8_t* bytes = dynamic_arr->buf;
	return (void*)(bytes + (index * dynamic_arr->typeSize));
}

void istd_dynamic_array_push_back(
	_Inout_ istd_dynamic_array arr, 
	_In_ void* val 
) {
	__istd_dynamic_array* dynamic_arr = (__istd_dynamic_array*)arr;

	dynamic_arr->length++;
	if (dynamic_arr->length > dynamic_arr->capacity) {
		dynamic_arr->buf = dynamic_arr->allocator.realloc(dynamic_arr->buf, dynamic_arr->length * dynamic_arr->typeSize);
		dynamic_arr->capacity = dynamic_arr->length;
	}

	istd_assert(istd_memcpy_safe((uint8_t*)(dynamic_arr->buf) + ((dynamic_arr->length - 1) * dynamic_arr->typeSize), dynamic_arr->length * dynamic_arr->typeSize, val, dynamic_arr->typeSize) == ISTD_ENONE, "istd_dynamic_array_push_back() failed. istd_memcpy_safe() failed.");
}

void istd_dynamic_array_pop_back(
	_Inout_ istd_dynamic_array arr
) {
	__istd_dynamic_array* dynamic_arr = (__istd_dynamic_array*)arr;
	istd_assert(dynamic_arr->length != 0, "istd_dynamic_array_pop_back() failed. Trying to pop back an empty array.");
	dynamic_arr->length--;
}

size_t istd_dynamic_array_length(
	_In_ istd_dynamic_array arr
) {
	return ((__istd_dynamic_array*)(arr))->length;
}

size_t istd_dynamic_array_capacity(
	_In_ istd_dynamic_array arr
) {
	return ((__istd_dynamic_array*)(arr))->capacity;
}

void* __istd_dynamic_array_buffer(
	_In_ istd_dynamic_array arr
) {
	return ((__istd_dynamic_array*)(arr))->buf;
}

void istd_dynamic_array_shrink_to_fit(
	_Inout_ istd_dynamic_array arr
) {
	__istd_dynamic_array* dynamic_arr = (__istd_dynamic_array*)arr;
	istd_assert(dynamic_arr->length < dynamic_arr->capacity, "istd_dynamic_array_shrink_to_fit() failed. The dynamic array length must be smaller than the capacity.");
	dynamic_arr->buf = dynamic_arr->allocator.realloc(dynamic_arr->buf, dynamic_arr->length * dynamic_arr->typeSize);
	dynamic_arr->capacity = dynamic_arr->length;
}

void istd_dynamic_array_resize(
	_Inout_ istd_dynamic_array arr, 
	_In_ size_t new_length
) {
	istd_assert(new_length != 0, "istd_dynamic_array_resize() failed. Given size must be greater than 0.");

	__istd_dynamic_array* dynamic_array = (__istd_dynamic_array*)arr;

	dynamic_array->length = new_length;

	if (dynamic_array->length > dynamic_array->capacity)
		dynamic_array->buf = dynamic_array->allocator.realloc(dynamic_array->buf, dynamic_array->typeSize * dynamic_array->length);
}

void istd_dynamic_array_free(
	_Pre_valid_ _Post_valid_ istd_dynamic_array arr
) {
	__istd_dynamic_array* dynamic_array = (__istd_dynamic_array*)arr;

	dynamic_array->allocator.free(dynamic_array->buf);
	dynamic_array->allocator.free(dynamic_array);
	arr = istd_nullptr;
}