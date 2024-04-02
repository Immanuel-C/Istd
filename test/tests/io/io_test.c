#include "io_test.h"

#include "io/io.h"

#include <stdio.h>
#include <stdarg.h>

void test_vprintln(const char* fmt, ...) {
	va_list list = istd_nullptr;
	va_start(list, fmt);

	istd_vprintln(fmt, list);

	va_end(list);
}

void test_vfprintln(FILE* stream, const char* fmt, ...) {
	va_list list = istd_nullptr;
	va_start(list, fmt);

	istd_vfprintln(stream, fmt, list);

	va_end(list);
}

istd_test_msg istd_stdcall test_io(void) {
	istd_test_msg msg = { 0 };

	istd_println("Test println -> %d", 124124532);
	test_vprintln("Test istd_vprintln -> 0x%x", 0x1234);
	test_vfprintln(stderr, "Test vfprintln -> %s", "output stream: stderr");
	istd_putln("Test putln");

	msg.passed = true;

	return msg;
}