#include "core.h"

#include "allocator/allocator.h"

istd_allocator istd_get_defualt_allocator(void) {
	return (istd_allocator) {
		.malloc = &istd_malloc_check,
		.realloc = &istd_realloc_check,
		.calloc = &istd_calloc_check,
		.free = &istd_free_check
	};
}
