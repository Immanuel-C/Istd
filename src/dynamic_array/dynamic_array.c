#include "dynamic_array.h"

#include "safe/string_safe.h"

typedef struct _istd_dynamic_array_t {
	size_t length;
	size_t capacity;
	size_t typeSize;
	void* buf;
} _istd_dynamic_array;

istd_dynamic_array* _istd_dynamic_array_create(size_t typeSize, size_t length, istd_allocator* allocator) {
	istd_assert(allocator != istd_nullptr, "_istd_dynamic_array_create() failed. Given allocator is null.");
	_istd_dynamic_array* arr = allocator->malloc(sizeof(_istd_dynamic_array));
	arr->typeSize = typeSize;
	arr->length = length;
	arr->capacity = length;
	arr->buf = allocator->malloc(typeSize * length);
	return (istd_dynamic_array*)arr;
}

void* _istd_dynamic_array_at(istd_dynamic_array* arr, size_t index) {
	istd_assert(arr != istd_nullptr, "_istd_dynamic_array_at() failed. Given array is null.");
	_istd_dynamic_array* dynamic_arr = (_istd_dynamic_array*)arr;

	istd_assert(index < dynamic_arr->length, "_istd_dynamic_array_at failed(). Given index is larger than length.");

	uint8_t* buf = dynamic_arr->buf;
	size_t typeSize = dynamic_arr->typeSize;

	return (void*)(buf + (index * typeSize));
}

void istd_dynamic_array_push_back(istd_dynamic_array* arr, void* val, istd_allocator* allocator) {
	istd_assert(arr != istd_nullptr, "istd_dynamic_array_push_back() failed. Given array is null.");

	_istd_dynamic_array* dynamic_arr = (_istd_dynamic_array*)arr;

	dynamic_arr->length++;
	if (dynamic_arr->length > dynamic_arr->capacity) {
		dynamic_arr->buf = allocator->realloc(dynamic_arr->buf, dynamic_arr->length * dynamic_arr->typeSize);
		dynamic_arr->capacity = dynamic_arr->length;
	}

	istd_assert(istd_memcpy_safe((uint8_t*)(dynamic_arr->buf) + ((dynamic_arr->length - 1) * dynamic_arr->typeSize), dynamic_arr->length * dynamic_arr->typeSize, val, dynamic_arr->typeSize) == ISTD_ENONE, "istd_memcpy_safe() failed.");
}

void istd_dynamic_array_pop_back(istd_dynamic_array* arr) {
	istd_assert(arr != istd_nullptr, "istd_dynamic_array_pop_back() failed. Given array is null.");
	_istd_dynamic_array* dynamic_arr = (_istd_dynamic_array*)arr;
	istd_assert(dynamic_arr->length != 0, "istd_dynamic_array_pop_back() failed. Trying to pop back an empty array.");
	dynamic_arr->length--;
}

size_t istd_dynamic_array_length(istd_dynamic_array* arr) {
	istd_assert(arr != istd_nullptr, "istd_dynamic_array_length() failed. Given array is null.");
	return ((_istd_dynamic_array*)(arr))->length;
}

size_t istd_dynamic_array_capacity(istd_dynamic_array* arr) {
	istd_assert(arr != istd_nullptr, "istd_dynamic_array_capacity() failed. Given array is null.");
	return ((_istd_dynamic_array*)(arr))->capacity;
}

void* _istd_dynamic_array_buffer(istd_dynamic_array* arr) {
	istd_assert(arr != istd_nullptr, "istd_dynamic_array_capacity() failed. Given array is null.");
	return ((_istd_dynamic_array*)(arr))->buf;
}

void istd_dynamic_array_shrink_to_fit(istd_dynamic_array* arr, istd_allocator* allocator) {
	istd_assert(arr != istd_nullptr, "istd_dynamic_array_shrink_to_fit() failed. Given array is null.");
	_istd_dynamic_array* dynamic_arr = (_istd_dynamic_array*)arr;
	istd_assert(dynamic_arr->length < dynamic_arr->capacity, "istd_dynamic_array_shrink_to_fit() failed. The dynamic array length must be smaller than the capacity.");
	dynamic_arr->buf = allocator->realloc(dynamic_arr->buf, dynamic_arr->length * dynamic_arr->typeSize);
	dynamic_arr->capacity = dynamic_arr->length;
}

void istd_dynamic_array_resize(istd_dynamic_array* arr, size_t new_length , istd_allocator* allocator) {
	istd_assert(arr != istd_nullptr, "istd_dynamic_array_resize() failed. Given array is null.");
	istd_assert(new_length != 0, "istd_dynamic_array_resize() failed. Given size must be greater than 0.");
	istd_assert(allocator != istd_nullptr, "istd_dynamic_array_resize() failed. Given allocator must not be null.");

	_istd_dynamic_array* dynamic_array = (_istd_dynamic_array*)arr;

	dynamic_array->length = new_length;

	if (dynamic_array->length > dynamic_array->capacity)
		dynamic_array->buf = allocator->realloc(dynamic_array->buf, dynamic_array->typeSize * dynamic_array->length);
}

void istd_dynamic_array_free(istd_dynamic_array* arr, istd_allocator* allocator) {
	istd_assert(arr != istd_nullptr, "istd_dynamic_array_free() failed. Given array is null.");
	istd_assert(allocator != istd_nullptr, "istd_dynamic_array_free() failed. Given allocator is null.");
	allocator->free(((_istd_dynamic_array*)(arr))->buf);
	allocator->free(arr);
	arr = istd_nullptr;
}