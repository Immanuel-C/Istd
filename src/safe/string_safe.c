#include "string_safe.h"


#if defined(__MINGW32__) || defined(__GNUC__) 
#define __STDC_WANT_LIB_EXT1__ 1
#endif

#include <string.h> 

#if defined(__MINGW32__) || defined(__GNUC__) 
#if defined(__STDC_LIB_EXT1__)
#define ISTD_LIB_EXT  
#endif
#endif


istd_errno istd_memcpy_safe(
	_Inout_updates_bytes_(dst_size)	void* dst,
	_In_							size_t dst_size,
	_In_reads_bytes_(src_size)		const void* src,
	_In_						    size_t src_size
) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)(int)memcpy_s(dst, dst_size, src, src_size);
	#else 

	istd_assert(dst != istd_nullptr, "istd_memcpy_safe() failed. dst is null");
	istd_assert(src != istd_nullptr, "istd_memcpy_safe() failed. src is null");
	istd_assert(dst_size != 0, "istd_memcpy_safe() failed. dst_size is 0");
	istd_assert(src_size != 0, "istd_memcpy_safe() failed. src_size is 0");

	istd_ignore_return(memcpy(dst, src, src_size));

	return ISTD_ENONE;

	#endif
}

istd_errno istd_memmove_safe(
	_Inout_updates_bytes_(dst_size) void* dst,
	_In_					        size_t dst_size,
	_In_reads_bytes_(src_size)      const void* src,
	_In_					        size_t src_size
) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)(int)memmove_s(dst, dst_size, src, src_size);
	#else 

	istd_assert(dst != istd_nullptr, "istd_memmove_safe() failed. dst is null");
	istd_assert(src != istd_nullptr, "istd_memmove_safe() failed. src is null");
	istd_assert(dst_size != 0, "istd_memmove_safe() failed. dst_size is 0");
	istd_assert(src_size != 0, "istd_memmove_safe() failed. src_size is 0");

	istd_ignore_return(memmove(dst, src, src_size));

	return ISTD_ENONE;

	#endif
}

// Most compilers dont implement this function.
// Do simple checks and return.
istd_errno istd_memset_safe(
	_Inout_updates_bytes_(dst_size)	void* dst,
	_In_						    size_t dst_size,
	_In_						    uint8_t fill,
	_In_						    size_t count
) {
	istd_assert(dst != istd_nullptr, "istd_memset_safe() failed. dst is null");
	istd_assert(dst_size != 0, "istd_memset_safe() failed. dst_size is 0");
	istd_assert(count != 0, "istd_memset_safe() failed. count is 0");
	istd_assert(dst_size <= count, "istd_memset_safe() failed. count must be greater than or equal to dst_size");
	istd_ignore_return(memset(dst, (int)fill, count));

	return ISTD_ENONE;
}

char* istd_strtok_safe(
	_In_z_	  char* str,
	_In_z_	  const char* delim,
	_Inout_z_ char** ptr
) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return strtok_s(str, delim, ptr);
	#else
	return strtok_r(str, delim, ptr);
	#endif
}


istd_errno istd_strcpy_safe(
	_Inout_updates_z_(dst_size) char* dst,
	_In_					    size_t dst_size,
	_In_z_					    const char* src
) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)(int)strcpy_s(dst, dst_size, src);
	#else

	istd_assert(dst != istd_nullptr, "istd_strcpy_safe() failed. dst is null");
	istd_assert(src != istd_nullptr, "istd_strcpy_safe() failed. src is null");
	istd_assert(dst_size != 0, "istd_strcpy_safe() failed. dst_size is 0");

	istd_ignore_return(strcpy(dst, src));

	return ISTD_ENONE;

	#endif
}

istd_errno istd_wcscpy_safe(
	_Inout_updates_z_(dst_size) wchar_t* dst,
	_In_				        size_t dst_size,
	_In_z_				        const wchar_t* src
) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)(int)wcscpy_s(dst, dst_size, src);
	#else

	istd_assert(dst != istd_nullptr, "istd_wcstrcpy_safe() failed. dst is null");
	istd_assert(src != istd_nullptr, "istd_wcstrcpy_safe() failed. src is null");
	istd_assert(dst_size != 0, "istd_wcstrcpy_safe() failed. dst_size is 0");

	istd_ignore_return(wcscpy(dst, src));

	return ISTD_ENONE;

	#endif
}

istd_errno istd_strncpy_safe(
	_Inout_updates_(dst_size) char* dst,
	_In_				      size_t dst_size,
	_In_				      const char* src,
	_In_				      size_t count
) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)(int)strncpy_s(dst, dst_size, src, count);
	#else

	istd_assert(dst != istd_nullptr, "istd_strncpy_safe() failed. dst is null");
	istd_assert(src != istd_nullptr, "istd_strncpy_safe() failed. src is null");
	istd_assert(dst_size != 0, "istd_strncpy_safe() failed. dst_size is 0");
	istd_assert(count != 0, "istd_strncpy_safe() failed. count is 0");

	istd_ignore_return(strncpy(dst, src, count));

	return ISTD_ENONE;

	#endif
}

istd_api istd_errno istd_stdcall istd_wcsncpy_safe(
	_Inout_updates_(dst_size) wchar_t* dst,
	_In_				      size_t dst_size,
	_In_				      const wchar_t* src,
	_In_				      size_t count
) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)(int)wcsncpy_s(dst, dst_size, src, count);
	#else

	istd_assert(dst != istd_nullptr, "istd_wcsncpy_safe() failed. dst is null");
	istd_assert(src != istd_nullptr, "istd_wcsncpy_safe() failed. src is null");
	istd_assert(dst_size != 0, "istd_wcsncpy_safe() failed. dst_size is 0");
	istd_assert(count != 0, "istd_wcsncpy_safe() failed. count is 0");

	istd_ignore_return(wcsncpy(dst, src, count));
	
	return ISTD_ENONE;

	#endif
}

istd_api istd_errno istd_stdcall istd_strcat_safe(
	_Inout_updates_z_(dst_size) char* dst,
	_In_				        size_t dst_size,
	_In_z_				        const char* src
) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)(int)strcat_s(dst, dst_size, src);
	#else

	istd_assert(dst != istd_nullptr, "istd_strcat_safe() failed. dst is null");
	istd_assert(src != istd_nullptr, "istd_strcat_safe() failed. src is null");
	istd_assert(dst_size != 0, "istd_strcat_safe() failed. dst_size is 0");

	istd_ignore_return(strcat(dst, src));

	return ISTD_ENONE;

	#endif
}

istd_api istd_errno istd_stdcall istd_wcscat_safe(
	_Inout_updates_z_(dst_size) wchar_t* dst,
	_In_				        size_t dst_size,
	_In_z_			            const wchar_t* src
) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)(int)wcscat_s(dst, dst_size, src);
	#else

	istd_assert(dst != istd_nullptr, "istd_wcscat_safe() failed. dst is null");
	istd_assert(src != istd_nullptr, "istd_wcscat_safe() failed. src is null");
	istd_assert(dst_size != 0, "istd_wcscat_safe() failed. dst_size is 0");

	istd_ignore_return(wcscat(dst, src));

	return ISTD_ENONE;

	#endif
}

istd_api istd_errno istd_stdcall istd_strncat_safe(
	_Inout_updates_z_(dst_size) char* dst,
	_In_				        size_t dst_size,
	_In_z_				        const char* src,
	_In_				        size_t count
) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)(int)strncat_s(dst, dst_size, src, count);
	#else

	istd_assert(dst != istd_nullptr, "istd_strncat_safe() failed. dst is null");
	istd_assert(src != istd_nullptr, "istd_strncat_safe() failed. src is null");
	istd_assert(dst_size != 0, "istd_strncat_safe() failed. dst_size is 0");
	istd_assert(count != 0, "istd_strncat_safe() failed. count is 0");

	istd_ignore_return(strncat(dst, src, count));

	return ISTD_ENONE;

	#endif
}

istd_api istd_errno istd_stdcall istd_wcsncat_safe(
	_Inout_updates_z_(dst_size) wchar_t* dst,
	_In_					    size_t dst_size,
	_In_z_				        const wchar_t* src,
	_In_					    size_t count
) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)(int)wcsncat_s(dst, dst_size, src, count);
	#else

	istd_assert(dst != istd_nullptr, "istd_wcsncat_safe() failed. dst is null");
	istd_assert(src != istd_nullptr, "istd_wcsncat_safe() failed. src is null");
	istd_assert(dst_size != 0, "istd_wcsncat_safe() failed. dst_size is 0");
	istd_assert(count != 0, "istd_wcsncat_safe() failed. count is 0");

	istd_ignore_return(wcsncat(dst, src, count));

	return ISTD_ENONE;

	#endif
}

istd_errno istd_strerror_safe(
	_Inout_updates_z_(buf_size) char* buf,
	_In_					    size_t buf_size,
	_In_					    istd_errno err
) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)(int)strerror_s(buf, buf_size, (int)err);
	#else

	istd_assert(buf != istd_nullptr, "istd_strerror_safe() failed. buf is null");
	istd_assert(buf_size != 0, "istd_strerror_safe() failed. buf_size is 0");
	istd_assert(err > 0 || err < ISTD_ERRNO_MAX, "istd_strerror_safe() failed. err must be a valid istd_errno value");
	buf = strerror((int)err);

	return ISTD_ENONE;

	#endif
}
