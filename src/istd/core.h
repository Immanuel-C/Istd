#if !defined(ISTD_CORE_H)
#define ISTD_CORE_H

#if defined(__cplusplus)
#define ISTD_EXTERN_C extern "C" {
#define ISTD_END_EXTERN_C }
#else
#define ISTD_EXTERN_C
#define ISTD_END_EXTERN_C 
#endif

ISTD_EXTERN_C

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#define ISTD_DEFINE_HANDLE(name) typedef struct name##_t* name

#if defined(__cplusplus)
#define istd_nullptr nullptr
#else
#define istd_nullptr (void*)0

#endif

#define istd_nullhnd istd_nullptr

#if defined(ISTD_DLL)
#if defined(ISTD_EXPORT_DLL)
#if defined(_MSC_VER) || defined(__clang__)
#define ISTD_API __declspec(dllexport)
#else
#define ISTD_API __attribute__((dllexport))
#endif
#else 
#if defined(_MSC_VER) || defined(__clang__)
#define ISTD_API __declspec(dllimport)
#else 
#define ISTD_API __attribute__((dllimport))
#endif
#endif
#else 
#define ISTD_API
#endif



#if defined(_MSC_VER)

#define istd_force_inline __forceinline

#else 

#define istd_force_inline __attribute__((always_inline))

#endif

#if defined(__linux__)
#include <stddef.h>
#endif

#define ISTD_ASSERT(condition, msg) assert((condition) && msg)

#define ISTD_IGNORE_RETURN(fun) (void)(fun)
#define ISTD_UNUSED_PARAMETER(param) (void)(sizeof(param))

typedef void* (*istd_pfn_malloc)(size_t size);
typedef void* (*istd_pfn_calloc)(size_t num_elements, size_t type_size);
typedef void* (*istd_pfn_realloc)(void* ptr, size_t new_size);
typedef void (*istd_pfn_free)(void* ptr);

typedef struct istd_allocator_t {
	istd_pfn_malloc malloc;
	istd_pfn_calloc calloc;
	istd_pfn_realloc realloc;
	istd_pfn_free free;
} istd_allocator;

typedef enum {
	ISTD_RESULT_SUCCESS = 0,
	ISTD_RESULT_ALLOCATION_FAILED = 1,
	ISTD_RESULT_NOT_FOUND = 2,
	ISTD_RESULT_PARAMETER_NULL = 3,
	ISTD_RESULT_PARAMETER_INVALID = 4,
	ISTD_RESULT_ACCESS_OUT_OF_BOUNDS = 5,
	ISTD_RESULT_FILE_COULD_NOT_OPEN = 6,
	ISTD_RESULT_FILE_TOO_BIG = 7,
	ISTD_RESULT_FORMAT_NOT_SUPPORTED = 8,
	ISTD_RESULT_MEM_OP_FAILED = 9,
} istd_result;

typedef uint64_t istd_flags;

#if !defined(_WCHAR_T_DEFINED)
    typedef unsigned short wchar_t;
#endif


ISTD_END_EXTERN_C

#endif
