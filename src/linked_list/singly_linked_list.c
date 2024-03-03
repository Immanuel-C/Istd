#include "singly_linked_list.h"

#include <safe/string_safe.h>

typedef struct _istd_node_t {
	void* buf;
	size_t buf_size;
	struct _istd_node_t* next;
} _istd_node;


istd_node* istd_singly_linked_list_node_create(
	_In_ void* buf,
	_In_ size_t length,
	_In_ size_t type_size,
	_In_ istd_allocator* allocator
) {
	_istd_node* head = allocator->malloc(sizeof(_istd_node));
	head->buf_size = length * type_size;
	head->buf = allocator->malloc(head->buf_size);
	istd_memcpy_safe(head->buf, head->buf_size, buf, head->buf_size);
	head->next = istd_nullptr;

	return (istd_node*)head;
}

void istd_singly_linked_list_push_front(
	_Inout_ istd_node** head,
	_In_ void* buf,
	_In_ size_t length,
	_In_ size_t type_size,
	_In_ istd_allocator* allocator
) {
	_istd_node* old_head = (_istd_node*)*head;
	_istd_node* new_head = (_istd_node*)istd_singly_linked_list_node_create(buf, length, type_size, allocator);
	new_head->next = old_head;
	*head = (istd_node*)new_head;
}

void istd_singly_linked_list_pop_front(
	_Inout_updates_(1) istd_node** head,
	_In_			   istd_allocator* allocator
) {
	_istd_node* old_head = (_istd_node*)*head;

	istd_assert(head != istd_nullptr, "istd_singly_linked_list_pop_front() failed. Head must not be null.");
	istd_assert(old_head->next != istd_nullptr, "istd_singly_linked_list_pop_front() failed. Cant pop back a list that has only 1 node.");

	*head = (istd_node*)old_head->next;

	old_head->next = istd_nullptr;

	istd_singly_linked_list_free((istd_node*)old_head, allocator);
}

istd_node* istd_singly_linked_list_next(
	_In_ istd_node* node
) {
	return (istd_node*)(((_istd_node*)(node))->next);
}

void* _istd_singly_linked_list_get_buffer(
	_In_ istd_node* node
) {
	return ((_istd_node*)(node))->buf;
}

void istd_singly_linked_list_free(
	_In_ istd_node* head,
	_In_ istd_allocator* allocator
) {
	_istd_node* tmp = istd_nullptr;
	void* tmp_buf = istd_nullptr;
	_istd_node* _head = (_istd_node*)head;


	while (_head != istd_nullptr) {
		tmp = _head;
		tmp_buf = _head->buf;
		
		_head = _head->next;

		allocator->free(tmp_buf);
		allocator->free(tmp);
	}
}
