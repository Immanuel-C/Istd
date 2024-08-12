#include "window.h"

#if defined(_WIN32)

#include "win32/window_win32.h"

#else

#error istd_window only supports windows for now!

#endif

istd_window istd_window_create(
	const wchar_t* title,
	int32_t width,
	int32_t height,
	int32_t x,
	int32_t y
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

bool istd_window_running(
	istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_running((istd_window_win32)window);

	#endif
}

void istd_window_update(
	istd_window window
) {
	#if defined(_WIN32)

	istd_window_win32_update((istd_window_win32)window);

	#endif
}

void istd_window_wait_event(
	istd_window window
) {
	#if defined(_WIN32)

	istd_window_win32_wait_event((istd_window_win32)window);

	#endif
}

istd_vector2_i32 istd_window_size(
	istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_size((istd_window_win32)window);

	#endif
}

istd_vector2_i32 istd_window_position(
	istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_position((istd_window_win32)window);

	#endif
}

istd_vector2_f32 istd_window_mouse_scroll_offset(
	istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_mouse_scroll_offset((istd_window_win32)window);

	#endif
}

istd_vector2_i32 istd_window_mouse_position(
	istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_mouse_position((istd_window_win32)window);

	#endif
}

bool istd_window_mouse_button_down(
	istd_window window,
	istd_mouse_button button,
	istd_key_modifier_flags mods
) {
	#if defined(_WIN32)

	return istd_window_win32_mouse_button_down((istd_window_win32)window, button, mods);

	#endif
}

bool istd_window_key_down(
	istd_window window,
	istd_key key,
	istd_key_modifier_flags mods
) {
	#if defined(_WIN32)

	return istd_window_win32_key_down((istd_window_win32)window, key, mods);

	#endif
}

void* istd_window_set_callback(
	istd_window window,
	void* callback_fun,
	int callback_type
) {
	#if defined(_WIN32)

	return istd_window_win32_set_callback((istd_window_win32)window, callback_fun, callback_type);

	#endif
}


void istd_window_set_user_ptr(
	istd_window window,
	void* ptr
) {
	#if defined(_WIN32)

	istd_window_win32_set_user_ptr((istd_window_win32)window, ptr);

	#endif
}

void* istd_window_get_user_ptr(
	istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_get_user_ptr((istd_window_win32)window);

	#endif
}

istd_float64 istd_window_get_time_ms(
	istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_get_time_ms((istd_window_win32)window);

	#endif
}

void istd_window_center(
	istd_window window,
	istd_monitor monitor
) {
	#if defined(_WIN32)

	istd_window_win32_center((istd_window_win32)window, (istd_monitor_win32)monitor);

	#endif
}

bool istd_window_iconified(
	istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_iconified((istd_window_win32)window);

	#endif
}

bool istd_window_maximized(
	istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_maximized((istd_window_win32)window);

	#endif
}

bool istd_window_focused(
	istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_focused((istd_window_win32)window);

	#endif
}

bool istd_window_mouse_entered(
	istd_window window
) {
	#if defined(_WIN32)

	return istd_window_win32_mouse_entered((istd_window_win32)window);

	#endif
}

void istd_window_close(
	istd_window window
) {
	#if defined(_WIN32)

	istd_window_win32_close((istd_window_win32)window);

	#endif
}


void istd_window_free(
	istd_window window
) {
	#if defined(_WIN32)

	istd_window_win32_free((istd_window_win32)window);

	#endif
}
