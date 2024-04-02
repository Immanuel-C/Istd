#if !defined(ISTD_WINDOW_H)
#define ISTD_WINDOW_H

#include "core.h"
#include "window_enums.h"
#include "math/vector.h"
#include "monitor.h"
#include <stdint.h>

ISTD_EXTERN_C

istd_define_handle(istd_window);

istd_api _Check_return_ _Ret_maybenull_ _Success_(return != istd_nullhnd) istd_window istd_stdcall istd_window_create(
	_In_z_ const wchar_t* title,
	_In_ int32_t width,
	_In_ int32_t height,
	_In_ int32_t x,
	_In_ int32_t y
);

istd_api _Check_return_ bool istd_stdcall istd_window_running(
	_In_ istd_window window
);

istd_api void istd_stdcall istd_window_update(
	_In_ istd_window window
);

istd_api void istd_stdcall istd_window_wait_event(
	_In_ istd_window window
);

istd_api istd_vector2_i32 istd_stdcall istd_window_size(
	_In_ istd_window window
);

istd_api istd_vector2_i32 istd_stdcall istd_window_position(
	_In_ istd_window window
);

istd_api istd_vector2_f32 istd_stdcall istd_window_mouse_scroll_offset(
	_In_ istd_window window
);

istd_api istd_vector2_i32 istd_stdcall istd_window_mouse_position(
	_In_ istd_window window
);

istd_api bool istd_stdcall istd_window_mouse_button_down(
	_In_ istd_window window,
	_In_ istd_mouse_button button,
	_In_ istd_key_modifier_flags mods
);

istd_api bool istd_stdcall istd_window_key_down(
	_In_ istd_window window,
	_In_ istd_key key,
	_In_ istd_key_modifier_flags mods
);

istd_api _Success_(return == istd_nullptr) _Ret_maybenull_ void* istd_stdcall istd_window_set_callback(
	_Inout_ istd_window window,
	_In_    void* callback_fun,
	_In_    int callback_type
);

istd_api void istd_stdcall istd_window_set_user_ptr(
	_In_ istd_window window,
	_In_ void* ptr
);

istd_api _Ret_maybenull_ void* istd_stdcall istd_window_get_user_ptr(
	_In_ istd_window window
);

istd_api istd_float64 istd_stdcall istd_window_get_time_ms(
	_In_ istd_window window
);

istd_api void istd_stdcall istd_window_center(
	_In_ istd_window window,
	_In_ istd_monitor monitor
);

istd_api bool istd_stdcall istd_window_iconified(
	_In_ istd_window window
);

istd_api bool istd_stdcall istd_window_maximized(
	_In_ istd_window window
);

istd_api bool istd_stdcall istd_window_focused(
	_In_ istd_window window
);

istd_api bool istd_stdcall istd_window_mouse_entered(
	_In_ istd_window window
);

istd_api void istd_stdcall istd_window_close(
	_In_ istd_window window
);

istd_api void istd_stdcall istd_window_free(
	_Pre_valid_ _Post_invalid_ istd_window window
);


ISTD_END_EXTERN_C

#endif