#include <iostream>
#include <fstream>
#include "common.h"
#include "PPMImage.h"
#include "Raytracer.h"
#include "Sphere.h"
#include "Plane.h"
#include "JPEGImage.h"

using namespace std;

const int IMAGE_WIDTH = 1680;
const int IMAGE_HEIGHT = 1050;

template<typename T>
void deleteObject(T* o) {
	delete o;
}

void loadTestScene(Raytracer& r) {
	Primitive* object = new Sphere(vector3_t(15,0,0), 3);
	r.addObject(object);
	object->setMaterial(new Material(color_t(0.5,0.7,0.5), 1, 0, 0));

	object = new Sphere(vector3_t(17,-4.5,4.5), 1.8);
	r.addObject(object);
	object->setMaterial(new Material(color_t(1,0.3,0.3), 0.3, 0.7, 0));

	object = new Sphere(vector3_t(19, 2, -2), 2);
	r.addObject(object);
	object->setMaterial(new Material(color_t(0.3,1,0.3), 1, 0, 0));

	object = new Sphere(vector3_t(13,3,3), 0.1);
	r.addObject(object);
	object->setMaterial(new Material(color_t(1,1,1), 50));

	object = new Plane(vector3_t(0, 0, -5), vector3_t(0, 0, 1));
	r.addObject(object);
	object->setMaterial(new Material(color_t(0.5, 0.5, 0.5), 1, 0, 0));
}

int main(int argc, char** argv) {
	int width = IMAGE_WIDTH, height = IMAGE_HEIGHT;
	if(argc >= 2) {
		// We have a width specified
		width = atoi(argv[1]);
		height = atoi(argv[2]);
		if(width < 0 || height < 0) {
			cerr << "You failed to supply a realistic image size." << endl;
			return 1;
		}
	}
	cout << "Test program started." << endl;
	ofstream f("result.jpeg");
	OutputBitmap* b = new JPEGImage(width, height);
	Raytracer r(b);

	loadTestScene(r);

	r.render();
	
	r.cleanup();

	f << b;

	delete b;

	cout << "Trace finished." << endl;

	return 0;
}
