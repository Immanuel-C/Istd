#if !defined(ISTD_DYNAMIC_ARRAY)
#define ISTD_DYNAMIC_ARRAY

#include "../core.h"

ISTD_EXTERN_C

#include "../allocator/allocator.h"

#include <stdint.h>

istd_define_handle(istd_dynamic_array);

/**
* Use macro istd_dynamic_array_create.
*/
istd_api istd_dynamic_array* istd_stdcall _istd_dynamic_array_create(size_t typeSize, size_t length, istd_allocator* allocator);
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
istd_api void* istd_stdcall _istd_dynamic_array_at(istd_dynamic_array* arr, size_t index);
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
istd_api void istd_stdcall istd_dynamic_array_push_back(istd_dynamic_array* arr, void* val, istd_allocator* allocator);

/**
* @brief Remove the value to the end of the array.
* @param arr the arr to pop back.
*/
istd_api void istd_stdcall istd_dynamic_array_pop_back(istd_dynamic_array* arr);
/**
* @brief Gets the length of the array.
* @param arr array to get the length of.
* @returns A size_t of the length of the array.
*/
istd_api size_t istd_stdcall istd_dynamic_array_length(istd_dynamic_array* arr);
/**
* @brief Gets the capacity of the array.
* @param arr array to get the capacity of.
* @returns A size_t of the capacity of the array.
*/
istd_api size_t istd_stdcall istd_dynamic_array_capacity(istd_dynamic_array* arr);
/**
* Use macro istd_dynamic_array_buffer.
*/
istd_api void* istd_stdcall _istd_dynamic_array_buffer(istd_dynamic_array* arr);
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
istd_api void istd_stdcall istd_dynamic_array_shrink_to_fit(istd_dynamic_array* arr, istd_allocator* allocator);
/**
* @brief Free dynamic array and set the pointer to istd_nullptr.
* @param arr array to free.
* @param allocator A pointer to a valid istd_allocator.
*/
istd_api void istd_stdcall istd_dynamic_array_free(istd_dynamic_array* arr, istd_allocator* allocator);

ISTD_END_EXTERN_C

#endif