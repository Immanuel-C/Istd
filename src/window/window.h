#if !defined(ISTD_WINDOW_H)
#define ISTD_WINDOW_H

#include "core.h"
#include "window_enums.h"
#include "math/vector.h"
#include "monitor.h"
#include <stdint.h>

ISTD_EXTERN_C

istd_define_handle(istd_window);

istd_api istd_window istd_window_create(
	const wchar_t* title,
	int32_t width,
	int32_t height,
	int32_t x,
	int32_t y
);

istd_api bool istd_window_running(
	istd_window window
);

istd_api void istd_window_update(
	istd_window window
);

istd_api void istd_window_wait_event(
	istd_window window
);

istd_api istd_vector2_i32 istd_window_size(
	istd_window window
);

istd_api istd_vector2_i32 istd_window_position(
	istd_window window
);

istd_api istd_vector2_f32 istd_window_mouse_scroll_offset(
	istd_window window
);

istd_api istd_vector2_i32 istd_window_mouse_position(
	istd_window window
);

istd_api bool istd_window_mouse_button_down(
	istd_window window,
	istd_mouse_button button,
	istd_key_modifier_flags mods
);

istd_api bool istd_window_key_down(
	istd_window window,
	istd_key key,
	istd_key_modifier_flags mods
);

istd_api void* istd_window_set_callback(
	istd_window window,
	void* callback_fun,
	int callback_type
);

istd_api void istd_window_set_user_ptr(
	istd_window window,
	void* ptr
);

istd_api void* istd_window_get_user_ptr(
	istd_window window
);

istd_api istd_float64 istd_window_get_time_ms(
	istd_window window
);

istd_api void istd_window_center(
	istd_window window,
	istd_monitor monitor
);

istd_api bool istd_window_iconified(
	istd_window window
);

istd_api bool istd_window_maximized(
	istd_window window
);

istd_api bool istd_window_focused(
	istd_window window
);

istd_api bool istd_window_mouse_entered(
	istd_window window
);

istd_api void istd_window_close(
	istd_window window
);

istd_api void istd_window_free(
	istd_window window
);

ISTD_END_EXTERN_C

#endif
