#if !defined(ISTD_IO_H)
#define ISTD_IO_H

#include "core.h"

#include <stdio.h>

ISTD_EXTERN_C

istd_api void istd_cdecl istd_println(
	_In_z_ const char* fmt,
	_In_ ...
);

istd_api void istd_cdecl istd_fprintln(
	_In_ FILE* stream,
	_In_z_ const char* fmt,
	_In_ ...
);

istd_api void istd_cdecl istd_vprintln(
	_In_z_ const char* fmt,
	_In_ va_list list
);

istd_api void istd_cdecl istd_vfprintln(
	_In_ FILE* stream,
	_In_z_ const char* fmt,
	_In_ va_list list
);

istd_api void istd_stdcall istd_putln(
	_In_z_ const char* str
);

ISTD_END_EXTERN_C


#endif