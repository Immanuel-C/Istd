#if !defined(ISTD_WINDOW_H)
#define ISTD_WINDOW_H

#include "core.h"
#include "window_enums.h"
#include "math/vector.h"
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

istd_api void istd_stdcall istd_window_free(
	_Pre_valid_ _Post_invalid_ istd_window window
);


ISTD_END_EXTERN_C

#endif