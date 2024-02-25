#if !defined(ISTD_ALLOCATOR)
#define ISTD_ALLOCATOR

#include "../core.h"

ISTD_EXTERN_C

istd_api void* istd_cdecl istd_malloc_check(size_t size);
istd_api void* istd_cdecl istd_calloc_check(size_t count, size_t size);
istd_api void* istd_cdecl istd_realloc_check(void* buf, size_t newSize);
istd_api void istd_cdecl istd_free_check(void* buf);

ISTD_END_EXTERN_C

#endif