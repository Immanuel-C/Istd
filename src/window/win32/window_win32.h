#if !defined(ISTD_WINDOW_WIN32_H)
#define ISTD_WINDOW_WIN32_H

#include "core.h"
#include "../window_enums.h"
#include "../../math/vector.h"
#include "monitor_win32.h"
#include "../../image/image.h"


#include <stdint.h>

ISTD_EXTERN_C

istd_define_handle(istd_window_win32);

istd_api istd_window_win32 istd_window_win32_create(
	const wchar_t* title,
	int32_t width,
	int32_t height,
	int32_t x,
	int32_t y,
	istd_allocator* allocator
);

istd_api bool istd_window_win32_running(
	istd_window_win32 window
);

istd_api void istd_window_win32_update(
	istd_window_win32 window
);

istd_api void istd_window_win32_wait_event(
	istd_window_win32 window
);

istd_api const wchar_t* istd_window_win32_title(
	istd_window_win32 window
);

istd_api void istd_window_win32_set_title(
	istd_window_win32 window,
	const wchar_t* new_title
);

istd_api istd_vector2_i32 istd_window_win32_size(
	istd_window_win32 window
);

istd_api istd_vector2_i32 istd_window_win32_framebuffer_size(
	istd_window_win32 window
);

istd_api void istd_window_win32_set_size(
	istd_window_win32 window,
	const istd_vector2_i32 new_size
);

istd_api istd_vector2_i32 istd_window_win32_position(
	istd_window_win32 window
);

istd_api void istd_window_win32_set_position(
	istd_window_win32 window,
	const istd_vector2_i32 new_position
);

istd_api istd_vector2_f32 istd_window_win32_mouse_scroll_offset(
	istd_window_win32 window
);

istd_api istd_vector2_i32 istd_window_win32_mouse_position(
	istd_window_win32 window
);

istd_api void istd_window_win32_set_mouse_position(
	istd_window_win32 window,
	istd_vector2_i32 new_mouse_position
);

istd_api bool istd_window_win32_mouse_button_down(
	istd_window_win32 window,
	istd_mouse_button button,
	istd_key_modifier_flags mods
);

istd_api bool istd_window_win32_key_down(
	istd_window_win32 window,
	istd_key key,
	istd_key_modifier_flags mods
);

istd_api void* istd_window_win32_set_callback(
	istd_window_win32 window, 
	void* callback_fun, 
	int callback_type
);

istd_api istd_key istd_window_win32_convert_vk_key_code_to_istd_key(
	int32_t vk_key_code
);

istd_api void istd_window_win32_set_user_ptr(
	istd_window_win32 window,
	void* ptr
);

istd_api void* istd_window_win32_get_user_ptr(
	istd_window_win32 window
);

istd_api istd_float64 istd_window_win32_get_time_ms(
	istd_window_win32 window
);

istd_api void istd_window_win32_center(
	istd_window_win32 window,
	istd_monitor_win32 monitor
);

istd_api bool istd_window_win32_iconified(
	istd_window_win32 window
);

istd_api bool istd_window_win32_maximized(
	istd_window_win32 window
);

istd_api bool istd_window_win32_focused(
	istd_window_win32 window
);

istd_api void istd_window_win32_set_style(
	istd_window_win32 window,
	istd_window_style_flags style
);

istd_api void istd_window_win32_fullscreen(
	istd_window_win32 window,
	bool fullscreen,
	istd_monitor_win32 monitor
);

istd_api bool istd_window_win32_mouse_entered(
	istd_window_win32 window
);

istd_api void istd_window_win32_set_icon(
	istd_window_win32 window,
	istd_image* image
);

istd_api uintptr_t istd_window_win32_hwnd(
	istd_window_win32 window
);

istd_api uintptr_t istd_window_win32_hdc(
	istd_window_win32 window
);

istd_api uintptr_t istd_window_win32_hinstance(
	istd_window_win32 window
);

istd_api void istd_window_win32_close(
	istd_window_win32 window
);

istd_api void istd_window_win32_free(
	istd_window_win32 window
);


ISTD_END_EXTERN_C

#endif
