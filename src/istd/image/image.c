#include "image.h"

#include <stdio.h>
#include <windows.h>

#include "allocator/allocator.h"

typedef enum __istd_image_type_t {
	ISTD_IMAGE_TYPE_BMP,
	ISTD_IMAGE_TYPE_UNKOWN,
} __istd_image_type;

#define ISTD_IMAGE_SIG_BMP 0x4D42 

// https://en.wikipedia.org/wiki/BMP_file_format#DIB_header_(bitmap_information_header) 
typedef enum __istd_bmp_compression_t {
	ISTD_BMP_COMPRESSION_NONE = 0,
	ISTD_BMP_COMPRESSION_RLE8 = 1,
	ISTD_BMP_COMPRESSION_RLE4 = 2,
	ISTD_BMP_COMPRESSION_BITFIELDS = 3,
	ISTD_BMP_COMPRESSION_JPEG = 4,
	ISTD_BMP_COMPRESSION_PNG = 5,
	ISTD_BMP_COMPRESSION_ALPHABITFIELDS = 6,
	ISTD_BMP_COMPRESSION_CMYK = 11,
	ISTD_BMP_COMPRESSION_CMYKRLE8 = 12,
	ISTD_BMP_COMPRESSION_CMYKRLE4 = 13,
} __istd_bmp_compression;

// Must not have padding as per the bmp spec.
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

static __istd_image_type __istd_determine_image_type(
	uint8_t* image_data,
	size_t  image_data_size
) {
	// Read first two bytes
	
	uint16_t sig = (*(uint16_t*)(image_data));
	
	if (sig == ISTD_IMAGE_SIG_BMP)
		return ISTD_IMAGE_TYPE_BMP;

	return ISTD_IMAGE_TYPE_UNKOWN;
}

static istd_result __istd_read_bmp_image(
	istd_image* image,
	uint8_t* bmp_image,
	size_t  image_data_size
) {
	__istd_bmp_header header = { 0 };

	memcpy(&header, bmp_image, sizeof(__istd_bmp_header)); 

	// No compression
	if (header.compression != ISTD_BMP_COMPRESSION_NONE) 
		return ISTD_RESULT_FORMAT_NOT_SUPPORTED;

	uint8_t* bmp_image_data = bmp_image + header.data_offset;

	image->width = (size_t)header.width;
	image->height = (size_t)header.height;
	// divide header.bpp by eight to convert to the number of colour channels
	image->channels = header.bpp / 8;


	if (true) {
		image->data = image->allocator.malloc(image->width * image->height * image->channels);

		if (image->data == istd_nullptr) 
			return ISTD_RESULT_ALLOCATION_FAILED;

		for (size_t i = 0; i < (image->width * image->height * image->channels) / sizeof(uint32_t); i += 1) {
			uint32_t pixel = ((uint32_t*)(bmp_image_data))[i];
			
			// Extract the colour channels. First 9 bits are blue, next 8 are green, next 7 are red, and the last 5 are alpha. The last 3 are padding/unused.
			uint8_t b = (uint8_t)((pixel >> 23) & 0x1FF);
			uint8_t g = (uint8_t)((pixel >> 15) & 0xFF);
			uint8_t r = (uint8_t)((pixel >> 8 ) & 0x7F);
			uint8_t a = (uint8_t)((pixel >> 3 ) & 0x1F);

			image->data[i * sizeof(uint32_t) + 0] = r;
			image->data[i * sizeof(uint32_t) + 1] = g;
			image->data[i * sizeof(uint32_t) + 2] = b;
			image->data[i * sizeof(uint32_t) + 3] = a;
		}
	}

	return ISTD_RESULT_SUCCESS;
}

istd_result istd_image_load(
	const char* filename,
	istd_image* image,
	istd_allocator* allocator
) {
	image->allocator = istd_check_allocator(allocator);

	FILE* file = fopen(filename, "rb");
	
	if (file == istd_nullptr) 
		return ISTD_RESULT_FILE_COULD_NOT_OPEN;

	// This function should never fail
	ISTD_IGNORE_RETURN(fseek(file, 0, SEEK_END));
	
	size_t file_size = (size_t)ftell(file);

	if (file_size == -1) {
		fclose(file);
		return ISTD_RESULT_FILE_TOO_BIG;
	}

	rewind(file);

	size_t image_data_size = file_size * sizeof(uint8_t);
	uint8_t* image_data = (uint8_t*)image->allocator.malloc(image_data_size);

	ISTD_IGNORE_RETURN(fread(image_data, sizeof(uint8_t), file_size, file));

	fclose(file);

	__istd_image_type image_type = __istd_determine_image_type(image_data, image_data_size);

	if (image_type == ISTD_IMAGE_TYPE_UNKOWN) {
		image->allocator.free(image_data);
		return ISTD_RESULT_NOT_FOUND;
	}

	switch (image_type) {
		case ISTD_IMAGE_TYPE_BMP:
			istd_result res = __istd_read_bmp_image(image, image_data, image_data_size);
			image->allocator.free(image_data);
			return res;

		default:
			image->allocator.free(image_data);
			return ISTD_RESULT_NOT_FOUND;
	}

}

void istd_image_free(
	istd_image* image
) {
	image->allocator.free(image->data);
}
