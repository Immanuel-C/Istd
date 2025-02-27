#include "test/test.h"
#include "tests/unordered_map/unordered_map_test.h"
#include "tests/thread/thread_test.h"
#include "tests/time/time_test.h"
#include "tests/linked_list/linked_list_test.h"
#include "tests/dynamic_array/dynamic_array_test.h"

#include <image/image.h>
#include <allocator/allocator.h>

#include <stdio.h>

int main(void) {
	istd_test(test_dynamic_array, "Dynamic Array");
	istd_test(test_linked_list, "Linked List");
	istd_test(test_time, "Timer/High Resolution");
	istd_test(test_thread, "Thread");
	istd_test(test_unordered_map, "Unordered Map");

	return 0;
}
