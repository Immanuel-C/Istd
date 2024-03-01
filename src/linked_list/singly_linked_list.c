#include "singly_linked_list.h"

#include <safe/string_safe.h>

istd_node* istd_singly_linked_list_create(void* buf, size_t buf_size, istd_allocator* allocator) {
	istd_node* head = allocator->malloc(sizeof(istd_node));
	head->buf = allocator->malloc(buf_size);
	istd_memcpy_safe(head->buf, buf_size, buf, buf_size);
	head->next = istd_nullptr;

	return head;
}

void istd_singly_linked_list_free(istd_node* head, istd_allocator* allocator) {
	istd_node* tmp = istd_nullptr;
	void* tmp_buf = istd_nullptr;

	while (head != istd_nullptr) {
		tmp = head;
		tmp_buf = head->buf;
		
		head = head->next;

		allocator->free(tmp_buf);
		allocator->free(tmp);
	}
}
