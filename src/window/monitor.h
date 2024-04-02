#if !defined(ISTD_MONITOR_H)
#define ISTD_MONITOR_H

#include "core.h"
#include "math/vector.h"

ISTD_EXTERN_C

istd_define_handle(istd_monitor);

istd_api istd_monitor istd_stdcall istd_monitor_primary(
	_In_opt_ istd_allocator* allocator
);

istd_api size_t istd_stdcall istd_monitor_count(void);

istd_api istd_monitor* istd_stdcall istd_monitor_all(
	_In_	 size_t* monitor_count,
	_In_opt_ istd_allocator* allocator
);

istd_api const wchar_t* istd_stdcall istd_monitor_name(
	_In_ istd_monitor monitor
);

istd_api istd_vector2_i32 istd_stdcall istd_monitor_size(
	_In_ istd_monitor monitor
);

istd_api istd_vector2_i32 istd_stdcall istd_monitor_position(
	_In_ istd_monitor monitor
);

istd_api istd_vector2_i32 istd_stdcall istd_monitor_dpi(
	_In_ istd_monitor monitor
);

istd_api void istd_stdcall istd_monitor_free(
	_In_ istd_monitor* monitors,
	_In_ size_t monitors_count
);

ISTD_END_EXTERN_C


#endif