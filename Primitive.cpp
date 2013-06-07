#include "Primitive.h"

double Primitive::doIntersect(const ray_t& ray, vector3& hit, vector3& normal) {
	// Future compatible, possible translation of objects.
	return this->intersect(ray, hit, normal);
}
