#include <algorithm>
#include "PPMImage.h"
#define CHANNEL_MAX 255

using namespace std;

PPMImage::PPMImage(unsigned int width, unsigned int height) : OutputBitmap(width, height) {
	bitmap = new uint32_t*[width];
	for(unsigned int i = 0; i < width; i++) {
		bitmap[i] = new uint32_t[height];
	}
}

PPMImage::~PPMImage() {
	for(unsigned int i = 0; i < width; i++) {
		delete[] bitmap[i];
	}
	delete[] bitmap;
}

void PPMImage::setPixel(unsigned int x, unsigned int y, const color& c) {
	uint32_t r,g,b;
	r = max(0, min(CHANNEL_MAX, (int) (c.channels.r * CHANNEL_MAX)));
	g = max(0, min(CHANNEL_MAX, (int) (c.channels.g * CHANNEL_MAX)));
	b = max(0, min(CHANNEL_MAX, (int) (c.channels.b * CHANNEL_MAX)));
	bitmap[x][y] = (r << 16) | (g << 8) | b;
}

void PPMImage::getPixel(unsigned int x, unsigned int y, color& c) const {
	uint32_t color = bitmap[x][y];
	c.channels.r = ((color >> 16) & 0xff) / CHANNEL_MAX;
	c.channels.g = ((color >> 8) & 0xff) / CHANNEL_MAX;
	c.channels.b = (color & 0xff) / CHANNEL_MAX;
}

color PPMImage::getPixel(unsigned int x, unsigned int y) const {
	uint32_t c = bitmap[x][y];
	double r = ((c >> 16) & 0xff) / CHANNEL_MAX;
	double g = ((c >> 8) & 0xff) / CHANNEL_MAX;
	double b = (c & 0xff) / CHANNEL_MAX;
	
	return color(r,g,b);
}

void PPMImage::write(ostream& output) const {
   // Write PPM header
	output << "P6\n"
		<< width << " " << height
		<< "\n" << 255 << "\n";
	// Write the PPM bitmap
	uint32_t c;
	for(unsigned int y = 0; y < height; y++) {
		for(unsigned int x = 0; x < width; x++) {
			c = bitmap[x][y];
			char r = (c >> 16) & 0xff;
			char g = (c >> 8) & 0xff;
			char b = c & 0xff;
			output.put(r);
			output.put(g);
			output.put(b);
		}
	}
}
