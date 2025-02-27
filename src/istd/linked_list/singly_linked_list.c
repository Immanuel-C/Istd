#include "singly_linked_list.h"

#include "allocator/allocator.h"

#include <string.h>

typedef struct __istd_node_t {
	void* buf;
	size_t buf_size;
	struct __istd_node_t* next;
	istd_allocator allocator;
} __istd_node;

void istd_singly_linked_list_free(
	istd_node head
) {
	__istd_node* tmp = istd_nullptr;
	void* tmp_buf = istd_nullptr;
	__istd_node* _head = (__istd_node*)head;


	while (_head != istd_nullptr) {
		tmp = _head;
		tmp_buf = _head->buf;
		
		_head = _head->next;

		tmp->allocator.free(tmp_buf);
		tmp->allocator.free(tmp);
	}
}

istd_node istd_singly_linked_list_node_create(
	void* buf,
	size_t length,
	size_t type_size,
	istd_allocator* allocator
) {
	istd_allocator alloc = istd_check_allocator(allocator);

	__istd_node* head = alloc.malloc(sizeof(__istd_node));
	head->buf_size = length * type_size;
	head->buf = alloc.malloc(head->buf_size);
	memcpy(head->buf, buf, head->buf_size);
	head->next = istd_nullptr;
	head->allocator = alloc;

	return (istd_node)head;
}

void istd_singly_linked_list_push_front(
	istd_node* head,
	void* buf,
	size_t length,
	size_t type_size
) {
	__istd_node* old_head = (__istd_node*)*head;
	__istd_node* new_head = (__istd_node*)istd_singly_linked_list_node_create(buf, length, type_size, istd_nullptr);
	new_head->next = old_head;
	*head = (istd_node)new_head;
}

void istd_singly_linked_list_pop_front(
	istd_node* head
) {
	__istd_node* old_head = (__istd_node*)*head;

	ISTD_ASSERT(head != istd_nullptr, "istd_singly_linked_list_pop_front() failed. Head must not be null.");
	ISTD_ASSERT(old_head->next != istd_nullptr, "istd_singly_linked_list_pop_front() failed. Cant pop back a list that has only 1 node.");

	*head = (istd_node)old_head->next;

	old_head->next = istd_nullptr;

	istd_singly_linked_list_free((istd_node)old_head);
}

istd_node istd_singly_linked_list_next(
	istd_node node
) {
	return (istd_node)(((__istd_node*)(node))->next);
}

void* __istd_singly_linked_list_get_buffer(
	istd_node node
) {
	return ((__istd_node*)(node))->buf;
}

