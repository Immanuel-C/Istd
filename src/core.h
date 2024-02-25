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

#if defined(__cplusplus)
#include <cassert>
#else
#include <assert.h>
#endif

#define istd_define_handle(name) typedef struct name##_t* name

#if defined(__cplusplus)
#define istd_nullptr nullptr
#else
#define istd_nullptr (void*)0
#endif

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

#if defined(_MSC_VER) || defined(__clang__)

#define istd_cdecl __cdecl
#define istd_stdcall __stdcall
#define istd_fastcall __fastcall

#elif defined(__MINGW32__) || defined(__GNUC__) 

#define istd_cdecl __attribute__((cdecl))
#define istd_stdcall __attribute__((stdcall))
#define istd_fastcall __attribute__((fastcall))

#endif

#define istd_assert(condition, msg) assert((condition) && msg)

#define istd_ignore_return(fun) (void)fun

typedef void* (istd_cdecl* istd_pfn_malloc)(size_t);
typedef void* (istd_cdecl* istd_pfn_calloc)(size_t);
typedef void* (istd_cdecl* istd_pfn_realloc)(void*, size_t);
typedef void (istd_cdecl* istd_pfn_free)(void*);

typedef struct istd_allocator_t {
	istd_pfn_malloc malloc;
	istd_pfn_calloc calloc;
	istd_pfn_realloc realloc;
	istd_pfn_free free;
} istd_allocator;

istd_api istd_allocator istd_stdcall istd_get_defualt_allocator();


typedef enum istd_errno_values {
	ISTD_ENONE        = 0,
	ISTD_EPERM        = 1,
	ISTD_ENOENT       = 2,
	ISTD_ESRCH        = 3,
	ISTD_EINTR        = 4,
	ISTD_EIO          = 5,
	ISTD_ENXIO        = 6,
	ISTD_E2BIG        = 7,
	ISTD_ENOEXEC      = 8,
	ISTD_EBADF        = 9,
	ISTD_ECHILD       = 10,
	ISTD_EAGAIN       = 11,
	ISTD_ENOMEM       = 12,
	ISTD_EACCES       = 13,
	ISTD_EFAULT       = 14,
	ISTD_EBUSY        = 16,
	ISTD_EEXIST       = 17,
	ISTD_EXDEV        = 18,
	ISTD_ENODEV       = 19,
	ISTD_ENOTDIR      = 20,
	ISTD_EISDIR       = 21,
	ISTD_ENFILE       = 23,
	ISTD_EMFILE       = 24,
	ISTD_ENOTTY       = 25,
	ISTD_EFBIG        = 27,
	ISTD_ENOSPC       = 28,
	ISTD_ESPIPE       = 29,
	ISTD_EROFS        = 30,
	ISTD_EMLINK       = 31,
	ISTD_EPIPE        = 32,
	ISTD_EDOM         = 33,
	ISTD_EDEADLK      = 36,
	ISTD_ENAMETOOLONG = 38,
	ISTD_ENOLCK       = 39,
	ISTD_ENOSYS       = 40,
	ISTD_ENOTEMPTY    = 41,
} istd_errno;

#if !defined(__cplusplus)
#include <stdbool.h>
#endif

ISTD_END_EXTERN_C

#endif