#include "window_win32.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>
#include <shellapi.h>

#include <stdio.h>
#include "allocator/allocator.h"
#include "math/vector.h"

#include "window/window_enums.h"
#include "window/window_callbacks.h"

#include <stddef.h>
#include <time.h>

// Forces MSVC to not add padding
istd_pragma(pack(push, 1))
typedef struct {
	HWND hwnd;
	HDC hdc;
	HINSTANCE hinstance;
	const wchar_t* title;
	const wchar_t* class_name;
	istd_vector2_i32 size, framebuffer_size;
	istd_vector2_i32 position, mouse_position;
	istd_vector2_f32 scroll_offset;
	bool running;
	bool iconified;
	bool maximized;
	bool focused;
	bool mouse_entered;

	bool keys[(size_t)ISTD_KEY_MAX];
	bool mouse_buttons[(size_t)ISTD_MOUSE_BUTTON_MAX];

	void* user_ptr;

	istd_allocator allocator;
	
	istd_window_callbacks callbacks;

	clock_t time_created;
} __istd_window_win32;
istd_pragma(pack(pop))

LRESULT CALLBACK window_callback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

istd_key_modifier istd_stdcall __istd_window_win32_get_key_modifiers(void) {
	istd_key_modifier mods = ISTD_KEY_MOD_NONE;

	if (GetKeyState(VK_SHIFT) & 0x8000)
		mods |= ISTD_KEY_MOD_SHIFT;
	if (GetKeyState(VK_CONTROL) & 0x8000)
		mods |= ISTD_KEY_MOD_CONTROL;
	if (GetKeyState(VK_MENU) & 0x8000)
		mods |= ISTD_KEY_MOD_ALT;
	if ((GetKeyState(VK_LWIN) | GetKeyState(VK_RWIN)) & 0x8000)
		mods |= ISTD_KEY_MOD_SUPER;
	if (GetKeyState(VK_CAPITAL) & 1)
		mods |= ISTD_KEY_MOD_CAPS_LOCK;
	if (GetKeyState(VK_NUMLOCK) & 1)
		mods |= ISTD_KEY_MOD_NUM_LOCK;

	return mods;
}

_Check_return_ _Ret_maybenull_ _Success_(return != istd_nullhnd) istd_window_win32 istd_window_win32_create(
	_In_z_   const wchar_t* title,
	_In_	 int32_t width,
	_In_	 int32_t height,
	_In_	 int32_t x,
	_In_	 int32_t y,
	_In_opt_ istd_allocator* allocator
) {
	istd_allocator* alloc = allocator;

	if (alloc == istd_nullptr)
		alloc = istd_get_defualt_allocator();

	__istd_window_win32* window = alloc->malloc(sizeof(__istd_window_win32));

	if (window == istd_nullptr) return istd_nullhnd;

	window->title = title;
	window->size.width = width;
	window->size.height = height;
	window->framebuffer_size = window->size;
	window->position.x = x;
	window->position.y = y;
	window->mouse_position = (istd_vector2_i32){ 0 };
	window->scroll_offset = (istd_vector2_f32){ 0 };
	window->iconified = false;
	window->maximized = false;
	window->focused = false;
	window->mouse_entered = false;
	window->running = true;
	window->user_ptr = istd_nullptr;
	window->allocator = *alloc;

	window->callbacks = __istd_init_window_callbacks();

	window->class_name = L"istd_window";

	window->hinstance = (HINSTANCE)GetModuleHandleW(istd_nullptr);

	WNDCLASSEXW wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = window_callback;
	wc.hInstance = window->hinstance;
	wc.lpszClassName = window->class_name;
	wc.style = CS_OWNDC;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.hCursor = istd_nullptr;
	wc.hIcon = istd_nullptr;

	if (!RegisterClassExW(&wc)) {
		alloc->free(window);
		return istd_nullhnd;
	}

	window->hwnd = CreateWindowExW(
		WS_EX_APPWINDOW,
		(LPCWSTR)window->class_name,
		(LPCWSTR)title,
		WS_OVERLAPPEDWINDOW,
		(int)window->position.x,
		(int)window->position.y,
		(int)window->size.width,
		(int)window->size.height,
		istd_nullptr,
		istd_nullptr,
		window->hinstance,
		istd_nullptr
	);

	if (window->hwnd == istd_nullhnd) {
		alloc->free(window);
		UnregisterClassW(window->class_name, window->hinstance);
		return istd_nullhnd;
	}

	window->hdc = GetDC(window->hwnd);

	if (window->hdc == istd_nullptr) {
		alloc->free(window);
		UnregisterClassW(window->class_name, window->hinstance);
		DestroyWindow(window->hwnd);
		return istd_nullhnd;
	}

	DragAcceptFiles(window->hwnd, TRUE); 

	SetWindowLongPtrW(window->hwnd, GWLP_USERDATA, (LONG_PTR)window);

	ShowWindow(window->hwnd, TRUE);

	window->time_created = clock();

	return (istd_window_win32)window;
}

_Check_return_ bool istd_window_win32_running(
	_In_ istd_window_win32 window
) {
	return ((__istd_window_win32*)window)->running;
}

void istd_stdcall istd_window_win32_update(
	_In_ istd_window_win32 window
) {
	MSG msg = { 0 };

	__istd_window_win32* _window = (__istd_window_win32*)window;

	while (PeekMessageW(&msg, _window->hwnd, 0, 0, PM_REMOVE)) {
		istd_ignore_return(TranslateMessage(&msg));
		istd_ignore_return(DispatchMessageW(&msg));
	}
}

void istd_window_win32_wait_event(
	_In_ istd_window_win32 window
) {
	istd_ignore_return(WaitMessage());
	istd_window_win32_update(window);
}

void istd_window_win32_close(
	_In_ istd_window_win32 window
) {
	__istd_window_win32* _window = (__istd_window_win32*)window;
	_window->running = false;
}

_Success_(return == istd_nullptr) _Ret_maybenull_ void* istd_window_win32_set_callback(
	_Inout_ istd_window_win32 window,
	_In_    void* callback_fun,
	_In_    int callback_type
) {
	__istd_window_win32* _window = (__istd_window_win32*)window;

	void* old_callback = istd_nullptr;

	switch (callback_type) {
		case ISTD_CALLBACK_TYPE_WINDOW_SIZE:
			old_callback = (void*)_window->callbacks.window_size;
			_window->callbacks.window_size = (istd_pfn_window_size_callback)callback_fun;
			break;

		case ISTD_CALLBACK_TYPE_FRAMEBUFFER_SIZE:
			old_callback = (void*)_window->callbacks.framebuffer_size;
			_window->callbacks.framebuffer_size = (istd_pfn_framebuffer_size_callback)callback_fun;
			break; 

		case ISTD_CALLBACK_TYPE_WINDOW_MOVE:
			old_callback = (void*)_window->callbacks.window_move;
			_window->callbacks.window_move = (istd_pfn_window_move_callback)callback_fun;
			break;

		case ISTD_CALLBACK_TYPE_WINDOW_ICONIFIED:
			old_callback = (void*)_window->callbacks.window_iconified;
			_window->callbacks.window_iconified = (istd_pfn_iconified_callback)callback_fun;
			break;

		case ISTD_CALLBACK_TYPE_WINDOW_MAXIMIZED:
			old_callback = (void*)_window->callbacks.window_maximized;
			_window->callbacks.window_maximized = (istd_pfn_maximized_callback)callback_fun;
			break;

		case ISTD_CALLBACK_TYPE_MOUSE_MOVE:
			old_callback = (void*)_window->callbacks.mouse_move;
			_window->callbacks.mouse_move = (istd_pfn_mouse_move_callback)callback_fun;
			break;

		case ISTD_CALLBACK_TYPE_MOUSE_BUTTON:
			old_callback = (void*)_window->callbacks.mouse_button;
			_window->callbacks.mouse_button = (istd_pfn_mouse_button_callback)callback_fun;
			break;

		case ISTD_CALLBACK_TYPE_MOUSE_SCROLL:
			old_callback = (void*)_window->callbacks.mouse_scroll;
			_window->callbacks.mouse_scroll = (istd_pfn_mouse_scroll_callback)callback_fun;
			break;

		case ISTD_CALLBACK_TYPE_MOUSE_ENTERED:
			old_callback = (void*)_window->callbacks.mouse_entered;
			_window->callbacks.mouse_entered = (istd_pfn_mouse_entered_callback)callback_fun;
			break;

		case ISTD_CALLBACK_TYPE_KEY:
			old_callback = (void*)_window->callbacks.key;
			_window->callbacks.key = (istd_pfn_key_callback)callback_fun;
			break;

		case ISTD_CALLBACK_TYPE_CHAR:
			old_callback = (void*)_window->callbacks.character;
			_window->callbacks.character = (istd_pfn_char_callback)callback_fun;
			break;

		case ISTD_CALLBACK_TYPE_PATH_DROP:
			old_callback = (void*)_window->callbacks.path_drop;
			_window->callbacks.path_drop = (istd_pfn_path_drop_callback)callback_fun;
			break;

	default:
		return istd_nullptr;
	}

	return old_callback;
}

istd_vector2_i32 istd_window_win32_size(
	_In_ istd_window_win32 window
) {
	return ((__istd_window_win32*)window)->size;
}

istd_vector2_i32 istd_window_win32_position(
	_In_ istd_window_win32 window
) {
	return ((__istd_window_win32*)window)->position;
}

istd_vector2_f32 istd_window_win32_mouse_scroll_offset(
	_In_ istd_window_win32 window
) {
	return ((__istd_window_win32*)window)->scroll_offset;
}

istd_vector2_i32 istd_window_win32_mouse_position(
	_In_ istd_window_win32 window
) {
	return ((__istd_window_win32*)window)->mouse_position;
}

bool istd_window_win32_mouse_button_down(
	_In_ istd_window_win32 window,
	_In_ istd_mouse_button button,
	_In_ istd_key_modifier mods
) {
	return (((__istd_window_win32*)window)->mouse_buttons[(size_t)button] == true) && ((__istd_window_win32_get_key_modifiers() & mods) == mods);
}


bool istd_window_win32_key_down(
	_In_ istd_window_win32 window,
	_In_ istd_key key,
	_In_ istd_key_modifier mods
) {
	return (((__istd_window_win32*)window)->keys[(size_t)key] == true) && ((__istd_window_win32_get_key_modifiers() & mods) == mods);
}

istd_key istd_window_win32_convert_vk_key_code_to_istd_key(
	_In_ int32_t vk_key_code
) {
    switch (vk_key_code)
    {
    case 48:
        return ISTD_KEY_0;
    case 49:
        return ISTD_KEY_1;
    case 50:
        return ISTD_KEY_2;
    case 51:
        return ISTD_KEY_3;
    case 52:
        return ISTD_KEY_4;
    case 53:
        return ISTD_KEY_5;
    case 54:
        return ISTD_KEY_6;
    case 55:
        return ISTD_KEY_7;
    case 56:
        return ISTD_KEY_8;
    case 57:
        return ISTD_KEY_9;
    case 65:
        return ISTD_KEY_A;
    case 66:
        return ISTD_KEY_A;
    case 67:
        return ISTD_KEY_C;
    case 68:
        return ISTD_KEY_D;
    case 69:
        return ISTD_KEY_E;
    case 70:
        return ISTD_KEY_F;
    case 71:
        return ISTD_KEY_G;
    case 72:
        return ISTD_KEY_H;
    case 73:
        return ISTD_KEY_I;
    case 74:
        return ISTD_KEY_J;
    case 75:
        return ISTD_KEY_K;
    case 76:
        return ISTD_KEY_L;
    case 77:
        return ISTD_KEY_M;
    case 78:
        return ISTD_KEY_N;
    case 79:
        return ISTD_KEY_O;
    case 80:
        return ISTD_KEY_P;
    case 81:
        return ISTD_KEY_Q;
    case 82:
        return ISTD_KEY_R;
    case 83:
        return ISTD_KEY_S;
    case 84:
        return ISTD_KEY_T;
    case 85:
        return ISTD_KEY_U;
    case 86:
        return ISTD_KEY_V;
    case 87:
        return ISTD_KEY_W;
    case 88:
        return ISTD_KEY_X;
    case 89:
        return ISTD_KEY_Y;
    case 90:
        return ISTD_KEY_Z;
    case VK_BACK:
        return ISTD_KEY_BACK;
    case VK_TAB:
        return ISTD_KEY_TAB;
    case VK_RETURN:
        return ISTD_KEY_ENTER;
    case VK_PAUSE:
        return ISTD_KEY_PAUSE;
    case VK_ESCAPE:
        return ISTD_KEY_ESCAPE;
    case VK_SPACE:
        return ISTD_KEY_SPACE;
    case VK_PRIOR:
        return ISTD_KEY_PAGEUP;
    case VK_NEXT:
        return ISTD_KEY_PAGEDOWN;
    case VK_END:
        return ISTD_KEY_END;
    case VK_HOME:
        return ISTD_KEY_HOME;
    case VK_LEFT:
        return ISTD_KEY_ARROW_LEFT;
    case VK_UP:
        return ISTD_KEY_ARROW_UP;
    case VK_RIGHT:
        return ISTD_KEY_ARROW_RIGHT;
    case VK_DOWN:
        return ISTD_KEY_ARROW_DOWN;
    case VK_SNAPSHOT:
        return ISTD_KEY_PRINT_SCREEN;
    case VK_INSERT:
        return ISTD_KEY_INSERT;
    case VK_DELETE:
        return ISTD_KEY_DELETE;
    case VK_ADD:
        return ISTD_KEY_ADD;
    case VK_MULTIPLY:
        return ISTD_KEY_MULTIPLY;
    case VK_SUBTRACT:
        return ISTD_KEY_SUBTRACT;
    case VK_DECIMAL:
        return ISTD_KEY_DECIMAL;
    case VK_DIVIDE:
        return ISTD_KEY_DIVIDE;
    case VK_SCROLL:
        return ISTD_KEY_SCROLL_LOCK;
    case VK_OEM_1:
        return ISTD_KEY_SEMICOLEN;
    case VK_OEM_PLUS:
        return ISTD_KEY_PLUS;
    case VK_OEM_COMMA:
        return ISTD_KEY_COMMA;
    case VK_OEM_MINUS:
        return ISTD_KEY_MINUS;
    case VK_OEM_PERIOD:
        return ISTD_KEY_PERIOD;
    case VK_OEM_2:
        return ISTD_KEY_FORWARD_SLASH;
    case VK_OEM_3:
        return ISTD_KEY_TILDE;
    case VK_OEM_4:
        return ISTD_KEY_LEFT_BOX_BRACES;
    case VK_OEM_5:
        return ISTD_KEY_BACK_SLASH;
    case VK_OEM_6:
        return ISTD_KEY_RIGHT_BOX_BRACES;
    case VK_OEM_7:
        return ISTD_KEY_SINGLE_QUOTES;
    case VK_NUMPAD0:
        return ISTD_KEY_NUMPAD0;
    case VK_NUMPAD1:
        return ISTD_KEY_NUMPAD1;
    case VK_NUMPAD2:
        return ISTD_KEY_NUMPAD2;
    case VK_NUMPAD3:
        return ISTD_KEY_NUMPAD3;
    case VK_NUMPAD4:
        return ISTD_KEY_NUMPAD4;
    case VK_NUMPAD5:
        return ISTD_KEY_NUMPAD5;
    case VK_NUMPAD6:
        return ISTD_KEY_NUMPAD6;
    case VK_NUMPAD7:
        return ISTD_KEY_NUMPAD7;
    case VK_NUMPAD8:
        return ISTD_KEY_NUMPAD8;
    case VK_NUMPAD9:
        return ISTD_KEY_NUMPAD9;
    case VK_F1:
        return ISTD_KEY_F1;
    case VK_F2:
        return ISTD_KEY_F2;
    case VK_F3:
        return ISTD_KEY_F3;
    case VK_F4:
        return ISTD_KEY_F4;
    case VK_F5:
        return ISTD_KEY_F5;
    case VK_F6:
        return ISTD_KEY_F6;
    case VK_F7:
        return ISTD_KEY_F7;
    case VK_F8:
        return ISTD_KEY_F8;
    case VK_F9:
        return ISTD_KEY_F9;
    case VK_F10:
        return ISTD_KEY_F10;
    case VK_F11:
        return ISTD_KEY_F11;
    case VK_F12:
        return ISTD_KEY_F12;
    case VK_LCONTROL:
        return ISTD_KEY_LCONTROL;
    case VK_RCONTROL:
        return ISTD_KEY_RCONTROL;
    case VK_LMENU:
        return ISTD_KEY_LALT;
    case VK_RMENU:
        return ISTD_KEY_RALT;
    case VK_LSHIFT:
        return ISTD_KEY_LSHIFT;
    case VK_RSHIFT:
        return ISTD_KEY_RSHIFT;
    case VK_LWIN:
        return ISTD_KEY_LSUPER;
    case VK_RWIN:
        return ISTD_KEY_RSUPER;
    case VK_CAPITAL:
        return ISTD_KEY_CAPSLOCK;
    case VK_NUMLOCK:
        return ISTD_KEY_NUMLOCK;
    default:
        // key code not supported by istd_window
        return ISTD_KEY_MAX;
    }
}

void  istd_window_win32_set_user_ptr(
	_In_ istd_window_win32 window,
	_In_ void* ptr
) {
	((__istd_window_win32*)window)->user_ptr = ptr;
}

_Ret_maybenull_ void* istd_window_win32_get_user_ptr(
	_In_ istd_window_win32 window
) {
	return ((__istd_window_win32*)window)->user_ptr;
}

istd_float64 istd_window_win32_get_time_ms(
	_In_ istd_window_win32 window
) {
	return ((istd_float64)(clock() - ((__istd_window_win32*)window)->time_created) / CLOCKS_PER_SEC) * 1000;
}

void istd_window_win32_free(
	_Pre_valid_ _Post_invalid_ istd_window_win32 window
) {
	__istd_window_win32* _window = (__istd_window_win32*)window;

	istd_ignore_return(ReleaseDC(_window->hwnd, _window->hdc));
	istd_ignore_return(UnregisterClassW(_window->class_name, _window->hinstance));
	istd_ignore_return(DestroyWindow(_window->hwnd));

	_window->allocator.free(_window);
}

static LRESULT CALLBACK window_callback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	__istd_window_win32* window = (__istd_window_win32*)GetWindowLongPtrW(hwnd, GWLP_USERDATA);

	if (window == istd_nullptr)
		return DefWindowProc(hwnd, msg, wparam, lparam);

	switch (msg)
	{
		case WM_CLOSE: {
			window->running = false;
			return 0;
		}

		case WM_NCCREATE:
			// If 0 is returned CreateWindowEx will return null.
			// Istd window depends on this.
			if (EnableNonClientDpiScaling(window->hwnd) == FALSE)
				return 0;

			break;
		case WM_MOVE: {
			window->position.x = (int32_t)GET_X_LPARAM(lparam);
			window->position.y = (int32_t)GET_Y_LPARAM(lparam);

			window->callbacks.window_move((istd_window)window, window->position);

			return 0;
		}

		case WM_SIZE: {
			bool iconified = wparam == SIZE_MINIMIZED ? true : false;
			bool maximized = wparam == SIZE_MAXIMIZED ? true : false;

			if (window->iconified != iconified) {
				window->iconified = iconified;
				window->callbacks.window_iconified((istd_window)window, window->iconified);
			}

			if (window->maximized != maximized) {
				window->maximized = maximized;
				window->callbacks.window_maximized((istd_window)window, window->maximized);
			}

			// On windows the client area is already adjusted for high dpi displays.
			window->size.width = (int32_t)LOWORD(lparam);
			window->size.height = (int32_t)HIWORD(lparam);
			window->framebuffer_size = window->size;

			window->callbacks.window_size((istd_window)window, window->size);
			window->callbacks.framebuffer_size((istd_window)window, window->framebuffer_size);
	
			return 0;
		}

		case WM_MOUSEMOVE: {
			// Tell Win32 to post a message if the cursor leaves this window
			if (window->mouse_entered == false) {
				TRACKMOUSEEVENT mouse_event = { 0 };
				mouse_event.cbSize = sizeof(mouse_event);
				mouse_event.dwFlags = TME_LEAVE;
				mouse_event.hwndTrack = window->hwnd;
				istd_ignore_return(TrackMouseEvent(&mouse_event));

				window->mouse_entered = true;

				window->callbacks.mouse_entered((istd_window)window, window->mouse_entered);
			}

			window->mouse_position.x = (int32_t)GET_X_LPARAM(lparam);
			window->mouse_position.y = (int32_t)GET_Y_LPARAM(lparam);

			window->callbacks.mouse_move((istd_window)window, window->mouse_position);

			return 0;
		}

		case WM_MOUSELEAVE: {
			window->mouse_entered = false;
			window->callbacks.mouse_entered((istd_window)window, window->mouse_entered);

			return 0;
		}

		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_KEYUP:
		case WM_KEYDOWN: {
			const bool down = (HIWORD(lparam) & KF_UP) ? false : true;
			istd_key_modifier mods = __istd_window_win32_get_key_modifiers();
			int32_t repeat = (HIWORD(lparam) & KF_REPEAT);
			istd_unused_parameter(repeat);
			uint32_t scanCode = ((lparam & 0x00ff0000) >> 16);
			// KF_EXTENDED broken wtf Win32!?
			bool extented = (lparam & 0x01000000) != 0;

			istd_key key = istd_window_win32_convert_vk_key_code_to_istd_key((int32_t)wparam);

			if (key == ISTD_KEY_MAX) {
				if (!extented && wparam == VK_MENU) key = ISTD_KEY_LALT;
				if (extented && wparam == VK_MENU) key = ISTD_KEY_RALT;
				if (!extented && wparam == VK_CONTROL) key = ISTD_KEY_LCONTROL;
				if (extented && wparam == VK_CONTROL) key = ISTD_KEY_RCONTROL;
				if (wparam == VK_SHIFT) {
					WPARAM mappedCode = MapVirtualKeyW(scanCode, MAPVK_VSC_TO_VK_EX);
					key = mappedCode == VK_LSHIFT ? ISTD_KEY_LSHIFT : ISTD_KEY_RSHIFT;
				}
			}

			// Unsupported Key
			if (key == ISTD_KEY_MAX) break;

			window->keys[(size_t)key] = down;

			// Auto iconify if super key is pressed and window is fullscreen.
			if ((key == ISTD_KEY_LSUPER || key == ISTD_KEY_RSUPER) && (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN) /* && window->fullscreen */)
				ShowWindow(window->hwnd, SW_MINIMIZE);

			window->callbacks.key((istd_window)window, key, mods, down);

			return 0;
		}

		case WM_SYSCOMMAND: {
			// Check if alt/alt + something was pressed usually this is a system command that is reserved to focus the menu but we want control over alt so we override it.
			if (wparam == SC_KEYMENU && HIWORD(lparam) <= 0)
				return 0;

			break;
		}

		case WM_UNICHAR:
		case WM_SYSCHAR:
		case WM_CHAR: {
			if (wparam == UNICODE_NOCHAR && msg == WM_UNICHAR) {
				// Not sent by windows but by a third party.
				return 1;
			}

			// Dont input char if its backspace, ...
			if (wparam < 32 || (wparam > 126 && wparam < 160))
				return 0;

			window->callbacks.character((istd_window)window, (char32_t)wparam, __istd_window_win32_get_key_modifiers());

			return 0;
		}

		case WM_MOUSEWHEEL: 
		case WM_MOUSEHWHEEL: {
			if (msg == WM_MOUSEWHEEL) {
				window->scroll_offset.x = 0.0f;
				window->scroll_offset.y = (istd_float32)(GET_WHEEL_DELTA_WPARAM(wparam) / WHEEL_DELTA);
			}
			else {
				// Inverted to keep constistancy with X11.
				window->scroll_offset.x = -((istd_float32)(GET_WHEEL_DELTA_WPARAM(wparam) / WHEEL_DELTA));
				window->scroll_offset.y = 0.0f;
			}

			window->callbacks.mouse_scroll((istd_window)window, window->scroll_offset);

			return 0;
		}

		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_XBUTTONDOWN:
		case WM_XBUTTONUP: {
			istd_mouse_button button = 0;
			istd_key_modifier mods = __istd_window_win32_get_key_modifiers();
			bool down = false;

			if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP) button = ISTD_MOUSE_BUTTON_LEFT;
			else if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP) button = ISTD_MOUSE_BUTTON_RIGHT;
			else if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP) button = ISTD_MOUSE_BUTTON_MIDDLE;
			else if (GET_XBUTTON_WPARAM(wparam) == XBUTTON1) button = ISTD_MOUSE_BUTTON_SIDE1;
			else button = ISTD_MOUSE_BUTTON_SIDE2;

			if (msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_MBUTTONDOWN || msg == WM_XBUTTONDOWN)
				down = true;

			window->mouse_buttons[(size_t)button] = down;

			window->callbacks.mouse_button((istd_window)window, button, mods, down);

			if (msg == WM_XBUTTONDOWN || msg == WM_XBUTTONUP)
				return 1;

			return 0;
		}

		case WM_DROPFILES: {
			HDROP drop = (HDROP)wparam;
			POINT mouse_pos = { 0 };

			if (DragQueryPoint(drop, &mouse_pos) == FALSE)
				break;

			window->mouse_position.x = mouse_pos.x;
			window->mouse_position.y = mouse_pos.y;

			window->callbacks.mouse_move((istd_window)window, window->mouse_position);

			const uint32_t file_count = (uint32_t)DragQueryFileW(drop, (UINT)UINT32_MAX, istd_nullptr, 0);
			wchar_t** paths = window->allocator.malloc(file_count * sizeof(wchar_t*));

			if (paths == istd_nullptr)
				break;

			for (uint32_t i = 0; i < file_count; i++) {
				const uint32_t length = DragQueryFileW(drop, i, istd_nullptr, 0);
				// We set the size to length plus one since the length does not include the null terminator
				paths[i] = window->allocator.malloc((length + 1) * sizeof(wchar_t));

				if (paths[i] == istd_nullptr) {
					window->allocator.free(paths);
				
					for (uint32_t y = 0; y < i; y++)
						window->allocator.free(paths[y]);

					break;
				}

				istd_ignore_return(DragQueryFileW(drop, i, paths[i], length + 1));
			}

			window->callbacks.path_drop((istd_window)window, paths, (size_t)file_count);

			for (uint32_t i = 0; i < file_count; i++) 
				window->allocator.free(paths[i]);

			window->allocator.free(paths);

			DragFinish(drop);

			return 0;
		}

	}

	return DefWindowProcW(window->hwnd, msg, wparam, lparam);
}