#include "allocator.h"

#include <stdlib.h>

static istd_allocator allocator = {
	.malloc = malloc,
	.calloc = calloc,
	.realloc = realloc,
	.free = free,
};

istd_allocator* istd_get_defualt_allocator(void) {
	return &allocator;
}

void istd_set_defualt_allocator(
	_In_ istd_allocator* new_allocator
) {
	allocator.malloc = new_allocator->malloc;
	allocator.calloc = new_allocator->calloc;
	allocator.realloc = new_allocator->realloc;
	allocator.free = new_allocator->free;
}
