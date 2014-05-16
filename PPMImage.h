#ifndef PPMIMAGE_H
#define PPMIMAGE_H

#include "OutputBitmap.h"
#include "stdint.h"

class PPMImage : public OutputBitmap {
	protected:
		unsigned char* bitmap;

		static const int CHANNEL_MAX;
		static const int CHANNELS;

		unsigned char* getPixelArray(unsigned int x, unsigned int y) const;

	public:
		PPMImage(unsigned int width, unsigned int height);
		~PPMImage();

		void setPixel(unsigned int x, unsigned int y, const color_t& c);
		void getPixel(unsigned int x, unsigned int y, color_t& c) const;
		color_t getPixel(unsigned int x, unsigned int y) const;
		virtual void write(ostream& output) const;

};

#endif
