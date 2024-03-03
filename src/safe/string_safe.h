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
istd_api istd_errno istd_stdcall istd_memcpy_safe(
	_Inout_updates_bytes_(dst_size)	void* dst,
	_In_							size_t dst_size, 
	_In_reads_bytes_(src_size)		const void* src, 
	_In_						    size_t src_size
);
/**
* @brief Moves source buffer into destination buffer. Calls memmove_s, if it is not available then call memmove and do basic checks.
* @param dst destination buffer that the data will get moved to.
* @param dst_size the size of the destination buffer in bytes.
* @param src source buffer that will get its contents moved to the destination buffer.
* @param src_size the size of the source buffer in bytes.
* @returns An istd_errno of the return value of memmove_s, if its not available the function always returns ISTD_ENONE.
*/
istd_api istd_errno istd_stdcall istd_memmove_safe(
	_Inout_updates_bytes_(dst_size) void* dst,
	_In_					        size_t dst_size, 
	_In_reads_bytes_(src_size)      const void* src, 
	_In_					        size_t src_size
);
/**
* @brief Sets destination buffer to fill value. Calls memset_s, if it is not available then call memset and do basic checks.
* @param dst destination buffer that will be set.
* @param dst_size the size of the destination buffer in bytes.
* @param fill the fill value.
* @param count number of bytes to set.
* @returns An istd_errno of the return value of memset_s, if its not available the function always returns ISTD_ENONE.
*/
istd_api istd_errno istd_stdcall istd_memset_safe(
	_Inout_updates_bytes_(dst_size)	void* dst,
	_In_						    size_t dst_size, 
	_In_						    uint8_t fill, 
	_In_						    size_t count
);
/**
* @brief Gets each token of a string seperated by a delimenator. Calls strtok_s, if it is not available then call strtok and do basic checks.
* @param str null terminated byte string to tokenize.
* @param delim null terminated byte string identifying delimiters.
* @param ptr pointer to char*. Used by strtok_s to store internal state.
* @returns the beginning of the next token or null pointer if there are no more tokens.
*/
istd_api char* istd_stdcall istd_strtok_safe(
	_In_z_	  char* str, 
	_In_z_	  const char* delim,
	_Inout_z_ char** ptr
);
/**
* @brief Copies source string into destination string. Calls strcpy_s, if it is not available then call strcpy and do basic checks.
* @param dst destination string that will get copied to.
* @param dst_size the size of the destination string.
* @param src source null terminated string that will get its contents copied to the destination string.
* @returns An istd_errno of the return value of strcpy_s, if its not available the function always returns ISTD_ENONE.
*/
istd_api istd_errno istd_stdcall istd_strcpy_safe(
	_Inout_updates_z_(dst_size) char* dst,
	_In_					    size_t dst_size, 
	_In_z_					    const char* src
);
/**
* @brief Copies source wide string into destination wide string. Calls wcscpy_s, if it is not available then call wcscpy and do basic checks.
* @param dst destination wide string that will get copied to.
* @param dst_size the amount of characters in the destination string.
* @param src source null terminated wide string that will get its contents copied to the destination string.
* @returns An istd_errno of the return value of wcscpy_s, if its not available the function always returns ISTD_ENONE.
*/
istd_api istd_errno istd_stdcall istd_wcscpy_safe(
	_Inout_updates_z_(dst_size) wchar_t* dst,
	_In_				        size_t dst_size, 
	_In_z_				        const wchar_t* src
);
/**
* @brief Copies a part of source string into the destination wide string. Calls strncpy_s, if it is not available then call strncpy and do basic checks.
* @param dst destination string that will get copied to.
* @param dst_size the amount of characters in the destination string.
* @param src source null terminated string that will get a part of its contents copied to the destination string.
* @param count the amount of characters that will get copied from the source string to the destination string.
* @returns An istd_errno of the return value of strcpy_s, if its not available the function always returns ISTD_ENONE.
*/
istd_api istd_errno istd_stdcall istd_strncpy_safe(
	_Inout_updates_(dst_size) char* dst,
	_In_				      size_t dst_size, 
	_In_				      const char* src, 
	_In_				      size_t count
);
/**
* @brief Copies a part of source wide string into the destination wide string. Calls wcsncpy_s, if it is not available then call wcsncpy and do basic checks.
* @param dst destination wide string that will get copied to.
* @param dst_size the amount of wide characters in the destination string.
* @param src source null terminated wide string that will get a part of its contents copied to the destination string.
* @param count the amount of wide characters that will get copied from the source string to the destination string.
* @returns An istd_errno of the return value of wcsncpy_s, if its not available the function always returns ISTD_ENONE.
*/
istd_api istd_errno istd_stdcall istd_wcsncpy_safe( 
	_Inout_updates_(dst_size) wchar_t* dst,
	_In_				      size_t dst_size, 
	_In_				      const wchar_t* src, 
	_In_				      size_t count
);
/**
* @brief Contatinates source string to destination string. Calls strcat_s, if it is not available then call strcat and do basic checks.
* @param dst destination string that will get the source string contantinated to.
* @param dst_size the amount of characters in the destination string.
* @param src source null terminated string that will get conatanated to the end of the destination string.
* @returns An istd_errno of the return value of strcat_s, if its not available the function always returns ISTD_ENONE.
*/
istd_api istd_errno istd_stdcall istd_strcat_safe( 
	_Inout_updates_z_(dst_size) char* dst,
	_In_				        size_t dst_size, 
	_In_z_				        const char* src
);
/**
* @brief Contatinates source wide string to destination wide string. Calls wcscat_s, if it is not available then call wcscat and do basic checks.
* @param dst destination wide string that will get the source wide string contantinated to it.
* @param dst_size the amount of wide characters in the destination string.
* @param src source null terminated wide string that will get conatinated to the end of the destination wide string.
* @returns An istd_errno of the return value of wcscat_s, if its not available the function always returns ISTD_ENONE.
*/
istd_api istd_errno istd_stdcall istd_wcscat_safe(
	_Inout_updates_z_(dst_size) wchar_t* dst, 
	_In_				        size_t dst_size, 
	_In_z_			            const wchar_t* src
);
/**
* @brief Contatinates a part of source string to destination string. Calls strncat_s, if it is not available then call strncat and do basic checks.
* @param dst destination string that will get part of the source string contantinated to.
* @param dst_size the amount of characters in the destination string.
* @param src source null terminated string that will have a part of it conatanated to the end of the destination string.
* @param count the amount of characters in the source string that will get concatinated.
* @returns An istd_errno of the return value of strcat_s, if its not available the function always returns ISTD_ENONE.
*/
istd_api istd_errno istd_stdcall istd_strncat_safe(
	_Inout_updates_z_(dst_size) char* dst,
	_In_				        size_t dst_size, 
	_In_z_				        const char* src, 
	_In_				        size_t count
);
/**
* @brief Contatinates a part of source wide string to destination wide  string. Calls wcsncat_s, if it is not available then call wcsncat and do basic checks.
* @param dst destination wide string that will get part of the source string contantinated to.
* @param dst_size the amount of wide characters in the destination string.
* @param src source null terminated wide string that will have a part of it conatanated to the end of the destination string.
* @param count the amount of wide characters in the source string that will get concatinated.
* @returns An istd_errno of the return value of wcsncat_s, if its not available the function always returns ISTD_ENONE.
*/
istd_api istd_errno istd_stdcall istd_wcsncat_safe(
	_Inout_updates_z_(dst_size) wchar_t* dst,
	_In_					    size_t dst_size, 
	_In_z_				        const wchar_t* src, 
	_In_					    size_t count
);
/**
* @brief Converts an error code to a string. Calls strerror_s, if it is not available then call strerror and do basic checks.
* @param buf string that will get the error code in string format.
* @param dst_size the amount of characters in the destination string.
*/
istd_api istd_errno istd_stdcall istd_strerror_safe(
	_Inout_updates_z_(buf_size) char* buf, 
	_In_					    size_t buf_size, 
	_In_					    istd_errno err
);


ISTD_END_EXTERN_C

#endif 