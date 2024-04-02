#if !defined(ISTD_WINDOW_WIN32_H)
#define ISTD_WINDOW_WIN32_H

#include "core.h"
#include "../window_enums.h"
#include "../../math/vector.h"
#include "monitor_win32.h"
#include <stdint.h>

ISTD_EXTERN_C

istd_define_handle(istd_window_win32);

istd_api _Check_return_ _Ret_maybenull_ _Success_(return != istd_nullhnd) istd_window_win32 istd_stdcall istd_window_win32_create(
	_In_z_ const wchar_t* title,
	_In_	 int32_t width,
	_In_	 int32_t height,
	_In_	 int32_t x,
	_In_	 int32_t y,
	_In_opt_ istd_allocator* allocator
);

istd_api _Check_return_ bool istd_stdcall istd_window_win32_running(
	_In_ istd_window_win32 window
);

istd_api void istd_stdcall istd_window_win32_update(
	_In_ istd_window_win32 window
);

istd_api void istd_stdcall istd_window_win32_wait_event(
	_In_ istd_window_win32 window
);

istd_api const wchar_t* istd_stdcall istd_window_win32_title(
	_In_ istd_window_win32 window
);

istd_api void istd_stdcall istd_window_win32_set_title(
	_In_   istd_window_win32 window,
	_In_z_ const wchar_t* new_title
);

istd_api istd_vector2_i32 istd_stdcall istd_window_win32_size(
	_In_ istd_window_win32 window
);

istd_api istd_vector2_i32 istd_stdcall istd_window_win32_framebuffer_size(
	_In_ istd_window_win32 window
);

istd_api void istd_stdcall istd_window_win32_set_size(
	_In_ istd_window_win32 window,
	_In_ const istd_vector2_i32 new_size
);

istd_api istd_vector2_i32 istd_stdcall istd_window_win32_position(
	_In_ istd_window_win32 window
);

istd_api void istd_stdcall istd_window_win32_set_position(
	_In_ istd_window_win32 window,
	_In_ const istd_vector2_i32 new_position
);

istd_api istd_vector2_f32 istd_stdcall istd_window_win32_mouse_scroll_offset(
	_In_ istd_window_win32 window
);

istd_api istd_vector2_i32 istd_stdcall istd_window_win32_mouse_position(
	_In_ istd_window_win32 window
);

istd_api void istd_stdcall istd_window_win32_set_mouse_position(
	_In_ istd_window_win32 window,
	_In_ istd_vector2_i32 new_mouse_position
);

istd_api bool istd_stdcall istd_window_win32_mouse_button_down(
	_In_ istd_window_win32 window,
	_In_ istd_mouse_button button,
	_In_ istd_key_modifier_flags mods
);

istd_api bool istd_stdcall istd_window_win32_key_down(
	_In_ istd_window_win32 window,
	_In_ istd_key key,
	_In_ istd_key_modifier_flags mods
);

istd_api _Success_(return == istd_nullptr) _Ret_maybenull_ void* istd_stdcall istd_window_win32_set_callback(
	_Inout_ istd_window_win32 window, 
	_In_    void* callback_fun, 
	_In_    int callback_type
);

istd_api istd_key istd_stdcall istd_window_win32_convert_vk_key_code_to_istd_key(
	_In_ int32_t vk_key_code
);

istd_api void istd_stdcall istd_window_win32_set_user_ptr(
	_In_ istd_window_win32 window,
	_In_ void* ptr
);

istd_api _Ret_maybenull_ void* istd_stdcall istd_window_win32_get_user_ptr(
	_In_ istd_window_win32 window
);

istd_api istd_float64 istd_stdcall istd_window_win32_get_time_ms(
	_In_ istd_window_win32 window
);

istd_api void istd_stdcall istd_window_win32_center(
	_In_ istd_window_win32 window,
	_In_ istd_monitor_win32 monitor
);

istd_api bool istd_stdcall istd_window_win32_iconified(
	_In_ istd_window_win32 window
);

istd_api bool istd_stdcall istd_window_win32_maximized(
	_In_ istd_window_win32 window
);

istd_api bool istd_stdcall istd_window_win32_focused(
	_In_ istd_window_win32 window
);

istd_api void istd_stdcall istd_window_win32_set_style(
	_In_ istd_window_win32 window,
	_In_ istd_window_style_flags style
);

istd_api void istd_stdcall istd_window_win32_fullscreen(
	_In_ istd_window_win32 window,
	_In_ bool fullscreen,
	_In_ istd_monitor_win32 monitor
);

istd_api bool istd_stdcall istd_window_win32_mouse_entered(
	_In_ istd_window_win32 window
);

istd_api uintptr_t istd_stdcall istd_window_win32_hwnd(
	_In_ istd_window_win32 window
);

istd_api uintptr_t istd_stdcall istd_window_win32_hdc(
	_In_ istd_window_win32 window
);

istd_api uintptr_t istd_stdcall istd_window_win32_hinstance(
	_In_ istd_window_win32 window
);

istd_api void istd_stdcall istd_window_win32_close(
	_In_ istd_window_win32 window
);

istd_api void istd_stdcall istd_window_win32_free(
	_Pre_valid_ _Post_invalid_ istd_window_win32 window
);


ISTD_END_EXTERN_C

#endif