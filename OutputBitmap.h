#ifndef OUTPUTBITMAP_H
#define OUTPUTBITMAP_H

#include <iostream>
#include "common.h"

using std::ostream;

class OutputBitmap {
	protected:
		unsigned int width, height;
		OutputBitmap(unsigned int width, unsigned int height) : width(width), height(height) {};

	public:
		virtual ~OutputBitmap() {};
		unsigned int getWidth() const { return width; };
		unsigned int getHeight() const { return height; };

		virtual void setPixel(unsigned int x, unsigned int y, const color_t& c) = 0;
		virtual void getPixel(unsigned int x, unsigned int y, color_t& c) const = 0;
		virtual color_t getPixel(unsigned int x, unsigned int y) const = 0;

		virtual void write(ostream& output) const = 0;
};

ostream& operator << (ostream& output, OutputBitmap* bitmap);

#endif
