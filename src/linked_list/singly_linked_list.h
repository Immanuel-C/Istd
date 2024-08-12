#if !defined(ISTD_SINGLY_LINKED_LIST)
#define ISTD_SINGLY_LINKED_LIST

#include "core.h"

ISTD_EXTERN_C

istd_define_handle(istd_node);

istd_api istd_node istd_singly_linked_list_node_create(
	void* buf, 
	size_t length, 
	size_t type_size,
	istd_allocator* allocator
);

istd_api void istd_singly_linked_list_push_front(
	istd_node* head, 
	void* buf, 
	size_t length, 
	size_t type_size 
);

istd_api void istd_singly_linked_list_pop_front(
	istd_node* head
);

istd_api istd_node istd_singly_linked_list_next(
	istd_node node
);

istd_api void* __istd_singly_linked_list_get_buffer(
	istd_node node
);

#define istd_singly_linked_list_get_buffer(type, node) (type*)__istd_singly_linked_list_get_buffer(node) 

istd_api void istd_singly_linked_list_free(
	istd_node head
);

ISTD_END_EXTERN_C

#endif
