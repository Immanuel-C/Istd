#include "window_test.h"

#include "window/window.h"
#include "window/monitor.h"

#if defined(_WIN32) 
#include "window/win32/window_win32.h"
#include "window/win32/monitor_win32.h"
#endif

#include "safe/string_safe.h"
#include "io/io.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uchar.h>


static void istd_stdcall window_move_callback(istd_window window, istd_vector2_i32 position) {
	istd_unused_parameter(window);
	istd_println("Window Moved: x -> %i, y -> %i", position.x, position.y);
}

static void istd_stdcall window_size_callback(istd_window window, istd_vector2_i32 size) {
	istd_unused_parameter(window);
	istd_println("Window Sized: width -> %i, height -> %i", size.width, size.height);
}

static void istd_stdcall framebuffer_size_callback(istd_window window, istd_vector2_i32 size) {
	istd_unused_parameter(window);
	istd_println("Framebuffer Sized: width -> %i, height -> %i", size.width, size.height);
}

static void istd_stdcall window_iconified_callback(istd_window window, bool iconified) {
	istd_unused_parameter(window);
	istd_println("Window Iconified: %s", iconified == true ? "true" : "false");
}

static void istd_stdcall window_maximized_callback(istd_window window, bool maximized) {
	istd_unused_parameter(window);
	istd_ignore_return(printf("Window Maximized: %s", maximized == true ? "true" : "false"));
}

static void istd_stdcall mouse_move_callback(istd_window window, istd_vector2_i32 mouse_position) {
	istd_unused_parameter(window);
	istd_println("Mouse Moved: x -> %i, y -> %i", mouse_position.x, mouse_position.y);
}

static void istd_stdcall mouse_scroll_callback(istd_window window, istd_vector2_f32 scroll_offset) {
	istd_unused_parameter(window);
	istd_println("Mouse Scroll Wheel Scrolled: x -> %0.3f, y -> %0.3f", scroll_offset.x, scroll_offset.y);
}

static inline const char* convert_mouse_button_to_cstring(istd_mouse_button button) {
	switch (button) {
		case ISTD_MOUSE_BUTTON_LEFT:
			return "left";
		case ISTD_MOUSE_BUTTON_RIGHT:
			return "right";
		case ISTD_MOUSE_BUTTON_MIDDLE:
			return "middle";
		case ISTD_MOUSE_BUTTON_SIDE1:
			return "side1";
		case ISTD_MOUSE_BUTTON_SIDE2:
			return "side2";
		case ISTD_MOUSE_BUTTON_MAX:
		default:
			return "undefined";
	}
}

static inline char* convert_key_modifiers_to_cstring(istd_key_modifier_flags mods) {
	size_t res_size = 512;
	char* res = malloc(res_size);

	if (res == istd_nullptr)
		return istd_nullptr;

	istd_ignore_return(istd_memset_safe(res, res_size, 0, res_size));
		
	const char* name;

	if (mods & ISTD_KEY_MOD_SHIFT_BIT) {
		name = "shift, ";
		istd_ignore_return(istd_strncpy_safe(res, res_size, name, strlen(name)));
	}

	if (mods & ISTD_KEY_MOD_CONTROL_BIT) {
		name = "control, ";
		istd_ignore_return(istd_strncat_safe(res, res_size, name, strlen(name)));
	}

	if (mods & ISTD_KEY_MOD_ALT_BIT) {
		name = "alt, ";
		istd_ignore_return(istd_strncat_safe(res, res_size, name, strlen(name)));
	}

	if (mods & ISTD_KEY_MOD_SUPER_BIT) {
		name = "super, ";
		istd_ignore_return(istd_strncat_safe(res, res_size, name, strlen(name)));
	}

	if (mods & ISTD_KEY_MOD_CAPS_LOCK_BIT) {
		name = "caps lock, ";
		istd_ignore_return(istd_strncat_safe(res, res_size, name, strlen(name)));
	}
	
	if (mods & ISTD_KEY_MOD_NUM_LOCK_BIT) {
		name = "num lock, ";
		istd_ignore_return(istd_strncat_safe(res, res_size, name, strlen(name)));
	}

	if (res[0] == 0) {
		name = "none";
		istd_ignore_return(istd_strncat_safe(res, res_size, name, strlen(name)));
	}

	return res;
}

static void istd_stdcall mouse_button_callback(istd_window window, istd_mouse_button button, istd_key_modifier_flags mods, bool down) {
	istd_unused_parameter(window);

	char* mod_str = convert_key_modifiers_to_cstring(mods);

	if (mod_str == istd_nullptr) 
		return;

	istd_println("Mouse button %s was %s, with key mods: %s", convert_mouse_button_to_cstring(button), down == true ? "pressed" : "released", mod_str);

	free(mod_str);
}

static void istd_stdcall mouse_entered_callback(istd_window window, bool entered) {
	istd_unused_parameter(window);
	istd_println("Mouse %s", entered == true ? "Entered" : "Exited");
}

static void istd_stdcall key_callback(istd_window window, istd_key key, istd_key_modifier_flags mods, bool down) {
	istd_unused_parameter(window);

	char* mod_str = convert_key_modifiers_to_cstring(mods);

	if (mod_str == istd_nullptr)
		return;

	istd_println("Key %zu was %s with key modifiers: %s", (uint64_t)key, down == true ? "pressed" : "released", mod_str);

	free(mod_str);

	if (key == ISTD_KEY_T)
		istd_println("Time since the window was created: %fs", istd_window_win32_get_time_ms((istd_window_win32)window) / 1000);


	if (key == ISTD_KEY_ESCAPE && mods == ISTD_KEY_MOD_NONE_BIT)
		istd_window_close(window);
}

static void istd_stdcall char_callback(istd_window window, char32_t character, istd_key_modifier_flags mods) {
	istd_unused_parameter(window);

	char* mod_str = convert_key_modifiers_to_cstring(mods);

	if (mod_str == istd_nullptr)
		return;

	istd_println("Character %lc was pressed with key mods: %s", character, mod_str);

	free(mod_str);
}

static void istd_stdcall dpi_callback(istd_window window, istd_vector2_i32 dpi) {
	istd_unused_parameter(window);

	istd_println("New monitor dpi: x -> %d, y -> %d", dpi.x, dpi.y);
}

static void istd_stdcall path_drop_callback(istd_window window, wchar_t** paths, size_t paths_size) {
	istd_unused_parameter(window);

	istd_println("Paths dropped:");

	for (size_t i = 0; i < paths_size; i++)
		istd_println("\t%S", paths[i]);
}

istd_test_msg istd_stdcall test_window(void) {
	istd_test_msg msg = { 0 };
	istd_window window = istd_window_create(L"Hello Window!", 800, 600, 100, 100);

	if (window == istd_nullptr) {
		msg.passed = false;
		msg.err_msg = "Window creation failed!";
		return msg;
	}
	
	istd_window_set_callback(window, (void*)window_move_callback, ISTD_CALLBACK_TYPE_WINDOW_MOVE);
	istd_window_set_callback(window, (void*)window_size_callback, ISTD_CALLBACK_TYPE_WINDOW_SIZE);
	istd_window_set_callback(window, (void*)framebuffer_size_callback, ISTD_CALLBACK_TYPE_FRAMEBUFFER_SIZE);
	istd_window_set_callback(window, (void*)window_iconified_callback, ISTD_CALLBACK_TYPE_WINDOW_ICONIFIED);
	istd_window_set_callback(window, (void*)window_maximized_callback, ISTD_CALLBACK_TYPE_WINDOW_MAXIMIZED);

	istd_window_set_callback(window, (void*)mouse_move_callback, ISTD_CALLBACK_TYPE_MOUSE_MOVE);
	istd_window_set_callback(window, (void*)mouse_scroll_callback, ISTD_CALLBACK_TYPE_MOUSE_SCROLL);
	istd_window_set_callback(window, (void*)mouse_button_callback, ISTD_CALLBACK_TYPE_MOUSE_BUTTON);
	istd_window_set_callback(window, (void*)mouse_entered_callback, ISTD_CALLBACK_TYPE_MOUSE_ENTERED);

	istd_window_set_callback(window, (void*)key_callback, ISTD_CALLBACK_TYPE_KEY);
	istd_window_set_callback(window, (void*)char_callback, ISTD_CALLBACK_TYPE_CHAR);

	istd_window_set_callback(window, (void*)dpi_callback, ISTD_CALLBACK_TYPE_DPI);

	istd_window_set_callback(window, (void*)path_drop_callback, ISTD_CALLBACK_TYPE_PATH_DROP);

	size_t monitor_count = 0;
	istd_monitor* monitors = istd_monitor_all(&monitor_count, istd_nullptr);
	for (size_t i = 0; i < monitor_count; i++) {
		istd_vector2_i32 size = istd_monitor_size(monitors[i]);
		istd_vector2_i32 position = istd_monitor_position(monitors[i]);
		istd_println("Monitor %d name: %S, x: %d, y: %d, width: %d, height: %d", i, istd_monitor_name(monitors[i]), position.x, position.y, size.width, size.height);

		#if defined(_WIN32)

		uintptr_t hmonitor = istd_monitor_win32_hmonitor((istd_monitor_win32)monitors[i]);

		istd_println("Monitor %d HMONITOR: 0x%"PRIxPTR , i, hmonitor);

		#endif
	}

	#if defined(_WIN32)

	uintptr_t hwnd = istd_window_win32_hwnd((istd_window_win32)window);
	uintptr_t hdc = istd_window_win32_hdc((istd_window_win32)window);
	uintptr_t hinstance = istd_window_win32_hinstance((istd_window_win32)window);

	istd_println("Window HWND: 0x%"PRIxPTR", Window HDC: 0x%"PRIxPTR", Window / Process HINSTANCE: 0x%"PRIxPTR, hwnd, hdc, hinstance);

	#endif

	while (istd_window_running(window)) {

		if (istd_window_key_down(window, ISTD_KEY_C, ISTD_KEY_MOD_NONE_BIT) == true)
			istd_window_center(window, monitors[0]);

		if (istd_window_key_down(window, ISTD_KEY_L, ISTD_KEY_MOD_NONE_BIT) == true && monitor_count > 1)
			istd_window_center(window, monitors[1]);

		if (istd_window_key_down(window, ISTD_KEY_J, ISTD_KEY_MOD_CONTROL_BIT) == true)
			istd_putln("Key J with key mod control was pressed!");

		istd_window_update(window);
	}

	istd_monitor_free(monitors, monitor_count);

	istd_window_free(window);

	msg.passed = true;

	return msg;
}
