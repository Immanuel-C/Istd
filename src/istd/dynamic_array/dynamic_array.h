#if !defined(ISTD_DYNAMIC_ARRAY)
#define ISTD_DYNAMIC_ARRAY

#include "allocator/allocator.h"
#include <stdint.h>
#include "core.h"

ISTD_EXTERN_C


ISTD_DEFINE_HANDLE(istd_dynamic_array);

/**
* @brief Use macro istd_dynamic_array_create.
*/
ISTD_API istd_dynamic_array __istd_dynamic_array_create( 
		size_t typeSize, 
		size_t length,
		istd_allocator* allocator 
	);
/**
* @brief Creates a dynamic array.
* @param type the type of data stored in the array.
* @param length a size_t that represents the amount of elements in the array
* @param allocator A pointer to a valid istd_allocator or null. If the allocator is null then it will use the defualt C allocator.
* @returns An istd_dynamic_array handle or istd_nullhnd if the function fails.
*/
#define istd_dynamic_array_create(type, length, allocator) __istd_dynamic_array_create((size_t)sizeof(type), length, allocator)
/**
* Use macro _istd_dynamic_array_at.
*/
ISTD_API void* __istd_dynamic_array_at( 
		istd_dynamic_array arr, 
		size_t index
	);
/**
* @brief Gets data in dynamic array at index.
* @param type the type of data stored in the array.
* @param arr the array to access.
* @param index A size_t of the index to access.
* @returns a pointer to the data. The type depends on param type.
*/
#define istd_dynamic_array_at(type, arr, index) (type*)__istd_dynamic_array_at(arr, index)
/**
* @brief Add a value to the end of the array.
* @param arr the arr to push back.
* @param val the value to store.
*/
ISTD_API void istd_dynamic_array_push_back( 
		istd_dynamic_array arr, 
		void* val
	);
/**
* @brief Remove the value to the end of the array.
* @param arr the arr to pop back.
*/
ISTD_API void istd_dynamic_array_pop_back( 
		istd_dynamic_array arr
	);
/**
* @brief Gets the length of the array.
* @param arr array to get the length of.
* @returns A size_t of the length of the array.
*/
ISTD_API size_t istd_dynamic_array_length( 
		istd_dynamic_array arr
	);
/**
* @brief Gets the capacity of the array.
* @param arr array to get the capacity of.
* @returns A size_t of the capacity of the array.
*/
ISTD_API size_t istd_dynamic_array_capacity( 
		istd_dynamic_array arr
	);
/**
* Use macro istd_dynamic_array_buffer.
*/
ISTD_API void* __istd_dynamic_array_buffer(
		istd_dynamic_array arr
	);
/**
* @brief Gets the raw data buffer of the array.
* @param type the type of data in the array.
* @param arr the arr to get the buffer from.
*/
#define istd_dynamic_array_buffer(type, arr) (type*)(__istd_dynamic_array_buffer(arr))
/**
* @brief Make array capacity fit to the length.
* @param arr the array to shrink
*/
ISTD_API void istd_dynamic_array_shrink_to_fit( 
		istd_dynamic_array arr
	);
/**
* @brief Resize the array.
* @param arr the array to resize.
* @param new_length the new length of the array.
*/
ISTD_API void istd_dynamic_array_resize( 
		istd_dynamic_array arr, 
		size_t new_length 
	);
/**
* @brief Free dynamic array and set the pointer to istd_nullptr.
* @param arr array to free.
*/
ISTD_API void istd_dynamic_array_free(
		istd_dynamic_array arr
	);

ISTD_END_EXTERN_C

#endif
