#if !defined(ISTD_ALLOCATOR)
#define ISTD_ALLOCATOR

#include "core.h"

ISTD_EXTERN_C

istd_api void* istd_cdecl istd_malloc_check( 
		_In_ size_t size
	);

istd_api void* istd_cdecl istd_calloc_check(
		_In_ size_t count, 
		_In_ size_t size
	);

istd_api void* istd_cdecl istd_realloc_check(
		_In_ void* buf, 
		_In_ size_t newSize
	);

istd_api void istd_cdecl istd_free_check( 
		_In_ void* buf
	);

ISTD_END_EXTERN_C

#endif