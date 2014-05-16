#include <iostream>
#include <fstream>
#include "common.h"
#include "PPMImage.h"
#include "Raytracer.h"
#include "Sphere.h"
#include "Plane.h"
#include "JPEGImage.h"
#include "TraceProgram.h"

using namespace std;

const int IMAGE_WIDTH = 1680;
const int IMAGE_HEIGHT = 1050;

int main(int argc, char** argv) {
	TraceProgram program;

	program.parseArguments(argc, argv);

	program.init();

	program.trace();

	program.write();

	return 0;
}
