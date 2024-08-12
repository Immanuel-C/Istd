#if !defined(ISTD_ALLOCATOR)
#define ISTD_ALLOCATOR

#include "core.h"

ISTD_EXTERN_C

istd_api istd_allocator* istd_get_defualt_allocator(void);

istd_api void istd_set_defualt_allocator(
	istd_allocator* new_allocator
);

ISTD_END_EXTERN_C

#endif
