#if !defined(ISTD_MONITOR_H)
#define ISTD_MONITOR_H

#include "core.h"
#include "math/vector.h"

ISTD_EXTERN_C

istd_define_handle(istd_monitor);

istd_api istd_monitor istd_monitor_primary(
	istd_allocator* allocator
);

istd_api size_t istd_monitor_count(void);

istd_api istd_monitor* istd_monitor_all(
	size_t* monitor_count,
	istd_allocator* allocator
);

istd_api const wchar_t* istd_monitor_name(
	istd_monitor monitor
);

istd_api istd_vector2_i32 istd_monitor_size(
	istd_monitor monitor
);

istd_api istd_vector2_i32 istd_monitor_position(
	istd_monitor monitor
);

istd_api istd_vector2_i32 istd_monitor_dpi(
	istd_monitor monitor
);

istd_api void istd_monitor_free(
	istd_monitor* monitors,
	size_t monitors_count
);

ISTD_END_EXTERN_C


#endif
