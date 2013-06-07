#ifndef PPMIMAGE_H
#define PPMIMAGE_H

#include "OutputBitmap.h"
#include <cstdint>

class PPMImage : public OutputBitmap {
	private:
		uint32_t** bitmap;
	public:
		PPMImage(unsigned int width, unsigned int height);
		~PPMImage();

		void setPixel(unsigned int x, unsigned int y, const color& c);
		void getPixel(unsigned int x, unsigned int y, color& c) const;
		color getPixel(unsigned int x, unsigned int y) const;
		virtual void write(ostream& output) const;

};

#endif
