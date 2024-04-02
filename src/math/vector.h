#if !defined(ISTD_VECTOR_H)
#define ISTD_VECTOR_H

#include "core.h"

#include <stdint.h>
#include "istd_float.h"

ISTD_EXTERN_C

/**
* Vector2
*/

typedef struct {
	union {
		int32_t x, i, r, width;
	};

	union {
		int32_t y, j, g, height;
	};
} istd_vector2_i32;

typedef struct {
	union {
		int64_t x, i, r, width;
	};

	union {
		int64_t y, j, g, height;
	};
} istd_vector2_i64;

typedef struct {
	union {
		istd_float32 x, i, r, width;
	};

	union {
		istd_float32 y, j, g, height;
	};
} istd_vector2_f32, istd_vector2;

typedef struct {
	union {
		istd_float64 x, i, r, width;
	};

	union {
		istd_float64 y, j, g, height;
	};
} istd_vector2_f64;

typedef struct {
	union {
		istd_float64_128 x, i, r, width;
	};

	union {
		istd_float64_128 y, j, g, height;
	};
} istd_vector2_f128;


/**
* Vector3
*/

typedef struct {
	union {
		int32_t x, i, r, width;
	};

	union {
		int32_t y, j, g, height;
	};

	union {
		int32_t z, k, b, depth;
	};
} istd_vector3_i32;

typedef struct {
	union {
		int64_t x, i, r, width;
	};

	union {
		int64_t y, j, g, height;
	};

	union {
		int64_t z, k, b, depth;
	};
} istd_vector3_i64;

typedef struct {
	union {
		istd_float32 x, i, r, width;
	};

	union {
		istd_float32 y, j, g, height;
	};

	union {
		istd_float32 z, k, b, depth;
	};
} istd_vector3_f32, istd_vector3;

typedef struct {
	union {
		istd_float64 x, i, r, width;
	};

	union {
		istd_float64 y, j, g, height;
	};

	union {
		istd_float64 z, k, b, depth;
	};
} istd_vector3_f64;

typedef struct {
	union {
		istd_float64_128 x, i, r, width;
	};

	union {
		istd_float64_128 y, j, g, height;
	};

	union {
		istd_float64_128 z, k, b, depth;
	};
} istd_vector3_f128;

/**
* Vector4
*/

typedef struct {
	union {
		int32_t x, i, r, width;
	};

	union {
		int32_t y, j, g, height;
	};

	union {
		int32_t z, k, b, depth;
	};

	union {
		int32_t w,    a;
	};
} istd_vector4_i32;

typedef struct {
	union {
		int64_t x, i, r, width;
	};

	union {
		int64_t y, j, g, height;
	};

	union {
		int64_t z, k, b, depth;
	};

	union {
		int64_t w,    a;
	};
} istd_vector4_i64;

typedef struct {
	union {
		istd_float32 x, i, r, width;
	};

	union {
		istd_float32 y, j, g, height;
	};

	union {
		istd_float32 z, k, b, depth;
	};	

	union {
		istd_float32 w,	   a;
	};
} istd_vector4_f32, istd_vector4;

typedef struct {
	union {
		istd_float64 x, i, r, width;
	};

	union {
		istd_float64 y, j, g, height;
	};

	union {
		istd_float64 z, k, b, depth;
	};

	union {
		istd_float64 w,    a;
	};
} istd_vector4_f64;

typedef struct {
	union {
		istd_float64_128 x, i, r, width;
	};

	union {
		istd_float64_128 y, j, g, height;
	};

	union {
		istd_float64_128 z, k, b, depth;
	};

	union {
		istd_float64_128 w,    a;
	};
} istd_vector4_f128;

ISTD_END_EXTERN_C

#endif