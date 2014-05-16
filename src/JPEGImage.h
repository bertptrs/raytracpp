#ifndef JPEGIMAGE_H
#define JPEGIMAGE_H
#include "OutputBitmap.h"
#include <vector>

class JPEGImage : public OutputBitmap {

	public:
		JPEGImage(unsigned int, unsigned int);
		virtual void write(ostream&) const;
};

#endif
