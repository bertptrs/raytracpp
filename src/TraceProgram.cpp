#include "TraceProgram.h"
#include <iostream>
#include <cstring>
#include "JPEGImage.h"
#include "PPMImage.h"
#include "Sphere.h"
#include "Plane.h"
#include "fstream"

const unsigned int TraceProgram::DEFAULT_HEIGHT = 400;
const unsigned int TraceProgram::DEFAULT_WIDTH = 400;

TraceProgram::TraceProgram()
	: width(DEFAULT_WIDTH), height(DEFAULT_HEIGHT), debug(false), tracer(nullptr), canvas(nullptr)
{
	filename = "out.jpeg";
}

TraceProgram::~TraceProgram()
{
}

void TraceProgram::parseArguments(int argc, char** argv)
{
	for (int i = 1; i < argc; i++)
	{
		if ((strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--width") == 0) && argc - i > 1)
		{
			i++;
			width = atoi(argv[i]);
			continue;
		}

		if ((strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--height") == 0) && argc - i > 1)
		{
			i++;
			height = atoi(argv[i]);
			continue;
		}

		if ((strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) && argc - i > 1)
		{
			i++;
			filename = string(argv[i]);
			continue;
		}

		if ((strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0))
		{
			debug = true;
			continue;
		}

		cerr << "Unreckognized command option: " << argv[i] << endl;
	}
}

bool TraceProgram::init()
{
	if (!initCanvas())
		return false;

	tracer = make_shared<Raytracer>(canvas);

	loadTestScene();

	return true;
}

void TraceProgram::trace()
{
	if (debug)
	{
		cout << "Drawing debug image." << endl;
		canvas->drawTestImage();
		return;
	} else {
		tracer->render();
	}

}

bool TraceProgram::initCanvas()
{
	if (hasEnding(filename, ".ppm"))
	{
		canvas = make_shared<PPMImage>(width, height);
		return true;
	}
	if (hasEnding(filename, ".jpg") || hasEnding(filename, ".jpeg"))
	{
		canvas = make_shared<JPEGImage>(width, height);
		return true;
	}

	cerr << "Unknown image type: " << filename << endl;
	return false;
}

bool TraceProgram::hasEnding(string haystack, string needle)
{
	if (haystack.length() >= needle.length())
	{
		return haystack.compare(haystack.length() - needle.length(), needle.length(), needle) == 0;
	} else {
		return false;
	}
}

void TraceProgram::loadTestScene() {
	shared_ptr<Primitive> object = make_shared<Sphere>(vector3_t(15,0,0), 3);
	tracer->addObject(object);
	object->setMaterial(make_shared<Material>(color_t(0.5,0.7,0.5), 1, 0, 0));

	auto lightMaterial = make_shared<Material>(color_t(1,1,1), 30);

	object = make_shared<Sphere>(vector3_t(17,-4.5,4.5), 1.8);
	tracer->addObject(object);
	object->setMaterial(make_shared<Material>(color_t(1,0.3,0.3), 0.3, 0.7, 0));

	object = make_shared<Sphere>(vector3_t(19, 2, -2), 2);
	tracer->addObject(object);
	object->setMaterial(make_shared<Material>(color_t(0.3,1,0.3), 1, 0, 0));

	object = make_shared<Sphere>(vector3_t(13,3,3), 0.5);
	tracer->addObject(object);
	object->setMaterial(lightMaterial);

	object = make_shared<Sphere>(vector3_t(13,0,8), 1);
	tracer->addObject(object);
	object->setMaterial(lightMaterial);

	object = make_shared<Plane>(vector3_t(0, 0, -5), vector3_t(0, 0, 1));
	tracer->addObject(object);
	object->setMaterial(make_shared<Material>(color_t(0.5, 0.5, 0.5), 1, 0, 0));
}

bool TraceProgram::write()
{
	ofstream output(filename.c_str());
	if (!output.good())
	{
		cerr << "Cannot write to file" << filename << endl;
		output.close();
		return false;
	} else {
		output << canvas;
		output.close();
		return true;
	}
}
