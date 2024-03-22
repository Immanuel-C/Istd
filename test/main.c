#include "test/test.h"
#include "tests/window/window_test.h"
#include "tests/unordered_map/unordered_map_test.h"
#include "tests/thread/thread_test.h"
#include "tests/time/time_test.h"
#include "tests/linked_list/linked_list_test.h"
#include "tests/dynamic_array/dynamic_array_test.h"
#include "tests/io/io_test.h"

int main(void) {

	istd_test(test_dynamic_array, "Dynamic Array");
	istd_test(test_linked_list, "Linked List");
	istd_test(test_time, "Timer/High Resolution");
	istd_test(test_thread, "Thread");
	istd_test(test_unordered_map, "Unordered Map");
	istd_test(test_io, "IO");
	istd_test(test_window, "Window");

	return 0;
}