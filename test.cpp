#include <iostream>
#include <fstream>
#include "common.h"
#include "PPMImage.h"
#include "Raytracer.h"
#include "Sphere.h"

using namespace std;

const int IMAGE_WIDTH = 800;
const int IMAGE_HEIGHT = 600;

template<typename T>
void deleteObject(T* o) {
	delete o;
}

void drawTestImage(OutputBitmap* b) {
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
}


void loadTestScene(Raytracer& r) {
	Primitive* object = new Sphere(vector3_t(15,0,0), 3);
	r.addObject(object);
	object->setMaterial(new Material(color_t(0.5,0.7,0.5), 1, 0, 0));

	object = new Sphere(vector3_t(17,-4.5,4.5), 1.8);
	r.addObject(object);
	object->setMaterial(new Material(color_t(1,0.3,0.3), 1, 0, 0));

	object = new Sphere(vector3_t(19, 2, -2), 2);
	r.addObject(object);
	object->setMaterial(new Material(color_t(0.3,1,0.3), 1, 0, 0));

	object = new Sphere(vector3_t(13,3,3), 0.1);
	r.addObject(object);
	object->setMaterial(new Material(color_t(1,1,1), 50));
}

int main() {
	cout << "Test program started." << endl;
	ofstream f("result.ppm");
	OutputBitmap* b = new PPMImage(IMAGE_WIDTH, IMAGE_HEIGHT);
	Raytracer r(b);

	loadTestScene(r);

	r.render();
	
	r.cleanup();

	f << b;

	delete b;

	cout << "Trace finished." << endl;

	return 0;
}
