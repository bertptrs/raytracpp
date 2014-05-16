#include <algorithm>
#include "PPMImage.h"

using namespace std;

const int PPMImage::CHANNEL_MAX = 255;
const int PPMImage::CHANNELS = 3;

PPMImage::PPMImage(unsigned int width, unsigned int height) : OutputBitmap(width, height) {
	bitmap = new unsigned char[width * height * CHANNELS];
}

PPMImage::~PPMImage() {
	delete[] bitmap;
}

void PPMImage::setPixel(unsigned int x, unsigned int y, const color_t& c) {
	unsigned char r,g,b;
	r = (unsigned char) max(0, min(CHANNEL_MAX, (int) (c.channels.r * CHANNEL_MAX)));
	g = (unsigned char) max(0, min(CHANNEL_MAX, (int) (c.channels.g * CHANNEL_MAX)));
	b = (unsigned char) max(0, min(CHANNEL_MAX, (int) (c.channels.b * CHANNEL_MAX)));
	unsigned char* pixel = getPixelArray(x, y);
	pixel[0] = r;
	pixel[1] = g;
	pixel[2] = b;
}

void PPMImage::getPixel(unsigned int x, unsigned int y, color_t& c) const {
	unsigned char* color = getPixelArray(x, y);
	c.channels.r = double(color[0] / CHANNEL_MAX);
	c.channels.g = double(color[1] / CHANNEL_MAX);
	c.channels.b = double(color[2] / CHANNEL_MAX);
}

color_t PPMImage::getPixel(unsigned int x, unsigned int y) const {
	unsigned char* c = getPixelArray(x, y);
	double r = double(c[0]) / CHANNEL_MAX;
	double g = double(c[1]) / CHANNEL_MAX;
	double b = double(c[2]) / CHANNEL_MAX;
	
	return color_t(r,g,b);
}

void PPMImage::write(ostream& output) const {
   // Write PPM header
	output << "P6\n"
		<< width << " " << height
		<< "\n" << 255 << "\n";
	// Write the PPM bitmap
	output.write((char*) bitmap, width * height * CHANNELS);
}

unsigned char* PPMImage::getPixelArray(unsigned int x, unsigned int y) const
{
	return (unsigned char*) bitmap + (y * width + x) * 3;
}
