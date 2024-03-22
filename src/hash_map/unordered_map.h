#if !defined(ISTD_UNORDERED_MAP_H)
#define ISTD_UNORDERED_MAP_H

#include "core.h"

ISTD_EXTERN_C

istd_define_handle(istd_unordered_map);

/**
* @brief a function pointer that an istd_unordered_map will use to create hashes.
* @param buf The buffer of data that the function will hash.
* @param buf_size the size of buf in bytes.
* @returns A hash of buf.
*/
typedef size_t (istd_stdcall* istd_pfn_hash_function)(const void* buf, size_t buf_size);
/**
@brief should use macro istd_unordered_map_create. Creates an istd_unordered_map.
@param type_size the size of the values that the map will hold in bytes.
@param capacity how many elements this table can hold without encountering collisions.
@param hash_function a hash function that can take a block of memory and turn it into a hash.
@returns A valid istd_unordered_map or istd_nullptr if the function fails.
*/
istd_api _Check_return_ _Ret_maybenull_ _Success_(return != istd_nullhnd) istd_unordered_map istd_stdcall __istd_unordered_map_create(
	_In_ const size_t type_size,
	_In_ const size_t capacity,
	_In_ istd_pfn_hash_function hash_function,
	_In_opt_ istd_allocator* allocator
);
/**
@brief creates an istd_unordered_map.
@param type the type of the values that the map will hold.
@param capacity how many elements this table can hold without encountering collisions.
@param hash_function a hash function that can take a block of memory and turn it into a hash.
@returns A valid istd_unordered_map or istd_nullptr if the function fails.
*/
#define istd_unordered_map_create(type, capacity, hash_function, allocator) __istd_unordered_map_create(sizeof(type), capacity, hash_function, allocator)
/**
* @brief inserts a key, value pair into an istd_unordered_map.
* @param map a handle to a valid istd_unordered_map.
* @param key a pointer to the key of the pair.
* @param key_size the size of the key in bytes.
* @param value the value to store. The size must equal to the size of the type passed into the istd_unordered_map_create macro.
* @returns if the function succeds ISTD_RESULT_SUCCESS is returned. ISTD_RESULT_ALLOCATION_FAILED is retunred if the function failed to allocate a new key, value pair.
*/
istd_api _Success_(return == ISTD_RESULT_SUCCESS) istd_result istd_stdcall istd_unordered_map_insert(
	_Inout_ istd_unordered_map map,
	_In_	const void* key,
	_In_	size_t key_size,
	_In_	const void* value
);
/**
* @brief erase's/free's a key, value pair using a key.
* @param map a handle to a valid istd_unordered_map.
* @param key a pointer to the key of the pair.
* @param key_size the size of the key in bytes.
* @returns if the function succeds ISTD_RESULT_SUCCESS is returned. ISTD_RESULT_NOT_FOUND if the key is not in the hash map.
*/
istd_api _Success_(return == ISTD_RESULT_SUCCESS) istd_result istd_stdcall istd_unordered_map_erase(
	_Inout_ istd_unordered_map map,
	_In_	const void* key,
	_In_	size_t key_size
);
/**
* @brief should use istd_unordered_map_search instead. Searches for a value in an istd_unordered_map.
* @param map a handle to a valid istd_unordered_map.
* @param key a pointer to the key of the pair.
* @param key_size the size of the key in bytes.
* @returns a pointer to the value if found. If the value cannot be found the function returns istd_nullptr;
*/
istd_api _Check_return_ _Ret_maybenull_ _Success_(return != istd_nullptr) void* istd_stdcall __istd_unordered_map_search(
	_In_ istd_unordered_map map,
	_In_ const void* key,
	_In_ const size_t key_size
);
/**
* @brief searches for a value in an istd_unordered_map.
* @param value_type the type of value stored in the unordered_map.
* @param map a handle to a valid istd_unordered_map.
* @param key a pointer to the key of the pair.
* @param key_size the size of the key in bytes.
* @returns a pointer to the value if found. If the value cannot be found the function returns istd_nullptr;
*/
#define istd_unordered_map_search(value_type, map, key, key_size) (value_type*)__istd_unordered_map_search(map, key, key_size);
/**
* @brief gets the capacity of an istd_unordered_map.
* @param map A valid istd_unordered_map.
* @returns the capacity of the given map.
*/
istd_api _Check_return_ size_t istd_stdcall istd_unordered_map_capacity(
	_In_ istd_unordered_map map
);
/**
* @brief free the map and all of the key, value pairs in it.
* @param map a pointer to a valud istd_unordered_map.
*/
istd_api _Check_return_ _Success_(return == ISTD_RESULT_SUCCESS) istd_result istd_stdcall istd_unordered_map_free(
	_Pre_valid_ _Post_invalid_ istd_unordered_map map
);

ISTD_END_EXTERN_C

#endif