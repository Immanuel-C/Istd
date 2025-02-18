#if !defined(ISTD_THREAD_H)
#define ISTD_THREAD_H

#include "core.h"

ISTD_EXTERN_C

#include <stdint.h>

ISTD_API void istd_this_thread_sleep(
	uint32_t miliseconds
);

ISTD_DEFINE_HANDLE(istd_thread);

typedef void* (*istd_pfn_thread)(void*);
typedef uint64_t istd_thread_id;

ISTD_API istd_thread istd_thread_create(
	istd_pfn_thread thread_fun,
	void* thread_fun_arg
);

ISTD_API istd_thread_id istd_thread_get_id(
	istd_thread thread
);

ISTD_API istd_thread_id istd_thread_get_current_id(void);

ISTD_API void istd_thread_join(
	istd_thread thread
);

ISTD_END_EXTERN_C

#endif
