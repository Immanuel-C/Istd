#include "dynamic_array/dynamic_array.h"
#include "linked_list/singly_linked_list.h"
#include "time/time.h"
#include "thread/thread.h"

#include <stdio.h>
#include <stdlib.h>

static void* print_singly_linked_list_ints(istd_node* head) {
	istd_node* next = head;

	printf("Singly linked list:\n\t");

	while (next != istd_nullptr) {
		printf("\t%i,\n", *istd_singly_linked_list_get_buffer(int, next));
		next = istd_singly_linked_list_next(next);
	}

	return 0;
}

typedef struct thread_info_t {
	uint64_t x, y, z, retval;
} thread_info;

static void* istd_stdcall thread_fun(void* arg) {
	thread_info* info = (thread_info*)arg;

	printf("Thread ID: %zu, x: %zu, y: %zu, z: %zu\n", (uint64_t)istd_thread_get_current_id(), info->x, info->y, info->z);

	info->retval = 50;

	return 0;
}

int main(void) {
	istd_allocator defualt_allocator = istd_get_defualt_allocator();

	istd_dynamic_array* dynamic_array = istd_dynamic_array_create(int, 2, &defualt_allocator);

	*istd_dynamic_array_at(int, dynamic_array, 0) = 1;
	*istd_dynamic_array_at(int, dynamic_array, 1) = 5;

	int val = 10;
	istd_dynamic_array_push_back(dynamic_array, &val, &defualt_allocator);

	printf("Values: %i, %i, %i\n", *istd_dynamic_array_at(int, dynamic_array, 0), *istd_dynamic_array_at(int, dynamic_array, 1), *istd_dynamic_array_at(int, dynamic_array, 2));

	istd_dynamic_array_pop_back(dynamic_array);

	printf("Length: %zu, Capacity: %zu\n", istd_dynamic_array_length(dynamic_array), istd_dynamic_array_capacity(dynamic_array));

	istd_dynamic_array_shrink_to_fit(dynamic_array, &defualt_allocator);

	val = 20;
	istd_dynamic_array_push_back(dynamic_array, &val, &defualt_allocator);

	printf("Length: %zu, Capacity: %zu\n", istd_dynamic_array_length(dynamic_array), istd_dynamic_array_capacity(dynamic_array));

	printf("Values: %i, %i, %i\n", *istd_dynamic_array_at(int, dynamic_array, 0), *istd_dynamic_array_at(int, dynamic_array, 1), *istd_dynamic_array_at(int, dynamic_array, 2));

	istd_dynamic_array_free(dynamic_array, &defualt_allocator);

	int i = 10;
	istd_node* head = istd_singly_linked_list_node_create(&i, 1, sizeof(i), &defualt_allocator);
	
	int i2 = 2;
	istd_singly_linked_list_push_front(&head, &i2, 1, sizeof(i2), &defualt_allocator);

	istd_singly_linked_list_pop_front(&head, &defualt_allocator);

	print_singly_linked_list_ints(head);

	istd_singly_linked_list_free(head, &defualt_allocator);

	istd_timer timer = istd_timer_start();

	istd_this_thread_sleep(500);

	double now_ms = istd_timer_now(timer, ISTD_MILISECONDS);

	printf("Time elapsed: %.4fms\n", now_ms);

	istd_this_thread_sleep(100);

	double elasped_time = istd_timer_end(timer, ISTD_SECONDS);

	printf("Time elapsed: %.4fs\n", elasped_time);

	thread_info info = {
		.x = 10,
		.y = 50,
		.z = 100,
		.retval = 0
	};

	istd_thread thread = istd_thread_create(thread_fun, &info);

	istd_thread_join(thread);

	printf("Thread return value: %zu", info.retval);

	return 0;
}