#if !defined(ISTD_WINDOW_CALLBACK_H)
#define ISTD_WINDOW_CALLBACK_H

#include "core.h"
#include "math\vector.h"
#include "window_enums.h"

#include <stdint.h>
#include <uchar.h>

ISTD_EXTERN_C

istd_define_handle(istd_window);

typedef void (* istd_pfn_window_size_callback)(istd_window, istd_vector2_i32);
typedef void (* istd_pfn_iconified_callback)(istd_window, bool);
typedef istd_pfn_window_size_callback istd_pfn_framebuffer_size_callback;
typedef istd_pfn_window_size_callback istd_pfn_window_move_callback;
typedef istd_pfn_iconified_callback istd_pfn_maximized_callback;

typedef istd_pfn_window_size_callback istd_pfn_mouse_move_callback;
typedef void (* istd_pfn_mouse_scroll_callback)(istd_window, istd_vector2_f32);
typedef void (* istd_pfn_mouse_button_callback)(istd_window, istd_mouse_button, istd_key_modifier_flags, bool);
typedef istd_pfn_iconified_callback istd_pfn_mouse_entered_callback;

typedef void (* istd_pfn_key_callback)(istd_window, istd_key, istd_key_modifier_flags, bool);
typedef void (* istd_pfn_char_callback)(istd_window, char32_t, istd_key_modifier_flags);

typedef istd_pfn_window_size_callback istd_pfn_dpi_callback;

typedef void (* istd_pfn_path_drop_callback)(istd_window, wchar_t**, size_t);

static void istd_defualt_window_size_callback(istd_window window, istd_vector2_i32 size) { 
	istd_unused_parameter(window);
	istd_unused_parameter(size);
}

static void istd_defualt_framebuffer_size_callback(istd_window window, istd_vector2_i32 size) {
	istd_unused_parameter(window);
	istd_unused_parameter(size);
}

static void istd_defualt_window_move_callback(istd_window window, istd_vector2_i32 position) {
	istd_unused_parameter(window);
	istd_unused_parameter(position);
}

static void istd_defualt_window_iconified_callback(istd_window window, bool iconified) {
	istd_unused_parameter(window);
	istd_unused_parameter(iconified);
}

static void istd_defualt_window_maximized_callback(istd_window window, bool maximized) {
	istd_unused_parameter(window);
	istd_unused_parameter(maximized);
}

static void istd_defualt_mouse_move_callback(istd_window window, istd_vector2_i32 position) {
	istd_unused_parameter(window);
	istd_unused_parameter(position);
}

static void istd_defualt_mouse_scroll_callback(istd_window window, istd_vector2_f32 scroll_offset) {
	istd_unused_parameter(window);
	istd_unused_parameter(scroll_offset);
}

static void istd_defualt_mouse_button_callback(istd_window window, istd_mouse_button button, istd_key_modifier_flags mods, bool down) {
	istd_unused_parameter(window);
	istd_unused_parameter(button);
	istd_unused_parameter(mods);
	istd_unused_parameter(down);
}

static void istd_defualt_mouse_entered_callback(istd_window window, bool entered) {
	istd_unused_parameter(window);
	istd_unused_parameter(entered);
}

static void istd_defualt_key_callback(istd_window window, istd_key key, istd_key_modifier_flags mods, bool down) {
	istd_unused_parameter(window);
	istd_unused_parameter(key);
	istd_unused_parameter(mods);
	istd_unused_parameter(down);
}

static void istd_defualt_char_callback(istd_window window, char32_t character, istd_key_modifier_flags mods) {
	istd_unused_parameter(window);
	istd_unused_parameter(character);
	istd_unused_parameter(mods);
}

static void istd_defualt_dpi_callback(istd_window window, istd_vector2_i32 new_dpi) {
	istd_unused_parameter(window);
	istd_unused_parameter(new_dpi);
}

static void istd_defualt_path_drop_callback(istd_window window, wchar_t** paths, size_t paths_size) {
	istd_unused_parameter(window);
	istd_unused_parameter(paths);
	istd_unused_parameter(paths_size);
}

typedef struct {
	/**
	* Window Callbacks
	*/
	istd_pfn_window_size_callback window_size;
	istd_pfn_framebuffer_size_callback framebuffer_size;
	istd_pfn_window_move_callback window_move;
	istd_pfn_iconified_callback window_iconified;
	istd_pfn_maximized_callback window_maximized;
	/**
	* Mouse Callbacks
	*/
	istd_pfn_mouse_move_callback mouse_move;
	istd_pfn_mouse_scroll_callback mouse_scroll;
	istd_pfn_mouse_button_callback mouse_button;
	istd_pfn_mouse_entered_callback mouse_entered;
	/**
	* Key Callbacks
	*/
	istd_pfn_key_callback key;
	istd_pfn_char_callback character;
	/**
	* Monitor/Window Callbacks
	*/
	istd_pfn_dpi_callback dpi;
	/**
	* Other Callbacks
	*/
	istd_pfn_path_drop_callback path_drop;

} istd_window_callbacks;

static istd_window_callbacks __istd_init_window_callbacks(void) {
	istd_window_callbacks callbacks = { 0 };

	callbacks.window_size = istd_defualt_window_size_callback;
	callbacks.framebuffer_size = istd_defualt_framebuffer_size_callback;
	callbacks.window_move = istd_defualt_window_move_callback;
	callbacks.window_iconified = istd_defualt_window_iconified_callback;
	callbacks.window_maximized = istd_defualt_window_maximized_callback;

	callbacks.mouse_move = istd_defualt_mouse_move_callback;
	callbacks.mouse_scroll = istd_defualt_mouse_scroll_callback;
	callbacks.mouse_button = istd_defualt_mouse_button_callback;
	callbacks.mouse_entered = istd_defualt_mouse_entered_callback;

	callbacks.key = istd_defualt_key_callback;
	callbacks.character = istd_defualt_char_callback;

	callbacks.dpi = istd_defualt_dpi_callback;

	callbacks.path_drop = istd_defualt_path_drop_callback;

	return callbacks;
}

ISTD_END_EXTERN_C

#endif
