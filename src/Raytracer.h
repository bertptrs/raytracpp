#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <list>
#include "common.h"
#include "OutputBitmap.h"
#include "Primitive.h"
#include <memory>

using namespace std;

typedef enum {
	OK,
	INVALID_CAMERA
} renderresult_t;

class Raytracer {
	private:
		static const int DEFAULT_DEPTH = 6;
		const shared_ptr<OutputBitmap> bitmap;
		plist_t scene;
		plist_t lights;
		ray_t camera;
		static const vector3_t UP;
		color_t BACKGROUND;
		int depth;

		vector3_t xDir, yDir;
		double scale;

		void initScreen();
		color_t getPixel(double sX, double sY);
		void initLights();

		shared_ptr<Primitive> trace(const ray_t& ray, vector3_t& hit, vector3_t& normal, color_t& color_t);
		shared_ptr<Primitive> getNearest(const ray_t& ray) const;
		inline color_t getDiffusion(const vector3_t& pos, const vector3_t& normal, const color_t& color);
		inline color_t getReflection(const vector3_t& pos, const vector3_t& normal, const vector3_t& inAngle, const color_t& color);
		inline color_t getRefraction(const vector3_t& pos, const vector3_t& normal, const vector3_t& inAngle, const color_t& color);



	public:
		Raytracer(shared_ptr<OutputBitmap> bitmap);
		
		void addObject(Primitive* object);
		void addObject(shared_ptr<Primitive> object);
		ray_t getCamera();

		renderresult_t render();
};

#endif
