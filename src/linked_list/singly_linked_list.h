#if !defined(ISTD_SINGLY_LINKED_LIST)
#define ISTD_SINGLY_LINKED_LIST

#include "core.h"

ISTD_EXTERN_C

ISTD_DEFINE_HANDLE(istd_node);

ISTD_API istd_node istd_singly_linked_list_node_create(
	void* buf, 
	size_t length, 
	size_t type_size,
	istd_allocator* allocator
);

ISTD_API void istd_singly_linked_list_push_front(
	istd_node* head, 
	void* buf, 
	size_t length, 
	size_t type_size 
);

ISTD_API void istd_singly_linked_list_pop_front(
	istd_node* head
);

ISTD_API istd_node istd_singly_linked_list_next(
	istd_node node
);

ISTD_API void* __istd_singly_linked_list_get_buffer(
	istd_node node
);

#define istd_singly_linked_list_get_buffer(type, node) (type*)__istd_singly_linked_list_get_buffer(node) 

ISTD_API void istd_singly_linked_list_free(
	istd_node head
);

ISTD_END_EXTERN_C

#endif
