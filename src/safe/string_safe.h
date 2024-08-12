#if !defined(ISTD_SAFE)
#define ISTD_SAFE

#include "core.h"

ISTD_EXTERN_C

#include <wchar.h>
#include <stdint.h>

/**
* @brief Copies source buffer into destination buffer. Calls memcpy_s, if it is not available then call memcpy and do basic checks.
* @param dst destination buffer that will get copied to.
* @param dst_size the size of the destination buffer in bytes.
* @param src source buffer that will get its contents copied to the destination buffer.
* @param src_size the size of the source buffer in bytes.
* @returns An istd_errno of the return value of memcpy_s, if its not available the function always returns ISTD_ENONE. 
*/
istd_api istd_errno istd_memcpy_safe(
	void* dst,
	size_t dst_size, 
	const void* src, 
	size_t src_size
);
/**
* @brief Moves source buffer into destination buffer. Calls memmove_s, if it is not available then call memmove and do basic checks.
* @param dst destination buffer that the data will get moved to.
* @param dst_size the size of the destination buffer in bytes.
* @param src source buffer that will get its contents moved to the destination buffer.
* @param src_size the size of the source buffer in bytes.
* @returns An istd_errno of the return value of memmove_s, if its not available the function always returns ISTD_ENONE.
*/
istd_api istd_errno istd_memmove_safe(
	void* dst,
	size_t dst_size, 
	const void* src, 
	size_t src_size
);
/**
* @brief Sets destination buffer to fill value. Calls memset_s, if it is not available then call memset and do basic checks.
* @param dst destination buffer that will be set.
* @param dst_size the size of the destination buffer in bytes.
* @param fill the fill value.
* @param count number of bytes to set.
* @returns An istd_errno of the return value of memset_s, if its not available the function always returns ISTD_ENONE.
*/
istd_api istd_errno istd_memset_safe(
	void* dst,
	size_t dst_size, 
	uint8_t fill, 
	size_t count
);
/**
* @brief Gets each token of a string seperated by a delimenator. Calls strtok_s, if it is not available then call strtok and do basic checks.
* @param str null terminated byte string to tokenize.
* @param delim null terminated byte string identifying delimiters.
* @param ptr pointer to char*. Used by strtok_s to store internal state.
* @returns the beginning of the next token or null pointer if there are no more tokens.
*/
istd_api char* istd_strtok_safe(
	char* str, 
	const char* delim,
	char** ptr
);
/**
* @brief Copies source string into destination string. Calls strcpy_s, if it is not available then call strcpy and do basic checks.
* @param dst destination string that will get copied to.
* @param dst_size the size of the destination string.
* @param src source null terminated string that will get its contents copied to the destination string.
* @returns An istd_errno of the return value of strcpy_s, if its not available the function always returns ISTD_ENONE.
*/
istd_api istd_errno istd_strcpy_safe(
	char* dst,
	size_t dst_size, 
	const char* src
);
/**
* @brief Copies source wide string into destination wide string. Calls wcscpy_s, if it is not available then call wcscpy and do basic checks.
* @param dst destination wide string that will get copied to.
* @param dst_size the amount of characters in the destination string.
* @param src source null terminated wide string that will get its contents copied to the destination string.
* @returns An istd_errno of the return value of wcscpy_s, if its not available the function always returns ISTD_ENONE.
*/
istd_api istd_errno istd_wcscpy_safe(
	wchar_t* dst,
	size_t dst_size, 
	const wchar_t* src
);
/**
* @brief Copies a part of source string into the destination wide string. Calls strncpy_s, if it is not available then call strncpy and do basic checks.
* @param dst destination string that will get copied to.
* @param dst_size the amount of characters in the destination string.
* @param src source null terminated string that will get a part of its contents copied to the destination string.
* @param count the amount of characters that will get copied from the source string to the destination string.
* @returns An istd_errno of the return value of strcpy_s, if its not available the function always returns ISTD_ENONE.
*/
istd_api istd_errno istd_strncpy_safe(
	char* dst,
	size_t dst_size, 
	const char* src, 
	size_t count
);
/**
* @brief Copies a part of source wide string into the destination wide string. Calls wcsncpy_s, if it is not available then call wcsncpy and do basic checks.
* @param dst destination wide string that will get copied to.
* @param dst_size the amount of wide characters in the destination string.
* @param src source null terminated wide string that will get a part of its contents copied to the destination string.
* @param count the amount of wide characters that will get copied from the source string to the destination string.
* @returns An istd_errno of the return value of wcsncpy_s, if its not available the function always returns ISTD_ENONE.
*/
istd_api istd_errno istd_wcsncpy_safe( 
	wchar_t* dst,
	size_t dst_size, 
	const wchar_t* src, 
	size_t count
);
/**
* @brief Contatinates source string to destination string. Calls strcat_s, if it is not available then call strcat and do basic checks.
* @param dst destination string that will get the source string contantinated to.
* @param dst_size the amount of characters in the destination string.
* @param src source null terminated string that will get conatanated to the end of the destination string.
* @returns An istd_errno of the return value of strcat_s, if its not available the function always returns ISTD_ENONE.
*/
istd_api istd_errno istd_strcat_safe( 
	char* dst,
	size_t dst_size, 
	const char* src
);
/**
* @brief Contatinates source wide string to destination wide string. Calls wcscat_s, if it is not available then call wcscat and do basic checks.
* @param dst destination wide string that will get the source wide string contantinated to it.
* @param dst_size the amount of wide characters in the destination string.
* @param src source null terminated wide string that will get conatinated to the end of the destination wide string.
* @returns An istd_errno of the return value of wcscat_s, if its not available the function always returns ISTD_ENONE.
*/
istd_api istd_errno istd_wcscat_safe(
	wchar_t* dst, 
	size_t dst_size, 
	const wchar_t* src
);
/**
* @brief Contatinates a part of source string to destination string. Calls strncat_s, if it is not available then call strncat and do basic checks.
* @param dst destination string that will get part of the source string contantinated to.
* @param dst_size the amount of characters in the destination string.
* @param src source null terminated string that will have a part of it conatanated to the end of the destination string.
* @param count the amount of characters in the source string that will get concatinated.
* @returns An istd_errno of the return value of strcat_s, if its not available the function always returns ISTD_ENONE.
*/
istd_api istd_errno istd_strncat_safe(
	char* dst,
	size_t dst_size, 
	const char* src, 
	size_t count
);
/**
* @brief Contatinates a part of source wide string to destination wide  string. Calls wcsncat_s, if it is not available then call wcsncat and do basic checks.
* @param dst destination wide string that will get part of the source string contantinated to.
* @param dst_size the amount of wide characters in the destination string.
* @param src source null terminated wide string that will have a part of it conatanated to the end of the destination string.
* @param count the amount of wide characters in the source string that will get concatinated.
* @returns An istd_errno of the return value of wcsncat_s, if its not available the function always returns ISTD_ENONE.
*/
istd_api istd_errno istd_wcsncat_safe(
	wchar_t* dst,
	size_t dst_size, 
	const wchar_t* src, 
	size_t count
);
/**
* @brief Converts an error code to a string. Calls strerror_s, if it is not available then call strerror and do basic checks.
* @param buf string that will get the error code in string format.
* @param buf_size the amount of characters in the destination string.
*/
istd_api istd_errno istd_strerror_safe(
	char* buf, 
	size_t buf_size, 
	istd_errno err
);


ISTD_END_EXTERN_C

#endif 
