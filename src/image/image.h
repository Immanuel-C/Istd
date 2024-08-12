#if !defined(ISTD_IMAGE_H)
#define ISTD_IMAGE_H


#include "core.h"

ISTD_EXTERN_C

/**
* Only supports .bmp images for now
*/

typedef struct {
	uint8_t* data;
	size_t width;
	size_t height;
	size_t channels;
	istd_allocator allocator;
} istd_image;

istd_api istd_result istd_image_load(
	const char* filename, 
	istd_image* image, 
	istd_allocator* allocator
);

istd_api void istd_image_free(
	istd_image* image
);

ISTD_END_EXTERN_C

#endif
