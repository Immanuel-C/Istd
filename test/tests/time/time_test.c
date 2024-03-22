#include "time_test.h"

#include "time/high_resolution.h"
#include "time/time.h"
#include "thread/thread.h"

#include "istd_float.h"

#include <stdio.h>


istd_test_msg istd_stdcall test_time(void) {
	istd_test_msg msg = { 0 };

	istd_timer timer = istd_timer_start();

	if (timer == istd_nullhnd) {
		msg.passed = false;
		msg.err_msg = "Failed to start a timer";
		return msg;
	}

	istd_this_thread_sleep(500);

	double now_ms = istd_timer_now(timer, ISTD_MILISECONDS);

	printf("Time elapsed: %.4fms\n", now_ms);

	istd_this_thread_sleep(100);

	double elasped_time = istd_timer_end(timer, ISTD_SECONDS);

	printf("Time elapsed: %.4fs\n", elasped_time);

	printf("Time since computer started: %fms\n", (istd_float64)(istd_high_resolution_now_ns() / 1000000));

	msg.passed = true;
	return msg;
}