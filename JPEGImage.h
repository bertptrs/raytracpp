#ifndef JPEGIMAGE_H
#define JPEGIMAGE_H
#include "PPMImage.h"
#include <vector>

class JPEGImage : public PPMImage {

	public:
		JPEGImage(unsigned int, unsigned int);
		virtual void write(ostream&) const;
};

#endif
