#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <list>
#include "common.h"
#include "OutputBitmap.h"
#include "Primitive.h"

using namespace std;

typedef enum {
	OK,
	INVALID_CAMERA
} renderresult_t;

class Raytracer {
	private:
		OutputBitmap* const bitmap;
		plist_t scene;
		ray_t camera;
		static const vector3_t UP;
		color_t BACKGROUND;

		vector3_t xDir, yDir;
		double scale;

		void initScreen();
		color_t getPixel(double sX, double sY);

		Primitive* trace(const ray_t& ray, vector3_t& hit, vector3_t& normal, color_t& color_t);


	public:
		Raytracer(OutputBitmap* bm);
		
		void addObject(Primitive* object);
		void removeObject(Primitive* object);
		ray_t getCamera();

		renderresult_t render();

		void cleanup();
};

#endif
