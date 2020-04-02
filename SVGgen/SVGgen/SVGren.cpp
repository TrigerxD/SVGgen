#include "SVGren.h"

void dummy() {
 	auto dom = svgdom::load(papki::FSFile("Results/dummy.svg"));
	auto img = svgren::render(*dom);
	write_bmp("Results/dummy.png", img.width, img.height, &*img.pixels.begin());
}

void write_bmp(const char* filename, int width, int height, std::uint32_t *buffer) {
	FILE *fp = NULL;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;

	// Open file for writing (binary mode)
	fp = fopen(filename, "w+b");
	if (fp == NULL) {
		fprintf(stderr, "Could not open file %s for writing\n", filename);
		std::stringstream ss;
		ss << "could not open file '" << filename << "' for writing";
		throw std::system_error(errno, std::generic_category(), ss.str());
	}

	// Initialize write structure
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		fprintf(stderr, "Could not allocate write struct\n");
		throw std::runtime_error("Could not allocate write struct");
	}

	// Initialize info structure
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fprintf(stderr, "Could not allocate info struct\n");
		throw std::runtime_error("Could not allocate info struct");
	}

	png_init_io(png_ptr, fp);

	// Write header (8 bit colour depth)
	png_set_IHDR(png_ptr, info_ptr, width, height,
		8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);


	png_write_info(png_ptr, info_ptr);

	// Write image data
	int y;
	auto p = buffer;
	for (y = 0; y < height; y++, p += width) {
		png_write_row(png_ptr, reinterpret_cast<png_bytep>(p));
	}

	// End write
	png_write_end(png_ptr, NULL);

	if (fp != NULL) fclose(fp);
	if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
}