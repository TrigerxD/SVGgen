#include <svgren/render.hpp>
#include <papki/FSFile.hpp> // we will need this to load the SVG file

#include <utki/debug.hpp>
#include <utki/config.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <png.h>
void dummy();
void write_png(const char* filename, int width, int height, std::uint32_t *buffer);