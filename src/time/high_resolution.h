#pragma once

#include "core.h"

#include "time.h"

ISTD_EXTERN_C

#include <stdint.h>

/**
* @brief Get time since computer started.
* @returns time since computer started in nanoseconds
*/
ISTD_API uint64_t istd_high_resolution_now_ns(void);


ISTD_END_EXTERN_C
