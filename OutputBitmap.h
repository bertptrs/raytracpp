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
		unsigned int getWidth() const { return width; };
		unsigned int getHeight() const { return height; };

		void setPixel(unsigned int x, unsigned int y, const color& c) = 0;
		void getPixel(unsigned int x, unsigned int y, color& c) = 0;
		color getPixel(unsigned int x, unsigned int y) = 0;

		void commit() = 0;

		void write(ostream& output) = 0;
};

operator << (ofstream& output, OutputBitmap bitmap) {
	bitmap.write(output);
}
