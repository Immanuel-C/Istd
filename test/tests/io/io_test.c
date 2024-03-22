#include "io_test.h"

#include "io/io.h"

#include <stdio.h>

istd_test_msg istd_stdcall test_io(void) {
	istd_test_msg msg = { 0 };

	istd_println("Test println -> %i", 124124532);
	istd_vprintln("Test vprintln", istd_nullptr);
	istd_vfprintln(stderr, "Test vfprintln", istd_nullptr);
	istd_putln("Test putln");

	msg.passed = true;

	return msg;
}