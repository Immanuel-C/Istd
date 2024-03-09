#if !defined(ISTD_UNORDERED_MAP_H)
#define ISTD_UNORDERED_MAP_H

#include "core.h"

ISTD_EXTERN_C

istd_define_handle(istd_unordered_map);

typedef size_t (istd_stdcall* istd_pfn_hash_function)(const void*, size_t);

istd_api istd_unordered_map istd_stdcall _istd_unordered_map_create(
	_In_ const size_t type_size,
	_In_ const size_t capacity,
	_In_ istd_pfn_hash_function hash_function
);

#define istd_unordered_map_create(type, capacity, hash_function) _istd_unordered_map_create(sizeof(type), capacity, hash_function)

istd_api int istd_stdcall istd_unordered_map_insert(
	_Inout_ istd_unordered_map map,
	_In_	const void* key,
	_In_	size_t key_size,
	_In_	const void* value
);

istd_api void* istd_stdcall istd_unordered_map_search(
	_Inout_ istd_unordered_map map,
	_In_	const void* key,
	_In_	const size_t key_size
);


istd_api int istd_stdcall istd_unordered_map_free(
	_Inout_ istd_unordered_map* map
);

ISTD_END_EXTERN_C

#endif