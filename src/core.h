#if !defined(ISTD_CORE)
#define ISTD_CORE

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

#include "salieri.h"

#define istd_define_handle(name) typedef struct name##_t* name

#if defined(__cplusplus)
#define istd_nullptr nullptr
#else
#define istd_nullptr (void*)0

#endif

#define istd_nullhnd istd_nullptr

#if defined(ISTD_DLL)
#if defined(ISTD_EXPORT_DLL)
#if defined(_MSC_VER) || defined(__clang__)
#define istd_api __declspec(dllexport)
#else
#define istd_api __attribute__((dllexport))
#endif
#else 
#if defined(_MSC_VER) || defined(__clang__)
#define istd_api __declspec(dllimport)
#else 
#define istd_api __attribute__((dllimport))
#endif
#endif
#else 
#define istd_api
#endif

// Linux doesn't support calling conventions but MINGW does.

#if defined(_WIN32) && (defined(_MSC_VER) || defined(__clang__))

#define istd_cdecl __cdecl
#define istd_stdcall __stdcall
#define istd_fastcall __fastcall

#define istd_disable_warning(code) __pragma(warning(suppress: code))

#define istd_pragma(command) __pragma(command)

#elif (defined(__MINGW32__) || defined(__GNUC__)) && !defined(__linux__)

#define istd_cdecl __attribute__((cdecl))
#define istd_stdcall __attribute__((stdcall))
#define istd_fastcall __attribute__((fastcall))

#define istd_disable_warning(code) 

#define istd_pragma(command) 

#else

#define istd_cdecl 
#define istd_stdcall 
#define istd_fastcall

#define istd_disable_warning(code) 

#define istd_pragma(command)

#endif

#if defined(_MSC_VER)

#define istd_force_inline __forceinline

#else 

#define istd_force_inline __attribute__((always_inline))

#endif

#if defined(__linux__)
#include <stddef.h>
#endif

#define istd_assert(condition, msg) assert((condition) && msg)

#define istd_ignore_return(fun) (void)(fun)
#define istd_unused_parameter(param) (void)(sizeof(param))

typedef void* (istd_cdecl* istd_pfn_malloc)(size_t size);
typedef void* (istd_cdecl* istd_pfn_calloc)(size_t num_elements, size_t type_size);
typedef void* (istd_cdecl* istd_pfn_realloc)(void* ptr, size_t new_size);
typedef void (istd_cdecl* istd_pfn_free)(void* ptr);

typedef struct istd_allocator_t {
	istd_pfn_malloc malloc;
	istd_pfn_calloc calloc;
	istd_pfn_realloc realloc;
	istd_pfn_free free;
} istd_allocator;

typedef enum istd_errno_values {
	ISTD_ENONE = 0,
	ISTD_EPERM = 1,
	ISTD_ENOENT = 2,
	ISTD_ESRCH = 3,
	ISTD_EINTR = 4,
	ISTD_EIO = 5,
	ISTD_ENXIO = 6,
	ISTD_E2BIG = 7,
	ISTD_ENOEXEC = 8,
	ISTD_EBADF = 9,
	ISTD_ECHILD = 10,
	ISTD_EAGAIN = 11,
	ISTD_ENOMEM = 12,
	ISTD_EACCES = 13,
	ISTD_EFAULT = 14,
	ISTD_EBUSY = 16,
	ISTD_EEXIST = 17,
	ISTD_EXDEV = 18,
	ISTD_ENODEV = 19,
	ISTD_ENOTDIR = 20,
	ISTD_EISDIR = 21,
	ISTD_ENFILE = 23,
	ISTD_EMFILE = 24,
	ISTD_ENOTTY = 25,
	ISTD_EFBIG = 27,
	ISTD_ENOSPC = 28,
	ISTD_ESPIPE = 29,
	ISTD_EROFS = 30,
	ISTD_EMLINK = 31,
	ISTD_EPIPE = 32,
	ISTD_EDOM = 33,
	ISTD_EDEADLK = 36,
	ISTD_ENAMETOOLONG = 38,
	ISTD_ENOLCK = 39,
	ISTD_ENOSYS = 40,
	ISTD_ENOTEMPTY = 41,
	ISTD_ERRNO_MAX
} istd_errno;

typedef enum {
	ISTD_RESULT_SUCCESS = 0,
	ISTD_RESULT_ALLOCATION_FAILED = 1,
	ISTD_RESULT_NOT_FOUND = 2,
	ISTD_RESULT_PARAMETER_NULL = 3,
	ISTD_RESULT_PARAMETER_INVALID = 4,
	ISTD_RESULT_ACCESS_OUT_OF_BOUNDS = 5,
} istd_result;

typedef uint64_t istd_flags;

ISTD_END_EXTERN_C

#endif