#if !defined(ISTD_ALLOCATOR)
#define ISTD_ALLOCATOR

#include "core.h"

ISTD_EXTERN_C

/**
 * @brief Get the default allocator provided by the system.
 * @return The default allocator.
 */
ISTD_API istd_allocator istd_get_defualt_allocator(void);
/** 
 * @brief Check if the allocator is NULL, if it is return the default allocator.
 * @return The allocator provided if it is not NULL, otherwise the default allocator.
*/
ISTD_API istd_allocator istd_check_allocator(istd_allocator* allocator);

const char* istd_result_to_string(istd_result result);
ISTD_END_EXTERN_C

#endif
