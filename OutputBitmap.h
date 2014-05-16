#ifndef OUTPUTBITMAP_H
#define OUTPUTBITMAP_H

#include <iostream>
#include "common.h"

using std::ostream;

class OutputBitmap {
	protected:
		unsigned char* bitmap;

		static const int CHANNEL_MAX;
		static const int CHANNELS;

		OutputBitmap(unsigned int width, unsigned int height);
		unsigned char* getPixelArray(unsigned int x, unsigned int y) const;

	public:
		const unsigned int width;
		const unsigned int height;

		virtual ~OutputBitmap();
		unsigned int getWidth() const { return width; };
		unsigned int getHeight() const { return height; };

		void setPixel(unsigned int x, unsigned int y, const color_t& c);
		void getPixel(unsigned int x, unsigned int y, color_t& c) const;
		color_t getPixel(unsigned int x, unsigned int y) const;

		virtual void write(ostream& output) const = 0;

		void drawTestImage();
};

ostream& operator << (ostream& output, OutputBitmap* bitmap);

#endif
