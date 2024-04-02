#include "monitor.h"

#if defined(_WIN32)

#include "win32/monitor_win32.h"

#endif

istd_monitor istd_monitor_primary(
	_In_opt_ istd_allocator* allocator
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
	_In_	 size_t* monitor_count,
	_In_opt_ istd_allocator* allocator
) {
	#if defined(_WIN32)

	return (istd_monitor*)istd_monitor_win32_all(monitor_count, allocator);

	#endif
}

const wchar_t* istd_monitor_name(
	_In_ istd_monitor monitor
) {
	#if defined(_WIN32)

	return istd_monitor_win32_name((istd_monitor_win32)monitor);

	#endif
}

istd_vector2_i32 istd_monitor_size(
	_In_ istd_monitor monitor
) {
	#if defined(_WIN32)

	return istd_monitor_win32_size((istd_monitor_win32)monitor);

	#endif
}

istd_vector2_i32 istd_monitor_position(
	_In_ istd_monitor monitor
) {
	#if defined(_WIN32)

	return istd_monitor_win32_position((istd_monitor_win32)monitor);

	#endif
}

istd_vector2_i32 istd_monitor_dpi(
	_In_ istd_monitor monitor
) {
	#if defined(_WIN32)

	return istd_monitor_win32_dpi((istd_monitor_win32)monitor);

	#endif
}

void istd_monitor_free(
	_In_ istd_monitor* monitors,
	_In_ size_t monitors_count
) {
	#if defined(_WIN32)

	istd_monitor_win32_free((istd_monitor_win32*)monitors, monitors_count);

	#endif
}