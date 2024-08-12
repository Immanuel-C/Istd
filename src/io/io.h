#if !defined(ISTD_IO_H)
#define ISTD_IO_H

#include "core.h"

#include <stdio.h>

ISTD_EXTERN_C

istd_api void istd_println(
	const char* fmt,
	...
);

istd_api void istd_fprintln(
	FILE* stream,
	const char* fmt,
	...
);

istd_api void istd_vprintln(
	const char* fmt,
	va_list list
);

istd_api void istd_vfprintln(
	FILE* stream,
	const char* fmt,
	va_list list
);

istd_api void istd_putln(
	const char* str
);

ISTD_END_EXTERN_C


#endif
