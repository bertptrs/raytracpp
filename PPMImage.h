#ifndef PPMIMAGE_H
#define PPMIMAGE_H

#include "OutputBitmap.h"

class PPMImage : public OutputBitmap {

	public:
		PPMImage(unsigned int width, unsigned int height);

		virtual void write(ostream& output) const;

};

#endif
