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


istd_errno istd_memcpy_safe(void* dst, size_t dst_size, const void* src, size_t src_size) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)memcpy_s(dst, dst_size, src, src_size);
	#else 

	istd_assert(dst != istd_nullptr, "istd_memcpy_safe() failed. dst is null");
	istd_assert(src != istd_nullptr, "istd_memcpy_safe() failed. src is null");
	istd_assert(dst_size != 0, "istd_memcpy_safe() failed. dst_size is 0");
	istd_assert(src_size != 0, "istd_memcpy_safe() failed. src_size is 0");

	istd_ignore_return(memcpy(dst, src, src_size));

	return ISTD_ENONE;

	#endif
}

istd_errno istd_memmove_safe(void* dst, size_t dst_size, const void* src, size_t src_size) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)memmove_s(dst, dst_size, src, src_size);
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
istd_errno istd_memset_safe(void* dst, size_t dst_size, uint8_t fill, size_t count) {
	istd_assert(dst != istd_nullptr, "istd_memset_safe() failed. dst is null");
	istd_assert(dst_size != 0, "istd_memset_safe() failed. dst_size is 0");
	istd_assert(count != 0, "istd_memset_safe() failed. count is 0");
	istd_assert(dst_size <= count, "istd_memset_safe() failed. count must be greater than or equal to dst_size");
	istd_ignore_return(memset(dst, (int)fill, count));

	return ISTD_ENONE;
}

char* istd_strtok_safe(char* str, const char* delim, char** ptr) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return strtok_s(str, delim, ptr);
	#else
	return strtok_r(str, delim, ptr);
	#endif
}


istd_errno istd_strcpy_safe(char* dst, size_t dst_size, const char* src) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)strcpy_s(dst, dst_size, src);
	#else

	istd_assert(dst != istd_nullptr, "istd_strcpy_safe() failed. dst is null");
	istd_assert(src != istd_nullptr, "istd_strcpy_safe() failed. src is null");
	istd_assert(dst_size != 0, "istd_strcpy_safe() failed. dst_size is 0");

	istd_ignore_return(strcpy(dst, src));

	return ISTD_ENONE;

	#endif
}

istd_errno istd_wcscpy_safe(wchar_t* dst, size_t dst_size, const wchar_t* src) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)wcscpy_s(dst, dst_size, src);
	#else

	istd_assert(dst != istd_nullptr, "istd_wcstrcpy_safe() failed. dst is null");
	istd_assert(src != istd_nullptr, "istd_wcstrcpy_safe() failed. src is null");
	istd_assert(dst_size != 0, "istd_wcstrcpy_safe() failed. dst_size is 0");

	istd_ignore_return(wcscpy(dst, src));

	return ISTD_ENONE;

	#endif
}

istd_errno istd_strncpy_safe(char* dst, size_t dst_size, const char* src, size_t count) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)strncpy_s(dst, dst_size, src, count);
	#else

	istd_assert(dst != istd_nullptr, "istd_strncpy_safe() failed. dst is null");
	istd_assert(src != istd_nullptr, "istd_strncpy_safe() failed. src is null");
	istd_assert(dst_size != 0, "istd_strncpy_safe() failed. dst_size is 0");
	istd_assert(count != 0, "istd_strncpy_safe() failed. count is 0");

	istd_ignore_return(strncpy(dst, src, count));

	return ISTD_ENONE;

	#endif
}

istd_api istd_errno istd_stdcall istd_wcsncpy_safe(wchar_t* dst, size_t dst_size, const wchar_t* src, size_t count) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)wcsncpy_s(dst, dst_size, src, count);
	#else

	istd_assert(dst != istd_nullptr, "istd_wcsncpy_safe() failed. dst is null");
	istd_assert(src != istd_nullptr, "istd_wcsncpy_safe() failed. src is null");
	istd_assert(dst_size != 0, "istd_wcsncpy_safe() failed. dst_size is 0");
	istd_assert(count != 0, "istd_wcsncpy_safe() failed. count is 0");

	istd_ignore_return(wcsncpy(dst, src, count));
	
	return ISTD_ENONE;

	#endif
}

istd_api istd_errno istd_stdcall istd_strcat_safe(char* dst, size_t dst_size, const char* src) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)strcat_s(dst, dst_size, src);
	#else

	istd_assert(dst != istd_nullptr, "istd_strcat_safe() failed. dst is null");
	istd_assert(src != istd_nullptr, "istd_strcat_safe() failed. src is null");
	istd_assert(dst_size != 0, "istd_strcat_safe() failed. dst_size is 0");

	istd_ignore_return(strcat(dst, src));

	return ISTD_ENONE;

	#endif
}

istd_api istd_errno istd_stdcall istd_wcscat_safe(wchar_t* dst, size_t dst_size, const wchar_t* src) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)wcscat_s(dst, dst_size, src);
	#else

	istd_assert(dst != istd_nullptr, "istd_wcscat_safe() failed. dst is null");
	istd_assert(src != istd_nullptr, "istd_wcscat_safe() failed. src is null");
	istd_assert(dst_size != 0, "istd_wcscat_safe() failed. dst_size is 0");

	istd_ignore_return(wcscat(dst, src));

	return ISTD_ENONE;

	#endif
}

istd_api istd_errno istd_stdcall istd_strncat_safe(char* dst, size_t dst_size, const char* src, size_t count) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)strncat_s(dst, dst_size, src, count);
	#else

	istd_assert(dst != istd_nullptr, "istd_strncat_safe() failed. dst is null");
	istd_assert(src != istd_nullptr, "istd_strncat_safe() failed. src is null");
	istd_assert(dst_size != 0, "istd_strncat_safe() failed. dst_size is 0");
	istd_assert(count != 0, "istd_strncat_safe() failed. count is 0");

	istd_ignore_return(strncat(dst, src, count));

	return ISTD_ENONE;

	#endif
}

istd_api istd_errno istd_stdcall istd_wcsncat_safe(wchar_t* dst, size_t dst_size, const wchar_t* src, size_t count) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)wcsncat_s(dst, dst_size, src, count);
	#else

	istd_assert(dst != istd_nullptr, "istd_wcsncat_safe() failed. dst is null");
	istd_assert(src != istd_nullptr, "istd_wcsncat_safe() failed. src is null");
	istd_assert(dst_size != 0, "istd_wcsncat_safe() failed. dst_size is 0");
	istd_assert(count != 0, "istd_wcsncat_safe() failed. count is 0");

	istd_ignore_return(wcsncat(dst, src, count));

	return ISTD_ENONE;

	#endif
}

istd_errno istd_strerror_safe(char* buf, size_t buf_size, istd_errno err) {
	#if defined(ISTD_LIB_EXT) || defined(_MSC_VER) || defined(__clang__)
	return (istd_errno)strerror_s(buf, buf_size, (int)err);
	#else

	istd_assert(buf != istd_nullptr, "istd_strerror_safe() failed. buf is null");
	istd_assert(buf_size != 0, "istd_strerror_safe() failed. buf_size is 0");
	istd_assert(err > 0 || err < ISTD_ERRNO_MAX, "istd_strerror_safe() failed. err must be a valid istd_errno value");
	buf = strerror((int)err);

	return ISTD_ENONE;

	#endif
}
