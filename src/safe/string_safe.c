#include "string_safe.h"
#include "../compiler/compiler.h"

#include <string.h> 


istd_errno istd_memcpy_safe(void* dst, size_t dst_size, void* src, size_t src_size) {
	if (istd_is_compiler_msvc() == true || istd_is_compiler_clang() == true)
		return (istd_errno)memcpy_s(dst, dst_size, src, src_size);

	istd_ignore_return(memcpy(dst, src, src_size));

	return ISTD_ENONE;
}
