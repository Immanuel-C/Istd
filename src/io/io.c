#include "io.h"

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <safe/string_safe.h>

void istd_println(
	_In_z_ const char* fmt,
	_In_ ...
) {
	va_list list = istd_nullptr;

	va_start(list, fmt);

	istd_vfprintln(stdout, fmt, list);

	va_end(list);
}

void istd_fprintln(
	_In_ FILE* stream,
	_In_z_ const char* fmt,
	_In_ ...
) {
	va_list list = istd_nullptr;

	va_start(list, fmt);

	istd_vfprintln(stream, fmt, list);

	va_end(list);
}

void istd_vprintln(
	_In_z_ const char* fmt,
	_In_ va_list list
) {
	istd_vfprintln(stdout, fmt, list);
}

void istd_vfprintln(
	_In_ FILE* stream,
	_In_z_ const char* fmt,
	_In_ va_list list
) {
	// Add two for null terminator and new line characters
	size_t fmt_with_new_line_size = strlen(fmt) + 2;
	char* fmt_with_new_line = malloc(fmt_with_new_line_size * sizeof(char));

	if (fmt_with_new_line == istd_nullptr)
		return;

	istd_ignore_return(istd_strcpy_safe(fmt_with_new_line, fmt_with_new_line_size, fmt));

	const char* new_line = "\n";
	istd_ignore_return(istd_strcat_safe(fmt_with_new_line, fmt_with_new_line_size, new_line));

	istd_ignore_return(vfprintf(stream, fmt_with_new_line, list));

	free(fmt_with_new_line);
}

istd_api void istd_stdcall istd_putln(
	_In_z_ const char* str
) {
	// Add two for null terminator and new line characters
	size_t str_with_new_line_size = strlen(str) + 2;
	char* str_with_new_line = malloc(str_with_new_line_size * sizeof(char));

	if (str_with_new_line == istd_nullptr)
		return;

	istd_ignore_return(istd_strcpy_safe(str_with_new_line, str_with_new_line_size, str));

	const char* new_line = "\n";
	istd_ignore_return(istd_strcat_safe(str_with_new_line, str_with_new_line_size, new_line));


	istd_ignore_return(puts(str_with_new_line));

	free(str_with_new_line);
}