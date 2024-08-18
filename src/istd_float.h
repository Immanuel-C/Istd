#if !defined(ISTD_FLOAT_H)
#define ISTD_FLOAT_H

#include "core.h"

ISTD_EXTERN_C

/**
* These types are not guarunteed to be the sizes that are defined.
* In the future they may be though.
*/

typedef float istd_float32;
typedef double istd_float64;
// Depending on the platform and compiler this may be either 64 or 128 bytes in size.
typedef long double istd_float64_128;

ISTD_END_EXTERN_C

#endif
