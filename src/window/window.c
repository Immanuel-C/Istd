#include "window.h"

#if defined(_WIN32)

#include "win32/window_win32.h"

#else

#error istd_window only supports windows for now!

#endif

_Check_return_ _Ret_maybenull_ _Success_(return != istd_nullhnd) istd_window istd_window_create(
	_In_z_ const wchar_t* title,
	_In_ int32_t width,
	_In_ int32_t height,
	_In_ int32_t x,
	_In_ int32_t y
) {
	#if defined(_WIN32)

	return (istd_window)istd_window_win32_create(
		title, 
		width, 
		height, 
		x, 
		y, 
		istd_nullptr
	);

	#endif
}


_Check_return_ bool istd_window_running(
	_In_ istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_running((istd_window_win32)window);

	#endif
}

void istd_window_update(
	_In_ istd_window window
) {
	#if defined(_WIN32)

	istd_window_win32_update((istd_window_win32)window);

	#endif
}

void istd_window_free(
	_Pre_valid_ _Post_invalid_ istd_window window
) {
	#if defined(_WIN32)

	istd_window_win32_free((istd_window_win32)window);

	#endif
}

