#if !defined(ISTD_THREAD_H)
#define ISTD_THREAD_H

#include "core.h"

ISTD_EXTERN_C

#include <stdint.h>

istd_api void istd_stdcall istd_this_thread_sleep(
	_In_ uint32_t miliseconds
);

istd_define_handle(istd_thread);

typedef void* (istd_stdcall* istd_pfn_thread)(void*);
typedef uint64_t istd_thread_id;

istd_api istd_thread istd_stdcall istd_thread_create(
	_In_	 istd_pfn_thread thread_fun,
	_In_opt_ void* thread_fun_arg
);

istd_api istd_thread_id istd_stdcall istd_thread_get_id(
	_In_ istd_thread thread
);

istd_api istd_thread_id istd_stdcall istd_thread_get_current_id(void);

istd_api void istd_stdcall istd_thread_join(
	_In_ _Post_ptr_invalid_ istd_thread thread
);

ISTD_END_EXTERN_C

#endif