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

void istd_window_wait_event(
	_In_ istd_window window
) {
	#if defined(_WIN32)

	istd_window_win32_wait_event((istd_window_win32)window);

	#endif
}

istd_vector2_i32 istd_window_size(
	_In_ istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_size((istd_window_win32)window);

	#endif
}

istd_vector2_i32 istd_window_position(
	_In_ istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_position((istd_window_win32)window);

	#endif
}

istd_vector2_f32 istd_window_mouse_scroll_offset(
	_In_ istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_mouse_scroll_offset((istd_window_win32)window);

	#endif
}

istd_vector2_i32 istd_window_mouse_position(
	_In_ istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_mouse_position((istd_window_win32)window);

	#endif
}

bool istd_window_mouse_button_down(
	_In_ istd_window window,
	_In_ istd_mouse_button button,
	_In_ istd_key_modifier_flags mods
) {
	#if defined(_WIN32)

	return istd_window_win32_mouse_button_down((istd_window_win32)window, button, mods);

	#endif
}

bool istd_window_key_down(
	_In_ istd_window window,
	_In_ istd_key key,
	_In_ istd_key_modifier_flags mods
) {
	#if defined(_WIN32)

	return istd_window_win32_key_down((istd_window_win32)window, key, mods);

	#endif
}

_Success_(return == istd_nullptr) _Ret_maybenull_ void* istd_window_set_callback(
	_Inout_ istd_window window,
	_In_    void* callback_fun,
	_In_    int callback_type
) {
	#if defined(_WIN32)

	return istd_window_win32_set_callback((istd_window_win32)window, callback_fun, callback_type);

	#endif
}


void istd_window_set_user_ptr(
	_In_ istd_window window,
	_In_ void* ptr
) {
	#if defined(_WIN32)

	istd_window_win32_set_user_ptr((istd_window_win32)window, ptr);

	#endif
}

_Ret_maybenull_ void* istd_window_get_user_ptr(
	_In_ istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_get_user_ptr((istd_window_win32)window);

	#endif
}

istd_float64 istd_window_get_time_ms(
	_In_ istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_get_time_ms((istd_window_win32)window);

	#endif
}

void istd_window_center(
	_In_ istd_window window,
	_In_ istd_monitor monitor
) {
	#if defined(_WIN32)

	istd_window_win32_center((istd_window_win32)window, (istd_monitor_win32)monitor);

	#endif
}

bool istd_window_iconified(
	_In_ istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_iconified((istd_window_win32)window);

	#endif
}

bool istd_window_maximized(
	_In_ istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_maximized((istd_window_win32)window);

	#endif
}

bool istd_window_focused(
	_In_ istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_focused((istd_window_win32)window);

	#endif
}

bool istd_window_mouse_entered(
	_In_ istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_mouse_entered((istd_window_win32)window);

	#endif
}

void istd_window_close(
	_In_ istd_window window
) {
	#if defined(_WIN32)

	istd_window_win32_close((istd_window_win32)window);

	#endif
}


void istd_window_free(
	_Pre_valid_ _Post_invalid_ istd_window window
) {
	#if defined(_WIN32)

	istd_window_win32_free((istd_window_win32)window);

	#endif
}

