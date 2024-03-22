#include "thread_test.h"

#include "thread/thread.h"

#include <stdio.h>

typedef struct thread_info_t {
	uint64_t x, y, z, retval;
} thread_info;


static void* istd_stdcall thread_fun(void* arg) {
	thread_info* info = (thread_info*)arg;

	printf("Thread ID: %zu, x: %zu, y: %zu, z: %zu\n", (uint64_t)istd_thread_get_current_id(), info->x, info->y, info->z);

	info->retval = 50;

	return istd_nullptr;
}

istd_test_msg istd_stdcall test_thread(void) {
	istd_test_msg msg = { 0 };

	thread_info info = {
		.x = 10,
		.y = 50,
		.z = 100,
		.retval = 0
	};

	istd_thread thread = istd_thread_create(thread_fun, &info);

	if (thread == istd_nullhnd) {
		msg.passed = false;
		msg.err_msg = "istd_thread_create() failed to create a new thread";
		return msg;
	}

	istd_thread_join(thread);

	printf("Thread return value: %zu\n", info.retval);

	msg.passed = true;

	return msg;
}