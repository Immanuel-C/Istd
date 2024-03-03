#if !defined(ISTD_DYNAMIC_ARRAY)
#define ISTD_DYNAMIC_ARRAY

#include "allocator/allocator.h"
#include <stdint.h>
#include "core.h"

ISTD_EXTERN_C


istd_define_handle(istd_dynamic_array);

/**
* Use macro istd_dynamic_array_create.
*/
istd_api istd_dynamic_array* istd_stdcall _istd_dynamic_array_create( 
		_In_ size_t typeSize, 
		_In_ size_t length,
		_In_ istd_allocator* allocator 
	);
/**
* @brief Creates a dynamic array.
* @param type the type of data stored in the array.
* @param length a size_t that represents the amount of elements in the array
* @param allocator A pointer to a valid istd_allocator.
* @returns An istd_dynamic_array handle.
*/
#define istd_dynamic_array_create(type, length, allocator) _istd_dynamic_array_create((size_t)sizeof(type), length, allocator)
/**
* Use macro _istd_dynamic_array_at.
*/
istd_api void* istd_stdcall _istd_dynamic_array_at( 
		_In_ istd_dynamic_array* arr, 
		_In_ size_t index
	);
/**
* @brief Gets data in dynamic array at index.
* @param type the type of data stored in the array.
* @param arr the array to access.
* @param index A size_t of the index to access.
* @returns a pointer to the data. The type depends on param type.
*/
#define istd_dynamic_array_at(type, arr, index) (type*)_istd_dynamic_array_at(arr, index)
/**
* @brief Add a value to the end of the array.
* @param arr the arr to push back.
* @param val the value to store.
* @param allocator A pointer to a valid istd_allocator.
*/
istd_api void istd_stdcall istd_dynamic_array_push_back( 
		_Inout_ istd_dynamic_array* arr, 
		_In_ void* val, 
		_In_ istd_allocator* allocator
	);
/**
* @brief Remove the value to the end of the array.
* @param arr the arr to pop back.
*/
istd_api void istd_stdcall istd_dynamic_array_pop_back( 
		_Inout_ istd_dynamic_array* arr
	);
/**
* @brief Gets the length of the array.
* @param arr array to get the length of.
* @returns A size_t of the length of the array.
*/
istd_api size_t istd_stdcall istd_dynamic_array_length( 
		_In_ istd_dynamic_array* arr
	);
/**
* @brief Gets the capacity of the array.
* @param arr array to get the capacity of.
* @returns A size_t of the capacity of the array.
*/
istd_api size_t istd_stdcall istd_dynamic_array_capacity( 
		_In_ istd_dynamic_array* arr
	);
/**
* Use macro istd_dynamic_array_buffer.
*/
istd_api void* istd_stdcall _istd_dynamic_array_buffer(
		_In_ istd_dynamic_array* arr
	);
/**
* @brief Gets the raw data buffer of the array.
* @param type the type of data in the array.
* @param arr the arr to get the buffer from.
*/
#define istd_dynamic_array_buffer(type, arr) (type*)(_istd_dynamic_array_buffer(arr))
/**
* @brief Make array capacity fit to the length.
* @param arr the array to shrink
* @param allocator A pointer to a valid istd_allocator.
*/
istd_api void istd_stdcall istd_dynamic_array_shrink_to_fit( 
		_Inout_ istd_dynamic_array* arr, 
		_In_ istd_allocator* allocator
	);
/**
* @brief Resize the array.
* @param arr the array to resize.
* @param new_length the new length of the array.
* @param allocator A pointer to a valid istd_allocator.
*/
istd_api void istd_stdcall istd_dynamic_array_resize( 
		_Inout_ istd_dynamic_array* arr, 
		_In_ size_t new_length, 
		_In_ istd_allocator* allocator
	);
/**
* @brief Free dynamic array and set the pointer to istd_nullptr.
* @param arr array to free.
* @param allocator A pointer to a valid istd_allocator.
*/
istd_api void istd_stdcall istd_dynamic_array_free(
		_Inout_	istd_dynamic_array* arr, 
		_In_ istd_allocator* allocator
	);

ISTD_END_EXTERN_C

#endif