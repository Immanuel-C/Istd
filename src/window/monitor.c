#include "monitor.h"

#if defined(_WIN32)

#include "win32/monitor_win32.h"

#endif

#include <stdint.h>

istd_monitor istd_monitor_primary(
	istd_allocator* allocator
) {
	#if defined(_WIN32)

	return (istd_monitor)istd_monitor_win32_primary(allocator);

	#endif
}

size_t istd_monitor_count(void) {
	#if defined(_WIN32)

	return istd_monitor_win32_count();

	#endif
}

istd_monitor* istd_monitor_all(
	size_t* monitor_count,
	istd_allocator* allocator
) {
	#if defined(_WIN32)

	return (istd_monitor*)istd_monitor_win32_all(monitor_count, allocator);

	#endif
}

const wchar_t* istd_monitor_name(
	istd_monitor monitor
) {
	#if defined(_WIN32)

	return istd_monitor_win32_name((istd_monitor_win32)monitor);

	#endif
}

istd_vector2_i32 istd_monitor_size(
	istd_monitor monitor
) {
	#if defined(_WIN32)

	return istd_monitor_win32_size((istd_monitor_win32)monitor);

	#endif
}

istd_vector2_i32 istd_monitor_position(
	istd_monitor monitor
) {
	#if defined(_WIN32)

	return istd_monitor_win32_position((istd_monitor_win32)monitor);

	#endif
}

istd_vector2_i32 istd_monitor_dpi(
	istd_monitor monitor
) {
	#if defined(_WIN32)

	return istd_monitor_win32_dpi((istd_monitor_win32)monitor);

	#endif
}

void istd_monitor_free(
	istd_monitor* monitors,
	size_t monitors_count
) {
	#if defined(_WIN32)

	istd_monitor_win32_free((istd_monitor_win32*)monitors, monitors_count);

	#endif
}
