#if !defined(ISTD_MONITOR_WIN32_H)
#define ISTD_MONITOR_WIN32_H

#include "core.h"
#include "math/vector.h"

ISTD_EXTERN_C

istd_define_handle(istd_monitor_win32);

istd_api istd_monitor_win32 istd_stdcall istd_monitor_win32_primary(
	_In_opt_ istd_allocator* allocator
);

istd_api size_t istd_stdcall istd_monitor_win32_count(void);

istd_api istd_monitor_win32* istd_stdcall istd_monitor_win32_all(
	_In_	 size_t* monitor_count,
	_In_opt_ istd_allocator* allocator
);

istd_api const wchar_t* istd_stdcall istd_monitor_win32_name(
	_In_ istd_monitor_win32 monitor
);

istd_api istd_vector2_i32 istd_stdcall istd_monitor_win32_size(
	_In_ istd_monitor_win32 monitor
);

istd_api istd_vector2_i32 istd_stdcall istd_monitor_win32_position(
	_In_ istd_monitor_win32 monitor
);

istd_api istd_vector2_i32 istd_stdcall istd_monitor_win32_dpi(
	_In_ istd_monitor_win32 monitor
);

istd_api uintptr_t istd_stdcall istd_monitor_win32_hmonitor(
	_In_ istd_monitor_win32 monitor
);

istd_api void istd_stdcall istd_monitor_win32_free(
	_In_ istd_monitor_win32* monitors,
	_In_ size_t monitors_count
);

ISTD_END_EXTERN_C

#endif