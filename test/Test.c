#include "dynamic_array/dynamic_array.h"
#include "linked_list/singly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

static void print_singly_linked_list_ints(istd_node* head) {
	istd_node* next = head;

	printf("Singly linked list:\n\t");

	while (next != istd_nullptr) {
		printf("%i,\n\t", *istd_singly_linked_list_get_buffer(int, next));
		next = istd_singly_linked_list_next(next);
	}
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
}