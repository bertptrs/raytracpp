#include "JPEGImage.h"
#include <jpeglib.h>
#include <cstring>

using namespace std;

JPEGImage::JPEGImage(unsigned int width, unsigned int height) :
	OutputBitmap(width, height)
{
}

void JPEGImage::write(ostream& output) const
{
	jpeg_compress_struct cinfo;
	jpeg_error_mgr jerr;
	unsigned char * mem = NULL;
	unsigned long memSize = 0;
	unsigned int rowSize = width * 3;
	JSAMPROW rowPointer = new unsigned char[rowSize];

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	cinfo.image_width = width;
	cinfo.image_height = height;
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_RGB;

	jpeg_set_defaults(&cinfo);
	jpeg_mem_dest(&cinfo, &mem, &memSize);
	jpeg_set_quality(&cinfo, 100, true);

	jpeg_start_compress(&cinfo, true);

	while (cinfo.next_scanline < cinfo.image_height) {
		memcpy(rowPointer, &bitmap[cinfo.next_scanline * rowSize], rowSize);
		jpeg_write_scanlines(&cinfo, &rowPointer, 1);
	}

	jpeg_finish_compress(&cinfo);


	output.write((char*) mem, memSize);

	delete[] rowPointer;
	jpeg_destroy_compress(&cinfo);
	free(mem);
}
