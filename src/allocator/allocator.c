#include "allocator.h"

#include <stdlib.h>

void* istd_malloc_check(_In_ size_t size) {
	void* buf = malloc(size);
	istd_assert(buf != istd_nullptr, "istd_malloc_check() failed. Allocated buffer is null!");
	return buf;
}

void* istd_calloc_check(_In_ size_t count, _In_ size_t size) {
	void* buf = calloc(count, size);
	istd_assert(buf != istd_nullptr, "istd_malloc_check() failed. Allocated buffer is null!");
	return buf;
}

void* istd_realloc_check(_In_ void* buf, _In_ size_t newSize) {
	void* newBuf = realloc(buf, newSize);
	istd_assert(newBuf != istd_nullptr, "istd_realloc_check() failed. Allocated buffer is null!");
	return newBuf;
}

void istd_free_check(_In_ void* buf) {
	istd_assert(buf != istd_nullptr, "istd_free_check() failed. Given buffer is null!");
	free(buf);
}
