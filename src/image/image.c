#include "image.h"

#include <stdio.h>
#include <windows.h>

#include "allocator/allocator.h"

#include "safe/string_safe.h"

typedef enum {
	ISTD_IMAGE_TYPE_BMP,
	ISTD_IMAGE_TYPE_UNKOWN,
} __istd_image_type;

typedef enum {
	ISTD_IMAGE_SIG_BMP = 0x4D42
} __istd_image_signature;

// Must not have padding as per the bmp spec.
istd_packed_struct
typedef struct {
	// Normal header
	uint16_t signature;			// File type
	uint32_t size;				// File size in bytes
	uint16_t reserved1;			// reserved
	uint16_t reserved2;			// reserved
	uint32_t data_offset;		// offset to image data

	// DIB Header
	uint32_t dib_header_size;	// DIB Header size in bytes
	uint32_t width;				// Width of the image
	uint32_t height;			// Height of the image
	uint16_t planes;			// Number of colour planes
	uint16_t bpp;				// Bits per pixel
	uint32_t compression;		// compression type
	uint32_t image_size;		// Image size in bytes
	int32_t x_resolution;		// Pixels per meter on the x axis
	int32_t y_resolution;		// Pixels per meter on the y axis
	uint32_t num_colours;		// Number of colours
	uint32_t important_colours;	// Important colours
} __istd_bmp_header;
istd_packed_struct_end

static __istd_image_type __istd_determine_image_type(
	uint8_t* image_data,
	size_t  image_data_size
) {
	// Read first two bytes
	if ((*(uint16_t*)(image_data)) == ISTD_IMAGE_SIG_BMP)
		return ISTD_IMAGE_TYPE_BMP;

	return ISTD_IMAGE_TYPE_UNKOWN;
}

static istd_result __istd_read_bmp_image(
	istd_image* image,
	uint8_t* image_data,
	size_t  image_data_size
) {
	__istd_bmp_header header = { 0 };

	if (istd_memcpy_safe(&header, sizeof(__istd_bmp_header), image_data, sizeof(__istd_bmp_header)) != ISTD_ENONE)
		return ISTD_RESULT_MEM_OP_FAILED;

	// No compression
	if (header.compression != 0) 
		return ISTD_RESULT_FORMAT_NOT_SUPPORTED;

	uint8_t* bmp_image_data = image_data + header.data_offset;
	// divide header.bpp by eight to convert to the number of colour channels
	size_t bytes_per_pixel = header.bpp / 8;
	size_t bmp_image_data_size = (size_t)(((header.width * header.height) * bytes_per_pixel) * sizeof(uint8_t));

	image->data = image->allocator.malloc(bmp_image_data_size);

	if (image->data == istd_nullptr) 
		return ISTD_RESULT_ALLOCATION_FAILED;

	for (size_t y = 0; y < header.height; y++) {
		for (size_t x = 0; x < header.width; x += bytes_per_pixel) {
			// RGB format		     BGR format
			image->data[y * x + 2] = bmp_image_data[y * x + 0];
			image->data[y * x + 1] = bmp_image_data[y * x + 1];
			image->data[y * x + 0] = bmp_image_data[y * x + 2];
		}
	}

	image->width = (size_t)header.width;
	image->height = (size_t)header.height;
	image->channels = bytes_per_pixel;

	return ISTD_RESULT_SUCCESS;
}

istd_result istd_image_load(
	const char* filename,
	istd_image* image,
	istd_allocator* allocator
) {
	istd_allocator* alloc = allocator;

	if (alloc == istd_nullptr)
		alloc = istd_get_defualt_allocator();

	image->allocator = *alloc;

	FILE* file = fopen(filename, "rb");
	
	if (file == istd_nullptr) 
		return ISTD_RESULT_FILE_COULD_NOT_OPEN;

	// This function should never fail
	istd_ignore_return(fseek(file, 0, SEEK_END));
	
	size_t file_size = (size_t)ftell(file);

	if (file_size == -1) {
		fclose(file);
		return ISTD_RESULT_FILE_TOO_BIG;
	}

	rewind(file);

	size_t image_data_size = file_size * sizeof(uint8_t);
	uint8_t* image_data = (uint8_t*)alloc->malloc(image_data_size);

	istd_ignore_return(fread(image_data, sizeof(uint8_t), file_size, file));

	fclose(file);

	__istd_image_type image_type = __istd_determine_image_type(image_data, image_data_size);

	if (image_type == ISTD_IMAGE_TYPE_UNKOWN) {
		alloc->free(image_data);
		return ISTD_RESULT_NOT_FOUND;
	}

	switch (image_type) {
		case ISTD_IMAGE_TYPE_BMP:
			istd_result res = __istd_read_bmp_image(image, image_data, image_data_size);
			alloc->free(image_data);
			return res;

		default:
			alloc->free(image_data);
			return ISTD_RESULT_NOT_FOUND;
	}

}

void istd_image_free(
	istd_image* image
) {
	image->allocator.free(image->data);
}
