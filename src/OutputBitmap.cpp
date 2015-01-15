#include "OutputBitmap.h"
#include <algorithm>
#include <limits>

using namespace std;

const int OutputBitmap::CHANNEL_MAX = numeric_limits<unsigned char>::max();
const int OutputBitmap::CHANNELS = 3;

OutputBitmap::OutputBitmap(unsigned int width, unsigned int height)
	: width(width), height(height)
{
	bitmap = vector<unsigned char>(width * height * CHANNELS);
}

OutputBitmap::~OutputBitmap()
{
}

ostream& operator << (ostream& output, OutputBitmap* bitmap) {
	bitmap->write(output);
	return output;
}

void OutputBitmap::setPixel(unsigned int x, unsigned int y, const color_t& c) {
	unsigned char r,g,b;
	r = (unsigned char) max(0, min(CHANNEL_MAX, (int) (c.channels.r * CHANNEL_MAX)));
	g = (unsigned char) max(0, min(CHANNEL_MAX, (int) (c.channels.g * CHANNEL_MAX)));
	b = (unsigned char) max(0, min(CHANNEL_MAX, (int) (c.channels.b * CHANNEL_MAX)));
	unsigned char* pixel = getPixelArray(x, y);
	pixel[0] = r;
	pixel[1] = g;
	pixel[2] = b;
}

void OutputBitmap::getPixel(unsigned int x, unsigned int y, color_t& c) const {
	auto color = getPixelArray(x, y);
	c.channels.r = double(color[0] / CHANNEL_MAX);
	c.channels.g = double(color[1] / CHANNEL_MAX);
	c.channels.b = double(color[2] / CHANNEL_MAX);
}

color_t OutputBitmap::getPixel(unsigned int x, unsigned int y) const {
	auto c = getPixelArray(x, y);
	double r = double(c[0]) / CHANNEL_MAX;
	double g = double(c[1]) / CHANNEL_MAX;
	double b = double(c[2]) / CHANNEL_MAX;
	
	return color_t(r,g,b);
}

const unsigned char* OutputBitmap::getPixelArray(unsigned int x, unsigned int y) const
{
	return &bitmap[(y * width + x) * 3];
}

unsigned char* OutputBitmap::getPixelArray(unsigned int x, unsigned int y)
{
	return &bitmap[(y * width + x) * 3];
}

void OutputBitmap::drawTestImage()
{
	color_t c(1,0,0);
	for(unsigned int x = 0; x < width / 2; x++) {
		for(unsigned int y = 0; y < height / 2; y++) {
			setPixel(x,y,c);
		}
	}
	c = color_t(0,1,0);
	for(unsigned int x = width / 2; x < width; x++) {
		for(unsigned int y = 0; y < height / 2; y++) {
			setPixel(x,y,c);
		}
	}
	c = color_t(0,0,1);
	for(unsigned int x = 0; x < width / 2; x++) {
		for(unsigned int y = height / 2; y < height; y++) {
			setPixel(x,y,c);
		}
	}
}
