#if !defined(ISTD_SAFE)
#define ISTD_SAFE

#include "../core.h"

ISTD_EXTERN_C

istd_api istd_errno istd_stdcall istd_memcpy_safe(void* dst, size_t dst_size, void* src, size_t src_size);

ISTD_END_EXTERN_C

#endif 