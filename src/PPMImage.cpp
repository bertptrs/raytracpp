#include "PPMImage.h"

using namespace std;

PPMImage::PPMImage(unsigned int width, unsigned int height) : OutputBitmap(width, height) {
}

void PPMImage::write(ostream& output) const {
   // Write PPM header
	output << "P6\n"
		<< width << " " << height
		<< "\n" << 255 << "\n";
	// Write the PPM bitmap
	output.write((char*) bitmap, width * height * CHANNELS);
}

