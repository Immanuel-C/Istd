#if !defined(ISTD_SINGLY_LINKED_LIST)
#define ISTD_SINGLY_LINKED_LIST

#include "core.h"

ISTD_EXTERN_C

typedef struct istd_node_t {
	void* buf;
	void* next;
} istd_node;

istd_api istd_node* istd_stdcall istd_singly_linked_list_create(void* buf, size_t buf_size, istd_allocator* allocator);


istd_api void istd_stdcall istd_singly_linked_list_free(istd_node* head, istd_allocator* allocator);

ISTD_END_EXTERN_C

#endif