#include "image_test.h"

#include <image/image.h>
#include <stdio.h>

istd_test_msg test_image(void) {
	istd_test_msg msg = { 0 };

	istd_image image = { 0 };

	istd_image_load("assets/blackbuck.bmp", &image, istd_nullptr);

	FILE* file = fopen("assets/blackbuck.raw", "wb");

	istd_ignore_return(fwrite(image.data, sizeof(uint8_t), image.width * image.height * image.channels, file));

	fclose(file);

	istd_image_free(&image);

	msg.passed = true;

	return msg;
}