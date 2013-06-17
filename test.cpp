#include <iostream>
#include <fstream>
#include "common.h"
#include "PPMImage.h"

using namespace std;

const int IMAGE_WIDTH = 480;
const int IMAGE_HEIGHT = 360;

int main() {
	cout << "Test program started." << endl;
	ofstream f("result.ppm");
	OutputBitmap* b = new PPMImage(IMAGE_WIDTH, IMAGE_HEIGHT);
	color_t c(1,0,0);
	for(int x = 0; x < IMAGE_WIDTH / 2; x++) {
		for(int y = 0; y < IMAGE_HEIGHT / 2; y++) {
			b->setPixel(x,y,c);
		}
	}
	c = color_t(0,1,0);
	for(int x = IMAGE_WIDTH / 2; x < IMAGE_WIDTH; x++) {
		for(int y = 0; y < IMAGE_HEIGHT / 2; y++) {
			b->setPixel(x,y,c);
		}
	}
	c = color_t(0,0,1);
	for(int x = 0; x < IMAGE_WIDTH / 2; x++) {
		for(int y = IMAGE_HEIGHT / 2; y < IMAGE_HEIGHT; y++) {
			b->setPixel(x,y,c);
		}
	}

	f << b;

	f.close();

	delete b;

	return 0;
}
