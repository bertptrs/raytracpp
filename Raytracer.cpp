#include "Raytracer.h"

const vector3 Raytracer::UP = vector3(0,0,1);

Raytracer::Raytracer(OutputBitmap* bm) :
	bitmap(bm)
{
	camera.origin = vector3(0,0,0);
	camera.direction = vector3(1,0,0);
}

void Raytracer::addObject(Primitive* object) {
	scene.push_back(object);
}

void Raytracer::removeObject(Primitive* object) {
	scene.remove(object);
}

renderresult_t Raytracer::render() {
	int width = bitmap->getWidth(), height = bitmap->getHeight();
	initScreen();

	if(xDir.squareLength() == 0 || yDir.squareLength() == 0)
		return INVALID_CAMERA;

	int x,y;
	double sX, sY;
	for(x = 0; x < width; x++) {
		sX = (double) (x - (width / 2)) / width;
		for(y = 0; y < height; y++) {
			sY = (double) (y - (height / 2)) / height;
			color pixel = getPixel(sX, sY);
			bitmap->setPixel(x, y, pixel);
		}
	}
	return OK;
}

void Raytracer::initScreen() {
	xDir = camera.direction.cross(UP);
	yDir = camera.direction.cross(xDir);
	scale = (double) bitmap->getWidth();
	scale /= bitmap->getHeight();
}

color Raytracer::getPixel(double sX, double sY) {
	ray_t ray = camera;
	ray.direction += xDir * sX;
	ray.direction += yDir * sY;

	color retColor;
	vector3 hit, normal;

	trace(ray, hit, normal, retColor);

	return retColor;
}

Primitive* Raytracer::trace(const ray_t& ray, vector3& hit, vector3& normal, color& color) {
	// FIXME: dummy
	return NULL;
}
