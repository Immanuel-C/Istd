#if !defined(ISTD_WINDOW_MAX_H)
#define ISTD_WINDOW_MAX_H

#include "core.h"

ISTD_EXTERN_C

typedef enum {
    // Numbers dont have virtual key codes
    ISTD_KEY_0,
    ISTD_KEY_1,
    ISTD_KEY_2,
    ISTD_KEY_3,
    ISTD_KEY_4,
    ISTD_KEY_5,
    ISTD_KEY_6,
    ISTD_KEY_7,
    ISTD_KEY_8,
    ISTD_KEY_9,

    // Alphabet dont have virtual key codes
    ISTD_KEY_A,
    ISTD_KEY_B,
    ISTD_KEY_C,
    ISTD_KEY_D,
    ISTD_KEY_E,
    ISTD_KEY_F,
    ISTD_KEY_G,
    ISTD_KEY_H,
    ISTD_KEY_I,
    ISTD_KEY_J,
    ISTD_KEY_K,
    ISTD_KEY_L,
    ISTD_KEY_M,
    ISTD_KEY_N,
    ISTD_KEY_O,
    ISTD_KEY_P,
    ISTD_KEY_Q,
    ISTD_KEY_R,
    ISTD_KEY_S,
    ISTD_KEY_T,
    ISTD_KEY_U,
    ISTD_KEY_V,
    ISTD_KEY_W,
    ISTD_KEY_X,
    ISTD_KEY_Y,
    ISTD_KEY_Z,

    ISTD_KEY_BACK,
    ISTD_KEY_TAB,
    ISTD_KEY_ENTER,
    ISTD_KEY_PAUSE,
    ISTD_KEY_ESCAPE,
    ISTD_KEY_SPACE,
    ISTD_KEY_PAGEUP,
    ISTD_KEY_PAGEDOWN,
    ISTD_KEY_END,
    ISTD_KEY_HOME,
    ISTD_KEY_ARROW_LEFT,
    ISTD_KEY_ARROW_UP,
    ISTD_KEY_ARROW_RIGHT,
    ISTD_KEY_ARROW_DOWN,
    ISTD_KEY_PRINT_SCREEN,
    ISTD_KEY_INSERT,
    ISTD_KEY_DELETE,
    ISTD_KEY_ADD,
    ISTD_KEY_MULTIPLY,
    ISTD_KEY_SUBTRACT,
    ISTD_KEY_DECIMAL,
    ISTD_KEY_DIVIDE,
    ISTD_KEY_SCROLL_LOCK,
    ISTD_KEY_SEMICOLEN,
    ISTD_KEY_PLUS,
    ISTD_KEY_COMMA,
    ISTD_KEY_MINUS,
    ISTD_KEY_PERIOD,
    ISTD_KEY_FORWARD_SLASH,
    ISTD_KEY_TILDE,
    ISTD_KEY_LEFT_BOX_BRACES,
    ISTD_KEY_BACK_SLASH,
    ISTD_KEY_RIGHT_BOX_BRACES,
    ISTD_KEY_SINGLE_QUOTES,

    ISTD_KEY_LCONTROL,
    ISTD_KEY_RCONTROL,
    ISTD_KEY_LSHIFT,
    ISTD_KEY_RSHIFT,
    ISTD_KEY_LALT,
    ISTD_KEY_RALT,
    ISTD_KEY_LSUPER,
    ISTD_KEY_RSUPER,
    ISTD_KEY_CAPSLOCK,
    ISTD_KEY_NUMLOCK,

    ISTD_KEY_NUMPAD0,
    ISTD_KEY_NUMPAD1,
    ISTD_KEY_NUMPAD2,
    ISTD_KEY_NUMPAD3,
    ISTD_KEY_NUMPAD4,
    ISTD_KEY_NUMPAD5,
    ISTD_KEY_NUMPAD6,
    ISTD_KEY_NUMPAD7,
    ISTD_KEY_NUMPAD8,
    ISTD_KEY_NUMPAD9,

    ISTD_KEY_F1,
    ISTD_KEY_F2,
    ISTD_KEY_F3,
    ISTD_KEY_F4,
    ISTD_KEY_F5,
    ISTD_KEY_F6,
    ISTD_KEY_F7,
    ISTD_KEY_F8,
    ISTD_KEY_F9,
    ISTD_KEY_F10,
    ISTD_KEY_F11,
    ISTD_KEY_F12,

    ISTD_KEY_MAX
} istd_key;

typedef enum {
	ISTD_MOUSE_BUTTON_LEFT,
	ISTD_MOUSE_BUTTON_RIGHT,
	ISTD_MOUSE_BUTTON_MIDDLE,
	ISTD_MOUSE_BUTTON_SIDE1,
	ISTD_MOUSE_BUTTON_SIDE2,
	ISTD_MOUSE_BUTTON_MAX
} istd_mouse_button;

typedef enum {
	ISTD_KEY_MOD_NONE = 0x0,
	ISTD_KEY_MOD_SHIFT = 0x1,
	ISTD_KEY_MOD_CONTROL = 0x2,
	ISTD_KEY_MOD_ALT = 0x4,
	ISTD_KEY_MOD_SUPER = 0x8,
	ISTD_KEY_MOD_CAPS_LOCK = 0x10,
	ISTD_KEY_MOD_NUM_LOCK = 0x20,
	ISTD_KEY_MOD_MAX = 7
} istd_key_modifier;

typedef enum {
	ISTD_CALLBACK_TYPE_WINDOW_SIZE,
	ISTD_CALLBACK_TYPE_FRAMEBUFFER_SIZE,
	ISTD_CALLBACK_TYPE_WINDOW_MOVE,
	ISTD_CALLBACK_TYPE_WINDOW_ICONIFIED,
	ISTD_CALLBACK_TYPE_WINDOW_MAXIMIZED,

    ISTD_CALLBACK_TYPE_MOUSE_MOVE,
	ISTD_CALLBACK_TYPE_MOUSE_BUTTON,
	ISTD_CALLBACK_TYPE_MOUSE_SCROLL,
	ISTD_CALLBACK_TYPE_MOUSE_ENTERED,

	ISTD_CALLBACK_TYPE_KEY,
	ISTD_CALLBACK_TYPE_CHAR,

    ISTD_CALLBACK_TYPE_PATH_DROP,

	ISTD_CALLBACK_TYPE_MAX
} istd_callback_type;

ISTD_END_EXTERN_C

#endif