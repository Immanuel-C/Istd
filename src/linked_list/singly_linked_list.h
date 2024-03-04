#if !defined(ISTD_SINGLY_LINKED_LIST)
#define ISTD_SINGLY_LINKED_LIST

#include "core.h"

ISTD_EXTERN_C

istd_define_handle(istd_node);

istd_api istd_node* istd_stdcall istd_singly_linked_list_node_create(
	_In_ void* buf, 
	_In_ size_t length, 
	_In_ size_t type_size,
	_In_ istd_allocator* allocator
);

istd_api void istd_stdcall istd_singly_linked_list_push_front(
	_Inout_ istd_node** head, 
	_In_	void* buf, 
	_In_	size_t length, 
	_In_	size_t type_size, 
	_In_	istd_allocator* allocator
);

istd_api void istd_stdcall istd_singly_linked_list_pop_front(
	_Inout_ istd_node** head,
	_In_    istd_allocator* allocator
);

istd_api istd_node* istd_stdcall istd_singly_linked_list_next(
	_In_ istd_node* node
);

istd_api void* istd_stdcall _istd_singly_linked_list_get_buffer(
	_In_ istd_node* node
);

#define istd_singly_linked_list_get_buffer(type, node) (type*)_istd_singly_linked_list_get_buffer(node) 

istd_api void istd_stdcall istd_singly_linked_list_free(
	_In_ istd_node* head, 
	_In_ istd_allocator* allocator
);

ISTD_END_EXTERN_C

#endif