#if !defined(ISTD_MONITOR_WIN32_H)
#define ISTD_MONITOR_WIN32_H

#include "core.h"
#include "math/vector.h"

ISTD_EXTERN_C

istd_define_handle(istd_monitor_win32);

istd_api istd_monitor_win32 istd_monitor_win32_primary(
	istd_allocator* allocator
);

istd_api size_t istd_monitor_win32_count(void);

istd_api istd_monitor_win32* istd_monitor_win32_all(
	size_t* monitor_count,
	istd_allocator* allocator
);

istd_api const wchar_t* istd_monitor_win32_name(
	istd_monitor_win32 monitor
);

istd_api istd_vector2_i32 istd_monitor_win32_size(
	istd_monitor_win32 monitor
);

istd_api istd_vector2_i32 istd_monitor_win32_position(
	istd_monitor_win32 monitor
);

istd_api istd_vector2_i32 istd_monitor_win32_dpi(
	istd_monitor_win32 monitor
);

istd_api uintptr_t istd_monitor_win32_hmonitor(
	istd_monitor_win32 monitor
);

istd_api void istd_monitor_win32_free(
	istd_monitor_win32* monitors,
	size_t monitors_count
);

ISTD_END_EXTERN_C

#endif
