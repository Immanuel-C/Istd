#include "linked_list_test.h"

#include "linked_list/singly_linked_list.h"

#include <stdio.h>

static void* print_singly_linked_list_ints(istd_node head) {
	istd_node next = head;

	printf("Singly linked list:\n\t");

	while (next != istd_nullptr) {
		printf("\t%i,\n", *istd_singly_linked_list_get_buffer(int, next));
		next = istd_singly_linked_list_next(next);
	}

	return 0;
}


istd_test_msg istd_stdcall test_linked_list(void) {
	istd_test_msg msg = { 0 };

	int i = 10;
	istd_node head = istd_singly_linked_list_node_create(&i, 1, sizeof(i), istd_nullptr);
	
	if (head == istd_nullhnd) {
		msg.passed = false;
		msg.err_msg = "Failed to create a node.";
		return msg;
	}

	int i2 = 2;
	istd_singly_linked_list_push_front(&head, &i2, 1, sizeof(i2));

	istd_singly_linked_list_pop_front(&head);

	print_singly_linked_list_ints(head);

	istd_singly_linked_list_free(head);

	msg.passed = true;
	return msg;
}