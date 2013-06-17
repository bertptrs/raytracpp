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
		list<Primitive*> scene;
		ray_t camera;
		static const vector3 UP;

		vector3 xDir, yDir;
		double scale;

		void initScreen();
		color getPixel(double sX, double sY);

		Primitive* trace(const ray_t& ray, vector3& hit, vector3& normal, color& color);

	public:
		Raytracer(OutputBitmap* bm);
		
		void addObject(Primitive* object);
		void removeObject(Primitive* object);

		renderresult_t render();
};

#endif
