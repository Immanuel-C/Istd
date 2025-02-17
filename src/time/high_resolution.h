#pragma once

#include "core.h"


ISTD_EXTERN_C

#include <stdint.h>

/**
* @brief Get time since computer started.
* @returns time since computer started in nanoseconds
*/
istd_api uint64_t istd_high_resolution_now_ns(void);


ISTD_END_EXTERN_C
