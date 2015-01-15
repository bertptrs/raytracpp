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
	for (unsigned int y = 0; y < height; y++) {
		for (unsigned int x = 0; x < width; x++) {
			const unsigned char* pixel = getPixelArray(x, y);
			for (int i = 0; i < CHANNELS; i++) {
				output << pixel[i];
			}
		}
	}
	output.write((char*) &bitmap, width * height * CHANNELS);
}

